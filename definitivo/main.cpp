#include <iostream>
#include <vector>
#include "Usuario.h"
#include "Plataforma.h"
#include "Administrador.h"
#include "Artista.h"
#include "Asistente.h"
#include "Evento.h"
using namespace std;
int main()
{
    Plataforma p;
    Localizacion* asturias = new Localizacion ("asturias", "monte", 100);
    Localizacion* huelva = new Localizacion ("huelva", "desierto", 900);
    Localizacion* albacete = new Localizacion ("albacete", "ciudad", 700);
    Localizacion* galicia = new Localizacion ("galicia", "monte", 100);

    p.localizaciones.push_back(asturias);
    p.localizaciones.push_back(huelva);
    p.localizaciones.push_back(albacete);
    p.localizaciones.push_back(galicia);

    Evento* aquasella = new Evento("aquasella", asturias, 20250601, 20.50, 10, false);
    Evento* monegros = new Evento("monegros", huelva, 20251225, 50, 30, true);
    Evento* ortigueira = new Evento("ortigueira", albacete, 20261005, 10, 20, false);
    Evento* riverland = new Evento("riverland", albacete, 20251005, 50, 50, false);

    p.eventos.push_back(aquasella);
    p.eventos.push_back(monegros);
    p.eventos.push_back(riverland);
    p.eventos.push_back(ortigueira);

    p.usuarios.push_back(new Artista("kaydy", "1234", "kaydy cain", "trap", "tengo una peluqueria", {aquasella, monegros}));
    p.usuarios.push_back(new Artista("badgyal", "1234", "badgyal", "requeton", "reina de españa", {riverland}));
    p.usuarios.push_back(new Artista("metrika", "1234", "metrika", "trap", "lipcombo", {ortigueira, monegros}));
    p.usuarios.push_back(new Artista("omar", "1234", "omar montes", "requeton", "ola", {aquasella, monegros, riverland}));
    //haacer un push_back en reservados
    p.usuarios.push_back(new AsistenteNormal("pepe", "1234", "5555", 100, 0.0f, {}, false));
    p.usuarios.push_back(new AsistenteVip("lola", "1234", "6666", 500, 0.0f, {}, true));
    p.usuarios.push_back(new Administrador("ramoncin", "1234"));

    // p.verEstadisticas(p.usuarios, p.eventos, p.localizaciones);

    p.alpha();


    // p.filtrarEvento(p.eventos);
    // p.filtrarArtista(p.usuarios);
    // p.filtrarLocalizacion(p.localizaciones);


    // p.recaudación(0);
    // p.guardarEventos(p.eventos);
    // p.guardarUsuarios(p.usuarios);
    // p.guardarLocalizaciones(p.localizaciones);

    // int opcion, opcionInicial;
    // bool bien = false;
    // Plataforma web;

    // while (!bien)
    // {
    //     cout << "Opciones:\n1.Registrarse\n2.Iniciar sesión\n3.Salir"<<endl;
    //     cin >> opcionInicial;
    //     if(opcionInicial >= 1 && opcionInicial <= 3)
    //         bien = true;
    //     cout << "Opción inválida, vuelva a intentarlo: " << endl;
    // }
    // if(opcionInicial == 1)
    //     bool registrado = web.registro(web.usuarios);
    // //esta funcion todavia no existe
    // else if(opcionInicial == 2)
    // {
    //     if(!registrado)
    //     {
    //         cout << "No puedes iniciar resión si no te has registrado" << endl;

    //     }
    //     web.usuarioActual = web.login(web.usuarios);
    //     while(!web.usuarioActual)
    //         web.usuarioActual = web.login(web.usuarios);
    //     while(web.usuarioActual)
    //     {
    //         web.mostrarMenu();
    //         cin >> opcion;
    //         web.ejecutarOpcion(opcion);
    //         if (opcion == 0) //darse de baja
    //             web.usuarioActual = nullptr;
    //     }
    //     cout << "Saliendo de la plataforma..." << endl;
    // }
    // else if(opcionInicial == 3)
    //     cout << "Saliendo de la plataforma..." << endl;


    //podriamos hacer un get usuarios
    // web.mostrarUsuarios(web.usuarios);

    // web.login(web.usuarios);
    // web.login(web.usuarios);

    //ficheros
    //binarios o de texto --> elegir de textio porque binario es mas movida
    //primero ponemos el identificador del objeto que es

}
