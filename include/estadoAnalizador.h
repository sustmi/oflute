/**
 * @file estadoAnalizador.h
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

#ifndef _ESTADOANALIZADOR_H_
#define _ESTADOANALIZADOR_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>

#include <string>
#include <map>

#include "estado.h"
#include "global.h"
#include "analizador.h"
#include "elementosInterfaz.h"

class Juego;

/**
 * @class EstadoAnalizador
 * @ingroup estadosPrincipales
 *
 * @brief Analizador de notas individual.
 *
 * Es una de las opciones principales del menú. Muestra una partitura
 * con una nota única que indica la que se está capturando por el
 * micrófono.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class EstadoAnalizador : public Estado{
public:

    /// Genera un nuevo estado.
    EstadoAnalizador(Juego * p);

    /// Lanza el estado, activando el analizador.
    void lanzar ();

    /// Actualiza los estados de transición.
    void update();

    /// Dibuja los elementos gráficos.
    void draw();

    /// Controla las pulsaciones de botones.
    void buttonDown(Gosu::Button boton);

    /// Destruye el estado
    ~EstadoAnalizador();

private:

    /// Diferentes estados de transición
    enum tTrans{ transIn, transHold, transOut };

    /// Estado de transición actual
    tTrans estadoTransicion;

    /// Flag que indica si el estado ha sido lanzado
    bool lanzado;

    /// Imagen para el logotipo
    boost::scoped_ptr<ElementoImagen> imgLogotipo;

    /// Imagen de la minipartitura
    boost::scoped_ptr<ElementoImagen> imgPartitura;

    /// Imagen del texto inferior
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    /// Imágenes de las figuras
    boost::shared_ptr<Gosu::Image> imgDo5, imgRe5, imgMi5, imgFa5, imgSol5, imgLa5, imgSi5, imgDo6, imgRe6;

    /// Botón volver
    boost::scoped_ptr<ElementoCombinado> btnVolver;

    /// Analizador
    Analizador analizador;
    
    /// Invierte las animaciones y detiene el analizador
    void salir();

};

#endif
