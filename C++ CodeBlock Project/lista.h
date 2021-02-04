#ifndef LISTA_H
#define LISTA_H

#include "lista.h"
#include "libro.h"
#include <iostream>


template <typename elemento> class lista
{
    public:

        lista();
        ~lista();
        int cantElemL() const;         //seria correcto tener una variable privada a la clase de tipo int? la cual incrementamos en uno cada vez que se entra en un agregar, asi despues el cantElementos seria un simple return esa variable de complejidad O de 1...
        bool perteneceL(elemento e) const;
        bool esVaciaL() const;
        void agregarPrincipio(const elemento & e);
        void agregarFinal(const elemento & e);
        void agregarpos(const elemento & e, int p);
        void eliminarL(elemento e);
        void vaciarL();
        const elemento & iteracionL(); // const;??  //preguntar
        //  PARA OBTENER UN ELEMENTO EN UNA POSICION HAY QUE AVANZAR CURSOR CON UN FOR DE ITERACIONES
        // SI DESPUES QUIERO VOLVER A OBTENER UN ELEMENTO EN OTRA POSICION TENDRIA QUE REINICIAR CURSOR EN PRIMERO
        void reiniciarcursor ();
        const elemento & datoprimero();     //no creo que tengan uso en el programa final pero para ver si la clase se comporta como
        const elemento & datocursor();              //espero me son muy utiles
        const elemento & datoultimo();


    private:

        struct nodo
        {
            elemento dato;
            nodo * sig;
        };
//me quede con las ganas de hacer una clase nodo que tenga este mismo comportamiento pero agregarle una sobrecarga de operador monario
//de la forma nodo nodo::operador++() {dato=sig->dato; sig=sig->sig; return *this} con esto reemplazaria todos los cursor=cursor->sig;
//con ++cursor; o ++primero; o ++(el puntero que este usando)       vale aclarar que no se si funcionaria

        nodo* crearNodo(elemento e)
        {
            nodo * aux = new nodo;
            aux -> dato = e;
            aux -> sig = 0;
            contador++;
            return aux;
        }

        nodo* primero;
        nodo* cursor;
        nodo* ultimo;
        int contador;

        void eliminarNodo(nodo * & l);      //si lista no la pasaria por referencia perderia la conexion entre nodo y nodo->sig->sig
};

#endif // LISTA_H
