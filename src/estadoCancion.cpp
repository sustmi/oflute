#include "estadoCancion.h"

#include "log.h"
#include "marcadorPuntos.h"

#include <pugixml.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>

#include <algorithm>


Cancion::Cancion(Gosu::Graphics & g, string ruta) : g(g), ruta(ruta) {
    lDEBUG << Log::CON("EstadoCanción") << " (" << ruta << ")";

    // Inicialmente la canción no está lanzada
    lanzado = false;

    // Tampoco se están capturando puntos
    capturandoPuntos = false;

    // El incremento de puntos cada vez, puede ser 1
    incrementoDePuntos = 1;

    // Seteamos el estado inicial como el primero
    estadoActual = e1;

    // Reiniciamos el contador de puntos
    puntos = 0;

}

void Cancion::lanzar(){
    distanciaPulso = 250;
    margenIzquierdo = 150;

    esperaInicial = 5; // 3 tiempos

    resalteNotaActual.reset( new Gosu::Image(g, L"media/secCanciones/cancionesIndicadorNota.png"));

    barraProgresoFondo.reset( new ElementoImagen(g, "media/secCanciones/cancionesBarraProgreso.png",
                                                 3, Animacion::tAlpha));
    barraProgresoFondo -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 30);
    barraProgresoFondo -> animacion -> set(0,0,255);
    barraProgresoFondo -> setXY(180, 560);

    barraProgreso.reset(new Gosu::Image(g, L"media/secCanciones/cancionesBarraRelleno.png"));

    imagenPartitura.reset( new ElementoImagen(g, "media/secCanciones/partitura.png", 
                                              3, Animacion::tAlpha));
    imagenPartitura -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 20);
    imagenPartitura -> animacion -> set (0, 0, 255);
    imagenPartitura -> setXY(0, 200);


    barraSuperior.reset(new ElementoCombinado(g, Animacion::tPos, 3));
    barraSuperior -> setImagen("media/secCanciones/cancionesTopBar.png");
    barraSuperior -> setTexto("00000", "media/fNormal.ttf",
                              49, 0xffffffff,
                              Texto::alignCentro,
                              true, 33,
                              0, 0);
    
    barraSuperior -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 0);
    barraSuperior -> animacion -> set(0,0,0);
    barraSuperior -> animacion -> set(1, -139, 0);


    barraInferior.reset(new ElementoCombinado(g, Animacion::tPos, 3));
    barraInferior -> setImagen("media/secCanciones/cancionesBottomBar.png");
    barraInferior -> setTexto("Progreso total:", "media/fNormal.ttf",
                              32, 0xffffffff,
                              Texto::alignIzq,
                              true, 39,
                              20, 90);

    barraInferior -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 10);
    barraInferior -> animacion -> set(0,0,0);
    barraInferior -> animacion -> set(1, 600, 461); //*/

    sistemaPartc . reset(new SistemaParticulas(g, 150, 150, // cantidad y duración
                                               80, 0.5,  // distancia y escala
                                               Gosu::Color(255,255,255)));

    Nota::initImagenes(g);
    parsear ();
}

