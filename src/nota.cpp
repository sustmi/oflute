/**
 * @file nota.cpp
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


#include "nota.h"

boost::shared_ptr<Gosu::Image> Nota::imgPuntillo;
boost::shared_ptr<Gosu::Image> Nota::imgFinal;

boost::shared_ptr<Gosu::Image> Nota::silRedonda;
boost::shared_ptr<Gosu::Image> Nota::silBlanca;
boost::shared_ptr<Gosu::Image> Nota::silNegra;
boost::shared_ptr<Gosu::Image> Nota::silCorchea;

boost::shared_ptr<Gosu::Image> Nota::figRedonda;
boost::shared_ptr<Gosu::Image> Nota::figBlanca;
boost::shared_ptr<Gosu::Image> Nota::figNegra;
boost::shared_ptr<Gosu::Image> Nota::figCorchea;

boost::shared_ptr<Gosu::Image> Nota::figBlancaInv;
boost::shared_ptr<Gosu::Image> Nota::figNegraInv;
boost::shared_ptr<Gosu::Image> Nota::figCorcheaInv;

void Nota::initImagenes(Gosu::Graphics & g){
    wstring cami = L"media/figuras/";

    imgPuntillo.reset(new Gosu::Image(g, cami + L"puntillo.png"));
    imgFinal.reset(new Gosu::Image(g, cami + L"figFinal.png"));

    silRedonda.reset(new Gosu::Image(g, cami + L"silRedonda.png"));
    silBlanca.reset(new Gosu::Image(g, cami + L"silBlanca.png"));
    silNegra.reset(new Gosu::Image(g, cami + L"silNegra.png"));
    silCorchea.reset(new Gosu::Image(g, cami + L"silCorchea.png"));
	
    figRedonda.reset(new Gosu::Image(g, cami + L"figRedonda.png"));
    figBlanca.reset(new Gosu::Image(g, cami + L"figBlanca.png"));
    figNegra.reset(new Gosu::Image(g, cami + L"figNegra.png"));
    figCorchea.reset(new Gosu::Image(g, cami + L"figCorchea.png"));
	
    figBlancaInv.reset(new Gosu::Image(g, cami + L"figBlancaInv.png"));
    figNegraInv.reset(new Gosu::Image(g, cami + L"figNegraInv.png"));
    figCorcheaInv.reset(new Gosu::Image(g, cami + L"figCorcheaInv.png"));	
	
}

Nota::Nota(Gosu::Graphics & g, t_altura altura, t_figura figura, float tiempos) : 
    altura(altura), figura(figura), tiemposDelante(tiempos){


    if(figura & Redonda){
        if(altura == Silencio){
            imagen = silRedonda;
        }else{
            imagen = figRedonda;
        }
    }

    else if(figura & Blanca){
        if(altura == Silencio){
            imagen = silBlanca;
        }else if(altura <= Si5){
            imagen = figBlanca;
        }else{
            imagen = figBlancaInv;
        }
    }

    else if(figura & Corchea){
        if(altura == Silencio){
            imagen = silCorchea;
        }else if(altura <= Si5){
            imagen = figCorchea;
        }else{
            imagen = figCorcheaInv;
        }
    }

    else if(figura & Negra){
        if(altura == Silencio){
            imagen = silNegra;
        }else if(altura <= Si5){
            imagen = figNegra;
        }else{
            imagen = figNegraInv;
        }
    }

    lDEBUG << Log::CON("Nota") 
           << boost::format(" %i %i %f") % altura % figura % tiempos;
}
    
float Nota::devolverDuracion(t_figura f){
    float dur = 0;
    if(f & Redonda){
        dur = 4;
    }else if(f & Blanca){
        dur = 2;
    }else if(f & Negra){
        dur = 1;
    }else if(f & Corchea){
        dur = 0.5;
    }
	
    if(f & Puntillo){
        dur += (dur / 2);
    }

    return dur;
	    
}

float Nota::devolverAltura(t_altura t, t_figura fig){
	
    if(t != Silencio){
        return (9 - t) * 18.6;
    }
    // Para los diferentes tipos de silencio
    else{
        if(fig == Redonda ){
            return 18;
        }

        else if(fig == Blanca){
            return 19;
        }

        else if(fig == Negra || fig == Corchea){
            return 18.6 * 5;
        }
        return 0;
    }
}

void Nota::updatePos(float x_){
    x = x_;
}

void Nota::draw(){
    if(x > -100){
        imagen -> draw(x, 162 + Nota::devolverAltura(altura, figura), 5);

        if(figura & Puntillo){
            imgPuntillo -> draw(x, 156 + Nota::devolverAltura(altura, figura), 5);
        }
    }
}

NotaFinal::NotaFinal(Gosu::Graphics & g, float tiempos) 
    : Nota(g, Do5, Nulo, tiempos){
}

void NotaFinal::draw(){
    imgFinal -> draw(x, 243, 5);
}
