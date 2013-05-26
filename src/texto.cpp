/**
 * @file texto.cpp
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


#include "texto.h"

int Texto::dividirTexto(){
	
    string::size_type lastPos = texto.find_first_not_of('\n', 0);
    string::size_type pos     = texto.find_first_of('\n', lastPos);
	
    lineas.clear();
    while (string::npos != pos || string::npos != lastPos)
    {
        lineas.push_back(texto.substr(lastPos, pos - lastPos));
        lastPos = texto.find_first_not_of('\n', pos);
        pos = texto.find_first_of('\n', lastPos);
    }	
    return lineas.size();
}

Texto::Texto(Gosu::Graphics& graphics, 
             string texto, string rutaFuente, unsigned tam, Gosu::Color color,
             unsigned alineacion, 
             bool sombra, unsigned opSombra, float x, float y, float z) 
    : 
    graphics(graphics), texto(texto), tam(tam), color(color), 
    alineacion(alineacion), sombra(sombra), opacidadSombra(opSombra), 
    x(x), y(y), z(z), rutaFuente(rutaFuente){

    // Poblamos el vector de líneas
    poblarVectores();
}

void Texto::poblarVectores(){

    // Se divide el texto según los saltos de línea
    dividirTexto();

    // Cargamos la fuente
    fuente.reset(new Gosu::Font(graphics, Gosu::widen(rutaFuente), tam));

    // Valores del desplazamiento de la sombra del texto
    offsetShadow[0] = 1;
    offsetShadow[1] = 2;
}

void Texto::update(){ }

void Texto::setText(string s){
    texto = s;
    poblarVectores();
}

string Texto::getText(){
    return texto;
}

void Texto::draw(){
    // Por defecto, pinta el texto al máximo de opacidad
    drawAlpha(255);
}

void Texto::draw(float z_){
    // Asigna la profundidad
    z = z_;

    // Y llama al método de pintado por defecto
    draw();
}

void Texto::draw(float x_, float y_, float z_, int a_){
    // Asigna los valores indicados
    x = x_;
    y = y_;
    z = z_;

    // Llama al método de pintado según la opacidad indicada
    drawAlpha(a_);
}

void Texto::drawAlpha(int a){
	
    // El interlineado será igual al tamaño de la fuente más cinco píxeles
    int salto = tam + 5;

    // Contador de líneas
    short i = 0;

    BOOST_FOREACH(string& s, lineas)
    {
        // Coordenada horizontal local
        int destX = 0;

        // Si la alineación es a la izquierda, la X será la indicada
        if(alineacion == 1){
            destX = x;
        }
        // Si la alineación es a la derecha
        else if(alineacion == 3){
            // La posición horizontal será la posicíon indicada menos el ancho del texto
            destX = x - fuente -> textWidth(Gosu::widen(s));
        }

        // Para la alineación centrada
        else{
            // La posición horizontal será la indicada menos la mitad del ancho del texto
            destX = x - fuente -> textWidth(Gosu::widen(s)) / 2;
        }

        // Le asignamos al color el alfa indicado
        color.setAlpha(a);

        // Pintamos la línea de texto
        fuente -> draw(Gosu::widen(s), destX, y + salto * i, z + 0.1, 1, 1, color);
	    
        // Si la sombra está activada, la pintamos
        if(sombra){
            fuente -> draw(Gosu::widen(s), destX + offsetShadow[0], y + salto * i + offsetShadow[1],
                           z, 1, 1, Gosu::Color(opacidadSombra * a / 255, 0, 0, 0));
        }

        // Aumentamos el contador de líneas
        i++;
    } 
}
