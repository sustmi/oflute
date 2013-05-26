/**
 * @file estadoMenuCanciones.h
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


#ifndef _ESTADOMENUCANCIONES_H_
#define _ESTADOMENUCANCIONES_H_

#include "estado.h"

#include "elementosInterfaz.h"

#include <vector>
using std::vector;

class Juego;
class Cancion;

/**
 * @class EstadoMenuCanciones
 * @ingroup estadosPrincipales
 *
 * @brief Menú de elección de canción.
 *
 * Permite al usuario elegir la canción, y lanzarla.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class EstadoMenuCanciones : public Estado{
public:
    EstadoMenuCanciones(Juego * p);

    /// Gestiona las transiciones
    void update();

    /// Dibuja los elementos gráficos
    void draw();

    /// Responde a la entrada del usuario
    void buttonDown(Gosu::Button boton);

    /// Liberación de recursos
    ~EstadoMenuCanciones();

private:
    /// Diferentes estados de transición
	enum tTrans{ transIn, transHold, transToCancion, transCancion, transOut };

    /// Estado de transición actual
    tTrans estadoTransicion;

    /// Canción actualmente cargada
    boost::scoped_ptr<Cancion> cancion;
    
    /// Indica si hay una canción cargada
    bool cancionCargada;

    /// Imagen del logotipo
    boost::scoped_ptr<ElementoImagen> imgLogotipo;

    /// Imagen para el marco de selección
    boost::scoped_ptr<ElementoImagen> imgSeleccion;

    /// Imagen para el botón de arriba
    boost::scoped_ptr<ElementoImagen> imgBtnUp;

    /// Imagen para el botón de abajo
    boost::scoped_ptr<ElementoImagen> imgBtnDown;

    /// Imagen para el botón de OK
    boost::scoped_ptr<ElementoImagen> imgBtnOk;

    /// Subtítulo
    boost::scoped_ptr<ElementoTexto> txtSubtitulo;

    /// Botón volver
    boost::scoped_ptr<ElementoCombinado> btnVolver;

    /// Representa un elemento en el menú de selección de canciones
    class EntradaMenuCanciones{
    public:
        /**
         * @brief Crea una nueva entrada del menú de canciones
         *
         * @param g Destino gráfico
         * @param titulo Título de la canción
         * @param descripcion Descripción de la canción
         * @param ruta Ruta al fichero de la canción que representa la entrada
         * @param pos Posición del elemento en el menú
         */

        EntradaMenuCanciones(Gosu::Graphics & g, string titulo, 
                             string descripcion, string ruta, int pos);

        /// Pinta la entrada del menú en la posición indicada
        void draw();

        /// Desplaza el elemento en el menú el nńumero de posiciones indicado
        void mover(int a);

        /// Devuelve la ruta al fichero con la información de la canción
        string getRuta();

    private:

        // Destino gráfico
        Gosu::Graphics & g;

        /// Cadena con el título de la canción
        string titulo;

        /// Cadena con la descripción de la canción
        string descripcion;

        /// Cadena con la ruta al fichero de la canción
        string ruta;

        /// Posición de la entrada en el menú de las canciones
        int pos;

        /// Posición vertical de destino
        float y_final;

        /// Posición vertical en un instante dado
        float y_actual;

        /// Número de pasos que tendrá la animación
        float pasos;

        /// Posición inicial
        int posInicial;

        /// Separación entre las entradas del menú
        int saltoEntreEntradas;

        /// Referencia a la fuente para pintar el título
        boost::scoped_ptr<Gosu::Font> txtTitulo;

        /// Referencia a la fuente para pintar la descripción
        boost::scoped_ptr<Gosu::Font> txtDescripcion;
    };

    /// Conjunto de canciones listadas
    vector<boost::shared_ptr<EntradaMenuCanciones> > conjuntoCanciones;

    /// Indicador de la canción actualmente seleccionada
    int cancionSeleccionada;

    /// Lista las canciones
    void listarCanciones();
    
    /// Pasa a la canción siguiente, moviendo el menú.
    void listaSiguiente();

    /// Pasa a la canción anterior, moviendo el menú.
    void listaAnterior();

    /// Iniverte las animaciones de todos los elementos
    void invertirAnimaciones();
};

#endif /* _ESTADOMENUCANCIONES_H_ */
