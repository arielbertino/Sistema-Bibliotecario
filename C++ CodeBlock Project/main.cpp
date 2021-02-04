/*
    Proyecto práctico especial
    Análisis y Diseño de Algoritmos I - Cursada 2015
    Ejemplo de un proyecto que utiliza la biblioteca boost para el
    acceso al sistema de archivos.
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h> // esta libreria es la que nos permite usar Sleep()
#include "lista.h"
#include "conjunto.h"
#include "arbolB.h"
#include "libro.h"
#include "Indice.h"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/convenience.hpp"

using namespace std;

using namespace boost::filesystem;

void procesarArchivos(const path & ruta, Indice &i, conjunto<libro*> &todosLibros);
void procesarInformacionLibro(const path & ruta, Indice &i, conjunto<libro*> &todosLibros);
void mostrarMenu(char & opcion);
void mostrarSubMenu(char & opcion);
void refinarBusqueda(conjunto<libro*> &parcialLibros, Indice &i);
string pidoGeneroPorPantalla();
void mostrarResultado (conjunto<libro*> &parcialLibros);
void creoArchivo (conjunto<libro*> &parcialLibros);
void guardarLibros(ofstream & arch, conjunto<libro*> &parcialLibros);

int main(int argc, char *argv[])
{
    pidoruta:
    cout << "Ingrese ruta del directorio raiz de la base de libros que desee procesar" << "\n";
    string rutita;
    cin >>  rutita;
    path ruta(rutita);

    if (! exists(ruta) )  {
       cout << "\nNo se encuentra la ruta especificada: " << ruta.native() << "\n";
       system("PAUSE");
       system("cls");
       goto pidoruta;
       return 1;
    }

    Indice i;
    conjunto<libro*> todosLibros;

    procesarArchivos(ruta, i, todosLibros);
//    i.imprimir();
    char opcion;
    bool si=true;
    bool inicio=false;
    conjunto<libro*> parcialLibros;
    /*cout << "Mira como te hago esperar 15 segundos";
    Sleep(15000);*/
    while (si)
    {
        mostrarMenu(opcion);

        switch (opcion) {
            case '1':{
                cout << endl << " Usted ha seleccionado: Iniciar nueva busqueda." << endl;
                cout << "Se ha eliminado la busqueda parcial, y se ha iniciado una nueva" << endl;
                parcialLibros.vaciarC();
                inicio=true;
                break;
            }
            case '2':{
                cout << endl << " Usted ha seleccionado: Refinar busqueda." << endl;
                if (inicio)
                {
                 refinarBusqueda(parcialLibros, i);
                }
                else{
                    cout << "Primero inicie una nueva busqueda"<< endl;
                    }
                break;
            }
            case '3':{
                cout << endl << " Usted ha seleccionado: Mostrar Titulos del resultado parcial." << endl;
                if (inicio)
                    mostrarResultado(parcialLibros);
                else{
                    cout << "primero inicie una nueva busqueda";
                    }
                break;
            }
            case '4':{
                cout << endl << " Usted ha seleccionado: Generar archivo con el resultado (ruta, titulo y autor)"<<endl;
                if (parcialLibros.cantElemC())
                {
                    creoArchivo(parcialLibros);
                }
                else{
                    cout << "La busqueda parcial no contiene libros, debido a esto no se ha creado archivo alguno"<<endl;
                    }
                break;
            }
            case '5':{
                cout << "Hasta la proxima amiguitos";
                return 0;
                break;
            }
            default:{
                cout << "Opcion invalida, Ingresar otra opcion" << endl;
            }
            break;
            }
        system ("PAUSE");
        system("cls");
    }

}

