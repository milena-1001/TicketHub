
#include "AsistenteNormal.h"

AsistenteNormal :: AsistenteNormal() {}
AsistenteNormal :: ~AsistenteNormal() {}

AsistenteNormal :: AsistenteNormal(string nombre, string contrasena,
                            string DNI, float cartera, float recompensas, vector <Evento*> lista_entradas, bool vip)
    : Asistente (nombre, contrasena, DNI, cartera, recompensas, lista_entradas, vip) {}

void AsistenteNormal :: mostrarMenu() const
{
    cout << "\nOpciones de asistente no vip:\na. Cerrar sesión\nb. Mostrar usuarios de la plataforma\n"
            "c. Mostrar historial de eventos de la plataforma\nd. Comprar entradas\ne. Vender entradas\n"
            "f. Ver mis entradas\ng. Ver información de un artista\nh. Mostrar futuros eventos disponibles para mí\n"
            "i. Ver mi cartera\nj. Búsquedas filtradas\nk. Ver mis recompensas\nl. Ver estadísticas de la plataforma\n";
}

void AsistenteNormal :: verEventos(vector <Evento*> eventos, Plataforma* p) const
{
    //aquí hacer distinción entre: aquellos eventos para los cuales queden entradas,
    //eventos que no se hayan realizado todavía (tema fechas) y que en este caso no sean vip
    cout << "Futuros eventos disponibles para ti: "<< endl;
    for(size_t i = 0; i < eventos.size(); i ++)
    {
        if(eventos[i]->getFecha() >= p->obtenerFechaActual() && eventos[i]->getFecha() <= p->obtenerFechaDentroDeUnMes()
            && eventos[i]->getEntradas() > 0 && !eventos[i]->getEsVip())
        {
            cout << "Evento en " << eventos[i]->getLocation()->getNombre() << " | Fecha: " <<
                eventos[i]->getFecha() << " | Precio: " << eventos[i]->getPrecio() <<
                " | Entradas: " << eventos[i]->getEntradas() << endl;
        }
    }
}

void AsistenteNormal :: comprarEntradas(Plataforma* plataforma)
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
        if(evento->getFecha() > plataforma->obtenerFechaDentroDeUnMes())
        {
            cout << "No puedes comprar entradas con más antelación de 1 mes" << endl;
            return;
        }
        if(!evento->getEsVip())
        {
            cout << "Seleccione el número de entradas que desea adquirir: ";
            cin >> num;
            if((evento->getEntradas() - num) >= 0) //si hay entradas disponibles del evento
            {
                if((getCartera() - (num * evento->getPrecio())) >= 0) //si tiene dinero suficiente
                {
                    //la plataforma se lleva un 30%
                    //el Uni significa unitario xd

                    bool opcionCorrecta = false;
                    while(!opcionCorrecta)
                    {
                        cout << "Desea usar sus recompensas para la compra de esta entrada?\n1. Sí\n2. No\n";
                        cout << "Tienes " << _recompensas << " euros de recompensa\n";
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

                    float beneficioUni = evento->getPrecio() * (0.3f / 1.3f); //la plataforma gana 30%
                    float recompensaUni = 0.1f*evento->getPrecio();  //el asistente gana 10%
                    plataforma->setFondos(plataforma->getFondos() + (beneficioUni - recompensaUni) * num);
                    cout << "Ha obtenido " << recompensaUni*num << " euros de beneficio por esta compra" << endl;
                    _recompensas = _recompensas + (recompensaUni * num);
                    misRecompensas();
                    evento->setEntradas(evento->getEntradas() - num);
                    for(size_t i = 0; i < num; i ++)
                    {
                        _entradas.push_back(evento);
                    }
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
            cout << "Acción denegada. Solo los asistentes VIP pueden adquirir entradas "
                    "para este evento." << endl;
    }
    else
        cout << "Evento inexistente" << endl;
}

