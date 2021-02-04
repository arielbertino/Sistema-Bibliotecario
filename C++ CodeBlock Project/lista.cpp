#include "assert.h"
#include "lista.h"
#include "libro.h"
#include <iostream>

template <typename elemento> lista<elemento>::lista()
{
        primero = 0;
        cursor = 0;
        ultimo = 0;
        contador = 0;
}

template <typename elemento> lista<elemento>::~lista()
{
    while (primero)
            eliminarNodo(primero);
}

template <typename elemento> void lista <elemento>::vaciarL() // LUCAS REVISA ESTO EL DESTRUCTOR DEBERIA HACER LO MISMO
{
    while (primero)
        eliminarNodo(primero);
    primero = 0;
    cursor = 0;
    ultimo = 0;
    contador = 0;
}

template <typename elemento> int lista<elemento>::cantElemL() const
{
    return contador;
}

template <typename elemento> bool lista<elemento>::perteneceL(elemento e) const
{
    nodo * aux = primero;       //podria llamar a una funcion privada a la clase a la cual le paso primero por copia
    while (aux!=0)  {           //y hacer si a esta ultima recursiva, algo muy similar a lo que planteo en los comentarios
    if (aux -> dato == e)       //de cantidad de elementos
        return true;
    aux = aux -> sig;
    }
    return false;
}

template <typename elemento> bool lista<elemento>::esVaciaL() const
{
    if (primero==0)
        return true;
    else return false;
}

template <typename elemento> void lista<elemento>::agregarPrincipio(const elemento & e)
{
    nodo * aux = crearNodo(e);          //hasta la practica de laboratorio del miercoles 20, no usabamos aux, usabamos 2 veces
    aux -> sig = primero;               //nuevonodo(e), entonces haciamos 2 nodos nuevos pensando que era el mismo
    primero = aux;                      //y perdiamos los punteros, estabamos haciendo 2 listas. eso nos explico FEDE
    if (ultimo == 0)                //contempla el caso especifico en el que se agrega el primer nodo
    {
        ultimo = primero;           //
        cursor = primero;
    }
}

template <typename elemento> void lista<elemento>::agregarFinal(const elemento & e)
{
    if (ultimo) /* != 0*/               //VER SI FUNCIONA COMO ENTENDI DEL LIBRO DE SCHILDT, true cualquier valor, false ==0...
    {   ultimo -> sig =  crearNodo(e);  //si estoy agregando el primer nodo, ultimo esta inicializado en 0 por lo que ultimo.sig no existe
        ultimo = ultimo -> sig;
        }
    else
        {
        ultimo =  crearNodo(e);
        primero = ultimo;       //contempla el caso especifico en el que se agrega el primer nodo
        cursor = ultimo;
        }
}

template <typename elemento> void lista<elemento>::agregarpos(const elemento & e, int p)
{                                               //ACLARACION: Si es una lista de n elementos, primero apunta a la posicion 0
    assert ((p>=0) && (p<=cantElemL()));        //y ultimo apunta a la poscion (n-1)
    nodo * aux = primero;
    if ((p>0) and (p<cantElemL()))    {
        while (p != 1){
                aux = aux -> sig;         //aux arranca en la pos 0 (primero) con este while me aseguro que que al terminar,
                p = p-1;                         //aux estara apuntando a la posicion anterior de en la que quiero agregar
            }
        nodo * aux2 = crearNodo(e) ;         //hasta la practica de laboratorio del miercoles 20, no usabamos aux2, usabamos 2 veces
        aux2 -> sig = aux -> sig;           //nuevonodo(e), entonces haciamos 2 nodos nuevos pensando que era el mismo
        aux -> sig = aux2;                  //y perdiamos los punteros, estabamos haciendo 2 listas
    }
    //else    {
        if (p==0)
            agregarPrincipio(e);
        if (p==cantElemL())
            agregarFinal(e);
   // }
}

template <typename elemento> void lista<elemento>::eliminarL(elemento e)
{
        nodo * aux = primero;
        if (perteneceL(e))
        {
            while (primero -> dato == e)
                {
                if (primero == cursor)                              //puede suceder que cursor sea primero
                    cursor = primero -> sig;                      //en ese caso cursor apunta al nodo siguiente, que seria el nuevo primero
                primero = primero -> sig;
                eliminarNodo(aux);      //podria haber mandado al puntero primero, pero el comportamiento es el mismo
                }
            while (aux->sig!=0)                                 //podemos elegir a que apunte cursor cuando se elimina su nodo (anterio o sig)
                if (aux->sig->dato == e)
                {
                    if (aux -> sig == cursor)               //puede suceder que estemos eliminando el nodo al que apunta cursor
                        cursor = aux;                         //en ese caso cursor apunta al nodo anterior.
                    eliminarNodo(aux ->sig);
                }
                else
                    aux = aux -> sig;         //si se sale del while es porque aux.sig es 0, por ende aux apunta al ultimo elemento
            ultimo = aux;              //en el caso que se elimine el ultimo elemento, perdemos el ultimo, entonces asignamos como nuevo ultimo aux
        }                        //si no se elimina ultimo, se esta diciendo que ultimo=ultimo, no afecta en nada a boca
        else
         cout << "el elemento ingresado aun no pertenece a la lista" << endl;
}

template <typename elemento> const elemento & lista<elemento>::iteracionL() //const
{                                                                          // porque ???
        assert (cursor!=0);
        nodo * aux = cursor;
        cursor=cursor->sig;
        return aux ->dato;
        //elemento e = cursor->dato;    cursor=cursor->sig;     return e;
        //que es menos costoso, una variable axiliar puntero o una int ???
}

template <typename elemento> void lista<elemento>::reiniciarcursor()
{                               //es necesario hacer un reiniciar cursor desp de que se finalice de recorrer la lista
    cursor = primero;           //porque cursor queda apuntando a NULL
}                 // podria agregar en iteracion un if (! cursor) cursor=primero, pero puede haber casos en los que quiera avanzar
        //hasta la posicion x iterando para ver que elemento hay en esa posicion y desp reiniciar, por lo que es necesaria esta funcion

template <typename elemento> const elemento & lista<elemento>::datoprimero()
{
    return primero -> dato;
}

template <typename elemento> const elemento & lista<elemento>::datocursor()
{
    return cursor -> dato;
}

template <typename elemento> const elemento & lista<elemento>::datoultimo()
{
    return ultimo -> dato;
}


template <typename elemento> void lista<elemento>::eliminarNodo(nodo * & l)
         {                                  //si lista no la pasaria por referencia perderia la conexion entre nodo y nodo->sig->sig
            nodo * aux = l;
            l = l -> sig;
            delete aux;
            contador--;     //elimino un elemento contador disminuye en 1
         }





/*template <typename elemento> const nodo lista<elemento>::nuevonodo(elemento e)        nodo tiene que ser publico
{                                                                                para poder usarlo como tipo de la funcion
    nodo * aux = new nodo;                          podemos usar private en el cpp??
    aux -> dato = e;                                creo que si pero ya lo hicimos en el .h y anda bien
    aux -> sig = 0;                                 despues de la primera entrega vemos
    return aux;
}
*/
template class lista<int>;
template class lista<unsigned int>;
template class lista<char>;
template class lista<float>;
template class lista<double>;

template class lista<libro*>;