/**
    Muestra la información de los archivos .txt del directorio indicado.
    Se invoca recursivamente con los subdirectorios encontrados durante la exploración.
*/
void procesarArchivos(const path & ruta, Indice &i, conjunto<libro*> &todosLibros) {
    directory_iterator iter_dir(ruta);
    directory_iterator fin_dir;

    while (iter_dir != fin_dir) {
        if (is_directory(*iter_dir)) {
//            cout << *iter_dir << " [Directorio]\n\n";
            procesarArchivos(iter_dir->path(), i, todosLibros);
        } else {
  //          cout << *iter_dir << " [Archivo] ";

            if (extension(*iter_dir) == ".txt") {
    //        	cout << "Archivo: " << *iter_dir << "\n";
            	procesarInformacionLibro(*iter_dir, i, todosLibros);
            }
        }
        iter_dir++;
    }
}

void procesarInformacionLibro(const path & ruta, Indice &i, conjunto<libro*> &todosLibros) {

    ifstream librito(ruta.string().c_str());
    libro* libromio = new libro();
    if (librito.is_open()) {

        libromio->mod_R(ruta.string());

        string linea;
        //titulo
        getline(librito, linea); //<titulo>...</titulo>
        //cout << linea.substr(8, linea.length() - 17) << endl;
        linea=linea.substr(8, linea.length() - 17);
        libromio->mod_T(linea);

        //autor
        getline(librito, linea); //<autor>...</autor>
      //  cout << linea.substr(7, linea.length() - 15) << endl;
        linea=linea.substr(7, linea.length() - 15);
        libromio->mod_A(linea);

        //editorial
        getline(librito, linea); //<editorial>...</editorial>
        //cout << linea.substr(11, linea.length() - 23) << endl;
        linea=linea.substr(11, linea.length() - 23);
        libromio->mod_E(linea);

        //paginas
        getline(librito, linea); //<paginas>...</paginas>
        //cout << linea.substr(9, linea.length() - 19) << endl;
        linea=linea.substr(9, linea.length() - 19);
        libromio->mod_P(linea);

        //genero
        getline(librito, linea); //<genero>...</genero>
        //cout << linea.substr(8, linea.length() - 17) << endl;
        linea=linea.substr(8, linea.length() - 17);
        libromio->mod_G(linea);

        //contenido
        getline(librito, linea); //<contenido>...</contenido>
        linea = linea.substr(11, linea.length());
        libromio->mod_C(linea);

        todosLibros.agregarC(libromio);
        i.agregarLibro(libromio);

        /*
        while (!librito.eof()) {
            string contenido;
            getline(librito, contenido);
            if (contenido != "</contenido>")
                linea += "\n" + contenido;
        }
        cout << linea << endl;
        */
        librito.close();
    }
}

void mostrarMenu(char & opcion)
{

    cout <<endl<< "Ingrese la opcion deseada del siguiente menu" << endl << endl;
    cout << "1. Iniciar nueva busqueda." << endl;
    cout << "2. Refinar busqueda." << endl;
    cout << "3. Mostrar resultado (titulo)." << endl;
    cout << "4. Generar archivo con el resultado (ruta, titulo y autor)." << endl;
    cout << "5. Salir." << endl;
    cin >> opcion;
}

void mostrarSubMenu(char & opcion2)
{

    cout << endl << "Ingrese la opcion deseada del Submenu de servicios" << endl << endl;
    cout << "1. Agregar al conjunto todos los libros etiquetados con un genero." << endl;
    cout << "2. Dejar en el conjunto todos los libros que no contengan un genero." << endl;
    cout << "3. Dejar en el conjunto todos los libros etiquetados con un genero." << endl;
    cout << "4. Volver sin hacer nada." << endl;
    cin >> opcion2;
}

string pidoGeneroPorPantalla()
{
    string aux;
    char aux2;
    pruebadeGOTO:
    cout << "Ingrese un genero para refinar su busqueda." << endl;
    cin >> aux;
    cout << "Usted ha ingresado: " << aux;
    pruebadeGOTO2:
    cout << endl << "Desea cambiar su eleccion (S/N)" <<endl ;
    cin >> aux2;
    switch (aux2) {
            case 'S':{
                cout << endl;
                goto pruebadeGOTO;
                break;
            }
            case 'N':{
                return aux;
                break;
            }
            default:{
                goto pruebadeGOTO2;
                break;
            }
    }

}

