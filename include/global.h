/**
 * @file global.h
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


#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/// Define las diferentes alturas (Do, Re, Mi...) de cada nota.
enum t_altura { Silencio, Do5, Re5, Mi5, Fa5, Sol5, La5, Si5, Do6, Re6 };

/// Define las diferentes figuras (Negra, Corchea...) de cada nota.
enum t_figura { Redonda = 1, 
		Blanca = 2, 
		Negra = 4, 
		Corchea = 8, 
		Nulo = 16,
		Puntillo = 32};

/// Operador OR binario para poder utilizar el puntillo
inline t_figura operator | (t_figura A, t_figura B){
    return t_figura( (int) A | (int) B );
}

/// Devuelve la duración de una figura como un numérico
float durfig(t_figura t);

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#define ANCHO 800
#define ALTO 600
#define FULLSCREEN false
#define REFRESCO 20

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <map>
#include <iostream>

using namespace std;

#ifdef WIN32
#define _(x) x
#else
#include <libintl.h>
#include <locale.h>
#define _(x) gettext(x)
#endif

#endif /* _GLOBAL_H_ */
