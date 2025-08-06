#include "Plataforma.h"
#include "AsistenteVip.h"

AsistenteVip :: AsistenteVip() {}
AsistenteVip :: ~AsistenteVip() {}

AsistenteVip :: AsistenteVip(string nombre, string contrasena, string DNI, float cartera, float recompensas,
                            vector <Evento*> lista_entradas, bool vip)
    : Asistente (nombre, contrasena, DNI, cartera, recompensas,lista_entradas, vip) {}

void AsistenteVip :: mostrarMenu() const
{
    cout << "\nOpciones de asistente vip:\na. Cerrar sesión\nb. Mostrar usuarios de la plataforma\n"
            "c. Mostrar historial de eventos de la plataforma\nd. Comprar entradas\ne. Vender entradas\n"
            "f. Ver mis entradas\ng. Ver información de un artista\nh. Mostrar futuros eventos disponibles para mí\n"
            "i. Ver mi cartera\nj. Búsquedas filtradas\nk. Ver mis recompensas\nl. Ver estadísticas de la plataforma\n";
}

// void AsistenteVip :: verEntradasMercado(vector <Evento*> _entradasVIP, Plataforma* p)
// {
//     //(boceto)
//     if(!_entradasVIP.empty())
//     {
//         cout << "Entradas disponibles: " << endl;
//         for(size_t i = 0; i < _entradasVIP.size(); i ++)
//         {
//             if(_entradasVIP[i]->getFecha() > p->obtenerFechaActual())
//             {
//                 cout << "Evento: " << _entradasVIP[i]->getNombre() << endl;
//                 cout << "Fecha: " << _entradasVIP[i]->getFecha() << endl;
//                 cout << "Localización: " << _entradasVIP[i]->getLocation()->getNombre() << endl;
//                 cout << "Precio: " << _entradasVIP[i]->getPrecio();
//                 cout << "-----------------------------" << endl;
//             }
//         }
//     }
//     else
//         cout << "Actualmente no hay entradas en el mercado VIP" << endl;
// }

// void AsistenteVip :: mercadoSecundario()
// {
//     bool enMercado = true;
//     cout << "***Bienvenido al mercado VIP de la plataforma***" << endl;
//     while(enMercado)
//     {
//         cout << "Opciones del mercado VIP: \n1. Mostrar entradas disponibles\n"
//                 "2. Comprar entradas\n3. Vender entradas\n4. Salir" << endl;
//         cin >> opcion;
//         switch(opcion)
//         {
//         case '1': verEntradasMercado(); break;
//         case '2': compraEntradasMercado(); break;
//         case '3': ventaEntradasMercado(); break;
//         case '4': cout << "Saliendo del mercado secundario..."; enMercado = false; break;
//         }
//     }
// }


void AsistenteVip :: verEventos(vector <Evento*> eventos, Plataforma* p) const
{
    //aquí hacer distinción entre: aquellos eventos para los cuales queden entradas,
    //eventos que no se hayan realizado todavía (tema fechas) y que en este caso no sean vip
    cout << "Futuros eventos disponibles para ti: "<< endl;
    for(size_t i = 0; i < eventos.size(); i ++)
    {
        if(eventos[i]->getFecha() >= p->obtenerFechaActual()
            && eventos[i]->getEntradas() > 0)
        {
            cout << "Evento en " << eventos[i]->getLocation()->getNombre() << " | Fecha: " <<
                eventos[i]->getFecha() << " | Precio: " << eventos[i]->getPrecio() <<
                " | Entradas: " << eventos[i]->getEntradas() << endl;
        }
    }
}

void AsistenteVip :: comprarEntradas(Plataforma* plataforma)
{
    char opcion;
    string nombre;
    size_t num;

    cout << "Nombre del evento para el cual se quiere obtener la entrada: ";
    getline(cin, nombre);
    Evento* evento = plataforma->obtenerEvento(nombre);

    if(evento)
    {
        if(evento->getFecha() < plataforma->obtenerFechaActual())
        {
            cout << "No puedes adquirir entradas de evento pasados" << endl;
            return;
        }
        cout << "Seleccione el número de entradas que desea adquirir: ";
        cin >> num;
        if((evento->getEntradas() - num) >= 0) //si hay entradas disponibles del evento
        {
            if((getCartera() - (num * evento->getPrecio())) >= 0) //si tiene dinero suficiente
            {
                //la plataforma se lleva un 30%
                //el Uni significa unitario xd
                float beneficioUni = evento->getPrecio() * (0.3f / 1.3f);
                float recompensaUni = 0.1f*evento->getPrecio();
                plataforma->setFondos(plataforma->getFondos() + (beneficioUni - recompensaUni) * num);
                _recompensas = _recompensas + (recompensaUni * num);
                misRecompensas();
                bool opcionCorrecta = false;
                while(!opcionCorrecta)
                {
                    cout << "Desea usar sus recompensas para la compra de esta entrada?\n1. Sí\n2. No\n";
                    cin >> opcion;
                    if(opcion == '1')
                    {
                        setCartera(getCartera() + _recompensas);
                        _recompensas = 0;
                        opcionCorrecta = true;
                    }
                    if(opcion == '2')
                        opcionCorrecta = true;
                }
                setCartera(getCartera() - (num * evento->getPrecio()));
                evento->setEntradas(evento->getEntradas() - num);
                _entradas.push_back(evento);
                cout << "Compra realizada con éxito :)" << endl;
            }
            else
                cout << "Saldo insuficiente" << endl;
        }
        else
            cout << "No hay suficientes entradas disponibles del evento "
                    "para realizar esta acción" << endl;
    }
    else
        cout << "Evento inexistente" << endl;
}
