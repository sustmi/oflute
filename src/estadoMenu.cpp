#include "estadoMenu.h"
#include "juego.h"
#include "log.h"

#include <cmath>

int posFinalesY[] = {281, 332, 383, 434, 485, 589 };

EstadoMenu::EstadoMenu (Juego * p) : Estado(p), sinDemoraInicial(false){
    lDEBUG << Log::CON("EstadoMenu");
    p -> setCaption(L"oFlute .:. Menú principal");

}

void EstadoMenu::lanzar(){
    lanzado = true;
    estadoAnim = eBOTONESIN;
 
    // Poblamos el puntero de las imágenes
    logoCusl.reset(new Gosu::Image(padre -> graphics(), L"media/secMenu/logo-cusl4.png"));
    logotipo.reset(new Gosu::Image(padre -> graphics(), L"media/secMenu/logoMenu.png"));
    barraRoja.reset(new Gosu::Image(padre -> graphics(), L"media/secMenu/barraInferior.png"));

    int duracionSalidaBotones = 50;
    
    int demoraInicial;
    if(sinDemoraInicial){
	demoraInicial = 0;
    }else{
	demoraInicial = 50;
    }
    
    // Inicializamos las animaciones
    int pInit = 290;
    for (int i = 0; i < 6; ++i)
    {
	posFinalesY[i] = pInit + i*51;
	if(i == 5) posFinalesY[i] = 589;
	animaciones[i].reset(new Animacion(1, duracionSalidaBotones, Animacion::tEaseOutQuart, demoraInicial + i * 10));
	animaciones[i] -> set(0, 600, posFinalesY[i]);

    }

    animLogoCusl.reset(new Animacion(1, duracionSalidaBotones, Animacion::tEaseOutBack, 40 + demoraInicial));
    animLogoCusl -> set(0, 820, 590);

    animLogotipo.reset(new Animacion(1, duracionSalidaBotones, Animacion::tEaseOutQuart, 10 + demoraInicial));
    animLogotipo -> set(0, 0, 255);

    // Inicializamos los botones del menú

    btn1.reset(new BotonMenu(padre -> graphics(), _("Analizador de notas"), Gosu::Color(255,3,69,90)));  // _("PRUEBA")
    btn2.reset(new BotonMenu(padre -> graphics(), _("Canciones"), Gosu::Color(255,34,139,114)));

    btn3.reset(new BotonMenu(padre -> graphics(), _("Lecciones"), Gosu::Color(255,188,216,56)));
    btn4.reset(new BotonMenu(padre -> graphics(), _("Calibrar micrófono"), Gosu::Color(255,245,215,19)));
    btn5.reset(new BotonMenu(padre -> graphics(), _("Salir"), Gosu::Color(255,250,115,0), 95));
}

void EstadoMenu::update(){
    if(!lanzado) 
	return;

    // 1: Sacando botones
    if(estadoAnim == eBOTONESIN){
	int j = 0;
	for (int i = 0; i < 6; ++i)
	{
	    animaciones[i] -> update();
	    if(animaciones[i] -> get(0) == posFinalesY[i]) ++j;
	}

	if(j == 5){
	    lDEBUG << "** Los botones llegaron a su lugar" ;
	    estadoAnim = eESTATICO;
	}
    }
    
    else if(estadoAnim == eESTATICO){
	// Los botones están en su sitio, parados
	
    }

    // 3: Inicialización del guardado de los botones, se reinician las animaciones
    
    else if(estadoAnim == eBOTONESOUT){
	float ultimaPos;
	for (int i = 5; i > -1; --i)
	{
	    ultimaPos = animaciones[i] -> get(0);
	    animaciones[i] . reset(new Animacion(1, 30, Animacion::tEaseInQuart, (5-i) * 10));
	    animaciones[i] -> set(0, ultimaPos, 600);

	}

	animLogoCusl . reset(new Animacion(1, 15, Animacion::tEaseInQuart));
	animLogoCusl -> set(0, 590, 820);

	animLogotipo . reset(new Animacion(1, 40, Animacion::tLinear, 10) );
	animLogotipo -> set(0, 255, 0);

	estadoAnim = eANIMOUT;
    }

    else if(estadoAnim == eANIMOUT){
	
	for (int i = 0; i < 6; ++i)
	{
	    animaciones[i] -> update();
	}

	if(animaciones[0] -> finished() &&
	   animaciones[1] -> finished() &&
	   animaciones[2] -> finished() &&
	   animaciones[3] -> finished() &&
	   animaciones[4] -> finished() &&
	   animaciones[5] -> finished() &&
	   animLogoCusl -> finished() &&
	   animLogotipo -> finished() )
	{
	    estadoAnim = eANIMEND;
	    lDEBUG << "** Los botones se escondieron." ;	    
	}
	
	
    }

    else if(estadoAnim == eANIMEND){
	padre -> cambiarEstado(estadoDestino);
    }
}

