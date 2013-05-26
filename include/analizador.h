/**
 * @file analizador.h
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

#ifndef _ANALIZADOR_H_
#define _ANALIZADOR_H_

//#include <portaudiocpp/PortAudioCpp.hxx>
#include <map>

#include "global.h"
#include "configuracion.h"
#include "analizadorProxy.h"

#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>

/**
 * @class Analizador
 *
 * @brief Controla el análisis de las notas, encargándose de mapear las frecuencias.
 *
 * También se encarga de gestionar el hilo en el que se ejecuta el
 * análisis. Guarda un objeto AnalizadorProxy que llevará a cabo el
 * análisis de forma paralela.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Analizador{
public:
    /// Inicializa el mapa de frecuencias.
    Analizador();

    /// Lanza el hilo con el analizador.
    void iniciar();

    /// Detiene el hilo del analizador.
    void detener();

    /// Devuelve la nota que actualmente se está registrando.
    t_altura notaActual();

    /// Devuelve el volumen que se está registrando.
    float volumenActual();

private:

    /// Lector de configuración para leer el volumen mínimo detectado.
    lectorConfiguracion lectorConfig;

    /// Objeto que se encarga de la gestión de sonido y el análisis.
    AnalizadorProxy proxy;

    /// Hilo en el que correrá el análisis.
    boost::scoped_ptr<boost::thread> hilo;

    /// Devuelve la nota asociada a una frecuencia, o la más cercana.
    t_altura asociarNota (double frecuencia);

    /// Mapa de frecuencias y notas.
    std::map<double, t_altura> notas;

    /// Flag que indica el estado del análisis
    bool detenido;    
};

#endif /* _ANALIZADOR_H_ */
