/**
 * @file estadoMenuLecciones.h
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

#ifndef _ESTADOLECCIONES_H_
#define _ESTADOLECCIONES_H_

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <Gosu/Gosu.hpp>

#include "global.h"
#include "estado.h"
#include "elementosInterfaz.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Leccion;

class Juego;

/**
 * @class EstadoMenuLecciones
 *
 * @brief Clase que modela el menú de selección de las lecciones.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
class EstadoMenuLecciones : public Estado{

public:
	/// Crea el menú de lecciones
	EstadoMenuLecciones(Juego * p);

	/// Controla la lógica de transiciones
	void update();
    
	/// Dibuja los elementos en pantalla
	void draw();

	/// Lee las lecciones contenidas en el directorio <b>lecciones</b>
	/// y las carga en el contenedor de lecciones.
	void listarLecciones();

	void buttonDown(Gosu::Button boton);

	/// Pasa a la anterior lección
	void anteriorLec();

	/// Pasa a la siguiente lección
	void siguienteLec();

	/// Cambia a la lección n-ésima
	void cambiarLeccion(unsigned n);

	/// Lanza la lección, ocultando temporalmente el menú
	void lanzarLeccion();

	~EstadoMenuLecciones();

private:
	/// Imagen de la pizarra
	boost::shared_ptr<ElementoImagen> pizarra;

	/// Imagen de la barra superior
	boost::shared_ptr<ElementoCombinado> barraSuperior;

	/// Imagen de la barra inferior
	boost::shared_ptr<ElementoCombinado> barraInferior;

	/// Imagen del bloque con el título de la lección
	boost::shared_ptr<ElementoCombinado> btnTitular;

	/// Imagen del bloque con el bloque de descripción
	boost::shared_ptr<ElementoCombinado> btnDescripcion;

	/// Texto de la descripción
	boost::shared_ptr<ElementoTexto> textoDesc;

	/// Botón comenzar
	boost::shared_ptr<ElementoCombinado> btnComenzar;

	/// Botón anterior lección
	boost::shared_ptr<ElementoCombinado> btnAntLec;

	/// Botón siguiente lección
	boost::shared_ptr<ElementoCombinado> btnSigLec;

	/// Contenedor de todos los elementos
	vector<boost::shared_ptr<Elemento> > conjuntoElementos;

	/**
	 * @class InfoLeccion
	 *
	 * @brief Estructura con información de las lecciones cargadas
	 *
	 * @author José Tomás Tocino García <theom3ga@gmail.com> 
	 *
	 */
    

	struct InfoLeccion{ 
		/// Posición de la lección
		int indice;
	
		/// Nombre de la lección
		string nombre;
	
		/// Descripción de la lección
		string descrip;

		/// Ruta al XML de la lección
		string ruta;
	};

	/// Objeto función para ordenar las lecciones según su índice
	struct ordenarLecciones{

        /// Devuelve true si el índice de la lección a es anterior al de la lección b
		bool operator()(InfoLeccion a, InfoLeccion b){
			return b.indice > a.indice;
		}
	};

	/// Indicador de la lección actual
	int leccionActual;

	/// Contenedor para las lecciones listadas
	vector<InfoLeccion> leccionesCargadas;

	/// Enumerado de estados de transición
	enum {eMostrando, eMenu, eOcultarInter, eMostrarInter, eLeccion, eOcultando};

	/// Estado de transición actual
	int estadoActual;

	/// Lección actualmente cargada
	Leccion * leccionMostrada;

	/// Direcciones de las transiciones.
	enum{dirMOSTRAR, dirOCULTAR};

	/** Inicia las animaciones para esconder los botones
	 *
	 * @param dir Dirección, dirMOSTRAR o dirOCULTAR
	 * @param saltarBarraInferior Indica si la barra de abajo debe ocultarse o no.
	 **/

	void iniciarAnimacionSalida(int dir, bool saltarBarraInferior = true);
};

#endif /* _ESTADOLECCIONES_H_ */
