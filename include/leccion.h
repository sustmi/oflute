/**
 * @file leccion.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Fichero para la clase Lección
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


#ifndef _LECCION_H
#define _LECCION_H_

#include <Gosu/Gosu.hpp>

#include <vector>
#include <string>

using namespace std;

#include <boost/shared_ptr.hpp>

#include "elementosInterfaz.h"

/**
 * @class Leccion
 *
 * @brief Lee una lección de un xml pasado como argumento, y genera una interfaz atendiendo a los elementos leídos del XML.
 *
 * Recibe la ruta de un archivo XML, que contendrá los elementos que deberán aparecer en la interfaz. Los elementos posibles son
 * cuadros de texto e imágenes. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Leccion{

public:
	/**
	 * @brief Construye una nueva lección a partir de un XML.
	 *
	 * @param g El destino gráfico en que se dibujará la interfaz
	 * @param ruta La ruta del fichero XML
	 *
	 */
	Leccion(Gosu::Graphics& g, string ruta);

	/// Dibuja cada uno de los elementos de la interfaz
	void draw();

private:
	/// Índice de la lección en el listado de lecciones.
	unsigned indice;

	/// Nombre de la lección.
	string nombre;

	/// Referencia al contenedor gráfico.
	Gosu::Graphics& g;

	/// Contenedor de los elementos de la interfaz.
	vector<boost::shared_ptr<Elemento> > elementos;

	/// Contenedor de las animaciones de cada elemento de la interfaz.
	vector<boost::shared_ptr<Animacion> > animaciones;

};

#endif /* _LECCION_H_ */