void EstadoMenu::draw(){
    if(!lanzado) 
	return;

    btn1 -> draw(0, animaciones[0] -> get(0), 2); 
    btn2 -> draw(0, animaciones[1] -> get(0), 3);
    btn3 -> draw(0, animaciones[2] -> get(0), 4);
    btn4 -> draw(0, animaciones[3] -> get(0), 5);
    btn5 -> draw(0, animaciones[4] -> get(0), 6);
    barraRoja -> draw(0, animaciones[5] -> get(0), 7);

    animLogoCusl -> update();
    animLogotipo -> update();

    logoCusl -> draw(animLogoCusl -> get(0), 10, 4);
    logotipo -> draw(330, 35, 30, 1,1, Gosu::Color(animLogotipo -> get(0), 255, 255, 255));

}

void EstadoMenu::buttonDown(Gosu::Button boton){
    if(!lanzado) 
	return;
    

    if(boton == Gosu::kbEscape){
	lDEBUG << "Escape pulsado " << VARV(estadoAnim);
	if(estadoAnim < eESTATICO){
	    for (int i = 0; i < 6; ++i)
	    {
		animaciones[i] -> end();
	    }
	    animLogoCusl -> end();
	    animLogotipo -> end();
	    estadoAnim = eESTATICO;
	}

	else if(estadoAnim < eBOTONESOUT){
	    estadoDestino = "salir";
	    estadoAnim = eBOTONESOUT;
	} //*/

	else if(estadoAnim < eANIMEND){
	    estadoAnim = eANIMEND;
	    for (int i = 0; i < 6; ++i)
	    {
		animaciones[i] -> end();
	    }
	    animLogoCusl -> end();
	    animLogotipo -> end();
	}
    }

    int x = padre -> input().mouseX();
    int y = padre -> input().mouseY();
	
    if((btn1 -> clicked(x,y) && (boton == Gosu::msLeft)) || ((boton == Gosu::kb1) || (boton == Gosu::kbNumpad1))){
	estadoDestino = "estadoAnalizador";
	estadoAnim = eBOTONESOUT;
    }
    
    else if((btn2 -> clicked(x,y) && (boton == Gosu::msLeft)) || ((boton == Gosu::kb2) || (boton == Gosu::kbNumpad2))){
	estadoDestino = "estadoMenuCanciones";
	estadoAnim = eBOTONESOUT;
    }
    
    else if((btn3 -> clicked(x,y) && (boton == Gosu::msLeft)) || ((boton == Gosu::kb3) || (boton == Gosu::kbNumpad3))){
	estadoDestino = "estadoMenuLecciones";
	estadoAnim = eBOTONESOUT;
    }
    
    else if((btn4 -> clicked(x,y) && (boton == Gosu::msLeft)) || ((boton == Gosu::kb4) || (boton == Gosu::kbNumpad4))){
	estadoDestino = "estadoCalibrar";
	estadoAnim = eBOTONESOUT;
    }
    
    else if((btn5 -> clicked(x,y) && (boton == Gosu::msLeft)) || ((boton == Gosu::kb5) || (boton == Gosu::kbNumpad5))){
	estadoDestino = "salir";
	estadoAnim = eBOTONESOUT;
    }

}

EstadoMenu::~EstadoMenu(){
    lDEBUG << Log::DES("EstadoMenu");
}//*/
