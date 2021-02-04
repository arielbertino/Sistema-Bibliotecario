#ifndef LIBRO_H
#define LIBRO_H
#include <string>
#include "lista.h"

using namespace std;

class libro
{
    public:
        libro();   //por si en algun momento necesito crear una estructura de libros, el compilaador necesita saber cuanto especio
        // necesita para crearlo.....estoo va en nereus ARIEL... NO NO VA EN NEREUS, EN NEREUS VA CON TODOS LOS PARAMETROS FEDE ES LA LEY
        ~libro();
        void mod_T (string titulo);
        void mod_A (string autor);
        void mod_P (string paginas);
        void mod_E (string editorial);
        void mod_G (string genero);
        void mod_C (string contenido);
        void mod_R (string ruta);
        string obt_R() const;
        string obt_T() const;
        string obt_A() const;
        string obt_P() const;
        string obt_E() const;
        string obt_G() const;
        string obt_C() const;

    private:
        string titulo, autor,  editorial, genero, contenido, paginas, ruta;
};

#endif // LIBRO_H