void Cancion::parsear(){
    pugi::xml_document documento;
    pugi::xml_parse_result resultado;
    pugi::xml_node nodoActual, nodoVacio;

    resultado = documento.load_file(ruta.c_str());
    if(!resultado){
        lERROR << "ERROR";
    }

    tituloCancion = documento.child("Song").child("Title").first_child().value();
    descripcionCancion =  documento.child("Song").child("Desc").first_child().value();;
    bpm = boost::lexical_cast<int>(documento.child("Song").child("BPM").first_child().value());

    string cadenaNotas = documento.child("Song").child("Notes").first_child().value();

    // Expresión regular para cazar las notas
    boost::regex myRegExp("(do|re|mi|fa|sol|la|si|xx)(5|6|0)(r|b|n|c)(p)?");

    // Iterador de regexp para iterar por las diferentes notas captadas
    boost::sregex_iterator myIt(cadenaNotas.begin(), cadenaNotas.end(), myRegExp), itEnd;

    float acumulado = 0;


    for(;myIt != itEnd; myIt++){
        bool puntillo = ((*myIt)[4] == "p");
        string figura = (*myIt)[3];
        string alturaRead = string((*myIt)[1]) + string((*myIt)[2]);

        t_altura alturaLocal = Do5;
        t_figura figuraLocal = (t_figura) Negra | Puntillo;
        float duracionLocal = 0;

        if(alturaRead == "do5") alturaLocal = Do5;
        else if(alturaRead == "re5") alturaLocal = Re5;
        else if(alturaRead == "mi5") alturaLocal = Mi5;
        else if(alturaRead == "fa5") alturaLocal = Fa5;
        else if(alturaRead == "sol5") alturaLocal = Sol5;
        else if(alturaRead == "la5") alturaLocal = La5;
        else if(alturaRead == "si5") alturaLocal = Si5;
        else if(alturaRead == "do6") alturaLocal = Do6;
        else if(alturaRead == "re6") alturaLocal = Re6;
        else if(alturaRead == "xx0") alturaLocal = Silencio;

        if(figura == "r"){
            figuraLocal = Redonda;
            duracionLocal = 4;
        }

        else if(figura == "b"){
            figuraLocal = Blanca;
            duracionLocal = 2;
        }

        else if(figura == "n"){
            figuraLocal = Negra;
            duracionLocal = 1;
        }

        else if(figura == "c"){
            figuraLocal = Corchea;
            duracionLocal = 0.5;
        }

        if(puntillo){
            duracionLocal += duracionLocal / 2;
            figuraLocal = figuraLocal | Puntillo;
        }

        conjNotas.push_back(boost::shared_ptr<Nota>(new Nota(g, alturaLocal, 
                                                             figuraLocal, acumulado)));
        acumulado += duracionLocal;

    }

    conjNotas.push_back(boost::shared_ptr<Nota>(new NotaFinal(g, acumulado)));

    numeroInicialNotas = conjNotas.size();

    lDEBUG << "BPM: " << bpm;
    milisegundosPorPulso = 1 / (bpm / 60.) * 1000;
    lDEBUG << "El espacio entre pulsos es " << milisegundosPorPulso << " ms";


    lDEBUG << "El intervalo de refresco es " << REFRESCO << " ms";
    // frecuencia = 1000./REFRESCO;
    // lDEBUG << "La frecuencia es de " << frecuencia << " Hz, es decir, salen " << frecuencia
	//    << " fotogramas por segundo.";

    lDEBUG << "La distancia de un pulso (espacio entre dos negras) es " << distanciaPulso << " px";
    lDEBUG << "Con " << bpm << " pulsos por minuto, se recorren " 
           << distanciaPulso * bpm << " píxeles por minuto, ó " 
           << distanciaPulso * bpm / 60. << " píxeles por segundo.";

    duracionCancion = acumulado * milisegundosPorPulso;
    maximoPuntos = incrementoDePuntos * (duracionCancion / REFRESCO);

    lDEBUG << "El total de tiempos de la canción es de " << acumulado << " pulsos.";
    lDEBUG << "El tiempo de la canción será de: " << duracionCancion << " ms";
    lDEBUG << "En cada lectura, se añadirán " << incrementoDePuntos << " puntos.";
    lDEBUG << "Máximo de puntos: " << maximoPuntos;

}

