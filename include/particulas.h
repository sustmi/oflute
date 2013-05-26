/**
 * @file particulas.h
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


#ifndef _PARTICULAS_H_
#define _PARTICULAS_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "animacion.h"

#include <ctime>
#include <vector>

#define lim 0.70
/**
 * @class Particula
 *
 * @brief Representa una partícula en un SistemaParticulas
 *
 * 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


struct Particula{

    /// Ángulo de eyección de la partícula.
    float angulo;
    
    /// Distancia máxima a la que llegará desde el punto de salida.
    float distancia;

    /// Tamaño relativo de la partícula.
    float tamanyo;

    /// Duración del movimiento
    int duracion;

    /// Imagen de la partícula.   
    boost::shared_ptr<Gosu::Image> imagen;

    /// Color de la partícula.
    Gosu::Color color;

    /// Posición en la animación.
    int pasoActual;

    /// Posición horizontal en el instante actual.
    float posX;

    /// Posición vertical en el instante actual.
    float posY;

    /// Variable temporal para ayudar en el cálculo de la posición.
    float posTemp;

    /// Variable temporal para ayudar en el cálculo del temaño.
    float coefTam;

    /// Genera una nueva partícula con los parámetros indicados.
    Particula(float angulo,
	      float distancia,
	      float tamanyo,
	      int duracion,
	      boost::shared_ptr<Gosu::Image> img,
	      Gosu::Color c) :
	angulo(angulo),
	distancia(distancia),
	tamanyo(tamanyo),
	duracion(duracion),
	imagen(img),
	pasoActual(0),
	posX(0),
	posY(0){

	color = Gosu::Color(Gosu::random(0, 1) * c.red(),
			    Gosu::random(0, 1) * c.green(),
			    Gosu::random(0, 1) * c.blue());
    }

    /// Actualiza la opsiciónposición y color de la partícula
    void update(){
	if(pasoActual != duracion) pasoActual ++;

	posTemp = Animacion::easeOutQuart(pasoActual, 0, 1, duracion); 

	if(posTemp >= lim){
	    color.setAlpha ( 255 * (1 - (posTemp - lim) / (1 - lim)));
	}else{
	    color.setAlpha(255);
	}

	coefTam = tamanyo * (1 - posTemp);
	
	posX = Gosu::offsetX(angulo, posTemp * distancia) 
	    - imagen -> width() * coefTam / 2;
	posY = Gosu::offsetY(angulo, posTemp * distancia) 
	    - imagen -> height() * coefTam / 2;
    }

    /// Pinta la partícula respecto de la posición de origen oX, oY.
    void draw(int oX, int oY){
	imagen -> draw(oX + posX, oY + posY, 7, coefTam, coefTam, color);//, Gosu::amAdditive);
    }

    /// Devuelve la vida de la partícula; 1 indica que ha terminado la animación
    float estado(){
	return (float)pasoActual / (float)duracion;
    }
};

/**
 * @class SistemaParticulas
 *
 * @brief Representa un sistema de partículas básico.
 *
 * Es un sistema simple, 2D, con dos tipos de partículas que se mueven
 * linealmente desde un punto central, desvaneciéndose.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class SistemaParticulas{
public:
    /**
     * @brief Crea un nuevo sistema de partículas
     *
     * @param g El destino gráfico.
     * @param n Cantidad de partículas.
     * @param d Duración del movimiento de cada partícula.
     * @param distancia Distancia máxima desde el centro del sistema.
     * @param escala Escala.
     * @param color Color.
     *
     */

    SistemaParticulas(Gosu::Graphics& g, unsigned n, unsigned d, 
		      unsigned distancia=200, float escala=1, 
		      Gosu::Color color = Gosu::Color::WHITE) : 
	g(g), cantidadParticulas(n), duracion(d), 
	distancia(distancia), escala(escala), color(color){

	activo = false;

	std::srand(std::clock());
	
	partc1 . reset(new Gosu::Image(g, L"media/particulas/partc1.png"));
	partc2 . reset(new Gosu::Image(g, L"media/particulas/partc2.png"));

//	vectorParticulas.resize(cantidadParticulas);

	for (size_t i = 0; i < cantidadParticulas; ++i)
	{
	    vectorParticulas.push_back(boost::shared_ptr<Particula>(nuevaPartc()));
	}
    }

    /// Genera y devuelve un puntero a una nueva partícula con
    /// parámetros aleatorios dentro de los indicados al generar el
    /// sistema.
    Particula * nuevaPartc(){
	return new Particula(Gosu::random(0,360),
			     Gosu::random(0, 1) * distancia,
			     Gosu::random(0, escala),
			     Gosu::random(0.1, 1) * duracion,
			     (Gosu::random(0,1)? partc1 : partc2),
			     color);
    }

    /// Actualiza la posición de las partículas, reiniciando las que ya han terminado su animación.
    void update(){
	for (unsigned i = 0; i < cantidadParticulas; ++i){
	    vectorParticulas[i] -> update();
	    if(activo)
		if(vectorParticulas[i] -> estado() > 0.5){
		    vectorParticulas[i].reset(nuevaPartc());
		}
	}	//*/
    
    }

    /// Cambia el estado del sistema.
    void toggle(){ activo = !activo; }

    /// Desactiva el sistema.
    void off(){ activo = false; }
    
    /// Activa el sistema.
    void on(){ activo = true; }

    /// Pinta las partículas.
    void draw(int origX, int origY){
	for (unsigned i = 0; i < cantidadParticulas; ++i){
	    vectorParticulas[i] -> draw(origX, origY);
	}

    }

private:
    /// Referencia al destino de dibujado de los gráficos.
    Gosu::Graphics & g;

    /// Cantidad de partículas
    unsigned cantidadParticulas;
 
    /// Duración de la animación de cada partícula
    unsigned duracion;

    /// Distancia máxima respecto al centro de cada partícula
    unsigned distancia;

    /// Escala (tamaño)
    float escala;

    /// Color
    Gosu::Color color;

    /// Shared pointers a las imágenes de las partículas, para cargarlos una vez por sistema en lugar de una vez por partícula.
    boost::shared_ptr<Gosu::Image> partc1, partc2;

    /// Contenedor de partículas.
    vector<boost::shared_ptr<Particula> > vectorParticulas;

    /// Indica si el sistema está activo o no.
    bool activo;

};

#endif /* _PARTICULAS_H_ */
