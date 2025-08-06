#include "Artista.h"
#include "Plataforma.h"

Artista :: Artista() {}
Artista :: ~Artista (){}
Artista :: Artista (string nombre, string contrasena, string nombreArtistico, string estilo_musical, string descripcion, vector<Evento*> lista_eventos) : Usuario (nombre,contrasena)
{
    _nombreArtistico = nombreArtistico;
    _estiloMusical = estilo_musical;
    _descripcion = descripcion;
    _listaEventos = lista_eventos;
}

void Artista :: mostrarMenu() const
{
    cout << "\nOpciones de artista:\n0. Cerrar sesión\n1. Mostrar usuarios de la plataforma\n"
            "2. Mostrar historial de eventos de la plataforma\n3. Crear un evento\n4. Modificar un evento\n"
            "5. Eliminar un evento\n6. Ver mis eventos\n7. Búsquedas filtradas\n8. Ver "
            "estadísticas de la plataforma" << endl;
}

string Artista :: getNombreArtista() const
{
    return _nombreArtistico;
}

string Artista :: getEstiloMusical() const
{
    return _estiloMusical;
}

string Artista :: getDescripcion() const
{
    return _descripcion;
}

const vector<Evento*> Artista :: getEventos() const
{
    //en la declaracion de la funcion:
    // -El primer const protege el vector de modificaciones externas.
    // -El segundo const garantiza que el método no alterará el objeto.
    return _listaEventos;
}

void Artista :: mostrarInfo(Plataforma* p) const
{
    vector <Evento*> listaEventos = getEventos();
    cout << "Información del artista: \n";
    cout << "•Nombre Artístico: " << this->getNombreArtista() <<endl;
    cout << "•Estilo musical: " << this->getEstiloMusical() <<endl;
    cout << "•Descripción:  " << this->getDescripcion() <<endl;
    cout << "•Futuros eventos: " << endl;
    for(size_t i = 0; i < listaEventos.size(); i ++)
    {
        if(listaEventos[i]->getFecha() >= p->obtenerFechaActual())
        {
            cout << "Evento: " << listaEventos[i]->getNombre() << " | Localizacion: " << listaEventos[i]->getLocation()->getNombre() << " | Fecha: " <<
                listaEventos[i]->getFecha() << " | Precio: " << listaEventos[i]->getPrecio() << " €"
                " | Entradas: " << listaEventos[i]->getEntradas() << " | VIP: ";
            if (listaEventos[i]->getEsVip())
                cout << "Sí" << endl;
            else
                cout << "No" << endl;
        }
    }
}

void Artista :: verMisEventos() const
{
    if(!_listaEventos.empty())
    {
        for(size_t i = 0; i < _listaEventos.size(); i ++)
        {
            cout << "Evento " << _listaEventos[i]->getNombre() << " en " << _listaEventos[i]->getLocation()->getNombre()
                 << " | Fecha: " << _listaEventos[i]->getFecha()
                 << " | Precio: " << _listaEventos[i]->getPrecio() << " | VIP: ";
            if (_listaEventos[i]->getEsVip())
                cout << "Sí";
            else
                cout << "No" << " | Entradas: " << _listaEventos[i]->getEntradas() << endl;
        }
    }
    else
        cout << "Todavía no has creado ningún evento" << endl;
}

void Artista :: crearEvento(vector<Evento*>& eventos, Plataforma* p)
{
    string nombre, nombre_loc, direccion_loc;
    int fecha;
    float precio, precioBase;
    int entradas, aforo;
    bool vip;

    cout << "Nombre del evento: ";
    getline(cin, nombre);
    cout << "Nombre de la localizacion: ";
    getline(cin, nombre_loc);

    if(p->buscarLocalizacion(nombre_loc) < 0) //si la localizacion NO se ha creado todavía
    {
        cout << "Dirección de la localizacion: ";
        getline(cin, direccion_loc);
        cout << "Aforo: ";
        cin >> aforo;
        cin.ignore();
        p->localizaciones.push_back(new Localizacion(nombre_loc, direccion_loc, aforo));
    }

    //si la localizacion ya existía o una vez ha sido creada con el if de arriba, se busca en el
    //vector de localizaciones y obtenemos un puntero a esa localizacion
    Localizacion* loc = p->obtenerLocalizacion(nombre_loc);

    //para crear un evento la localizacion tiene que estar disponible en la fecha deseada
    cout << "Fecha del evento (formato YYYYMMDD): ";
    cin >> fecha;

    if(fecha < p->obtenerFechaActual())
    {
        cout << "No puedes crear un evento en una fecha pasada" << endl;
        return;
    }
    if(!loc->disponibleFecha(fecha)) //si la funcion NO devuelve 1
    {
        cout << "La localización no está disponible en la fecha deseada" << endl;
        return;
    }
    else //localizacion disponible
    {
        // cout << endl;
        cout << "Precio por entrada:  ";
        cin >> precio;
        precio = precio + 0.3*precio;
        // la plataforma se va a llevar un 30% del precio de la entrada para sus fondos
        // (el precio base lo pone el artista)
        cin.ignore();
        cout << "Número de entradas: ";
        cin >> entradas;
        cin.ignore();
        if(entradas > loc->getAforo())
        {
            cout << "El número de entradas supera el aforo permitido. Esto es ilegal." << endl;
            return;
        }
        do {
            cout << "Seleccione tipo de evento:\n0.Normal\n1.VIP:" << endl;
            cin >> vip;
            cin.ignore();
        } while (vip != 1 && vip != 0);
        Evento* nuevoEvento = new Evento(nombre, loc, fecha, precio, entradas, vip);
        loc->getReservados().push_back(nuevoEvento);
        eventos.push_back(nuevoEvento);
        _listaEventos.push_back(nuevoEvento);
        cout << "Evento creado con éxito" << endl;
    }
}