void Cancion::update(){
    if(estadoActual == e1){
        if(barraSuperior -> animacion -> finished() &&
           barraInferior -> animacion -> finished() &&
           imagenPartitura -> animacion -> finished() &&
           barraProgresoFondo -> animacion -> finished() )
        {
            lDEBUG << "Animaciones de interfaz terminadas.";
            estadoActual = e2;

            analizador.iniciar();

        }
    }else if (estadoActual == e2){
        notaLeida = analizador . notaActual();
        if(!lanzado){
            temporizador.restart();
            lanzado = true;
        }else{
            sistemaPartc -> update();

            double transcurrido = temporizador.elapsed();
            double pulsosTranscurridos = transcurrido / milisegundosPorPulso;

            float estaNota, posHorizontal;

            vector<boost::shared_ptr<Nota> >::iterator iteradorNota;

            for(iteradorNota = conjNotas.begin();
                iteradorNota != conjNotas.end();
                ){

                estaNota = (*iteradorNota) -> tiemposDelante;
		
                posHorizontal = (estaNota + esperaInicial - pulsosTranscurridos) * distanciaPulso;

                /*
                  Para ver qué nota corresponde en cada momento,
                  hacemos el siguiente cálculo.  MargenIzquierdo es el
                  punto en el que se empieza a tocar la nota. Así,
                  para que una nota sea la que debe tocarse en ese
                  momento, debe estar a la izquierda del margen,
                  y su punto final (es decir, el punto inicial +
                  duración) debe estar a la derecha del margen (ya que
                  si está a la izquierda es que ya ha acabado su
                  tiempo.


                */
                if(posHorizontal <= margenIzquierdo
                   &&
                   margenIzquierdo < (posHorizontal + Nota::devolverDuracion((*iteradorNota) -> figura) * distanciaPulso) ){
                    notaEnLinea = (*iteradorNota) -> altura;

                    if(!capturandoPuntos){
                        capturandoPuntos = true;
                        lDEBUG << "CAPTURANDO PUNTOS";
                        t2.restart();
                    }
                }

                (*iteradorNota) -> updatePos(posHorizontal);		

                if(posHorizontal < -25 &&
                   margenIzquierdo > (posHorizontal + Nota::devolverDuracion((*iteradorNota) -> figura) * distanciaPulso) - 50){
                    // Nota fuera del pentagrama
                    iteradorNota = conjNotas.erase(iteradorNota);

                    if(conjNotas.end() == iteradorNota + 1){
                        capturandoPuntos = false;
                        t2.pause();
                        lDEBUG << "FIN CAPTURA PUNTOS: " << t2.elapsed();
                    }
                }else{
                    ++iteradorNota;
                }
		
            } // fin for

            if(notaEnLinea == notaLeida && capturandoPuntos){
                puntos += incrementoDePuntos;
                sistemaPartc -> on();
            }else{
                sistemaPartc -> off();
            }


            barraSuperior -> setText(boost::lexical_cast<string>(puntos));
            if(conjNotas.empty()){
                estadoActual = e3;
                analizador.detener();

                barraSuperior -> animacion -> reverse();
                barraInferior -> animacion -> reverse();
                imagenPartitura -> animacion -> reverse();
                barraProgresoFondo -> animacion -> reverse();

                barraSuperior -> animacion -> init();
                barraInferior -> animacion -> init();
                imagenPartitura -> animacion -> init();
                barraProgresoFondo -> animacion -> init();
            }
        }// fin if lanzado
    }

    else if(estadoActual == e3){
        if(barraSuperior -> animacion -> finished() &&
           barraInferior -> animacion -> finished() &&
           imagenPartitura -> animacion -> finished() &&
           barraProgresoFondo -> animacion -> finished() )
        {
            lDEBUG << "Animaciones de interfaz terminadas.";
            estadoActual = e4;
            maximoPuntos = incrementoDePuntos * (t2.elapsed() / REFRESCO);
            marcadorFinal.reset(new MarcadorPuntos(g, tituloCancion, descripcionCancion,
                                                   puntos, maximoPuntos));
	    
        }

    }    
}



bool entorno(float a, float b, float e){
    return (a >= b - e) && (a <= b + e);
}

void Cancion::draw(){
    barraSuperior -> draw();
    barraInferior -> draw();
    imagenPartitura -> draw();
    barraProgresoFondo -> draw();

    if(estadoActual == e2 || estadoActual == e3){
        barraProgreso -> draw(184, 564, 5, 1 - (float)conjNotas.size() / (float)numeroInicialNotas, 1);
	
        if(notaLeida != Silencio){
            resalteNotaActual -> draw(0, Nota::devolverAltura(notaLeida)+258.5, 5);
        }

        if(lanzado){
            sistemaPartc -> draw(margenIzquierdo, Nota::devolverAltura(notaEnLinea) + 283);
            for_each(conjNotas.begin(), conjNotas.end(), boost::bind(&Nota::draw, _1));
        }
    }

    else if(estadoActual == e4){
        marcadorFinal -> draw();
    }


}

void Cancion::buttonDown(Gosu::Button boton){
    if(boton == Gosu::kbEscape){
        analizador.detener();
    }

}

Cancion::~Cancion(){
    analizador.detener();
    lDEBUG << Log::DES("EstadoCanción");
}
