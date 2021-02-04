#include "Indice.h"


Indice::Indice()
{
    this->r=0;
}

Indice::~Indice()
{
    if (r)
        vaciarIndice(r);
}

 void Indice::vaciarIndice(nodoIndice * & cursor)  // CHE NO DEBERIA A LA VEZ QUE BORRA EL NODOD DEL INDICE BORRAR LOS PUNTEROS A LOS LIBRO O ESO LO HACE AUTOMATICAMENTE EL DESTRUSTOR DE CONJUNTO? ME QUEDO DANDO VUELTAS TE RECUERDO SON LAS 9:14 AM ESTOY DEL ORTO
        {
            if (cursor->izq)
                vaciarIndice(cursor->izq);
            if (cursor->der)
                vaciarIndice(cursor->der);
            delete cursor;
        }

void Indice::agregarLibro(libro * l)
    {
        string generosbuscados = l->obt_G();
        int  i=generosbuscados.length();      //i=tamanio del string
        int  j=0;
        while (j<i)     // es  un bucle muy sencillo que se podria haber resuelto con un for, su cometido es agregar
        {       //el mismo libro una vez en CADA genero y no una sola vez en un genero del estilo "fantasia historia ... terror"
            string generoindividual;
            while (j<i && generosbuscados[j]!=' ')
            {
                generoindividual=generoindividual+generosbuscados[j];
                j++;
            }
            nodoIndice * nodoDelGenero=nodoBuscado(generoindividual, r);
            nodoDelGenero->cursorLibro.agregarC(l);
            j++;
        }
}

void Indice::devolverGenero(string genero, conjunto<libro*> & resultado)
    {
        nodoIndice * nodoDelGenero=nodoBuscado(genero, r);
        nodoDelGenero->cursorLibro.reiniciarcursorC();
        for (int j=0; j<nodoDelGenero->cursorLibro.cantElemC(); j++)
        {
            resultado.agregarC(nodoDelGenero->cursorLibro.iteracionC());
        }
        if ((nodoDelGenero->cursorLibro.cantElemC())==0)
            cout << "No hay libros del genero elegido" << endl;
    }


Indice::nodoIndice * Indice::nodoBuscado(string generobuscado, nodoIndice* &nodoI)
{

    if (nodoI!=0)
    {
        if (nodoI->genero==generobuscado)
            return nodoI;
        else
        {
            if (nodoI->genero>generobuscado)
                return nodoBuscado(generobuscado, nodoI->izq);
            else
                return nodoBuscado(generobuscado, nodoI->der);
        }
    }
    else
    {
        nodoI=new nodoIndice;
        nodoI->genero=generobuscado;
        nodoI->der=0;
        nodoI->izq=0;
        return nodoI;
    }

}
/*
void Indice::imprimir()
{
    imprimirR(r);
}

void Indice::imprimirR(nodoIndice * i)
{
    if (i)
    {
        imprimirR(i->izq);
        cout << "Los libros del genero " << i->genero << " son:"<< endl;
        i->cursorLibro.reiniciarcursorC();
        for (int j=0; j<i->cursorLibro.cantElemC() ; j++)
        {
            cout << i->cursorLibro.iteracionC()->obt_T() << " // ";
        }
        cout << endl << endl;
        imprimirR(i->der);
    }
}*/
