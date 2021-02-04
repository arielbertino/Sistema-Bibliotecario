#ifndef CONJUNTO_H
#define CONJUNTO_H
#include "lista.h"
#include "libro.h"


template <typename elemento> class conjunto
{
    public:

        conjunto();
        ~conjunto();
        int cantElemC() const ;
        bool perteneceC(elemento e) const;
        void agregarC(const elemento & e);
        void eliminarC(elemento e);
        void vaciarC();
        void reiniciarcursorC ();
        /* Para implementar union, interseccion y diferencia intentamos hacer SOBRECARGA DE OPERADORES como se trata en
        el un manual de HERBERT SCHILDT, basandonos en el ejemplo de sobrecarga de operaciones binarias */
        /* a = b+c+d :  b llama a + con c como argumento, entonces el this apunta a b,
        despues (b+c) llama a + con d como argumento y el this se hace hacia (b+c)*/
        /*conjunto<elemento>*/void unionC(conjunto<elemento> & c, conjunto<elemento> & c_resultante);        //si no usaba parametros me destruia
        /*conjunto<elemento>*/void interseccionC(conjunto<elemento> & c, conjunto<elemento> & c_resultante);  //los conjuntos desp de usarlos
        /*conjunto<elemento>*/void diferenciaC (conjunto<elemento> & c, conjunto<elemento> & c_resultante);
        const elemento & iteracionC(); //const;      en un principio eran funciones de tipo cojunto pero cuando queria retornar la variable
                                                    //auxiliar donde guardaba el nuevo conjunto devolvia esta variable despues de eliminarla
                                            //porque al ser local a la funcion se destruye antes de terminar para liberar memoria
                    //PODRIA HACERLAS TIPO CONJUNTO, pasar como parametros los conjuntos con los que quiero operar, agregar en lo que apunte this
                    //this->agregarC(e) y hacer un return *this por lo que se devolveria el conjunto que llama a la funcion modificado
                    //entonces se podria hacer cresult.diferencia((c1.unionC(c2,c3)),c3)
                    //como esta codificado ahora se tiene que escribir (c2.union(c3,c1)).diferencia(c3,cresult)
                    //preguntar como es preferible
    private:

        lista<elemento> cursorC ;

};

#endif // CONJUNTO_H
