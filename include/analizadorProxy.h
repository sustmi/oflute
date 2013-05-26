/**
 * @file analizadorProxy.h
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


#ifndef _ANALIZADORPROXY_H_
#define _ANALIZADORPROXY_H_

#include <map>
#include <cmath>

#include "configuracion.h"
#include "log.h"
#include "global.h"

#include <pulse/simple.h>

/**
 * @class tipoBuffer
 *
 * @brief Búffer en el que se guardan los datos de la captura.
 *
 * El sistema de audio va capturando audio y volcando los datos en
 * este búffer, que luego se pasa a la función de Fourier para
 * calcular la frecuencia.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class tipoBuffer{
public:
    tipoBuffer():pos(0){}

    /// Posición de escritura en el búffer
    int pos;

    /// Búffer con los datos de entrada
    int in[4096];

    /// Búffer con los datos procesados tras la FFT
    float out[2048];

    /// Último volumen leído
    float lastVolume;

    /// Mayores frecuencias leídas.
    float mayores[5];

};

/**
 * @class AnalizadorProxy
 *
 * @brief Se encarga de lanzar el audio y realizar el análisis FFT.
 *
 * El operador () de esta clase se lanzará en un hilo aparte y se
 * encargará de lanzar el sistema de audio, utilizando la <a href="http://0pointer.de/lennart/projects/pulseaudio/doxygen/simple.html">Simple API de Pulseaudio</a>.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class AnalizadorProxy{

public:
    /// Inicializa el búffer y las constantes.
    AnalizadorProxy();

    /// Constructor de copia - no se utiliza
    AnalizadorProxy(const AnalizadorProxy& copia);

    /// Búffer en el que se guardan los datos para realizar el análisis.
    tipoBuffer * miBuffer;

    /// Devuelve la frecuencia fundamental detectada, teóricamente
    /// correspondiente a la nota que está tocando la flauta.
    float notaActual();
    
    /// Método que se lanza en el hilo. 
    void operator()();

    /// Activa el análisis
    void lanzar();

    /// Detiene el análisis
    void detener();

    /// Libera los recursos y para el flujo de entrada.
    ~AnalizadorProxy(); //*/

private:

    /// Flujo de entrada de PulseAudio.
    pa_simple * sIn;

    /// Constante para pasar de índice del vector del búffer a frecuencia.
    float int_to_hz;

    /// Constante para pasar de frecuencia a índice del vector del búffer.
    float hz_to_int;

    /// Controla si se ha iniciado el análisis
    bool iniciado;

    /// Controla si se debe terminar el análisis.
    bool salir;

};

#endif /* _ANALIZADORPROXY_H_ */
