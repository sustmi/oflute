/**
 * @file texto.h
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

#ifndef _TEXTO_H_
#define _TEXTO_H_

#include <iostream>
#include <string>
#include <vector>

#include <Gosu/Gosu.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "log.h"

using namespace std;

/**
 * @class Texto
 *
 * @brief Pinta un cuadro de texto
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
class Texto{

public:
    /// Alineación del texto
    enum tAlign{ alignIzq = 1, alignCentro, alignDer };

    /**
     * @brief Crea un nuevo cuadro de texto
     *
     * @param graphics El objeto gráfico.
     * @param texto Texto a escribir.
     * @param rutaFuente Ruta a la fuente que se usará para pintar el texto.
     * @param tam Tamaño del texto.
     * @param color Color del texto.
     * @param alineacion Alineación del texto. 1 = izquierda, 2 = centrado, 3 = derecha.
     * @param sombra Si hay que imprimir sombra o no.
     * @param opSombra Opacidad de la sombra. Irrelevante si no hay sombra.
     * @param x Posición horizontal.
     * @param y Posición vertical.
     * @param z Profundidad.
     *
     */

    Texto(Gosu::Graphics& graphics, 
	  string texto, string rutaFuente, unsigned tam, Gosu::Color color = Gosu::Color::WHITE,
	  unsigned alineacion = 1, 
	  bool sombra = false, unsigned opSombra = 80, float x = 0, float y = 0, float z = 0);

    /// Método de conveniencia, realmente no hace nada.
    void update();

    /// Cambia la cadena asignada al texto
    void setText(string s);

    /// Devuelve la cadena asignada al texto
    string getText();

    /// Pinta el texto con la opacidad al máximo por defecto.
    void draw();

    /**
     * @brief Pinta el texto con la opacidad indicada.
     *
     * @param a La opacidad (alpha) con la que pintar el texto.
     */
    void drawAlpha(int a);

    /**
     * @brief Pinta el texto en la profundidad indicada.
     *
     * @param z_ La profundidad en la que pintae l texto.
     */
    void draw(float z_);

    /**
     * @brief Pinta el texto en la posición y con los parámetros indicados
     *
     */
    void draw(float x_, float y_, float z_, int a_ = 255);

    /// Devuelve la alineación del texto
    unsigned getAlineacion() { return alineacion; }

private:

    /// Objeto que será el destino gráfico.
    Gosu::Graphics& graphics;

    /// Fuente del texto
    boost::scoped_ptr<Gosu::Font> fuente;

    /// Texto a escribir.
    string texto;

    /// Texto dividido en líneas.
    vector<string> lineas;

    /// Tamaño del texto.
    unsigned tam;

    /// Color del texto.
    Gosu::Color color;

    /// Alineación, 1 = izquierda, 2 = centrado, 3 = derecha.
    unsigned alineacion;

    /// Existencia de la sombra
    bool sombra;

    /// Opacidad de la sombra
    unsigned opacidadSombra;

    /** Posición horizontal del texto. 	Para el texto justificado a la
     *	izquierda, es la esquina sup izq. Para el texto justif. a la
     *	derecha, es la esquina sup der. Para el texto centrado, es la
     *	posición central superior
     **/
    float x;

    /// Posición vertical 
    float y;
    
    /// Profundidad
    double z;

    ///Desplazamiento de la sombra respecto al texto
    int offsetShadow[2];

    /// Ruta de la fuente
    string rutaFuente;
    
    /** @brief Divide el texto según los saltos de línea, metiendo cada línea en el vector lineas.
     *  Función adaptada de http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
     */
    int dividirTexto();
    
    /// Carga la fuente a utilizar en el texto
    void poblarVectores();

};

#endif /* _TEXTO_H_ */
