#include "juego.h"

#include "estado.h"

#include "estadoImagenFija.h"
#include "estadoMenu.h"
#include "estadoAnalizador.h"
#include "estadoMenuLecciones.h"
#include "estadoMenuCanciones.h"
#include "estadoCalibrarMicro.h"

#include "log.h"

#include <boost/lexical_cast.hpp>


Juego::Juego() : Gosu::Window (ANCHO, ALTO, FULLSCREEN, REFRESCO), cambiandoEstado(false){
    lDEBUG << Log::CON("Juego");
    setCaption(L"oFlute .:.");

    cursor.reset( new Gosu::Image(graphics(), L"media/pointerCursor.png"));

    fondoComun.reset( new Gosu::Image(graphics(), L"media/fondoGenerico.png"));
    animacionFondo.reset (new Animacion(1, 50, Animacion::tEaseOutQuad));
    animacionFondo -> set(0, 0, 255);

    cambiarEstado("estadoAutor");
}

void Juego::update(){
    if(cambiandoEstado){
        realizarCambioEstado();
    }else{
        estadoActual -> update();
    
        if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro"){
            animacionFondo -> update();
        }
    }
}

void Juego::draw(){
    // Dibujamos el cursor en la posición del ratón
    // Usamos Z=999 para que esté encima de todo

    cursor -> draw(input().mouseX(), input().mouseY(), 999);
    estadoActual -> draw();
    if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro"){
        fondoComun -> draw(0,0,1, 1,1, Gosu::Color(animacionFondo -> get(0), 255, 255, 255));
    }
}


void Juego::cambiarEstado(std::string destino){
    lDEBUG << "Petición para cambiar estado a: " << Log::cRojo << destino << Log::cDef;
    cambiandoEstado = true;
    siguienteEstado = destino;
}

void Juego::realizarCambioEstado(){
    lDEBUG << "Realizando el cambio de estado.";
    estadoCadena = siguienteEstado;

    cambiandoEstado = false;
    siguienteEstado = "";
    
    if (estadoCadena == "estadoAutor"){
        estadoActual.reset( 
            new EstadoImagenFija(this, L"media/estadoAutor.png", "estadoIntro"));
        estadoActual -> lanzar();	
    }

    else if(estadoCadena == "estadoIntro"){
        estadoActual.reset(
            new EstadoImagenFija(this, L"media/estadoIntro.png", "estadoMenu"));
        estadoActual -> lanzar();
    }
	
    else if(estadoCadena == "estadoMenu"){
        estadoActual.reset(new EstadoMenu(this));
        estadoActual -> lanzar();
    }
    
    else if(estadoCadena == "estadoMenuSinFondo"){
        estadoActual.reset(new EstadoMenu(this));
        static_cast<EstadoMenu * >(estadoActual . get()) -> quitarDemoraInicial();
        estadoActual -> lanzar();
    }

    else if(estadoCadena == "estadoAnalizador"){
        estadoActual.reset(new EstadoAnalizador(this));
        estadoActual -> lanzar();
    }

    else if(estadoCadena == "estadoMenuLecciones"){
        estadoActual.reset(new EstadoMenuLecciones(this));
    }

    else if(estadoCadena == "estadoMenuCanciones"){
        estadoActual.reset(new EstadoMenuCanciones(this));
        estadoActual -> lanzar();
    }

    else if(estadoCadena == "estadoCalibrar"){
        estadoActual.reset(new EstadoCalibrarMicro(this));
    }
	
    else if(estadoCadena == "salir"){
        close();
    }
}
    
void Juego::buttonDown(Gosu::Button boton){
    if(estadoCadena != "estadoAutor" && estadoCadena != "estadoIntro" && boton == Gosu::kbEscape){
        animacionFondo -> end();
    }
    estadoActual -> buttonDown(boton);
}    

Juego::~Juego(){
    lDEBUG << Log::DES("Juego");
}
