#ifndef ARBOLB_H
#define ARBOLB_H
#include "lista.h"

template <typename elemento> class arbolB
{
    public:

        arbolB();
        ~arbolB();
        void agregarAbalanceado(const elemento & e);
        bool perteneceA(elemento e) const;
        int  cantElemA() const;
        int cantElemSubArbol (arbolB<elemento> subArbol) const;
        bool esVacioA() const;
        int  profundidadA() const;
        lista<elemento> crearListaFrontera();
        lista<elemento> crearListaArbol();

    private:
                //QUIERO PONER TODAS ESTAS FUNCIONES EN  EL CPP COMO PRIVADAS
        struct nodoAB
        {
            elemento dato;
            nodoAB *izq, *der;
        };

        nodoAB * cursorAB;

        nodoAB * crearNodoAB(elemento e)
        {                                        //en un principio quisimos poner la implementacion en el .cpp pero crearNodo quiere ser
            nodoAB * nodus =  new (nodoAB);         //ser privada a la clase y solo podemos cambiar el nivel de acceso a private en lista.h
            nodus->dato  = e;                                                       //por lo menos eso tenemos entendido
            nodus->izq   = 0;
            nodus->der   = 0;
            return nodus;
        }

        void vaciarArbol( nodoAB * & a )
        {
            if (a->izq!=0)
                vaciarArbol(a->izq);
            if (a->der!=0)
                vaciarArbol(a->der);
            delete a;
        }

        bool perteneceSubArbol(elemento e, nodoAB * subArbol) const
        {
            if (subArbol->dato == e)
                return true;
            else
                {
                if (subArbol -> izq)
                    return perteneceSubArbol(e, subArbol -> izq);
                if (subArbol -> der)
                    return perteneceSubArbol(e, subArbol -> der);
                }
            return false;
        }

        int cantElemSubArbol (nodoAB * subArbol) const
        {
            if (subArbol)
                return (1 + cantElemSubArbol(subArbol -> izq) + cantElemSubArbol(subArbol -> der));
            else
                return 0;
        }

        int profundidadSubArbol (nodoAB * subArbol) const
        {
            if (subArbol)
                if (cantElemSubArbol(subArbol -> izq) >= cantElemSubArbol(subArbol -> der) ) // SI EL ARBOL NO SE CARGA COMPLETANDO LOS
                    return (1 + profundidadSubArbol(subArbol -> izq));                         //NIVELES ESTA FUNCION NO SIEMPRE DEVUELVE
                else                                                                            //EL VALOR CORRECTO
                    return (1 + profundidadSubArbol(subArbol -> der));
            else
                return 0;
           /* if (subArbol)                                 //si el arbol se carga como yo espero se tendria que poder hacer asi la profundidad
                return (1 + profundidadSubArbol(subArbol -> izq));
            else
                return 0;*/
        }

        void crearListaFronteraSubArbol (nodoAB * subArbol, lista<elemento> & fronteraLista)
        {
            if ((subArbol -> izq) and (subArbol -> der))
                {
                    if (subArbol -> izq)
                        crearListaFronteraSubArbol(subArbol -> izq, fronteraLista);
                    if (subArbol -> der)
                        crearListaFronteraSubArbol(subArbol -> der, fronteraLista);
                }
            else
                fronteraLista.agregarFinal(subArbol -> dato);
        }

        void crearListaSubArbol (nodoAB * subArbol, lista<elemento> & arbolLista)
        {
            if (subArbol)
                {
                    if (subArbol -> izq)
                        crearListaSubArbol(subArbol -> izq, arbolLista);
                    arbolLista.agregarFinal(subArbol -> dato);
                    if (subArbol -> der)
                        crearListaSubArbol(subArbol -> der, arbolLista);
                }
        }

        /*     MI ORDEN PROPUESTO
                              8
                      4               12
                  2       6       10      14
                1   3   5   7   9   11  13  15

        1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 -...- 15
        */

};

#endif // ARBOLB_H
