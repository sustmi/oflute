/**
 * @file estadoMenuLecciones.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#include "juego.h"
#include "estadoMenuLecciones.h"
#include "leccion.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <pugixml.hpp>

EstadoMenuLecciones::EstadoMenuLecciones(Juego * p) : Estado(p) {

	estadoActual = eMostrando;

	leccionMostrada = NULL;
	leccionActual = -1;

	////////////////////////////////////////
	// Definición de la imagen de la pizarra

	pizarra.reset(new ElementoImagen(padre -> graphics(), "media/menuLecciones/pizarra.png", 
	                                 2, Animacion::tAlphaPos));
	pizarra -> animacion = new Animacion(3, 30, Animacion::tEaseOutQuad, 0);
	pizarra -> animacion -> set(0, 0, 255); // alfa
	pizarra -> animacion -> set(1, -450, 35); // x
	pizarra -> animacion -> set(2, 128, 128); // y

	conjuntoElementos.push_back(pizarra);

	////////////////////////////////////////
	// Definición de la barra superior

	barraSuperior.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );

	// Configuramos la animación

	barraSuperior -> animacion = new Animacion(2, 30, Animacion::tEaseOutQuad, 0);
	barraSuperior -> animacion -> set(0, 0, 0); // Sin movimiento en el eje X
	barraSuperior -> animacion -> set(1, -70, 0); // Movimiento vertical

	barraSuperior -> setImagen("media/menuLecciones/mTop.png");

	// Configuramos el texto

	tConfTexto * cTexto = new tConfTexto;
	cTexto-> cadena = _("Listado de lecciones");
	cTexto-> rutaFuente = "media/fLight.ttf";
	cTexto-> tam = 54;
	barraSuperior -> setTexto(*cTexto, 34, 0);

	delete cTexto;

	conjuntoElementos.push_back(barraSuperior);


	//////////////////////////////////////
	// Definición de la barra inferior
	barraInferior.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );

	barraInferior -> animacion = new Animacion(2, 30, Animacion::tEaseOutQuad, 0);
	barraInferior -> animacion -> set(0, 0, 0);
	barraInferior -> animacion -> set(1, 600, 554);

	barraInferior -> setImagen("media/menuLecciones/mBottom.png");

	tConfTexto * confInferiorTexto = new tConfTexto;
	confInferiorTexto -> cadena = _("Volver al menú");
	confInferiorTexto -> rutaFuente = "media/fNormal.ttf";
	confInferiorTexto -> tam = 28;
	barraInferior -> setTexto(*confInferiorTexto, 52, 7);

	delete confInferiorTexto;

	conjuntoElementos.push_back(barraInferior);

	//////////////////////////////////////////
	// Definición del primer botón (En el que aparece "Lección nº1")

	btnTitular.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );

	btnTitular -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 10);
	btnTitular -> animacion -> set(0, 800, 400);
	btnTitular -> animacion -> set(1, 69, 69);

	btnTitular -> setImagen("media/menuLecciones/mBtn1.png");

	tConfTexto * confBtnTexto = new tConfTexto;
	confBtnTexto -> cadena = _("Lección nº1");
	confBtnTexto -> rutaFuente = "media/fNormal.ttf";
	confBtnTexto -> tam = 36;
	confBtnTexto -> sombra = false;
	confBtnTexto -> alineacion = Texto::alignDer;
	btnTitular -> setTexto(*confBtnTexto, -20, 7);

	conjuntoElementos.push_back(btnTitular);


	///////////////////////////////
	// Definición del fondo de la descripción

	btnDescripcion.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );

	btnDescripcion -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 20);
	btnDescripcion -> animacion -> set(0, 800, 400);
	btnDescripcion -> animacion -> set(1, 127, 127);

	btnDescripcion -> setImagen("media/menuLecciones/mBtn2.png");

	confBtnTexto -> cadena = _("Descripción:");
	confBtnTexto -> sombra = true;
	confBtnTexto -> color = Gosu::Color(255, 227, 253, 94);
	btnDescripcion -> setTexto(*confBtnTexto, -20, 10);

	conjuntoElementos.push_back(btnDescripcion);

	//////////////////////////////////////
	// Definición del texto de la descripción

	textoDesc . reset( new ElementoTexto( padre -> graphics(), " ", "media/fNormal.ttf",
	                                      36, 0xffffffff, Texto::alignDer,
	                                      true, 80,
	                                      4, Animacion::tAlpha) );
	textoDesc -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 13);
	textoDesc -> animacion -> set(0,0,255);
	textoDesc -> setXY(780, 175);

	conjuntoElementos.push_back(textoDesc);
	///////////////////////////////
	// Botón comenzar 

	btnComenzar.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );
	btnComenzar -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 30);
	btnComenzar -> animacion -> set(0, 800, 400);
	btnComenzar -> animacion -> set(1, 351, 351);

	btnComenzar -> setImagen("media/menuLecciones/mBtn3.png");
	confBtnTexto -> color = Gosu::Color(255,255,255,255);
	confBtnTexto -> cadena = _("Comenzar lección");
	confBtnTexto -> alineacion = Texto::alignCentro;
	btnComenzar -> setTexto(*confBtnTexto, 10, 10);

	conjuntoElementos.push_back(btnComenzar);

	///////////////////////////////
	// Botón Siguiente Lección
	btnSigLec.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );
	btnSigLec -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 40);
	btnSigLec -> animacion -> set(0, 800, 400);
	btnSigLec -> animacion -> set(1, 417, 417);

	btnSigLec -> setImagen("media/menuLecciones/mBtn4.png");

	confBtnTexto -> cadena = _("Siguiente lección");
	btnSigLec -> setTexto(*confBtnTexto, 10, 13);

	conjuntoElementos.push_back(btnSigLec);

	/////////////////////////////
	// Botón Anterior Lección
	btnAntLec.reset( new ElementoCombinado( padre -> graphics(), Animacion::tPos, 2) );
	btnAntLec -> animacion = new Animacion(2, 20, Animacion::tEaseOutQuad, 50);
	btnAntLec -> animacion -> set(0, 800, 400);
	btnAntLec -> animacion -> set(1, 487, 487);

	btnAntLec -> setImagen("media/menuLecciones/mBtn5.png");

	confBtnTexto -> cadena = _("Anterior lección");
	btnAntLec -> setTexto(*confBtnTexto, 10, 10);
	conjuntoElementos.push_back(btnAntLec);

	delete confBtnTexto;

	//*/


}

