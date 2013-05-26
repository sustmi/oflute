#ifndef _MARCADORPUNTOS_H_
#define _MARCADORPUNTOS_H_

/**
 * @file marcadorPuntos.h
 * 
 * @author José Tomás Tocino García
 * @date 2011
 *
 * Copyright (C) 2011 José Tomás Tocino García <theom3ga@gmail.com>
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

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
using namespace std;

#include "elementosInterfaz.h"
#include "global.h"

/**
 * @class MarcadorPuntos Representa el marcador de puntos que aparece al
 * terminar de tocar una canción.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class MarcadorPuntos{
public:
    /**
     * @brief Crea un nuevo marcador de puntos
     *
     * @param g Destino gráfico
     * @param tituliCanc Título de la canción
     * @param descCanc Descripción de la canción
     * @param puntosConseguidos Puntos conseguidos
     * @param puntosTotales Máximo de puntos conseguibles con esta canción
     */

    MarcadorPuntos(Gosu::Graphics & g, string tituloCanc, string descCanc,
                   int puntosConseguidos, int puntosTotales){

        imgLogotipo.reset(new ElementoImagen(g,
                                             "media/ofluteLogoGrande.png",
                                             3, Animacion::tAlpha));
	
        imgLogotipo -> setXY(75, 100);
        imgLogotipo -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic);
        imgLogotipo -> animacion -> set(0, 0, 255);

        // CONFIGURACIÓN DEL SUBTÍTULO
        txtSubtitulo.reset(new ElementoTexto(g,
                                             _("Puntuaciones"),
                                             "media/fNormal.ttf",
                                             34, Gosu::Color(0xffa4a4a4),
                                             Texto::alignCentro,
                                             true, 10, 3, 
                                             Animacion::tAlpha));
	
        txtSubtitulo -> setXY(180, 425);
        txtSubtitulo -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 10);
        txtSubtitulo -> animacion -> set(0, 0, 255);

        // Título canción
        txtTituloCancion.reset(new ElementoTexto(g,
                                                 tituloCanc,
                                                 "media/fNormal.ttf",
                                                 54, Gosu::Color(0xffacc827),
                                                 Texto::alignIzq,
                                                 true, 10, 3, 
                                                 Animacion::tAlpha));
	
        txtTituloCancion -> setXY(379, 60);
        txtTituloCancion -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 20);
        txtTituloCancion -> animacion -> set(0, 0, 255);


        // Descripción de la canción
        txtDescCancion.reset(new ElementoTexto(g,
                                               descCanc,
                                               "media/fNormal.ttf",
                                               20, Gosu::Color(0xff6a8800),
                                               Texto::alignIzq,
                                               true, 10, 3, 
                                               Animacion::tAlpha));
	
        txtDescCancion -> setXY(379, 120);
        txtDescCancion -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 30);
        txtDescCancion -> animacion -> set(0, 0, 255);

        // Recuadro con el porcentaje
        imgRecuadroPorcentaje.reset(new ElementoImagen(g,
                                                       "media/marcoPuntos.png",
                                                       3, Animacion::tAlpha));
	
        imgRecuadroPorcentaje -> setXY(379, 152);
        imgRecuadroPorcentaje -> animacion = new Animacion(1, 50, Animacion::tEaseOutCubic, 40);
        imgRecuadroPorcentaje -> animacion -> set(0, 0, 255);

        // Calculamos el porcentaje de aciertos
        float porcentaje = (float) puntosConseguidos / (float) puntosTotales * 100;

        // Convertimos el porcentaje a cadena
        string cadenaPorcentaje = boost::lexical_cast<string>((int)porcentaje) + "%";

        // Creamos el texto para el porcentaje
        txtPorcentaje.reset(new ElementoTexto(g,
                                              cadenaPorcentaje,
                                              "media/fNormal.ttf",
                                              170, Gosu::Color(0xfffd7603),
                                              Texto::alignCentro,
                                              true, 10, 3, 
                                              Animacion::tAlpha));
	
        txtPorcentaje -> setXY(558, 145);
        txtPorcentaje -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 50);
        txtPorcentaje -> animacion -> set(0, 0, 255);

        // Submensaje "de aciertos"
        txtAciertos.reset(new ElementoTexto(g,
                                            _("de aciertos"),
                                            "media/fNormal.ttf",
                                            40, Gosu::Color(0xfffd7603),
                                            Texto::alignCentro,
                                            true, 10, 3, 
                                            Animacion::tAlpha));
	
        txtAciertos -> setXY(558, 300);
        txtAciertos -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 60);
        txtAciertos -> animacion -> set(0, 0, 255);

        string mensaje = "";
        if(porcentaje > 80){
            mensaje = _("¡Muy bien hecho! Eres un artista\nDebes estar orgulloso.");
        }
        else{
            mensaje = _("¡Debes esforzarte más!\nSé que puedes hacerlo mucho mejor");
        }

        txtMensaje.reset(new ElementoTexto(g,
                                           mensaje,
                                           "media/fNormal.ttf",
                                           33, Gosu::Color(0xff05779d),
                                           Texto::alignCentro,
                                           true, 10, 3, 
                                           Animacion::tAlpha));
	
        txtMensaje -> setXY(558, 375);
        txtMensaje -> animacion = new Animacion(1, 40, Animacion::tEaseOutCubic, 70);
        txtMensaje -> animacion -> set(0, 0, 255);
    }

    /// Pintamos los elementos del marcador de puntos
    void draw(){
        imgLogotipo -> draw();
        txtSubtitulo -> draw();
	
        txtTituloCancion -> draw();
        txtDescCancion -> draw();
	
        imgRecuadroPorcentaje -> draw();
        txtPorcentaje -> draw();
        txtAciertos -> draw();
        txtMensaje -> draw();
    }
    
private:

    /// Referencia a la imagen del logotipo
    boost::scoped_ptr<ElementoImagen> imgLogotipo;

    /// Referencia a la imagen del recuadro
    boost::scoped_ptr<ElementoImagen> imgRecuadroPorcentaje;

    /// Texto del subtítulo
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    /// Texto del título de la canción
    boost::scoped_ptr<ElementoTexto> txtTituloCancion;

    /// Texto de la descripción de la canción
    boost::scoped_ptr<ElementoTexto> txtDescCancion;

    /// Texto para el porcentaje de aciertos
    boost::scoped_ptr<ElementoTexto> txtPorcentaje;

    /// Texto para el mensaje bajo el porcentaje
    boost::scoped_ptr<ElementoTexto> txtAciertos;

    /// Texto para el mensaje de ánimo
    boost::scoped_ptr<ElementoTexto> txtMensaje;
};

#endif /* _MARCADORPUNTOS_H_ */