void Artista :: modificarEvento(Plataforma* p)
{
    string nombre, nuevoNombre, nombre_loc, direccion_loc;
    int fecha;
    float precio;
    int entradas, aforo;
    bool vip;

    cout << "Nombre del evento a modificar: ";
    getline(cin, nombre);
    Evento* e = p->obtenerEvento(nombre);
    if(!e)
    {
        cout << "Ese evento todavía no ha sido creado";
        return;
    }
    else
    {
        cout << "***Modificación de datos del evento***" << endl;
        cout << "Nombre: ";
        getline(cin, nuevoNombre);
        cout << "Nombre de la localizacion: ";
        getline(cin, nombre_loc);

        //aqui hay que ver si el artista ha cambiado la localizacion o es la misma que antes
        //porque en el caso de que la haya cambiado:
        //1.hay que verificar si la localizacion elegida ya ha sido creada anteriormente o
        //es una localizacion nueva, en ese caso la creamos.
        //2.que no coincidan la nueva localizacion y la nueva fecha con otra fecha y localizacion
        //de otro evento.
        //3.hay que eliminar del vector de reservados de localizacion el evento anterior
        //y añadir este otro evento.

        //paso 1
        if(p->buscarLocalizacion(nombre_loc) < 0) //si la localizacion NO se ha creado antes
        {
            cout << "Dirección de la localizacion: ";
            getline(cin, direccion_loc);
            cout << "Aforo: ";
            cin >> aforo;
            p->localizaciones.push_back(new Localizacion(nombre_loc, direccion_loc, aforo));
        }
        Localizacion* nuevaLoc = p->obtenerLocalizacion(nombre_loc);

        //paso 2
        cout << "Fecha del evento: ";
        cin >> fecha;
        if(!nuevaLoc->disponibleFecha(fecha)) //verificamos que esté disponible en la fecha
        {
            cout << "La localización no está disponible en la fecha deseada" << endl;
            return;
        }

        //paso 3
        // Si cambia la localización, quitarlo de la anterior
        if (e->getLocation() != nuevaLoc)
        {
            e->getLocation()->eliminarReservado(e); //método para quitar eventos reservados
            nuevaLoc->getReservados().push_back(e);
            e->setLocation(nuevaLoc);
        }
        cout << "Precio por entrada:  ";
        cin >> precio;
        cin.ignore();
        cout << "Número de entradas: ";
        cin >> entradas;
        cin.ignore();
        if(entradas > nuevaLoc->getAforo())
        {
            cout << "El número de entradas supera el aforo permitido. Esto es ilegal." << endl;
            return;
        }
        do {
            cout << "Seleccione tipo de evento:\n0.Normal\n1.VIP:" << endl;
            cin >> vip;
            cin.ignore();
        } while (vip != '1' && vip != '0');

        e->setNombre(nuevoNombre);
        e->setEntradas(entradas);
        e->setFecha(fecha);
        e->setPrecio(precio);
        e->setVip(vip);
        //el setlocation lo tengo arriba
        cout << "Evento modificado correctamente" << endl;
    }
}

void Artista :: eliminarEvento(vector <Evento*>& eventos, Plataforma* p)
{
    string nombre;
    cout << "Nombre del evento a eliminar:  ";
    getline(cin, nombre);
    Evento* e = p->obtenerEvento(nombre);
    if (!e)
    {
        cout << "Ese evento todavía no ha sido creado";
        return;
    }
    else
    {
        int i = p->buscarEvento(nombre); //para saber la posicion dentro del vector de eventos
        e->getLocation()->eliminarReservado(e);
        eventos.erase(eventos.begin() + i);
        _listaEventos.erase(_listaEventos.begin() + i);
        delete e;
        cout << "El evento ha sido eliminado" << endl;
    }
}