void EstadoMenuLecciones::listarLecciones(){


	boost::filesystem::path rutaDirectorio("./lecciones");
	boost::filesystem::directory_iterator inicial(rutaDirectorio), final;

	pugi::xml_document documento;
	pugi::xml_parse_result resultado;
	pugi::xml_node nodoActual, nodoVacio;
	pugi::xml_attribute atributo;

	for(; inicial != final ; ++ inicial){
		if(boost::to_lower_copy(inicial -> path() . extension()) == ".xml"){

			EstadoMenuLecciones::InfoLeccion lecActual;
			string ruta = boost::lexical_cast<string>(inicial -> path());

			lDEBUG << "Intentando cargar archivo " << ruta;

			resultado = documento . load_file(ruta.c_str());

			if(!resultado){
				lERROR << LOC() << " Error al leer el documento: " << ruta;
				lERROR << resultado.description(); 
				continue;
			}

			lecActual.ruta = ruta;

			/////////////////////
			// Leemos el número de lección

			nodoActual = documento.child("Lec").child("index");

			if(nodoActual == nodoVacio){
				lERROR << "El fichero " << ruta << " no está bien formado. "
				       << "(Falta índice)";
				continue;
			}

			lecActual.indice = boost::lexical_cast<int>(nodoActual.first_child().value());


			/////////////////
			// Leemos el nombre de la lección

			nodoActual = documento.child("Lec").child("nombre");

			if(nodoActual == nodoVacio){
				lERROR << "El fichero " << ruta << " no está bien formado. "
				       << "(Falta nombre)";
				continue;
			}

			lecActual.nombre = nodoActual.first_child().value();


			/////////////////////
			// Leemos la descripción
			nodoActual = documento.child("Lec").child("descrip");

			if(nodoActual == nodoVacio){
				lERROR << "El fichero " << ruta << " no está bien formado. "
				       << "(Falta descripción)";
				continue;
			}

			lecActual.descrip = nodoActual.first_child().value();

			leccionesCargadas.push_back(lecActual);

		}
	}

	sort(leccionesCargadas.begin(), leccionesCargadas.end(), ordenarLecciones());
	leccionActual = 0;
	cambiarLeccion(leccionActual);
}



void EstadoMenuLecciones::cambiarLeccion(unsigned n){
	leccionActual = n;

	tConfTexto * confBtnTexto = new tConfTexto;
	confBtnTexto -> cadena = string(_("Lección nº")) + boost::lexical_cast<string>(leccionesCargadas[n].indice);
	confBtnTexto -> rutaFuente = "media/fNormal.ttf";
	confBtnTexto -> tam = 36;
	confBtnTexto -> sombra = false;
	confBtnTexto -> alineacion = Texto::alignDer;
	btnTitular -> setTexto(*confBtnTexto, -20, 7);

	delete confBtnTexto;

	textoDesc -> setText(leccionesCargadas[n] . descrip);
}



void EstadoMenuLecciones::draw() {
	barraInferior -> draw();  

	if(estadoActual != eLeccion){
		pizarra -> draw();
		barraSuperior -> draw();
		btnTitular -> draw();
		textoDesc -> draw();
		btnComenzar -> draw();
		btnAntLec -> draw();
		btnSigLec -> draw();
		btnDescripcion -> draw();
	}else if(estadoActual == eLeccion){
		leccionMostrada -> draw();
	}
	
	//*/
}

