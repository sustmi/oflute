/**
 * @file estado.h
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

/**
 * @defgroup estadosPrincipales Estados principales
 * Se accede a ellos desde el menú principal.
 **/


#ifndef _ESTADO_H_
#define _ESTADO_H_

#include <Gosu/Gosu.hpp>
#include <iostream>

#include "log.h"

using namespace std;

class Juego;

/**
 * @class Estado
 * @ingroup estadosPrincipales
 *
 * @brief Clase base para los diferentes estados del juego.
 *
 * Esta clase abstracta tiene los métodos a los que llamará la clase de control (Juego).
 * Cada estado deberá implementar estos métodos con las acciones que crea conveniente.
 * No puede instanciarse por sí misma, debe crearse una clase heredada.
*/

class Estado{
protected:
    /**
     @brief Puntero al padre creador.

     Nos sirve para poder cambiar de estado (llamando a #Juego::cambiarEstado()), acceder al sistema gráfico (con Juego::graphics()) y otras acciones.
    **/
    Juego * padre;

public:
    /**
       @brief Constructor - Crea un estado.

       Recibe un puntero a Juego, que será quien lleve el control de los estados.

       @param p puntero a la clase Juego que controla la aplicación
    **/
    Estado(Juego * p);

    /// Si es necesario lanzar acciones independientes del constructor, irán aquí.
    virtual void lanzar(){
	    lDEBUG << "lanzar";
    }

    /// Virtual puro. Cada estado implementa la lógica de control aquí.
    virtual void update() = 0;

    /// Virtual puro. Cada estado implementa el redibujado aquí.
    virtual void draw() = 0;

    /// Opcionalmente los estados pueden responder a la entrada redefiniendo este método.
    virtual void buttonDown(Gosu::Button){};

    virtual ~Estado();
};

#endif /* _ESTADO_H_ */
