#include "Administrador.h"
#include "Artista.h"
#include "Asistente.h"
#include "AsistenteNormal.h"
#include "AsistenteVip.h"

Administrador :: Administrador() {}

Administrador :: Administrador(string nombre, string contrasena) : Usuario(nombre, contrasena){}

Administrador :: ~Administrador() {}

void Administrador :: mostrarMenu() const
{
    cout << "\nOpciones de administrador:\n0. Cerrar sesión\n1. Mostrar usuarios de la plataforma\n"
            "2. Mostrar historial de eventos de la plataforma\n3. Crear un usuario\n4. Modificar un usuario\n"
            "5. Eliminar un usuario\n6. Ver información de un artista\n7. Búsquedas filtradas\n"
            "8. Ver estadísticas de la plataforma" << endl;
}

void Administrador :: verArtista(Plataforma* plataforma)
{
    //la función obtener usuario de plataforma te devuelve *usuario
    //entonces se podría hacer dynamic_cast:
    string nombre;
    cout << "Nombre de usuario del artista que quieres ver: ";
    cin >> nombre;
    Usuario* usuario = plataforma->obtenerUsuario(nombre);
    if(usuario)
    {
        if (Artista* artista = dynamic_cast<Artista*>(usuario))
        {
            artista->mostrarInfo(plataforma);
        }
        else
            cout << "El nombre de usuario introducido no pertence a un artista" << endl;
    }
    else
        cout << "Ese usuario no existe" << endl;
}

void Administrador :: crearUsuario(vector<Usuario*>& usuarios, Plataforma* i)
{
    string nombre, contrasena;
    char opcion;
    Usuario* usuarioNuevo;

    cout << "***Nuevo usuario***" << endl;
    cout << "Nombre de usuario: ";
    cin >> nombre;

    if(i->buscarUsuario(nombre) >= 0)
    {
        cout << "Ese nombre de usuario ya existe" << endl;
    }
    else
    {
        cout << "Contraseña: ";
        cin >> contrasena;

        cout << "Opciones de tipo de usuario: "<< endl << "1.Administrador"
             << endl << "2.Artista" << endl << "3.Asistente" << endl;
        cin >> opcion;
        cin.ignore();
        switch(opcion)
        {
        case '1': usuarioNuevo = new Administrador(nombre, contrasena); break;
        case '2':
        {
            string nombreArtistico, estilo, descripcion;

            cout << "Nombre artístico: ";
            getline(cin, nombreArtistico);
            cout << "Estilo musical: ";
            getline(cin, estilo);
            cout << "Descripción: ";
            getline(cin, descripcion);
            usuarioNuevo = new Artista(nombre, contrasena, nombreArtistico, estilo, descripcion, {});
            break;
        }
        case '3':
        {
            string dni;
            float dinero;
            do {
                cout << "Seleccione tipo de asistente:\na.Normal\nb.VIP" << endl;
                cin >> opcion;
                cin.ignore();
            } while (opcion != 'a' && opcion != 'b');

            cout << "DNI: " << endl; //hacer algun tipo de control aqui
            getline(cin, dni);
            cout << "Dinero en la cartera: " << endl;
            cin >> dinero;
            cin.ignore();
            if(opcion == 'a')
                usuarioNuevo = new AsistenteNormal(nombre, contrasena, dni, dinero, 0.0f, {}, false);
            //al crearlo noo tiene recompensas, estas se obtienen cuando empieza a comprar
            else
                usuarioNuevo = new AsistenteVip(nombre, contrasena, dni, dinero, 0.0f, {}, true);
            break;
        }
        }
        usuarios.push_back(usuarioNuevo);
        cout << "Usuario " << nombre << " creado" << endl;
    }
}

void Administrador :: modificarUsuario(vector<Usuario*>& usuarios)
{
    //esta funcion puede ser mucho mas tocha. habría no solo que distinguir entre qué tipo de usuario
    //quieres modificar, sino también qué quieres modificar de esos usuarios (variádica)
    //se reduce solo a modificar el nombre y la contraseña

    string nombre, nuevoNombre, nuevaContra;

    cout << "Escribe el nombre del usuario que deseas modificar: ";
    cin >> nombre;
    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i]->getNombre() == nombre)
        {
            cout << "Introduzca el nuevo nombre de usuario: ";
            cin >> nuevoNombre;
            usuarios[i]->setNombre(nuevoNombre);
            cout << "Introduzca la nueva contraseña de " << nuevoNombre << " :";
            cin >> nuevaContra;
            usuarios[i]->setContrasena(nuevaContra);
            return;
        }
    } cout << "Usuario no encontrado" << endl;
}

void Administrador :: eliminarUsuario(vector <Usuario*>& usuarios)
{
    string nombre;
    cout << "Escribe el nombre del usuario que deseas eliminar: ";
    cin >> nombre;
    if(this->getNombre() == nombre)
    {
        cout << "No puedes eliminarte a ti mismo!"<< endl; //si da tiempo lanzar una excepcion
    }
    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i]->getNombre() == nombre)
        {
            delete usuarios[i];
            usuarios.erase(usuarios.begin() + i);
            //delete libera el espacio de memoria donde se habia creado el  usuario con el new
            //, para evitar fugas de memoria (memoryleaks)
            //con el erase se elimina el puntero de la posición i en el vector usuarios
            cout << "Usuario " << nombre << " eliminado." << endl;
            return;
        }
    }
    cout << "Usuario no encontrado" << endl;
}
