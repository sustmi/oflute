/**
 * @file entradaMenuCanciones.cpp
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

#include "estadoMenuCanciones.h"

EstadoMenuCanciones::EntradaMenuCanciones::EntradaMenuCanciones (Gosu::Graphics & g, string titulo, 
                                                                 string descripcion, string ruta, 
                                                                 int pos)
    : g(g), titulo(titulo), descripcion(descripcion), ruta(ruta), pos(pos){
	
    txtTitulo.reset(new Gosu::Font(g, L"media/fLight.ttf", 48, 0));
    txtDescripcion.reset(new Gosu::Font(g, L"media/fNormal.ttf", 26, 0));
    
    posInicial = 110;
    saltoEntreEntradas = 90;
    y_final = posInicial + pos * saltoEntreEntradas;
    y_actual = 600;
    pasos = 15;
}

void EstadoMenuCanciones::EntradaMenuCanciones::draw(){

    Gosu::Color colorTitulo(0xffacc827);
    Gosu::Color colorDesc(0xff6a8800);

    if(pos != 0){
        colorTitulo.setAlpha(100);
        colorDesc.setAlpha(100);
    }


    y_actual += (y_final - y_actual) / pasos;

    txtTitulo -> draw(Gosu::utf8ToWstring(titulo), 
                      440, 
                      y_actual, 5, 1, 1, colorTitulo);

    txtDescripcion -> draw(Gosu::utf8ToWstring(descripcion), 
                           440,
                           y_actual + 50, 
                           5, 1, 1, colorDesc);
}

void EstadoMenuCanciones::EntradaMenuCanciones::mover(int a){
    pos += a;
    y_final = posInicial + pos * saltoEntreEntradas;
}

string EstadoMenuCanciones::EntradaMenuCanciones::getRuta(){
    return ruta;
}