void refinarBusqueda(conjunto<libro*> &parcialLibros, Indice &i)
{
    char opcion2=0;
    mostrarSubMenu(opcion2);
    switch (opcion2) {
            case '1':{
                cout << endl << " Usted ha seleccionado: Agregar al conjunto todos los libros etiquetados con un genero." << endl;
                string genero = pidoGeneroPorPantalla();
                i.devolverGenero(genero, parcialLibros);
                break;
            }
            case '2':{
                cout << endl << " Usted ha seleccionado: Dejar en el conjunto todos los libros que no contengan un genero." << endl;
                string genero = pidoGeneroPorPantalla();
                conjunto <libro*> aux, aux2;
                i.devolverGenero(genero, aux);
                parcialLibros.diferenciaC(aux, aux2);
                parcialLibros.vaciarC();
                parcialLibros.unionC(aux2, parcialLibros);
                break;
            }
            case '3':{
                cout << endl << " Usted ha seleccionado: Dejar en el conjunto todos los libros etiquetados con un genero." << endl;
                string genero = pidoGeneroPorPantalla();
                conjunto <libro*> aux, aux2;
                i.devolverGenero(genero, aux);
                /*if (aux.cantElemC()==0)
                {
                    podria agregar un goto para no perder la busqueda
                }*/
                parcialLibros.interseccionC(aux, aux2);
                parcialLibros.vaciarC();
                parcialLibros.unionC(aux2, parcialLibros);/*
                if (parcialLibros.cantElemC()==0)
                    cout << "Se ha perdido la busqueda parcial" << endl;*/
                break;
            }
            case '4':{
                cout << endl << " Usted ha seleccionado: Volver sin hacer nada." << endl;
                break;
            }
            default:{
                system("cls");
                cout << "Opcion invalida, Ingresar otra opcion" << endl;
                refinarBusqueda(parcialLibros, i);
            }
            break;
    }
}

void mostrarResultado (conjunto<libro*> &parcialLibros)
{
    cout << "Los libros contenidos en su busqueda parcial son:"<< endl;
        parcialLibros.reiniciarcursorC();
        for (int j=0; j<parcialLibros.cantElemC() ; j++)
        {
            if (!(j%5))
                cout << endl;
            cout << parcialLibros.iteracionC()->obt_T() << "  //  ";
        }/*
        parcialLibros.reiniciarcursorC();
        cout << parcialLibros.iteracionC()->obt_R();*/
        cout << endl << endl;
}

void creoArchivo (conjunto<libro*> &parcialLibros)
{
    pidoruta:
    cout << "Ingrese un nombre para el archivo que se va a crear en la carpeta Resultados" << "\n";
    string rutita;
    cin.clear();
    cin >>  rutita;
    rutita += ".txt";
    path ruta(rutita);
    if (exists(ruta) )  {
       cout << "\nEl archivo: " << ruta.native() << " ya existe" << "\n";
       system("PAUSE");
       system("cls");
       goto pidoruta;
    }

    ofstream archSalida(rutita.c_str(), ios::trunc);
    if (archSalida.is_open()) {
        guardarLibros(archSalida, parcialLibros);
        archSalida.close();
    } else
        cout << "Error al crear el archivo de salida\n";


}
void guardarLibros(ofstream & arch, conjunto<libro*> &parcialLibros) {
    parcialLibros.reiniciarcursorC();
    for (int i = 0; i < parcialLibros.cantElemC(); i++) {
        libro* libroGuardar = parcialLibros.iteracionC();
        arch << "Ruta: " << libroGuardar->obt_R() << " // ";
        arch << "Titulo: " << libroGuardar->obt_T() << " // ";
        arch << "Autor: " << libroGuardar->obt_A() << "\n";
    }
}

