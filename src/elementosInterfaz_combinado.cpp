#include "elementosInterfaz.h"

ElementoCombinado::ElementoCombinado (Gosu::Graphics & g, Animacion::atribAnim animar, double z) 
    : Elemento (animar, z), g(g)
{
    lDEBUG << Log::CON("ElementoCombinado");
}


void ElementoCombinado::setTexto (string str, string rutaFuente, unsigned int tam, 
				  Gosu::Color color, unsigned int alineacion, 
				  bool sombra, int opacidadSombra, 
				  int tX, int tY)
{

    texto.reset(new Texto(g, str, rutaFuente,
			  tam, color, alineacion,
			  sombra, opacidadSombra));

    textoX = tX;
    textoY = tY;
}

void ElementoCombinado::setTexto (tConfTexto t, int x, int y)
{
    setTexto(t.cadena, t.rutaFuente,
	     t.tam, t.color,
	     t.alineacion, t.sombra, t.opacidadSombra,
	     x, y);

}

void ElementoCombinado::setText(string s){
    texto -> setText(s);
}
void ElementoCombinado::setTextoXY (int x, int y)
{
    textoX = x;
    textoY = y;
}

void ElementoCombinado::setImagen (string ruta)
{
    imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));
}

void ElementoCombinado::drawEnd (float x, float y, double z, int a)
{
    
    imagen -> draw(x,y,z,1,1,Gosu::Color(a,255,255,255));
    

    switch(texto -> getAlineacion()){
    case Texto::alignIzq:	
	texto -> draw(x + textoX, y + textoY, z + 0.1, a);
	break;

    case Texto::alignCentro:
	texto -> draw(x + imagen -> width() / 2 + textoX, y + textoY, z + 0.1, a);
	break;

    case Texto::alignDer:
	texto -> draw(x + imagen -> width() + textoX, y + textoY, z + 0.1, a);
	break;
    }

}

int ElementoCombinado::getWidth ()
{
    return imagen -> width();
}

int ElementoCombinado::getHeight ()
{
    return imagen -> height();
}
