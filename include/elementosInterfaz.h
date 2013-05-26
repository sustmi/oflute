/**
 * @file elementosInterfaz.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * 
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

#ifndef _ELEMENTOSINTERFAZ_H_
#define _ELEMENTOSINTERFAZ_H_

#include <boost/scoped_ptr.hpp>
#include <boost/format.hpp>

#include <Gosu/Gosu.hpp>

#include "animacion.h"
#include "texto.h"
#include "log.h"

/**
 * @brief Bloque de configuración para un elemento de interfaz de cuadro de texto. 
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

struct tConfTexto
{
    /// Cadena a escribir.
    string cadena;

    /// Ruta de la fuente a usar.
    string rutaFuente;

    /// Tamaño de la fuente.
    unsigned int tam;

    /// Color de la fuente.
    Gosu::Color color;

    /// Alineación del texto
    Texto::tAlign alineacion;

    /// Sombra
    bool sombra;

    /// Opacidad de la sombra
    int opacidadSombra;

    /// Constructor básico, inicializa algunos valores por defecto.
    tConfTexto ();
};

/**
 * @brief Bloque de configuración para las animaciones. 
 *
 * Se utiliza una estructura para encapsular la configuración
 * de cada animación, en lugar de pasar los parámetros de inicialización al constructor.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
struct tConfAnim
{
    ///@{
    ///@name Valores iniciales

    /// Posición horizontal inicial
    int inicialX;

    /// Posición vertical inicial.
    int inicialY;

    /// Opacidad inicial
    int inicialA;
    ///@}
    
    ///@{
    ///@name Valores finales

    /// Posición horizontal final.
    int finalX;

    /// Posición vertical final.
    int finalY;

    /// Opacidad final.
    int finalA;

    /// Profundidad
    int z;
    ///@}


    /// Tipo de animación
    Animacion::atribAnim animar;

    /// Espera inicial de la animación
    int wait;

    /// Duración de la animación.

    int duracion;
    tConfAnim ();
};



/**
 * @class Elemento
 *
 * @brief Base para los elementos de la interfaz del menú.
 *
 * Ayuda a abstraer la animación de los elementos.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */
class Elemento
{
protected:
    /// Tipo de animación a realizar.
    Animacion::atribAnim animar;

    ///@{
    ///@name Atributos con el valor final
    int finalX;
    int finalY;
    int finalAlpha;
    double z;
    ///@}

    ///@{
    ///@name Atributos con el valor inicial
    int inicialX;
    int inicialY;
    int inicialAlpha;
    ///@}
    
    ///@{
    ///@name Atributos con el valor actual
    float currentX;
    float currentY;
    float currentAlpha;
    ///@}

    /// Inicializa el objeto animación. 
    void setupAnimacion (int wait, int duracion);

    /// Actualiza la posición actual según la animación definida.
    void actualizarPosicion ();

public:
    Animacion * animacion;

    Elemento(Animacion::atribAnim animar, double z);

    /// Devuelve el ancho del elemento. Cada subclase devolverá el ancho que corresponda.
    virtual int getWidth () = 0;

    /// Devuelve la altura del elemento. Cada subclase devolverá la altura que corresponda.
    virtual int getHeight () = 0;

    /// Devuelve la posición horizontal actual.
    float currX ();

    /// Devuelve la posición vertical actual.
    float currY ();

    /// Ajsuta las posiciones finales para elementos no animados
    void setXY(int x, int y);

    /// Comprueba si el elemento ha sido clickeado, basándose en la posición actual y el tamaño.
    bool clicked (int x, int y);

    /// Método de dibujado, actualiza la posición y llama al método drawEnd.
    void draw ();

    /// Método final de dibujado. Cada subclase debe implementarlo según sea conveniente.
    virtual void drawEnd (float x, float y, double z, int a) = 0;

    ~ Elemento ();
};


/**
 * Representa una imagen de la interfaz a partir de la clase base Elemento.
 */

class ElementoImagen : public Elemento
{
    /// Referencia a la imagen
    boost::scoped_ptr <Gosu::Image> imagen;

    /// Ruta a la imagen cargada
    string ruta;
public:

    /**
     * @brief Crea un nuevo ElementoImagen con los atributos indicados
     *
     * @param g Destino gráfico donde se pintará el elemento
     * @param ruta Ruta a la imagen cargada
     * @param z Profundidad de pintado de la imagen
     * @param animar Forma de animar el elemento
     *
     */

    ElementoImagen (Gosu::Graphics & g, string ruta, double z, Animacion::atribAnim animar);

