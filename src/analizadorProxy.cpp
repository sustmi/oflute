/**
 * @file analizadorProxy.cpp
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

#include <iomanip>
#include <fstream>
#include <cmath>

#include "analizadorProxy.h"

#include "kissfft/tools/kiss_fftr.h"

#define BUFSIZE 4096

AnalizadorProxy::AnalizadorProxy() : sIn(0), iniciado(false), salir(false){
	lDEBUG << Log::CON("AnalizadorProxy");
    
	sIn = NULL;

	miBuffer = new tipoBuffer;

	// Definimos dos constantes para hacer las conversiones desde 
	// posición del vector a frecuencia y viceversa
    
	//Para pasar de pos de vector a frecuencia, multiplicamos por 22050/2048
	int_to_hz = 22050./(BUFSIZE / 2.); // ~ 10.76660156250000000000000

	// Para pasar de frecuencia a posición de vector, multiplicamos por 2048/22050
	hz_to_int = (BUFSIZE / 2.)/22050.; // ~ 0.928798185941043083900226

	lDEBUG << VARV(int_to_hz) << "  " << VARV(hz_to_int);
};

AnalizadorProxy::AnalizadorProxy(const AnalizadorProxy& copia){
	lDEBUG << Log::CON("AnalizadorProxy Constructor de copia");
	int_to_hz = copia.int_to_hz;
	hz_to_int = copia.hz_to_int;
	iniciado = copia.iniciado;
	salir = copia.salir;
	miBuffer = new tipoBuffer;    
}

float AnalizadorProxy::notaActual(){
	return miBuffer -> mayores[0];
}


void AnalizadorProxy::lanzar(){
	iniciado = true;
}

void AnalizadorProxy::detener(){
	lDEBUG << "AnalizadorProxy::detener...";
	iniciado = false;
	salir = true;

	//pa_simple_free(sIn);

	lDEBUG << VARV(iniciado);
	lDEBUG << VARV(salir);
}

AnalizadorProxy::~AnalizadorProxy(){
	lDEBUG << Log::DES("AnalizadorProxy");

	if(sIn != 0)
		pa_simple_free(sIn);
	//pa_simple_free(sOut);

	if(miBuffer != 0){
		delete miBuffer;
		miBuffer = NULL;
	}
}



void AnalizadorProxy::operator()(){

	pa_sample_spec ss;
	ss.format = PA_SAMPLE_S16LE;
	ss.rate = 44100;
	ss.channels = 1;


	lDEBUG << "Tamaño del formato: " << pa_sample_size(&ss);



	int error;

	pa_buffer_attr atr;
	atr.maxlength = (uint32_t) -1;
	atr.prebuf =  (uint32_t) -1;
	atr.minreq =  (uint32_t) -1;
	atr.fragsize = 1;
	atr.tlength = 1;

	if (!(sIn = pa_simple_new(NULL, "oFlute", PA_STREAM_RECORD, NULL, 
	                          "record", &ss, NULL, &atr, &error))) {
		cerr << "ERROR" << endl;
	}

	/*
	  if (!(sOut = pa_simple_new(NULL, "nozin", PA_STREAM_PLAYBACK, NULL, 
	  "playback", &ss, NULL, &atr, &error))) {
	  cout << "ERROR" << endl;
	  }

	//*/

	cout << "Frame size: " << pa_frame_size(&ss) << endl
	     << "Sample size: " << pa_sample_size(&ss) << endl
	     << "Formato intermedio: " << sizeof(int16_t) << endl
	     << "Convers: " << sizeof(int) << endl;
    
	float magnitude;

	int limInf = 450 * hz_to_int;
	int limSup = 1500 * hz_to_int;
    
	cout << "limInf: " << limInf << endl
	     << "limSup: " << limSup << endl;

	kiss_fftr_cfg configFFT = kiss_fftr_alloc(BUFSIZE, 0, NULL, NULL);

	for(;;){
		if(iniciado){
			int16_t buf[BUFSIZE];
			float in[BUFSIZE];
			kiss_fft_cpx out[BUFSIZE / 2 + 1];

			float maxValue[] = {0,0,0};
			float maxPos[] = {0,0,0};
                
			if (pa_simple_read(sIn, buf, sizeof(buf), &error) < 0) {
				cerr << "ERROR al grabar" << endl;
			}

			// Dump al fichero y al vector de flotantes
			for (int i = 0; i < BUFSIZE; ++i)
			{
				in[i] = (float)buf[i];
			}

#if 1
			kiss_fftr(configFFT, in, out);
	    
			for(int i = limInf; i <= limSup; ++i){
				for (int j = 0; j < 3; j++)
				{
					magnitude = std::sqrt(std::pow(out[i].r,2) + std::pow(out[i].i, 2));
					if( magnitude > maxValue[j]){
						maxValue[j] =  magnitude;
						maxPos[j] = i;
						break;
					}
				}                   
			} 
	    

			miBuffer -> lastVolume = maxValue[0];
	    
			miBuffer -> mayores[0] = maxPos[0]  * int_to_hz;
			miBuffer -> mayores[1] = maxPos[1]  * int_to_hz;
			miBuffer -> mayores[2] = maxPos[2]  * int_to_hz;

			/*
			  int ancho = 18;
			  std::cout << '\xd' << "Datos:" 
			  << std::setw(ancho) << miBuffer -> mayores[0] 
			  << std::setw(ancho) << miBuffer -> mayores[1]  
			  << std::setw(ancho) << miBuffer -> mayores[2]  
			  << std::setw(ancho) << maxValue[0]
			  << std::flush;        
			//*/
	    
#endif
			/*

			// Dump al altavoz
			if (pa_simple_write(sOut, buf, sizeof(buf), &error) < 0) {
			cerr << "ERROR al reproducir" << endl;
			}

			//*/
	    

		}


		if(!iniciado && salir){
			return;
		}
	}

    
//*/
}
#if 0
#endif
