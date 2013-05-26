/**
 * @file analizador.cpp
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


#include <iostream>
#include <iomanip>

// Para usar abs
#include <cmath>

// Para usar min_element
#include <algorithm>

#include <boost/ref.hpp>

#include "analizador.h"
#include "FFT.h"
#include "log.h"

using namespace std;

Analizador::Analizador(){
    lDEBUG << Log::CON("Analizador");

    detenido = true;

    notas[523.25] = Do5;
    notas[592.163] = Re5;
    notas[656.763] = Mi5;
    notas[699.829] = Fa5;
    notas[785.692] = Sol5;
    notas[893.628] = La5;
    notas[1001.29] = Si5;
    notas[1076.66] = Do6;
    notas[1195.09] = Re6;
}

t_altura Analizador::asociarNota(double frecuencia){
    std::map<double, t_altura> diferencias;
    std::map<double, t_altura>::iterator iter;

    for(iter = notas.begin();
        iter != notas.end();
        ++iter)
    {
        diferencias[abs(frecuencia - iter -> first)] = iter -> second;
    }
    
    iter = min_element(diferencias.begin(), diferencias.end());
    return iter -> second;
    
}


void Analizador::iniciar(){
    lDEBUG << "Analizador::iniciar...";
    detenido = false;

    proxy . lanzar();
    hilo.reset(new boost::thread(boost::ref(proxy)));
    lDEBUG << "Hilo lanzado!";
}

void Analizador::detener(){
    if(!detenido){
        detenido = true;
        lDEBUG << "Analizador::detener...";
        proxy . detener();
        hilo -> join();
    }
}

t_altura Analizador::notaActual(){
    if(lectorConfig.sonidoLimite() <= volumenActual()){
        float f = proxy . notaActual();
        if(f == 0){
            return Silencio;
        }else{
            return asociarNota(f);
        }
    }else{
        return Silencio;
    }
}

float Analizador::volumenActual(){
    return proxy . miBuffer -> lastVolume;
}
