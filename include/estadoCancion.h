/**
 * @file estadoCancion.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * 
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


#ifndef _CANCION_H_
#define _CANCION_H_

#include <boost/shared_ptr.hpp>
#include "global.h"

#include <vector>
#include <string>

using namespace std;

#include "nota.h"
#include "crono.h"
#include "elementosInterfaz.h"
#include "particulas.h"

#include "analizador.h"

//class Juego;
class MarcadorPuntos;

/**
 * @class Cancion
 *
 * @brief Representa un estado en el que se está tocando una canción
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class Cancion{

public:
    /**
     * @brief Crea un nuevo estado con la canción indicada en la ruta.
     *
     * @param g Destino gráfico donde se pintarán las imágenes
     * @param ruta Ruta a la canción
     *
     */

    Cancion(Gosu::Graphics & g, string ruta);

    void lanzar();
    void update();
    void draw();
    void buttonDown(Gosu::Button boton);
    
    ~Cancion();

private:
    Analizador analizador;

    /// Representa el número de pulsos por minuto
    int bpm;

    /// Número de milisegundos por pulso, inversa de los bpm
    float milisegundosPorPulso;

    /// Cadena con el título de la canción
    string tituloCancion;

    /// Cadena con la descripción de la canción
    string descripcionCancion;

    /// Número de píxeles que en pantalla ocupa una negra
    int distanciaPulso;

    /// Distancia desde el lado izquierdo hasta el punto donde se tocan las notas
    int margenIzquierdo;

    /// Espera inicial antes de la primera nota
    float esperaInicial;

    /// Cronómetro temporizador 
    Crono temporizador, t2;

    /// Flag que indica si se ha lanzado el estado
    bool lanzado;

    /// Flag que indica si se están capturando puntos
    bool capturandoPuntos;

    /// Duración de la canción en milisegundos
    float duracionCancion;
    
    /// Offset de los puntos por acierto
    int incrementoDePuntos;

    /// Contador de puntos
    int puntos;

    /// Máximo de puntos para esta canción. Se utiliza para obtener el porcentaje final.
    int maximoPuntos;
    
    /// Conjunto de notas de la canción
    vector<boost::shared_ptr<Nota> > conjNotas;

    /// Guarda el número de notas cargadas inicialmente
    size_t numeroInicialNotas;

    /// Nota actualmente en la zona de reproducción
    t_altura notaEnLinea;

    /// Nota leída
    t_altura notaLeida;

    /// Marcador de puntos
    boost::scoped_ptr<MarcadorPuntos> marcadorFinal;

    /// Destino gráfico
    Gosu::Graphics & g;
    
    /// Ruta al fichero de la canción
    string ruta;

    /// Enumeración de estados
    enum {e1, e2, e3, e4};

    /// Estado actual
    int estadoActual;

    /// Imagen para resaltar la nota actual
    boost::scoped_ptr<Gosu::Image> resalteNotaActual;

    /// Imagen que representa la partitura
    boost::scoped_ptr<ElementoImagen> imagenPartitura;

    /// Imagen que representa el fondo de la barra de progreso
    boost::scoped_ptr<ElementoImagen> barraProgresoFondo;

    /// Imagen que representa la barra de progreso
    boost::scoped_ptr<Gosu::Image> barraProgreso;

    /// Imagen que representa la barra superior
    boost::scoped_ptr<ElementoCombinado> barraSuperior;

    /// Imagen que representa la barra inferior
    boost::scoped_ptr<ElementoCombinado> barraInferior;

    /// Referencia al sistema de partículas que aparece al acertar una nota.
    boost::scoped_ptr<SistemaParticulas> sistemaPartc;

    /// Parsea el fichero XML de la canción
    void parsear();
};

#endif /* _CANCION_H_ */
