#include "elementosInterfaz.h"

ElementoImagen::ElementoImagen (Gosu::Graphics & g, string ruta, double z, Animacion::atribAnim animar)
    : Elemento (animar, z)
{
    imagen.reset(new Gosu::Image(g, Gosu::widen(ruta)));
}

void ElementoImagen::drawEnd (float x, float y, double z, int a)
{
    //lDEBUG << "img @ " << x << "," << y << "," << z << "(" << a;
    imagen -> draw(x,y,z,1,1, Gosu::Color(a, 255, 255, 255));
}

int ElementoImagen::getWidth ()
{
    return imagen -> width();
}

int ElementoImagen::getHeight ()
{
    return imagen -> height();
}

