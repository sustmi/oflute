/**
 * @file crono.h
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

#ifndef _CLASETIMER_H_
#define _CLASETIMER_H_

#include <Gosu/Gosu.hpp>

#include <numeric>

/**
 * @class Crono
 *
 * @brief Temporizador/cronómetro basado en Boost::Timer pero adaptado para Gosu.
 *
 * Utiliza los temporizadores de Gosu (Gosu::milliseconds()) para controlar el tiempo.
 * El funcionamiento es sencillo:
 * \code
 * Crono T;
 * cout << "Tiempo transcurrido: " << T.elapsed() << "ms" << endl;
 * // Es posible pausar y reanudar el temporizador
 * T.pause();
 * // ...
 * T.resume();
 * // ...
 * // Lógicamente también podemos reiniciarlo
 * T.restart();
 * \endcode
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class Crono{

public:
	/// Crea un nuevo temporizador.
	Crono(){
		restart();
	}

	/// Pausa el temporizador, guardando el tiempo acumulado.
	void pause(){
		if(corriendo){
			corriendo = false;
			tiempoAcumulado += lecturaParcial();
		}
	}

	/// Reanuda el temporizador, partiendo de la posición por donde lo había dejado.
	void resume(){	
		corriendo = true;
		ultimoTiempoLeido = Gosu::milliseconds();
	}

	/// Reinicia el temporizador.
	void restart(){
		corriendo = true;
		ultimoTiempoLeido = Gosu::milliseconds();
		tiempoAcumulado = 0;
	}

	/// Devuelve el tiempo transcurrido desde el último reinicio del temporizador.
	unsigned long elapsed(){
		if(corriendo){
			return lecturaParcial() + tiempoAcumulado;
		}else{
			return tiempoAcumulado;
		}
	}
  
private:
	/// Devuelve el tiempo desde la última parada
	unsigned long lecturaParcial(){
		return Gosu::milliseconds() - ultimoTiempoLeido;
	}

	/// Guarda el momento en el que se inicia el temporizador.
	unsigned long ultimoTiempoLeido;  

	/// Guarda el tiempo acumulado entre paradas
	unsigned long tiempoAcumulado;

	/// Indica si el temporizador está corriendo o no
	bool corriendo;
};

#endif /* _CLASETIMER_H_ */