void EstadoMenuLecciones::anteriorLec(){
	if(leccionActual <= 0){
		cambiarLeccion(leccionesCargadas.size() - 1);
	}else{
		cambiarLeccion(leccionActual - 1);
	}
	
}

void EstadoMenuLecciones::siguienteLec(){
	if(leccionActual == (int)(leccionesCargadas.size() - 1)){
		cambiarLeccion(0);
	}else{
		cambiarLeccion(leccionActual + 1);
	}
}


void EstadoMenuLecciones::buttonDown(Gosu::Button boton){
	if(boton == Gosu::msLeft){
		int x = padre -> input().mouseX();
		int y = padre -> input().mouseY();
	
		if(estadoActual == eMenu){
			if(barraInferior -> clicked(x, y)){
				estadoActual = eOcultando;
				iniciarAnimacionSalida(dirOCULTAR, false);
			}
	    
			else if(btnAntLec -> clicked(x, y)){
				anteriorLec();
			}

			else if(btnSigLec -> clicked(x, y)){
				siguienteLec();
			}
	    
			else if(btnComenzar -> clicked(x, y)){
				estadoActual = eOcultarInter;
				iniciarAnimacionSalida(dirOCULTAR);
			}
		}

		else if(estadoActual == eLeccion){	    
			if(barraInferior -> clicked(x, y)){
				estadoActual = eMostrarInter;
				iniciarAnimacionSalida(dirMOSTRAR);  
				delete leccionMostrada;
				leccionMostrada = NULL;
			}
		}
	}else if(boton == Gosu::kbLeft){
		anteriorLec();
	}else if(boton == Gosu::kbRight){
		siguienteLec();
	}else if(boton == Gosu::kbReturn){
		estadoActual = eOcultarInter;
		iniciarAnimacionSalida(dirOCULTAR);
	}
}

void EstadoMenuLecciones::iniciarAnimacionSalida(int dir, bool saltarBarraInferior){
	foreach(boost::shared_ptr<Elemento>& E, conjuntoElementos){
		if(E == barraInferior && saltarBarraInferior) continue;
		E -> animacion -> reverse();
		if(dir == dirMOSTRAR){
			E -> animacion -> setTipoAnimacion(Animacion::tEaseOutQuad);
		}else{
			E -> animacion -> setTipoAnimacion(Animacion::tEaseInQuad);
		}
		E -> animacion -> init();
	}
}


void EstadoMenuLecciones::lanzarLeccion(){
	lDEBUG << LOC();

    
	leccionMostrada = new Leccion(padre -> graphics(), 
	                              leccionesCargadas[leccionActual].ruta);
	estadoActual = eLeccion;//*/
    
}

void EstadoMenuLecciones::update(){

	// El Menú está saliendo
	if(estadoActual == eMostrando){

		/*
		// Si al estar saliendo se pulsa Escape, se terminan las animaciones
		if(padre -> input() . down(Gosu::kbEscape)){
		lDEBUG << "Terminando animaciones...";
		foreach(boost::shared_ptr<Elemento>& E, conjuntoElementos){
		E -> animacion -> end();
		}

		estadoActual = eMenu;
		} //*/

		if(barraSuperior -> animacion -> finished() && btnAntLec -> animacion -> finished()){
			estadoActual = eMenu;
		}
	}

	// Menú activo
	else if(estadoActual == eMenu){
		if(leccionActual == -1){
			listarLecciones();
		}

		if(padre -> input() . down(Gosu::kbEscape)){
			estadoActual = eOcultando;
			iniciarAnimacionSalida(dirOCULTAR, false);
		}
	} 

	else if(estadoActual == eOcultarInter){
		if(btnAntLec -> animacion -> finished()){
			estadoActual = eLeccion;
			leccionMostrada = new Leccion(padre -> graphics(),
			                              leccionesCargadas[leccionActual].ruta);
		}
	}

	else if(estadoActual == eMostrarInter){
		if(btnAntLec -> animacion -> finished()){
			estadoActual = eMenu;
		}

	}

	else if(estadoActual == eOcultando){
		if(btnAntLec -> animacion -> finished()){
			padre -> cambiarEstado("estadoMenuSinFondo");
		}
	}

	else if(estadoActual == eLeccion){
		if(padre -> input() . down(Gosu::kbEscape)){
			estadoActual = eMostrarInter;
			iniciarAnimacionSalida(dirMOSTRAR);  
			delete leccionMostrada;
			leccionMostrada = NULL;
		}
	}
}


EstadoMenuLecciones::~EstadoMenuLecciones(){
	if(leccionMostrada != NULL){
		delete leccionMostrada;
	}
}