    /**
     * @brief Pinta la imagen en las coordenadas indicadas
     *
     * @param x Coordenada horizontal
     * @param y Coordenada vertical
     * @param z Coordenada de profundidad
     * @param a Opacidad
     *
     */
    void drawEnd (float x, float y, double z, int a);

    /// Devuelve el ancho de la imagen
    int getWidth ();

    /// Devuelve el alto de la imagen
    int getHeight ();
};



/**
 * Representa un elemento que modela un marco de texto a partir de la base Elemento.
 */

class ElementoTexto : public Elemento
{
    /// Referencia al texto que se pintará.
    boost::scoped_ptr <Texto> texto;
public:

    /**
     * @brief Crea un nuevo elemento de texto con los parámetros indicados.
     *
     * @param g Destino gráfico
     * @param str Cadena de texto a pintar
     * @param rutaFuente Ruta de la tipografía a utilizar
     * @param tam Tamaño de la fuente
     * @param color Color de la fuente
     * @param alineacion Alineación del texto
     * @param sombra Flag que indica si hay que utilizar sombra o no.
     * @param opacidadSombra Indica la opacidad de la sombra
     * @param z Indica la profundidad de pintado del texto
     * @param animar Opciones de animación del texto
     **/

    ElementoTexto (Gosu::Graphics & g,
		   string str, string rutaFuente,
		   unsigned int tam, Gosu::Color color,
		   unsigned int alineacion, bool sombra, int opacidadSombra,
		   double z,
		   Animacion::atribAnim animar);

    /// Pinta el texto en la posición indicada
    void drawEnd (float x, float y, double z, int a);

    /// Cambia la cadena de texto a pintar
    void setText (string s);

    /// Devuelve el ancho del texto
    int getWidth ();

    /// Devuelve el alto del texto
    int getHeight ();
};



//////////////////////////////////////////////

/**
 * Representa una combinación de un texto sobre una imagen, modelados a partir
 * de la clase base Elemento.
 */

class ElementoCombinado : public Elemento
{
    /// Elemento de texto a pintar
    boost::scoped_ptr <Texto> texto;

    /// Posición horizontal del texto con respecto a la imagen
    int textoX;

    /// Posición vertical del texto con respecto a la imagen
    int textoY;

    /// Referencia a la imagen
    boost::scoped_ptr <Gosu::Image> imagen;

    /// Referencia al destino gráfico
    Gosu::Graphics & g;
public:
    /// Crea un nuevo elemento combinado, aunque es necesario utilizar los otros de métodos para 
    /// inicializar el resto de valores.
    ElementoCombinado (Gosu::Graphics & g, Animacion::atribAnim animar, double z);

    /**
     * @brief Inicializa los valores de la parte de texto del elemento.
     *
     * @param str Cadena de texto a pintar
     * @param rutaFuente Ruta de la tipografía a utilizar
     * @param tam Tamaño de la fuente
     * @param color Color de la fuente
     * @param alineacion Alineación del texto
     * @param sombra Flag que indica si hay que utilizar sombra o no.
     * @param opacidadSombra Indica la opacidad de la sombra
     * @param tX Indica la posición horizontal del texto con respecto a la imagen
     * @param tY Indica la posición vertical del texto con respecto a la imagen
     */

    void setTexto (string str, string rutaFuente, 
		   unsigned int tam, Gosu::Color color, 
		   unsigned int alineacion, 
		   bool sombra, int opacidadSombra, 
		   int tX, int tY);

    /**
     * @brief Inicializa los valores del texto, pero encapsulando la configuración
     *
     * @param t Objeto que encapsula la configuración del texto
     * @param x Posición horizontal del texto
     * @param y Posición vertical del texto
     */
    void setTexto (tConfTexto t, int x, int y);

    /**
     * @brief Modifica la posición del texto respecto a la imagen. 
     *
     * @param x Nueva posición horizontal
     * @param y Nueva posición vertical
     */
    void setTextoXY (int x, int y);

    /**
     * @brief Asigna la imagen al elemento, indicando la ruta.
     *
     * @param ruta Ruta al fichero de imagen a cargar
     */
    void setImagen (string ruta);

    /**
     * @brief Asigna la cadena de texto a pintar sobre la imagen
     *
     * @param s Cadena de texto a pintar
     */
    void setText(string s);

    /// Pinta el elemento combinado en las coordenadas y con la opacidad indicada
    void drawEnd (float x, float y, double z, int a);

    /// Devuelve el ancho del elemento combinado
    int getWidth ();

    /// Devuelve el alto del elemento combinado
    int getHeight ();
};
#endif /* _ELEMENTOSINTERFAZ_H_ */
