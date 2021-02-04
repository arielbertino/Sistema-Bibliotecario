#include "arbolB.h"

template <typename elemento> arbolB<elemento>::arbolB()    //TERMINADO
{
    cursorAB = 0;
}

template <typename elemento> arbolB<elemento>::~arbolB()   //TERMINADO
{
    if (cursorAB)
        vaciarArbol(cursorAB);
}

template <typename elemento> void arbolB<elemento>::agregarAbalanceado(const elemento & e)
{
    if (cursorAB)
    {
        nodoAB * aux = cursorAB;              //NO HACE NADA ESTO COMO CALCULO LA COMPLEJIDAD DE ESTO???? BUENO MM LO DEJO ASINOMAS EN EL INFORME SON LAS 5:04 am EL ATAQUE DE ZOMBIE EMPIEZA A FLORECER
        while(aux)
        {
            if (cantElemSubArbol(aux -> izq) <= cantElemSubArbol(aux -> der) )      //en un principio era un arbol binario de busqueda
                if (aux -> izq)                                                 //eso lo hacia mas facil de pensar y hasta mas eficiente en todo
                    aux = aux->izq;                                         //pero tome en cuenta la posibilidad de que elemento sea una
                else                                                //estructura para la cual no este definida la operacion de comparar con <=
                    {                                           //y me acorde algo que hable con fede donde para otro problema me dijo que podia
                    aux -> izq = crearNodoAB(e);              //definir en la clase las funciones operator< operator>, etc
                    return;                                 //pero eso era mas complejo todavia. asi que me parecio preferible para ese caso en
                    }                                    //particular donde elemento es una estructura que no puedo decir si es menor o igual a otra
            else                                        //hacer un arbol equilibrado o balanceado, similar a un heap (en lo completo unicamente)
                if (aux -> der)                         //pero no ordenado por una inminente imposibilidad
                    aux = aux -> der;                   //si al recibir la 2da parte del trabajo veo que elemento se puede comparar
                else                                    //voy a preferir hacer el arbol binario de busqueda
                    {
                    aux -> der = crearNodoAB(e);        //si en la rama a la que me dijo la comparacion que tengo que acceder hay algun elemento
                    return;                         //avanzo por esa rama, cuando llegue a un punto donde quiera acceder a un nodo vacio
                    }                               //agrego en ese nodo, si en vez de hacer asi dijiera aux = crearnodoAB(e)
        }                                           //ese nuevo nodo no estaria en el arbol, porque nunca dije que aux->izq/der apunta a el
    }
    else
        cursorAB=crearNodoAB(e);            //agrego la raiz del arbol
}

template <typename elemento> bool arbolB<elemento>::perteneceA(/*nodoAB*miArbol,*/ elemento e) const    //TERMINADO
{
    /*if (!arbolB)
        return false;
    else
        if (arbolB->dato = e)                     // ALGO ASI SERIA MAS O MENOS
            return true;
        else
            return ((perteneceA(miArbol->izq, e) && perteneceA(miArbol->der));*/
    return perteneceSubArbol(e, cursorAB);  //ME SACO ESTO, PARA QUE PIJA SON LOS METODOS CON SUBARBOLES NO ENTIENDO
}


template <typename elemento> int arbolB<elemento>::cantElemA() const    //TERMINADO
{
    return cantElemSubArbol(cursorAB);
}

template <typename elemento> bool arbolB<elemento>::esVacioA()const   //TERMINADO
{
    if (cursorAB == 0)
        return true;
    else
        return false;
}

template <typename elemento> int arbolB<elemento>::profundidadA() const
{
    return profundidadSubArbol(cursorAB); // SIN IMPLEMENTAR
}

template <typename elemento> lista<elemento> arbolB<elemento>::crearListaFrontera()
{                                   //tengo que revisar a fondo el comportamiento de esta lista, se trae algo entre manos, no me termina de cerrar
    lista<elemento> fronteraLista;      //puede ser que tenga el mismo inconveniente que en conjunto ==> fronteraLista la declaro dentro de esta
    crearListaFronteraSubArbol(cursorAB, fronteraLista);    //funcion, por ende es inicializada en cero luego modificada y antes de terminar
    return fronteraLista;                                   //la funcion tiene que ser destruida para liberar la memoria
}                   //de ser asi crearListaFrontera es de tipo void y se le pasa fronteraLista por referencia

template <typename elemento> lista<elemento> arbolB<elemento>::crearListaArbol()
{                                   //el enunciado dice claramente listar, y hacer una lista es lo mas facil. pero no me parece lo mas eficiente
    lista<elemento> arbolLista;                 //en relacion a la memoria inutilmente utilizada, lo dejo para pensar mas adelante
    crearListaSubArbol(cursorAB, arbolLista);
    return arbolLista;                          //igualmente creo cometer el mismo error? que en la lista de la frontera
}

//NO ENTIENDO PORQUE ESTO ANDA. NO SE TENDRIA QUE VACIAR ARBOLISTA O FRONTERALISTA ANTES DE RETORNAR LA RESPECTIVA LISTA??
//AL PROVARLO 2 O 3 VECES MAS ENCUENTRO QUE DEVUELVE LA LISTA VACIA COMO TENIA ENTENDIDO QUE DEBIA SUCEDER
//OTRA POSIBLE SOLUCION
//      USO A ARBOLLISTA COMO VARIABLES PRIVADAS A LA CLASE
//      EN ARBOL LISTA HAGO UN AGREGAR FINAL LISTA EN CADA AGREGAR DEL ARBOL
//      A FRONTERA LISTA LA PODRIA HACER TAMBIEN UNA VARIABLE PRIVADA A LA CLASE ARBOL Y HACER LO MISMO QUE SE ESTA HACIENDO AHORA
//      (PASARSELA COMO PARAMETRO A CREARLISTASUBARBOL) PERO SOLO FUNCIONARIA LA PRIMERA VEZ QUE SE QUIERA CREAR LA LISTA FRONTERA
 //     YA QUE DESP SE LE AGREGARIA LA NUEVA LISTA FRONTERA A LA ANTERIOR, ESO SE SOLUCIONARIA HACIENDO UN ~lista() DE FRONTERA LISTA
 //     ANTES DE LLAMAR A LA FUNCION QUE LA CREA, PERO TENGO ENTENDIDO QUE NO SE PUEDE HACER
 //     LA MEJOR OPCION PARA LISTA FRONTERA CREO QUE SERIA NO USAR NINGUNA VARIABLE PRIVADA Y HACER LA FUNCION QUE LA CREA DE TIPO VOID
        //          PASANDOLE UNA LISTA VACIA COMO PARAMETRO Y EN ELLA CREAR LISTAFRONTERA

template class arbolB<int>;
template class arbolB<unsigned int>;
template class arbolB<float>;
template class arbolB<double>;
