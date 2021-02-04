#ifndef INDICE_H
#define INDICE_H
#include "iostream"
#include "libro.h"
#include "conjunto.h"

/* arbol indice por ahora es un ABB (arbol binario de busqueda) esta la posibilidad de hacerlo un AVL (Adelson-Velskii y Landis)
que seria un arbol binario de busqueda balanceado. por lo que lei es agregar una rotacion a derecha o izquierda
segun corresponda despues de cada agregar. pero esa rotacion puede ser simple o doble depende de los casos y el problema ya no son los punteros
sino como decidir cuando hacer una rotacion simple y cuando una doble ...
*/

// CHABON DEJATE DE JORDER MAN TE QUERES RE COMPLICAR AL PEDO CON EL ARBOL BALANCEADO Y LAS ROTACIONES ES ALPEDO NO LO PIDEN EN NINGUN LADO ESO
// SE ENTIENDE QUE TE DEVORASTE EL LIBRO DE SCHILDT PERO PARA UN POCO NI A MONTOTO SE LO PIDEN ESTO JEJE SIN ANIMOS DE OFENDER

/* agregar una variable privada que sea un conjunto de string, al que se le agregan los generos cuando se crea el arbol, por como se comporta
conjunto no va a haber generos repetidos. despues agregar 2 funciones publicas: una que dado un string devuelva un bool de tipo observadora
llamada pertenece y que use el pertenece de conjuntos. la otra funcion no se le pasan parametros y devuelve un string con todos los generos
del conjunto de generos
La funcionalidad de esto es proveer a la aplicacion la posibilidad de no agregar al arbol generos mal escritos por el usuario, y tambien
mostrar al usuario por pantalla los generos existentes de libros para no buscar algo que no hay */
class Indice
{
    public:

        Indice();
        ~Indice();
        void agregarLibro(libro * l);
        void devolverGenero(string genero, conjunto<libro*> & resultado) ;//const; no es observadora, cambiar TDA
/*en un principio devolver genero era una funcion del tipo conjunto de punteros a libros pero matias bien me dijo que esa implementacion
me iba a traer problemas, los mismos que me trajo el union/interseccion/diferencia en la clase conjuntos*/
  //      void imprimir();
/*la funcion imprimir la hicimos con matias para asegurarnos de que el arbolIndice guarda bien los libros antes de comenzar a hacer
el submenu de servicios o el mostrar resultados, la dejo comentada sabiendo que su implementacion seria una falta de criterio.
y esperando nunca tener que volver a usarla porque la aplicacion se comporta segun lo esperado por la catedra*/

    private:

        struct nodoIndice
            {
                conjunto<libro*> cursorLibro;
                string genero;
                nodoIndice *izq, *der;
            };

//        void imprimirR(nodoIndice * i);

        nodoIndice * r;
/*al igual que en arbolBinario de la primera entrega hice 2 funciones privadas a la clase que devuelven un nodoIndice
como el tipo de datos que devuelven es tambien privado a la clase no puedo hacer su implementacion en el cpp porque nodoIndice no es una clase
aceptada.. para los casos en lo que hay que agregar un nodo al arbol hice lo mismo que en el arbol binario: recorro por izquierda/derecha buscando
el elemento (genero en este caso) antes de avanzar pregunto si hay algo en el nodo al que voy a avanzar, cuando llego al caso en el que no hay
nada es porque llegue a la posicion donde tengo que agregar un nodo, entonces para que este nuevo nodo quede vinculado al arbol lo creo en el
puntero ->izq/->der del nodo padre. ya que si avanzo hasta llegar al puntero NULL y alli creo el nodo ese nodo no estaria vinculado al arbol
*/
        nodoIndice * nodoBuscado(string generobuscado, nodoIndice* &);
/*para hacer la funcion nodo buscado conte con la ayuda de matias, en un principio hice una funcion nodobuscado yo solo y la hice iterando,
sin usar recusion, matias me ayudo a hacer lo mismo pero haciendo la recursion de la misma. mi problema era que declaraba una variable
auxiliar dentro de la funcion que era igual a raiz y no podia volver a llamar la funcion porque volveria a tener aux=raiz, muy sencillo
fue solucionarlo llamando en primera instanca a la funcion nodo buscado con raiz pasado por referencia. Ademas cuando llamaba por izq o
der a la misma funcion no hacia el return. otro aspecto que cambie por recomendacion de matias es la funcion privada nuevo nodoIndice
que en un principio la hice pensando que se iba a usar en repetidas ocaciones pero a fin de cuentas hay una sola situacion en la que se
crea un nuevo nodo*/
// SI EL TRABAJO DEPENDIERA DE MI NO PONDRIA QUE NOS AYUDO OTRO AYUDANTE A NO SER QUE EN LA DEFENZA QUIERAS QUE NOS ROMPAN EL CULITO
// O SIMPLEMENTE QUE MARTIN SE CALIENTE NO NOS PONGA LA NOTA QUE NECESITAMOS PARA EL TP FINAL, DESDE YA QUEDA EN TUS MANOS SACAR O
// NO TODOS ESTOS COMENTARIO QUE DE HECHO SON LARGUISIMOS , DE ULTIMA PONGAMOSLO EN EL INFORME, REPITO SIN NOMBRAR A MATIAS, NOS AYUDO BOCHA
// PERO TAMPOCO SIRVE DE NADA FANFARRONEAR Y PERDER NOTA OK????

        void vaciarIndice( nodoIndice * & cursor );
};

#endif // INDICE_H
