/**
 * @file estadoCalibrarMicro.h
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

#ifndef _ESTADOCALIBRARMICRO_H_
#define _ESTADOCALIBRARMICRO_H_

#include "estado.h"
#include "elementosInterfaz.h"
#include "crono.h"

#include "analizador.h"
#include "configuracion.h"

#include <vector>

using namespace std;

class Juego;

/**
 * @class EstadoCalibrarMicro
 *
 * @brief Estado para calibrar el micrófono.
 *
 * Es una de las opciones del menú principal, y sirve para calcular
 * cuál es el umbral del micrófono cuando no hay sonido siendo
 * capturado, para poder tener una referencia.
 *
 * Al iniciar la captura, se le pide al usuario que guarde silencio y
 * se capturan sonidos a intervalos regulares, guardando el volumen en
 * cada momento. Al finalizar la captura, se hace la media de esos valores.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class EstadoCalibrarMicro : public Estado{
public:
    /// Crea un nuevo estado, cargando las imágenes 
    EstadoCalibrarMicro(Juego * p);

    /// Durante la captura, guarda los valores leídos para luego hacer
    /// el cálculo del valor medio.
    void update();

    /// Dibuja los elementos y textos en pantalla.
    void draw();

    /// Detecta pulsaciones de botones.
    void buttonDown (Gosu::Button boton);

    /// Destruye el estado
    ~EstadoCalibrarMicro();

private:
    /// Se utiliza para escribir en el fichero de configuración el
    /// valor calculado
    lectorConfiguracion archivoConf;

    /// Lleva a cabo el análisis y control de sonido.
    Analizador analizador;

    /// Se utiliza para calcular el tiempo que está capturando sonidos
    /// para hacer la media.
    Crono crono;

    //@{ 
    /// @name Elementos gráficos

    boost::scoped_ptr<ElementoImagen> imgMicro;
    boost::scoped_ptr<ElementoTexto> textoDesc;
    boost::scoped_ptr<ElementoTexto> cartelCapturando;

    //@}

    /// Vector de valores leídos para hacer la media.
    vector<float> valoresLeidos;

    /// Media calculada
    float mediaValores;

    /// Estado de la captura.
    /// 0 = La captura no se ha iniciado.
    /// 1 = Captura iniciada
    /// 2 = Captura terminada

    int estadoCaptura;
};

#endif /* _ESTADOCALIBRARMICRO_H_ */
