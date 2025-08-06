#include "Asistente.h"
#include "Plataforma.h"

Asistente::Asistente() {}

Asistente::~Asistente() {}

Asistente::Asistente(string nombre, string contrasena, string DNI, float cartera, float recompensas, vector<Evento*> lista_entradas, bool vip): Usuario(nombre,contrasena)
{
    _DNI = DNI;
    _cartera = cartera;
    _entradas = lista_entradas;
    _recompensas = recompensas;
    _esVip  = vip;
}


void Asistente :: misRecompensas()
{
    cout << "Muchas gracias por ser un fiel cliente de nuestra plataforma! <3" << endl;
    cout << "Su dinero de recompensa por sus compras es de: " << _recompensas << " euros" << endl;
}

void Asistente :: setCartera(float dinero)
{
    _cartera = dinero;
}

float Asistente :: getCartera() const
{
    return _cartera;
}

vector <Evento*>& Asistente :: getEntradas()
{
    return _entradas;
}

void Asistente :: verArtista(Plataforma* plataforma)
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

string Asistente :: getDNI()
{
    return _DNI;
}

void Asistente :: verCartera() const
{
    cout <<  "Saldo disponible: " << getCartera() << " €" << endl;
}

void Asistente :: verEntradas() const
{
    if(!_entradas.empty())
    {
        cout << "Tus entradas son: " << endl;
        for(size_t i = 0; i < _entradas.size(); i ++)
        {
            cout << "Evento: " << _entradas[i]->getNombre() << endl;
            cout << "Fecha: " << _entradas[i]->getFecha() << endl;
            cout << "Localización: " << _entradas[i]->getLocation()->getNombre() << endl;
            cout << "-----------------------------" << endl;
        }
    }
    else
        cout << "Actualmente no tienes entradas" << endl;

    // //map <key, value> es como una agenda telefónica o un diccionario-> guarda pares de datos, donde
    // //cada clave (key) se asocia con un valor (value). Sirve para guardar datos relacionados entre
    // //sí, como Nombre -> edad, y en este caso Evento* -> entradas adquiridas por el asistente para ese
    // //evento. Para usarlo necesitamos #include <map>.
    // //El tipo de variable que te devuelve el map cuando accedes a él usando
    // //la clave es el tipo de variable del valor, sin embargo al revés no pasa lo contrario.
    // //Es decir, no puedes acceder a un map usando el valor para que te devuelva la clave, porque
    // //el map está pensado para buscar por clave y no por valor.

    // map<Evento*, int> entradasAdquiridas; //clave: evento*, valor: numero d entradas
    // if (entradas.empty())
    // {
    //     cout << "No tienes entradas compradas." << endl;
    //     return;
    // }

    // //el vector de entradas tiene las entradas que ha comprado el asistente.
    // for (size_t i = 0; i < entradas.size(); i++)
    // {
    //     Evento* evento = entradas[i]; //accedemos al evento i-ésimo del vector(puntero a evento)
    //     entradasAdquiridas[evento]++;
    // }

    // //usamos :: para accdeder al  iterator it, que es un tipo de la clase map
    // map<Evento*, int>::iterator it;
    // for (it = entradasAdquiridas.begin(); it != entradasAdquiridas.end(); ++it) {
    //     Evento* evento = it->first;
    //     int cantidad = it->second;

    //     cout << cantidad << " entrada(s) para:\n";
    //     cout << "  Nombre: " << evento->getNombre() << endl;
    //     cout << "  Fecha: " << evento->getFecha() << endl;
    //     cout << "  Localización: " << evento->getLocation() << endl;
    //     cout << "--------------------------\n";
    // }
}

int Asistente:: buscarEntrada(const string& nombre)
{
    for(size_t i = 0; i < _entradas.size(); i ++)
    {
        if (_entradas[i]->getNombre()== nombre)
            return i;
    }
    return -1;
}

void Asistente :: venderEntradas(Plataforma* plataforma)
{
    string nombre;
    int num;

    cout << "Nombre del evento para el cual se quiere vender la entrada: ";
    cin >> nombre;

    //no es solo comprobar que el evento exista (que el usuario no haya
    //metido el nombre que le haya dado la gana), si no tambien que ese evento pertenezca
    //al vector de entradas del usuario (para poderla vender ha tenido que comprarla antes)

    Evento* evento = plataforma->obtenerEvento(nombre);
    int i = buscarEntrada(nombre);
    if(i < 0)
    {
        cout << "Usted no ha adquirido entradas para este evento previamente" << endl;
        return;
    }
    if(evento)
    {
        if(evento->getFecha() < plataforma->obtenerFechaActual())
        {
            cout << "No puedes vender entradas de evento pasados" << endl;
            return;
        }
        cout << "Seleccione el número de entradas que desea vender: ";
        cin >> num;

        int contador = 0;
        for (int i = 0; i < _entradas.size(); ++i) //cuantas entradas tiene el asistente para el evento
        {
            if (_entradas[i] == evento)
            {
                contador++;
            }
        }

        if(contador >= num)
        {
            //a qué precio la quieres vender -> control antiestafa
            setCartera(getCartera() + (num * evento->getPrecio()));
            evento->setEntradas(evento->getEntradas() + num); //las entradas que vende se van al evento?
            int borradas = 0;
            for (int i = 0; i < _entradas.size() && borradas < num; ++i)
            {
                if (_entradas[i] == evento)
                {
                    _entradas.erase(_entradas.begin() + i);
                    i--; //hay que retroceder el índice porque el vector se desplaza con el erase!!
                    borradas++;
                }
            }
            cout <<  _entradas.size() << endl;
            cout << "Venta realizada con éxito :)" << endl;
        }
        else
            cout << "No tienes tantas entradas de este evento para vender" << endl;
    }
    else
        cout << "Evento inexistente" << endl;
}
