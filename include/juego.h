/**
 * @file juego.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Clase principal del juego
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

#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <Gosu/Gosu.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>

#include "animacion.h"

#include "global.h"


class Estado;

/**
 * @class Juego
 * @brief Clase principal del juego
 *
 * Sirve como pilar para el resto del juego. Hereda de la base 
 * Gosu::Window y se encarga de pasar de un estado a otro, así como
 * de pasarle los eventos al estado actual.
 *
 * Implementa las funciones update() y draw() para llevar a cabo el Game Loop,
 * ejecutándose ambas en cada iteración.
 */

class Juego : public Gosu::Window{

public:
    /** 
     * @brief Constructor, inicio básico.
     *
     * Carga en memoria el primer estado y lo lanza.
     */
    Juego();

    /**
     * @brief Procesa la lógica del juego. 
     * 
     * Como la lógica de cada estado es controlada por la clase que 
     * corresponda a ese estado, este método simplemente llama
     * al update del estado actual.
     */
    void update();

    /**
     * @brief Procesa el dibujado de los gráficos.
     *
     * Igual que en el método #update, simplemente llama al método de 
     * dibujado de la clase del estado actual.
     */
    void draw();

    /**
     * @brief Activa el proceso de cambio de estado
     *
     * Recibe una cadena con el estado al que pasar, que se guarda.
     * Al terminar la iteración actual se llama a realizarCambioEstado
     * para que se termine el cambio de estado.
     *
     * @param destino Una cadena con información sobre el estado al que cambiar
     *
     **/
    void cambiarEstado(std::string destino);

    /** @brief Evento de presión de un botón.
     * 
     * Lo mismo que en #update y #draw, paso transparente a la clase del estado actual.
     *
     * @param boton El botón que se ha pulsado.
     **/
    void buttonDown(Gosu::Button boton);

    /** 
     * @brief Destructor básico.
     *
     **/
    ~Juego();

private:
    /// Contenedor del estado actual
    boost::scoped_ptr <Estado> estadoActual;

    /// Cadena con el estado actual
    std::string estadoCadena;

    /// Flag que indica si en la próxima iteración se cambiará el estado.
    /// Esto es así para no cambiar el estado a mitad de la iteración, pues
    /// puede provocar errores.
    bool cambiandoEstado;

    /// Cadena que guarda el siguiente estado
    std::string siguienteEstado;

    /// Finaliza el proceso de cambio de estado
    void realizarCambioEstado();

    /// Imagen para el cursor del ratón
    boost::scoped_ptr <Gosu::Image> cursor;

    /// Fondo común en todas las pantallas del juego excepto los créditos 
    boost::scoped_ptr <Gosu::Image> fondoComun;

    /// Animación para el fondo
    boost::scoped_ptr <Animacion> animacionFondo;

};

#endif /* _JUEGO_H_ */
