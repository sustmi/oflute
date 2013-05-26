#include "elementosInterfaz.h"

ElementoTexto::ElementoTexto (Gosu::Graphics & g,
		   string str, string rutaFuente,
		   unsigned int tam, Gosu::Color color,
		   unsigned int alineacion, bool sombra, int opacidadSombra,
		   double z,
		   Animacion::atribAnim animar)
    : Elemento(animar, z)
{
    texto.reset(new Texto(g, str, rutaFuente, 
			  tam, color, alineacion, 
			  sombra, opacidadSombra));
}

void ElementoTexto::drawEnd (float x, float y, double z, int a)
{
    texto -> draw(x, y, z, a);
}

void ElementoTexto::setText (string s)
{
    texto -> setText(s);
}

int ElementoTexto::getWidth ()
{
    return 0;
}

int ElementoTexto::getHeight ()
{
    return 0;
}
