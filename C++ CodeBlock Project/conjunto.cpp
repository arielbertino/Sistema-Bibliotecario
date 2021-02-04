#include "conjunto.h"
#include "lista.h"
#include "libro.h"

template <typename elemento> conjunto <elemento> ::conjunto()
{
     //   cursorC.lista(); // cursorC = 0; ?        es necesario? al declarar a cursorC como una lista se tendria que inicializar como tal
}

template <typename elemento> conjunto <elemento> ::~conjunto()
{
     //   cursorC.~lista();                     como tambien tendria que liberar la memoria que utilizo por si mismo
}

template <typename elemento> void conjunto <elemento> :: vaciarC()
{
    cursorC.vaciarL();
}


template <typename elemento> int conjunto<elemento>::cantElemC() const
{
      return cursorC.cantElemL();
}

template <typename elemento> bool conjunto<elemento>::perteneceC (elemento e) const
{
    return cursorC.perteneceL(e);
}

template <typename elemento> void conjunto<elemento>::agregarC(const elemento & e)
{
    if (! perteneceC(e))
        cursorC.agregarFinal(e);
}

template <typename elemento> void conjunto<elemento>::eliminarC(elemento e)
{
    cursorC.eliminarL(e);   //HAY QUE MEJORAR ESTO, el eliminarL recorre toda la lista buscando el elemento, eliminandolo en todas sus
}                           //ocurrencias, cuando el eliminarC al eliminar el elemento tendria que finalizar, con un return 0 por ejemplo


template <typename elemento> void conjunto<elemento>::reiniciarcursorC()
{
    cursorC.reiniciarcursor();
}

template <typename elemento> void conjunto<elemento>::unionC(conjunto <elemento> & c, conjunto<elemento> & c_resultante)
{
   // c_resultante = c;    //igualo el resultado al 2do conjunto, horrible! lo devolveria modificado (me di cuenta desp de 4 dias)
    this->reiniciarcursorC();               //por si el cursor del 1er conjunto no apunta a primero
    for (int i=0; i<(this->cantElemC()); i++) //este for recorre todo el conjunto que llame a union
        {
            elemento e = this->iteracionC();
            c_resultante.agregarC(e);
        }
    this->reiniciarcursorC();               //cursorL de cursorC quedaba apuntando a NULL
    c.reiniciarcursorC();
    for (int i=0; i<(c.cantElemC()); i++) //este for recorre todo el conjunto que llame a union
        {
            elemento e = c.iteracionC();      //no puedo preguntar por si pertenece iteracionC y despues hacer un agregar con IteracionC
            if ( ! c_resultante.perteneceC(e))        //porque estaria avanzando 2 veces, cosa que podria hacer saltar el assert de iteracionL
                c_resultante.agregarC(e);                     //ademas de saltearse un elemento para agregar
        }
    c.reiniciarcursorC();        //se recorrio todo el conjunto c y el cursorL de cursorC quedo apuntando a NULL
}


template <typename elemento> void conjunto<elemento>::interseccionC(conjunto <elemento> & c, conjunto<elemento> & c_resultante)
{               //recorro a c y agrego a c_resultante los elementos de c que tambien esten en el conjunto que llamo a interseccion
    this->reiniciarcursorC();                //??por si el cursor del 1er conjunto no apunta a primero. necesario??
    if (this->cantElemC() and c.cantElemC()) //si uno de los 2 conjuntos es vacio no tiene sentido recorrer el 2do porque la interseccion sera vacia
    {
        c.reiniciarcursorC();               //por si el cursor del 2do conjunto no apunta a primero
        for (int i=0; i<(c.cantElemC()); i++)  //recorro todo el conjunto c
        {
            elemento e = c.iteracionC();      //no puedo preguntar por si pertenece iteracionC y despues hacer un agregar con IteracionC
            if ( this->perteneceC(e))        //porque estaria avanzando 2 veces, entonces podria hacer saltar el assert de iteracionL
                c_resultante.agregarC(e);                     //ademas de saltearse un elemento para comparar
        }
    }
    c.reiniciarcursorC();           //se recorrio todo el conjunto c y el cursorL de cursorC quedo apuntando a NULL
}

template <typename elemento> void conjunto<elemento>::diferenciaC /* operator- */(conjunto <elemento> & c, conjunto<elemento> & c_resultante)
{                               //agrego a c_resultante todos los elementos del primer conjunto que no esten en el segundo. SHORT THE BALL
    if (this->cantElemC())
    {
        this->reiniciarcursorC();                //por si el cursor del 1er conjunto no apunta a primero
        for (int i=0; i<(this->cantElemC()); i++)
        {
            elemento e = this->iteracionC();
            if ( ! c.perteneceC(e))          //NO HACE LA DIRENCIA, AGREGA A RESULTANTE LOS QUE SE REPITEN EN AMBOS
                c_resultante.agregarC(e);    // LA IDEA ES CARGAR EL RESULTANTE CON LOS ELEMTOS DEL IMPLICITO Y DESPUES SI LOS ELEMENTOS DE C PERTENCEN A RESULTANTE ELIMINARLO DE RESULTANTE Y LISTO
        }
    }
    this->reiniciarcursorC();           //se recorrio todo el conjunto que llama a - y el cursorL de cursorC quedo apuntando a NULL
}

template <typename elemento> const elemento & conjunto<elemento>::iteracionC() // const
{
        return cursorC.iteracionL();
}

template class conjunto<int>;
template class conjunto<unsigned int>;
template class conjunto<char>;
template class conjunto<float>;
template class conjunto<double>;
template class conjunto<libro*>;
