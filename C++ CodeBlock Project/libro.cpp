#include "libro.h"


libro::libro() { }

void libro :: mod_T (string titulo)
{
   this -> titulo = titulo;
}

void libro :: mod_A (string autor)
{
   this -> autor = autor;
}

void libro :: mod_P (string paginas)
{
   this -> paginas = paginas;
}

void libro :: mod_E (string editorial)
{
   this -> editorial = editorial;
}

void libro :: mod_G (string genero)
{
   this -> genero = genero;
}

void libro :: mod_C (string contenido)
{
   this -> contenido = contenido;
}

void libro :: mod_R (string ruta)
{
   this -> ruta = ruta;
}

libro::~libro() {   }

string libro::obt_R() const { return ruta;}
string libro::obt_T() const { return titulo;}
string libro::obt_A() const { return autor;}
string libro::obt_P() const { return paginas;}
string libro::obt_E() const { return editorial;}
string libro::obt_G() const { return genero;}
string libro::obt_C() const { return contenido;}
