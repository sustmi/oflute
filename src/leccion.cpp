#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "global.h"

#include "leccion.h"
#include "log.h"

#include "pugixml.hpp"

Leccion::Leccion(Gosu::Graphics& g, string ruta) : g(g){
	lDEBUG << "Constructor de lección para el archivo >" << ruta << "<";

	// Creamos un nuevo objeto XML
	pugi::xml_document doc;
	pugi::xml_parse_result resultado;
	pugi::xml_node nodoActual, nodoVacio;
	pugi::xml_attribute atributo, atributoVacio;

	// Intentamos leer y cargar el fichero en el objeto XML
	resultado = doc.load_file(ruta.c_str());
	if(!resultado){
		lERROR << "#### ERROR al intentar abrir el fichero '" << ruta << "'.";
		/// @todo Arreglar el control de errores cuando no existe el XML
		throw 42;
	}

	nodoActual = doc.child("Lec").child("elementos");

	///////////////////////////////////////
	// Iteramos sobre las imágenes definidas en el XML (nodos hijos img)
	for(pugi::xml_node elemento = nodoActual.child("img");
	    elemento;
	    elemento = elemento.next_sibling("img")){

		// Leemos la ruta
		string ruta = elemento.attribute("src").value();
		
		// Posicióºn
		int x = elemento.attribute("x").as_int();
		int y = elemento.attribute("y").as_int();

		int animar, wait, duracion;

		if((atributo = elemento.attribute("animar")) == atributoVacio){
			animar = 1;
		}else{
			animar = atributo.as_int();
		}

		if((atributo = elemento.attribute("wait")) == atributoVacio){
			wait = 0;
		}else{
			wait = atributo.as_int();
		}

		if((atributo = elemento.attribute("duracion")) == atributoVacio){
			duracion = 40;
		}else{
			duracion = atributo.as_int();
		}	    
		
		// Atributo z, profundidad.
		double z = elemento.attribute("z").as_double();

		lDEBUG << "Imagen (" << ruta << ") @ " << x << "," << y;

	    
		// Creamos el elemento y lo introducimos en el vector de elementos
		boost::shared_ptr<Elemento> E
			(new ElementoImagen(g, ruta, z, ((animar==1)?Animacion::tAlpha:Animacion::tNada)));
		E -> setXY(x, y);
		if(animar == 1){
			E -> animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
			E -> animacion -> set(0, 0, 255);
		}

		elementos.push_back(E);
		//*/
	};

	//////////////////////////////////////
	// TEXTOS
	for(pugi::xml_node elemento = nodoActual.child("texto");
	    elemento;
	    elemento = elemento.next_sibling("texto")){

		string texto;
		texto = elemento.first_child().value();

		string rutaFuente;
		if((atributo = elemento.attribute("fuente")) == atributoVacio){
			rutaFuente = "media/fNormal.ttf";
		}else{
			rutaFuente = atributo.value();
		}

		// Posición
		int x = elemento.attribute("x").as_int();
		int y = elemento.attribute("y").as_int();
		int tam = elemento.attribute("tam").as_int();
		int align = elemento.attribute("align").as_int();
		int sombra = elemento.attribute("sombra").as_int();
		int opacSombra = elemento.attribute("opacSombra").as_int();

		int animar, wait, duracion;

		if((atributo = elemento.attribute("animar")) == atributoVacio){
			animar = 1;
		}else{
			animar = atributo.as_int();
		}

		if((atributo = elemento.attribute("wait")) == atributoVacio){
			wait = 0;
		}else{
			wait = atributo.as_int();
		}

		if((atributo = elemento.attribute("duracion")) == atributoVacio){
			duracion = 20;
		}else{
			duracion = atributo.as_int();
		}	    
		
		// Atributo z, profundidad.
		double z = elemento.attribute("z").as_double();

		int ca = elemento.attribute("ca").as_int();
		int cr = elemento.attribute("cr").as_int();
		int cg = elemento.attribute("cg").as_int();
		int cb = elemento.attribute("cb").as_int();
	    
		lDEBUG << "Texto (" << ruta << ") @ " << x << "," << y << " :";

	    
		boost::shared_ptr<Elemento> T
			( new ElementoTexto(g, texto, rutaFuente, tam, 
			                    Gosu::Color(ca, cr, cg, cb), align,
			                    sombra, opacSombra, z+3, 
			                    (animar == 1)? Animacion::tAlpha:Animacion::tNada) );

		T -> setXY(x, y);
		if(animar == 1){
			T -> animacion = new Animacion(1, duracion, Animacion::tEaseOutQuad, wait);
			T -> animacion -> set(0, 0, 255);
		}

		elementos.push_back(T);//*/

	} //*/
}

void Leccion::draw(){

	foreach(boost::shared_ptr<Elemento>& T, elementos)
	{
		T -> draw();
	}
}

