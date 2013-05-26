#include "juego.h"
#include "estadoCalibrarMicro.h"
#include "log.h"
#include "global.h"

#include <string>
#include <cmath>

using std::string;

EstadoCalibrarMicro::EstadoCalibrarMicro (Juego * p) : Estado(p){
	lDEBUG << Log::CON("EstadoCalibrarMicro");

	imgMicro.reset(new ElementoImagen(padre -> graphics(), "media/micro.png", 4, Animacion::tAlpha));
	imgMicro -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad);
	imgMicro -> animacion -> set(0, 0, 255);
	imgMicro -> setXY(536, 236);

	string t1 = _("Para calibrar el micrófono, \npulse la tecla espacio y\n");
	t1 += _("guarde silencio durante\n2 segundos.");

	textoDesc.reset(new ElementoTexto(padre -> graphics(), t1, "media/fNormal.ttf",
	                                  40, 0xffbeda3b, Texto::alignCentro, true, 30, 
	                                  4, Animacion::tAlpha));
	textoDesc -> setXY(250, 200);
	textoDesc -> animacion = new Animacion(1, 20, Animacion::tEaseOutQuad, 15);
	textoDesc -> animacion -> set(0, 0, 255);

	cartelCapturando.reset(new ElementoTexto(padre -> graphics(), _("Calibrando. Guarde silencio."),
	                                         "media/fNormal.ttf",
	                                         50, 0xfffd7603, Texto::alignCentro, true, 30,
	                                         4, Animacion::tNada));
	cartelCapturando -> setXY(400, 400);

	estadoCaptura = 0;
    
}

void EstadoCalibrarMicro::update(){
	if(estadoCaptura == 1){
		valoresLeidos.push_back(analizador.volumenActual());

		if(crono.elapsed() > 2000){
			analizador.detener();
			estadoCaptura = 2;

			double suma = 0;
			foreach(float & f, valoresLeidos){
				suma += f;
			}
			mediaValores = suma / valoresLeidos.size();
	    
			lDEBUG << "Media: " << mediaValores;

			if(isnan(mediaValores)){
				cartelCapturando -> setText(_("Calibración errónea.\nPulse espacio para repetir la calibración."));
			}else{
				archivoConf.setSonidoLimite(mediaValores);
				cartelCapturando -> setText(_("Calibración completa.\nPulse escape para volver al menú."));
			}
		}
	}
}

void EstadoCalibrarMicro::draw(){
	imgMicro -> draw();
	textoDesc -> draw();

	if(estadoCaptura > 0){
		cartelCapturando -> draw();
	}
}

void EstadoCalibrarMicro::buttonDown(Gosu::Button boton){
	if(estadoCaptura != 1){
		if(boton == Gosu::kbSpace){
			lDEBUG << "Se inicia la calibración...";

			analizador.iniciar();

			crono.restart();
			estadoCaptura = 1;
		}
	}

	if(boton == Gosu::kbEscape && (estadoCaptura == 0 || estadoCaptura == 2)){
		padre -> cambiarEstado("estadoMenuSinFondo");
	}

	// controlSonido.detenerFlujo();
}

EstadoCalibrarMicro::~EstadoCalibrarMicro(){
	lDEBUG << Log::DES("EstadoCalibrarMicro");
}
