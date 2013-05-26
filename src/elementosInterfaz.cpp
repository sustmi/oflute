#include "elementosInterfaz.h"

tConfTexto::tConfTexto ()
    : color (Gosu::Color(255,255,255,255)), 
      alineacion (Texto::alignIzq), 
      sombra (true), 
      opacidadSombra (80)
{}


tConfAnim::tConfAnim ()
    : inicialX (0), inicialY (0), inicialA (0), 
      finalX (0), finalY (0), finalA (255), 
      z (0), animar (Animacion::tNada), 
      wait (0), duracion (30)
{}

void Elemento::actualizarPosicion ()
{
    if(animar != Animacion::tNada){
	if(animar == Animacion::tAlpha){
	    currentAlpha = animacion -> get(0);
	    currentX = finalX;
	    currentY = finalY;
	}

	else if(animar == Animacion::tPos){
	    currentAlpha = finalAlpha;
	    currentX = animacion -> get(0);
	    currentY = animacion -> get(1);
	}

	else{
	    currentAlpha = animacion -> get(0);
	    currentX = animacion -> get(1);
	    currentY = animacion -> get(2);
	}
    }else{
	currentX = finalX;
	currentY = finalY;
	currentAlpha = finalAlpha;
    }
}

Elemento::Elemento(Animacion::atribAnim animar, double z)
    : animar(animar), finalX(0), finalY(0), finalAlpha(255), z(z), animacion(0)
{

}

void Elemento::setXY(int x, int y){
    finalX = x;
    finalY = y;
}

float Elemento::currX (){ 
    return currentX; 
}

float Elemento::currY (){ 
    return currentY; 
}

bool Elemento::clicked (int x, int y)
{
    return (x >= currentX && x <= currentX + getWidth() &&
	    y >= currentY && y <= currentY + getHeight());
}

void Elemento::draw ()
{
    if(animar != Animacion::tNada){
	animacion -> update();
    }
    actualizarPosicion();
    drawEnd(currentX, currentY, z, currentAlpha);
}

Elemento::~ Elemento ()
{
    if(animar != Animacion::tNada){
	delete animacion;
    }
}



