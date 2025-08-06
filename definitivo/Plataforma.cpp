
#include "Plataforma.h"

void Plataforma :: alpha()
{
    string input;
    char opcionInicial, opcion;
    bool enPlataforma = true;

    while(enPlataforma)
    {
        cout <<"Opciones de plataforma:\n1. Registrarse\n2. Iniciar sesión\n3. Darse de baja\n4. Salir "
             "de la plataforma" << endl;
        getline(cin, input);
        if (input.length() == 1 && (input[0] >= '1' && input[0] <= '4'))
        {
            opcionInicial = input[0];

            switch(opcionInicial)
            {
                case '1':registro(usuarios);break;
                case '2':
                {
                    usuarioActual = login(usuarios);
                    if(!usuarioActual)
                    {
                        cout << "Inicio de sesión fallido." << endl;
                        break;
                    }
                    while(usuarioActual)
                    {
                        usuarioActual->mostrarMenu();
                        cin >> opcion;
                        cin.ignore();
                        ejecutarOpcion(opcion);
                    }
                    cout << "Cerrando sesión..." << endl;
                    usuarioActual = nullptr;
                    break;
                }
                case '3':
                {
                    string nombre;
                    if(!usuarios.empty())
                    {
                        cout << "Introduce tu nombre de usuario: ";
                        getline(cin, nombre);
                        cin.ignore();
                        int posicion = buscarUsuario(nombre);
                        if(posicion >= 0)
                        {
                            delete obtenerUsuario(nombre);
                            usuarios.erase(usuarios.begin() + posicion);
                        }
                        else
                        {
                            cout << "Nombre de usuario incorrecto" << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << "No hay usuarios registrados actualmente en la plataforma" << endl;
                        break;
                    }
                }
                case '4':
                {
                    //limpiamos la memoria al salir
                    for(size_t i = 0; i < usuarios.size(); i ++)
                        delete usuarios[i];
                    usuarios.clear();
                    for(size_t i = 0; i < eventos.size(); i ++)
                        delete eventos[i];
                    eventos.clear();
                    for(size_t i = 0; i < localizaciones.size(); i ++)
                        delete localizaciones[i];
                    localizaciones.clear();
                    cout << "Saliendo de la plataforma..." << endl;
                    enPlataforma = false;
                    break;
                }
            }
        }
        else
            cout << "Opción incorrecta" << endl;
    }
}

Usuario* Plataforma :: login(const vector<Usuario*>& usuarios)
{
    string nombre, contrasena;
    cout << "***Inicio de sesión***" << endl;
    cout << "Introduce tu nombre de usuario: " ;
    getline(cin, nombre);
    cout << "Introduce tu contraseña: ";
    getline(cin, contrasena);

    int posicion = buscarUsuario(nombre);
    if(posicion >= 0)
    {
        if (usuarios[posicion]->verificarContrasena(contrasena))
            return obtenerUsuario(nombre);
    }
    return nullptr;
}

void Plataforma :: registro(vector<Usuario*>& usuarios)
{
    string nombre, contrasena;
    char opcion;

    cout << "***Nuevo usuario***" << endl;
    cout << "Nombre de usuario: ";
    getline(cin, nombre);

    if(buscarUsuario(nombre) >= 0)
    {
        cout << "Ese nombre de usuario ya existe" << endl;

    }
    else
    {
        cout << "Contraseña: ";
        getline(cin, contrasena);

        cout << "Opciones de tipo de usuario: "<< endl << "1.Administrador"
             << endl << "2.Artista" << endl << "3.Asistente" << endl;
        cin >> opcion;
        cin.ignore();
        switch(opcion)
        {
            case '1': usuarioActual = new Administrador(nombre, contrasena); break;
            case '2':
            {
                string nombreArtistico, estilo, descripcion;

                cout << "Nombre artístico: ";
                getline(cin, nombreArtistico);
                cout << "Estilo musical: ";
                getline(cin, estilo);
                cout << "Descripción: ";
                getline(cin, descripcion);
                cin.ignore();
                usuarioActual = new Artista(nombre, contrasena, nombreArtistico, estilo, descripcion, {});
                break;
            }
            case '3':
            {
                string dni;
                float dinero;
                cout << "DNI: "; //hacer algun tipo de control aqui
                getline(cin, dni);
                cout << "Dinero en la cartera: ";
                cin >> dinero;
                cin.ignore();
                do {
                    cout << "Seleccione tipo de asistente:\na.Normal\nb.VIP:" << endl;
                    cin >> opcion;
                    cin.ignore();
                } while (opcion != 'a' && opcion != 'b');

                if(opcion == 'a')
                    usuarioActual = new AsistenteNormal(nombre, contrasena, dni, dinero, 0.0f, {}, false);
                else
                    usuarioActual = new AsistenteVip(nombre, contrasena, dni, dinero, 0.0f, {}, true);
                break;
            }
        }
        usuarios.push_back(usuarioActual);
        cout << "Usuario registrado" << endl;
    }
}


void Plataforma :: setFondos(float dinero)
{
    _fondos = dinero;
}

float Plataforma :: getFondos()
{
    return _fondos;
}

// void Plataforma :: sistemaRecompensas()
// {
//     //cada vez que un asistente compre una entrada, el dinero gastado se
//     //almacena en una variable
//     //por cada euro que se gasta, la plataforma le da 10 céntimos, los cuales se van acumulando
//     //este dinero que se va acumulando puede añadirse a la cartera del asistente si este lo desea,
//     //para usarlo en sus compras
// }

// void Plataforma :: estadisticasPlataforma()
// {
//     cout << "¿Qué quieres ver?" << endl;
//     cout << "Opciones:\n1. Total de eventos creados\n2. Total de entradas vendidas\n"
//             "3. Ingresos totales de la plataforma\n4. Dinero gastado por los asistentes\n"
//             "5. Recompensas totales entregadas\n6. Número total de usuarios por tipo\n";
// }

void Plataforma :: verEstadisticas(const vector<Usuario*>& usuarios, const vector <Evento*>& eventos, vector <Localizacion*>& localizaciones)
{
    //reutilizamos código de la funcion de busquedas filtradas
    char opcion;
    cout << "Opciones: " << endl;
    cout << "1. Artistas que más eventos han hecho\n2. Localizaciones más cotizadas\n"
            "3. Eventos vip vs no vip\n4. Número de eventos por año\n5. Total "
            "de entradas disponibles de cada evento\n6. Total de entradas compradas"
            "por cada tipo de asistente\n7. Dinero gastado por cada tipo de asistente\n"
            "8. Ver ingresos totales de la plataforma\n" << endl;
    cin >> opcion;
    switch(opcion)
    {
    case '1':
    {
        vector<Artista*> artistas;

        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if (Artista* a = dynamic_cast<Artista*>(usuarios[i]))
            {
                artistas.push_back(a); //relleno mi vector de artistas
            }
        }
        for (size_t i = 0; i < artistas.size(); i++)
        {
            for (size_t j = i + 1; j < artistas.size(); j++)
            {
                size_t numEventos1 = artistas[i]->getEventos().size();
                size_t numEventos2 = artistas[j]->getEventos().size();

                if (numEventos1 < numEventos2) {
                    // Intercambio punteros
                    Artista* temp = artistas[i];
                    artistas[i] = artistas[j];
                    artistas[j] = temp;
                }
            }
        }
        //despues de esto los artistas ya estan ordenados por número de eventos en orden ascendente
        //Ahora quiero mostrar el número de eventos de cada artista
        for(size_t i = 0; i < artistas.size(); i ++)
        {
            cout << i + 1 << " ";
            for(size_t j = 0; j < artistas[i]->getEventos().size(); j ++)
            {
                cout << "▅";
            }
            cout << endl;
        }
        for(size_t i = 0; i < artistas.size(); i ++)
        {
            cout << "Artista " << i + 1 << ": " << artistas[i]->getNombre() << " | Eventos: " <<
                    artistas[i]->getEventos().size()<< endl;
        }
        break;
    }
    case '2':
    {
        //2. Localizaciones más cotizadas->sería ver que localizaciones tieenen mas eventos reservados
        //es como ver que artistas tienen mas eventos

        for (size_t i = 0; i < localizaciones.size(); i++)
        {
            for (size_t j = i + 1; j < localizaciones.size(); j++)
            {
                size_t numEventos1 = localizaciones[i]->getReservados().size();
                size_t numEventos2 = localizaciones[j]->getReservados().size();

                if (numEventos1 < numEventos2){
                    // Intercambio punteros
                    //para poder hacer esto he quitado el const de localizacion que pasaba por parametro
                    //a esta funcion porque si no no me dejaba modificarlo, otra opcion era
                    //dejar el const y hacer una copia del vector pero realmente me da igual que se modifique
                    //el orden
                    Localizacion* temp = localizaciones[i];
                    localizaciones[i] = localizaciones[j];
                    localizaciones[j] = temp;
                }
            }
        }
        for(size_t i = 0; i < localizaciones.size(); i ++)
        {
            cout << endl;
            cout << i + 1 << " ";
            for(size_t j = 0; j < localizaciones[i]->getReservados().size(); j ++)
            {
                cout << "▅";
            }
            cout << endl;
        }
        cout << endl;
        for(size_t i = 0; i < localizaciones.size(); i ++)
        {
            cout << "Lcalizacion " << i + 1 << ": " << localizaciones[i]->getNombre() << " | Eventos: " <<
                localizaciones[i]->getReservados().size()<< endl;
        }
        break;
    }
    case '3':
    {
        size_t numVip = 0;
        for(size_t i = 0; i < eventos.size(); i ++)
        {
            if(eventos[i]->getEsVip())
                numVip ++;;
        }
        cout << endl;
        cout << "Vip:    ";
        for(size_t i = 0; i < numVip; i ++)
            cout << "▅";
        cout << endl ;
        cout << "No Vip: ";
        for(size_t i = 0; i < (eventos.size() - numVip); i ++)
            cout << "▅";
        cout << endl << endl;
        cout << "Número de eventos Vip: " << numVip << "\nNúmero de eventos no Vip: " <<
            eventos.size() - numVip << endl;
        break;
    }
    case '4':
    {
        //numero de eventos por año
        //si hay un año en el que se han hecho eventos, contamos los eventoos que se han hecho
        vector <int> aniosEventos;

        for(size_t  i = 0; i < eventos.size(); i ++)
        {
            //sería pillar la fecha y de esta pillar las 4 primeras cifras que es  el año
            //suponiendo que nadie va a hacer eventos con año de fecha < 1000 y fecha > 9999
            
            int fecha = eventos[i]->getFecha();
            int anio = fecha/10000;
            aniosEventos.push_back(anio);
        }
        //una vez he guardado todos los años en los que hay eventos
        sort(aniosEventos.begin(), aniosEventos.end()); // me los ordena de menor a mayor
        //el problema es que en este vector tengo años repetiddos (de eventos que se haceen en el mismo
        //año):
        //unique elimina los elementos duplicados que se eencuentran juntos(por eso usamos el sort)
        //y mueve el vector hacia delante esas posiciones, por lo que si ha eliminado algo, las posiciones
        //del final del vector se quedan con valores indeterminados (basura). Como esta funcion
        //devuelve un puntero a la ultima posicion + 1  donnde quedan valores determinados (nuevo
        //tamaño "logico" del vector) usamos el erase desde esa posicion hasta el final para que
        //borre los términos que no queremos.

        aniosEventos.erase(unique(aniosEventos.begin(), aniosEventos.end()), aniosEventos.end());
        vector<int> contador(aniosEventos.size(), 0);

        for(size_t i = 0; i < aniosEventos.size(); i ++)
        {
            contador[i] = 0;
            cout << aniosEventos[i]  << " ";
            for(size_t j = 0; j < eventos.size(); j ++)
            {
                if(aniosEventos[i] == (eventos[j]->getFecha()/10000))
                {
                    cout << "▅";
                    contador[i] += 1;
                }

            }
            cout << endl;
        }
        cout << endl;
        for(size_t i = 0; i < aniosEventos.size(); i ++)
        {
            cout << "Año: " << aniosEventos[i] << " | Eventos: " <<  contador[i] <<  endl;
        }
        break;
    }
    case '5':
    {
        // 5. Total de entradas disponibles por cada evento
        //cada evento tiene un int de entradas, que es el número de entradas
        for(size_t i = 0; i < eventos.size(); i ++)
        {
            cout << i + 1 << " ";
            for(size_t j = 0; j < eventos[i]->getEntradas(); j ++)
            {
                cout << "▅";
            }
            cout << endl;
        }
        for(size_t i = 0; i < eventos.size(); i ++)
        {
            cout << "Evento " << i + 1 << " " << eventos[i]->getNombre() <<
                " | Entradas disponibles: " << eventos[i]->getEntradas() << endl;
        }
        break;
    }
    case '6':
    {
        // 6. entradas compradas por cada tipo de asistente
        vector <AsistenteNormal*> normal;
        vector <AsistenteVip*> vip;
        int totalEntradasNormal = 0;
        int totalEntradasVip = 0;

        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if(AsistenteNormal* n = dynamic_cast<AsistenteNormal*>(usuarios[i]))
            {
                normal.push_back(n);
            }
            if(AsistenteVip* v = dynamic_cast<AsistenteVip*>(usuarios[i]))
            {
                vip.push_back(v);
            }
        }
        cout <<  "Entradas compradas por asistentes no vip:\n";
        for(size_t i = 0; i < normal.size(); i ++)
        {
            cout << i + 1 << "  ";
            for(size_t j = 0; j < normal[i]->getEntradas().size(); j ++)
            {
                cout << "▅";
                totalEntradasNormal ++;
            }
            cout  << endl;
        }
        for(size_t i = 0; i < normal.size(); i ++)
        {
            cout << "Asistente no vip  " << i + 1 << " : " << normal[i]->getNombre() <<
                " | Entradas compradas: " << normal[i]->getEntradas().size() << endl;
        }

        cout <<  "Entradas compradas por asistentes vip:\n";
        for(size_t i = 0; i < vip.size(); i ++)
        {
            cout << i + 1 << "  ";
            for(size_t j = 0; j < vip[i]->getEntradas().size(); j ++)
            {
                cout << "▅";
                totalEntradasVip ++;
            }
            cout << endl;
        }
        for(size_t i = 0; i < vip.size(); i ++)
        {
            cout << "Asistente vip  " << i + 1 << " : " << vip[i]->getNombre() <<
                " | Entradas compradas: " << vip[i]->getEntradas().size() << endl;
        }
        cout << "·Total entradas compradas por los asistentes no vip: " <<  totalEntradasNormal << endl;
        cout << "·Total entradas compradas por los asistentes vip: " << totalEntradasVip <<  endl;
        cout << "·Total de entradas compradas en la plataforma: " << totalEntradasVip + totalEntradasNormal << endl;
        if(totalEntradasNormal < totalEntradasVip)
        {
            cout << "Los asistentes Vip han comprado " << totalEntradasVip - totalEntradasNormal <<
                " más entradas que los asistentes no vip" << endl;
        }
        else
        {
            cout << "Los asistentes no Vip han comprado " << totalEntradasNormal - totalEntradasVip <<
                " más entradas que los asistentes vip" << endl;
        }

        break;
    }
    case '7':
    {
        // 7. Dinero gastado por los asistentes
        //será ver cuantas entradas ha comprado cada tipo de asistente y multiplicarlo por el precio
        //de cada entrada
        vector <AsistenteNormal*> normal;
        vector <AsistenteVip*> vip;
        vector <float> dineroNormal;
        vector <float> dineroVip;
        float totalDineroNormal = 0;
        float totalDineroVip = 0;

        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if(AsistenteNormal* n = dynamic_cast<AsistenteNormal*>(usuarios[i]))
            {
                normal.push_back(n);
            }
            if(AsistenteVip* v = dynamic_cast<AsistenteVip*>(usuarios[i]))
            {
                vip.push_back(v);
            }
        }
        //le damos dimensiones a estos vectores y los rellenamos con 0
        dineroNormal.resize(normal.size(), 0.0f);
        dineroVip.resize(vip.size(), 0.0f);

        cout <<  "Dinero gastado por asistentes no vip:\n";
        for(size_t i = 0; i < normal.size(); i ++)
        {
            cout << i + 1 << "  ";
            for(size_t j = 0; j < normal[i]->getEntradas().size(); j ++)
            {
                cout << "▅";
                dineroNormal[i] = dineroNormal[i] + (normal[i]->getEntradas()[j]->getPrecio());
            }
            cout << endl;
        }
        for(size_t i = 0; i < normal.size(); i ++)
        {
            cout << "Asistente no vip  " << i + 1 << " :" << normal[i]->getNombre() <<
                " | Dinero gastado: " << dineroNormal[i] << endl;
        }

        cout <<  "Dinero gastado por asistentes vip:\n";
        for(size_t i = 0; i < vip.size(); i ++)
        {
            cout << i + 1 << "  ";
            for(size_t j = 0; j < vip[i]->getEntradas().size(); j ++)
            {
                cout << "▅";
                dineroVip[i] = dineroVip[i] + (vip[i]->getEntradas()[j]->getPrecio());
            }
            cout << endl;
        }
        for(size_t i = 0; i < vip.size(); i ++)
        {
            cout << "Asistente vip  " << i + 1 << " :" << vip[i]->getNombre() <<
                " | Dinero gastado: " << dineroVip[i] << endl;
        }

        //ahora sumando todos los elementos de los vectores correspondientes al dinero
        for(size_t i = 0; i < dineroNormal.size(); i ++)
        {
            totalDineroNormal = totalDineroNormal + dineroNormal[i];
        }
        for(size_t i = 0; i < dineroVip.size(); i ++)
        {
            totalDineroVip = totalDineroVip + dineroVip[i];
        }
        cout << "Total dinero gastado por los asistentes no vip: " <<  totalDineroNormal << endl;
        cout << "Total dinero gastado por los asistentes vip: " << totalDineroVip <<  endl;
        cout << "Total de dinero gastado en la plataforma: " << totalDineroVip + totalDineroNormal << endl;
        if(totalDineroNormal < totalDineroVip)
        {
            cout << "Los asistentes Vip han gastado " << totalDineroVip - totalDineroNormal <<
                " más euros que los asistentes no vip" << endl;
        }
        else
        {
            cout << "Los asistentes no Vip han gastado " << totalDineroNormal - totalDineroVip <<
                " más euros que los asistentes vip" << endl;
        }
        break;
    }
    case '8':
    {
        cout << "La plataforma ha recaudado " << _fondos << " euros" << endl;
        break;
    }
    default: cout << "Opcion incorrecta" << endl; break;
    }
}

void Plataforma :: filtrarLocalizacion(const vector <Localizacion*>& localizaciones)
{
    string nombre , direccion;
    vector <int> aforo;
    char opcion;
    bool encontrado = false;
    cout << "¿Cómo quieres filtrar tu búsqueda de localizaciones?" << endl;
    cout << "1. Buscar por nombre\n2. Mostrar por direccion\n3. Mostrar por aforo\n";
    cin >> opcion;
    cin.ignore();
    switch(opcion)
    {
    case '1':
    {
        cout << "Escribe el nombre de la localización que quieres encontrar: ";
        getline(cin, nombre);
        for(size_t i = 0; i < localizaciones.size(); i ++)
        {
            if(localizaciones[i]->getNombre() == nombre)
            {
                localizaciones[i]->mostrarInfo();
                encontrado = true;
            }
        }
        if(!encontrado)
        {
            cout << "Localización no encontrada" << endl;
        }
        break;
    }
    case '2':
    {
        cout << "Escribe el nombre de la dirección de la localización que quieres encontrar: ";
        getline(cin, direccion);
        for(size_t i = 0; i < localizaciones.size(); i ++)
        {
            if(localizaciones[i]->getDireccion() == direccion)
            {
                localizaciones[i]->mostrarInfo();
                cout << endl;
                encontrado = true;
            }
        }
        if(!encontrado)
        {
            cout << "Localización no encontrada" << endl;
        }
        break;
    }
    case '3':
    {
        cout << "Opciones:\n1. De menor a mayor aforo\n2. De mayor a menor aforo\n";
        cin >> opcion;
        for(size_t i = 0; i < localizaciones.size(); i ++)
        {
            aforo.push_back(localizaciones[i]->getAforo());
        }
        sort(aforo.begin(), aforo.end());
        switch(opcion)
        {
        case '1':
        {
            for(size_t i = 0; i < aforo.size(); i ++)
            {
                for(size_t j = 0; j < localizaciones.size(); j ++)
                {
                    if(aforo[i] == localizaciones[j]->getAforo())
                    {
                        localizaciones[j]->mostrarInfo();
                        cout << endl;
                    }
                }
            }
            break;
        }
        case '2':
        {
            reverse(aforo.begin(), aforo.end());
            for(size_t i = 0; i < aforo.size(); i ++)
            {
                for(size_t j = 0; j < localizaciones.size(); j ++)
                {
                    if(aforo[i] == localizaciones[j]->getAforo())
                    {
                        localizaciones[j]->mostrarInfo();
                        cout << endl;
                    }
                }
            }
            break;
        }
        default: cout << "Opcion incorrecta" << endl;
        }
        break;
    }
    default: cout << "Opcion incorrecta" << endl; break;
    }
}

void Plataforma :: filtrarEvento(const vector <Evento*>& eventos)
{
    string nombre;
    vector <string> nombres;
    char opcion;
    bool encontrado = false;
    cout << "¿Cómo quieres filtrar tu búsqueda de eventos?" << endl;
    cout << "1. Buscar por nombre\n2. Mostrar por orden alfabético\n3. Mostrar por fecha"
            "\n4. Mostrar los eventos Vip y los No Vip" << endl;
    cin >> opcion;
    switch(opcion)
    {
    case '1':
    {
        cout << "Escribe el nombre del evento que quieres encontrar: ";
        cin >> nombre;
        for(size_t i = 0; i < eventos.size(); i ++)
        {
            if(eventos[i]->getNombre() == nombre)
            {
                eventos[i]->mostrarEvento();
                encontrado = true;
            }
        }
        if(!encontrado)
        {
            cout << "Evento no encontrado" << endl;
        }
        break;
    }
    case '2':
    {
        cout << "Opciones:\n1. Mostrar por nombre de la A a la Z\n2. Mostrar por nombre de la Z a la A\n";
        cin >> opcion;
        for(size_t i = 0; i < eventos.size(); i ++)
        {
            nombres.push_back(eventos[i]->getNombre());
        }
        sort(nombres.begin(), nombres.end()); //sort es una funcion de la libreria algoritm que me
        //ordena un vector (tanto de palabras, números) usando el operador <
        switch(opcion)
        {
        case '1':
        {
            for(size_t i = 0; i < nombres.size(); i ++)
            {
                for(size_t j = 0; j < nombres.size(); j ++)
                {
                    if(nombres[i] == eventos[j]->getNombre())
                    {
                        eventos[j]->mostrarEvento();
                    }
                }
            }
            break;
        }
        case '2':
        {
            reverse(nombres.begin(), nombres.end()); //uso la funcion reverse para invertir el orden
            //del vector, que estaba ya ordenado alfabéticamente con sort
            for(size_t i = 0; i < nombres.size(); i ++)
            {
                for(size_t j = 0; j < nombres.size(); j ++)
                {
                    if(nombres[i] == eventos[j]->getNombre())
                    {
                        eventos[j]->mostrarEvento();
                    }
                }
            }
            break;
        }
        default: cout << "Opcion incorrecta" << endl; break;
        }
        break;
    }
    case '3':
    {
        vector <int> fechas;

        cout << "Opciones:\n1. Orden cronológico ascendente\n2. Orden cronológico descendente\n";
        cin >> opcion;

        for(size_t i = 0; i < eventos.size(); i ++)
        {
            fechas.push_back(eventos[i]->getFecha());
        }
        sort(fechas.begin(), fechas.end());

        switch(opcion)
        {
        case '1':
        {
            for(size_t i = 0; i < fechas.size(); i ++)
            {
                for(size_t j = 0; j < fechas.size(); j ++)
                {
                    if(fechas[i] == eventos[j]->getFecha())
                    {
                        eventos[j]->mostrarEvento();
                    }
                }
            }
            break;
        }
        case '2':
        {
            reverse(fechas.begin(), fechas.end());

            for(size_t i = 0; i < fechas.size(); i ++)
            {
                for(size_t j = 0; j < fechas.size(); j ++)
                {
                    if(fechas[i] == eventos[j]->getFecha())
                    {
                        eventos[j]->mostrarEvento();
                    }
                }
            }
            break;
        }
        default: cout << "Opcion incorrecta" << endl; break;
        }
        break;
    }
    case '4':
    {
        mostrarEventos(eventos); break;
    }
    default: cout << "Opcion incorrecta" << endl; break;
    }
}

void Plataforma :: filtrarArtista(const vector<Usuario*>& usuarios)
{
    //preguntar que filtros quiere aplicar a la búsqueda: por orden alfabético (de A a Z o al revés),
    //por número de eventos (de mayor a menor o al revés), por eventos  en una localización,
    //es decir, que el usuario quiera buscar que artistas han hecho un evento en cierta localizacion
    //que simplemente quiera buscar un artista por su nombre y ver su información

    string nombre;
    vector <string> nombres;
    char opcion;
    bool encontrado = false;
    cout << "¿Cómo quieres filtrar tu búsqueda de artistas?" << endl;
    cout << "1. Buscar por nombre\n2. Mostrar por orden alfabético\n3. Mostrar por número de eventos\n";
    cin >> opcion;
    switch(opcion)
    {
    case '1':
    {
        cout << "Escribe el nombre de usuario del artista al que quieres encontrar: ";
        cin >> nombre;
        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if(usuarios[i]->getNombre() == nombre)
            {
                if (Artista* artista = dynamic_cast<Artista*>(usuarios[i]))
                {
                    artista->mostrarInfo(this);
                    encontrado = true;
                }
            }
        }
        if(!encontrado)
        {
            cout << "Artista no encontrado" << endl;
        }
        break;
    }
    case '2':
    {
        cout << "Opciones:\n1. Mostrar por nombre de la A a la Z\n2. Mostrar por nombre de la Z a la A\n";
        cin >> opcion;
        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if (Artista* artista = dynamic_cast<Artista*>(usuarios[i]))
            {
                //me creo un vector para meter todos los nombres de los artistas
                nombres.push_back(artista->getNombre());
            }
        }
        sort(nombres.begin(), nombres.end()); //sort es una funcion de la libreria algoritm que me
        //ordena un vector (tanto de palabras, números) usando el operador <
        switch(opcion)
        {
        case '1':
        {
            for(size_t i = 0; i < nombres.size(); i ++)
            {
                Artista* a = dynamic_cast<Artista*>(obtenerUsuario(nombres[i]));
                a->mostrarInfo(this);
                cout << endl;
            }
            break;
        }
        case '2':
        {
            reverse(nombres.begin(), nombres.end()); //uso la funcion reverse para invertir el orden
            //del vector, que estaba ya ordenado alfabéticamente con sort
            for(size_t i = 0; i < nombres.size(); i ++)
            {
                Artista* a = dynamic_cast<Artista*>(obtenerUsuario(nombres[i]));
                a->mostrarInfo(this);
                cout << endl;
            }
            break;
        }
        default: cout << "Opcion incorrecta" << endl; break;
        }
        break;
    case '3': //filtrar por numero de eventos
    {
        vector<Artista*> artistas;

        for(size_t i = 0; i < usuarios.size(); i ++)
        {
            if (Artista* a = dynamic_cast<Artista*>(usuarios[i]))
            {
                artistas.push_back(a); //relleno mi vector de artistas
            }
        }
        for (size_t i = 0; i < artistas.size(); i++)
        {
            for (size_t j = i + 1; j < artistas.size(); j++)
            {
                size_t numEventos1 = artistas[i]->getEventos().size();
                size_t numEventos2 = artistas[j]->getEventos().size();

                if (numEventos1 < numEventos2) {
                    // Intercambio punteros
                    Artista* temp = artistas[i];
                    artistas[i] = artistas[j];
                    artistas[j] = temp;
                }
            }
        }
        cout << "Opciones:\n1. De mayor a menor número de eventos\n2. De menor a mayor número"
                " de eventos\n";
        cin  >> opcion;
        switch(opcion)
        {
        case '1':
        {
            for(size_t i = 0; i < artistas.size(); i ++)
            {
                artistas[i]->mostrarInfo(this);
                cout << endl;
            }
            break;
        }
        case '2':
        {
            reverse(artistas.begin(), artistas.end());
            for(size_t i = 0; i < artistas.size(); i ++)
            {
                artistas[i]->mostrarInfo(this);
                cout << endl;
            }
            break;
        }
        default: cout << "Opcion incorrecta" << endl; break;
        }
    break;
    }
    default: cout << "Opcion incorrecta" << endl; break;
    }
    }
}

void Plataforma :: filtrarBusqueda(const vector<Usuario*>& usuarios, const vector <Evento*>& eventos, const vector <Localizacion*>& localizaciones)
{
    char opcion;
    cout << "Opciones de búsqueda filtrada:\n1. Filtros para artistas\n2. Filtros para eventos\n3.Filtros"
            " para localizaciones" << endl;
    cin >> opcion;
    switch(opcion)
    {
    case '1': this->filtrarArtista(usuarios); break;
    case '2': this->filtrarEvento(eventos); break;
    case '3': this->filtrarLocalizacion(localizaciones); break;
    default: cout << "Opcion incorrecta" << endl; break;
    }
}

int Plataforma :: obtenerFechaActual()
{
    time_t t = time(nullptr); //obtiene el tiempo actual del sistema
    tm* tm_actual = localtime(&t); //localtime devuelve un puntero a una estructura tm con la hora loca

    int anio = tm_actual->tm_year + 1900; //tm_year almacena el num de años  desde 1900,,
    //si estamos en 2025, tm será 125 y por eso le sumamos 1900
    int mes = tm_actual->tm_mon + 1; //tm_mon representa los meses pero enero es 0 (por eso +1)
    int dia = tm_actual->tm_mday;

    return anio * 10000 + mes * 100 + dia; //formato YYYYMMDD
}

int Plataforma :: obtenerFechaDentroDeUnMes()
{
    time_t t = time(nullptr);
    tm tm_mas_un_mes = *localtime(&t);
    tm_mas_un_mes.tm_mon += 1;
    mktime(&tm_mas_un_mes); // normaliza

    int anio = tm_mas_un_mes.tm_year + 1900;
    int mes = tm_mas_un_mes.tm_mon + 1;
    int dia = tm_mas_un_mes.tm_mday;

    return anio * 10000 + mes * 100 + dia;
}

void Plataforma :: guardarUsuarios(const vector<Usuario*>& usuarios)
{
    ofstream archivo("Usuarios.txt");
    if (!archivo)
    {
        cerr << "Error al abrir el archivo para guardar usuarios.\n";
        return;
    }
    //si se ha abierto/creado con exito el archivo:
    for (size_t i = 0;  i < usuarios.size(); i ++)
    {
        if (Administrador* admin = dynamic_cast<Administrador*>(usuarios[i])) {
            archivo << "Administrador " << admin->getNombre() << " " << admin->getContrasena() << endl;
        }
        else if (Artista* artista = dynamic_cast<Artista*>(usuarios[i])) {
            archivo << "Artista " << artista->getNombre() << " " << artista->getContrasena() << " "
                    << artista->getNombreArtista() << " " << artista->getEstiloMusical() << " "
                    << artista->getDescripcion() << endl;
        }
        else if (AsistenteNormal* normal = dynamic_cast<AsistenteNormal*>(usuarios[i]))
        {
            archivo << "Asistente no vip " << normal->getNombre() << " " << normal->getContrasena() << " "
                    << normal->getCartera() << " " << normal->getDNI() << " ";
            vector <Evento*> entradas = normal->getEntradas();
            for(size_t i = 0; i < entradas.size(); i ++)
            {
                archivo << entradas[i]->getNombre() << " ";
            }
        }
        else if (AsistenteVip* vip = dynamic_cast<AsistenteVip*>(usuarios[i])) {
            archivo << "Asistente vip " << vip->getNombre() << " " << vip->getContrasena() << " "
                    << vip->getCartera() << " " << vip->getDNI() << " ";
            vector <Evento*> entradas = vip->getEntradas();
            for(size_t i = 0; i < entradas.size(); i ++)
            {
                archivo << entradas[i]->getNombre() << " ";
            }
        }
    }
    archivo.close();
}

void Plataforma :: guardarEventos(const vector<Evento*>& eventos)
{
    ofstream output("Eventos.txt");
    if(!output)
    {
        cerr << "No se ha podido abrir el archivo para guardar eventos" << endl;
        return;
    }
    for(size_t i = 0; i < eventos.size(); i ++)
    {
        output << "Evento en " << eventos[i]->getLocation()->getNombre() << " | Fecha: " <<
               eventos[i]->getFecha() << " | Precio: " << eventos[i]->getPrecio() << " | VIP: ";
        if (eventos[i]->getEsVip())
            output << "Sí";
        else
            output << "No" << " | Entradas: " << eventos[i]->getEntradas() << endl;
    }
    output.close();
}

void Plataforma :: guardarLocalizaciones(const vector <Localizacion*>& localizaciones)
{
    ofstream output("Localizaciones.txt");
    if(!output)
    {
        cerr << "No se ha podido abrir el archivo para guardar localizaciones" << endl;
        return;
    }
    for(size_t i = 0; i < localizaciones.size(); i ++)
    {
        output << "Nombre: " << localizaciones[i]->getNombre() << " | Dirección: " <<
            localizaciones[i]->getDireccion() << "  | Aforo: " << localizaciones[i]->getAforo() <<
            " | Eventos reservados: ";
        vector <Evento*> reservados = localizaciones[i]->getReservados();
        for(size_t i = 0; i < reservados.size(); i ++)
        {
            output << reservados[i]->getNombre() << ", ";
        }
    }
    output.close();
}

void Plataforma :: mostrarUsuarios(const vector<Usuario*>& usuarios) const
{
    size_t admin_count = 0;
    size_t artist_count = 0;
    size_t asistent_count = 0;
    cout << "Lista de usuarios: \n";
    for (size_t i = 0; i < usuarios.size(); i ++)
    {
        if(Administrador* admin = dynamic_cast<Administrador*>(usuarios[i]))
        {
            cout << "•Administrador: ";
            cout << admin->getNombre() << endl;
            admin_count++;
        }
        else if(Artista* artista = dynamic_cast<Artista*>(usuarios[i]))
        {
            cout << "•Artista: ";
            cout << artista->getNombre() << endl;
            artist_count++;
        }
        else if(Asistente* asistente = dynamic_cast<Asistente*>(usuarios[i]))
        {
            cout << "•Asistente: ";
            cout << asistente->getNombre() << endl;
            asistent_count++;
        }
    }
    cout << "Número de usuarios registrados:\n•Administradores: "<< admin_count <<
        "\n•Asistentes: "<< asistent_count << "\n•Artistas: "<< artist_count <<
        "\n•Total usuarios: " <<  admin_count + asistent_count + artist_count << endl;
}

void Plataforma :: mostrarEventos(const vector <Evento*>& eventos) const
{
    cout << "Lista de eventos de la plataforma: \n";
    if(eventos.empty())
    {
        cout << "Actualmente no hay eventos en la plataforma" << endl;
        return;
    }
    cout << "Eventos VIP:" << endl;
    for(size_t i = 0; i < eventos.size(); i ++)
    {
        if(eventos[i]->getEsVip())
        {
            cout << eventos[i]->getNombre() << endl;
        }
    }
    cout << "Eventos NO VIP:" << endl;
    for(size_t i = 0; i < eventos.size(); i ++)
    {
        if(!eventos[i]->getEsVip())
        {
            cout << eventos[i]->getNombre() << endl;
        }
    }
}

int Plataforma :: buscarEvento(const string& nombreEvento) const
{
    for (size_t i = 0; i < eventos.size(); ++i)
    {
        if (eventos[i]->getNombre() == nombreEvento)
        {
            return static_cast <int>(i);
        }
    }
    return -1; // no encontrado
}

Evento* Plataforma :: obtenerEvento(const string& nombreEvento)
{
    int pos = buscarEvento(nombreEvento);
    if (pos != -1) {
        return eventos[pos];
    }
    return nullptr;
}

int Plataforma :: buscarUsuario(const string& nombre) const
{
    for (size_t i = 0; i < usuarios.size(); ++i)
    {
        if (usuarios[i]->getNombre() == nombre){
            return static_cast <int>(i);
        }
    }
    return -1; // no encontrado
}

Usuario* Plataforma :: obtenerUsuario(const string& nombre)
{
    int pos = buscarUsuario(nombre);
    if (pos != -1) {
        return usuarios[pos];
    }
    return nullptr;
}

int Plataforma:: buscarLocalizacion(const string& nombre) const
{
    for (size_t i = 0; i < localizaciones.size(); ++i)
    {
        if (localizaciones[i]->getNombre() == nombre){
            return static_cast <int>(i);
        }
    }
    return -1; // no encontrado
}

Localizacion* Plataforma :: obtenerLocalizacion(const string& nombre)
{
    int pos = buscarLocalizacion(nombre);
    if(pos != -1)
        return localizaciones[pos];
    return nullptr;
}

void Plataforma :: ejecutarOpcion(int opcion)
{
    if (!usuarioActual)
    {
        cout << "No has iniciado sesión.\n";
        return;
    }
    //estructura: dynamic_cast <tipo de la clase derivada*> (puntero a la clase base)
    //devuelve lo que está entre <> si la conversión es válida, es decir si el puntero de la base
    //está apuntando realmente a la clase derivada. Si la conversión no es válida devuelve nullptr(vector nulo)
    //me explico para este primer caso:
    //si usuarioActual apunta a un objeto que es de tipo administrador, devolverá un ptr a administrador.
    //si usuarioActual apunta a un artista o asistente, la conversión no será válida y se devolverá nullptr
    //(por lo que no entrará en el if).
    //lo mismo para los demás casos, así nos aseguramos de que cada "rol" solo pueda hacer cosas de su rol
    if (Administrador* admin = dynamic_cast<Administrador*>(usuarioActual))
    {
        switch (opcion)
        {
        case '0': usuarioActual = nullptr; break;
        case '1': mostrarUsuarios(usuarios); break;
        case '2': mostrarEventos(eventos); break;
        case '3': admin->crearUsuario(usuarios, this); break;
        case '4': admin->modificarUsuario(usuarios); break;
        case '5': admin->eliminarUsuario(usuarios); break;
        case '6': admin->verArtista(this); break;
        case '7': filtrarBusqueda(usuarios, eventos, localizaciones); break;
        case '8': verEstadisticas(usuarios, eventos, localizaciones); break;
        default: cout << "Opción no válida.\n"; break;
        }
    }
    else if (Artista* artista = dynamic_cast<Artista*>(usuarioActual))
    {
        switch (opcion)
        {
        case '0': usuarioActual = nullptr; break;
        case '1': mostrarUsuarios(usuarios); break;
        case '2': mostrarEventos(eventos); break;
        case '3': artista->crearEvento(eventos, this); break;
        case '4': artista->modificarEvento(this); break;
        case '5': artista->eliminarEvento(eventos, this); break;
        case '6': artista->verMisEventos(); break;
        case '7': filtrarBusqueda(usuarios, eventos, localizaciones); break;
        case '8': verEstadisticas(usuarios, eventos, localizaciones); break;
        default: cout << "Opción no válida.\n"; break;
        }
    }
    else if (AsistenteNormal* asistenteNormal = dynamic_cast<AsistenteNormal*>(usuarioActual))
    {
        switch (opcion)
        {
        case 'a': usuarioActual = nullptr; break;
        case 'b': mostrarUsuarios(usuarios); break;
        case 'c': mostrarEventos(eventos); break;
        case 'd': asistenteNormal->comprarEntradas(this); break;
        case 'e': asistenteNormal->venderEntradas(this); break;
        case 'f': asistenteNormal->verEntradas(); break;
        case 'g': asistenteNormal->verArtista(this); break;
        case 'h': asistenteNormal->verEventos(eventos, this); break;
        case 'i': asistenteNormal->verCartera(); break;
        case 'j': filtrarBusqueda(usuarios, eventos, localizaciones); break;
        case 'k': asistenteNormal->misRecompensas();break;
        case 'l': verEstadisticas(usuarios, eventos, localizaciones); break;
        default: cout << "Opción no válida.\n"; break;
        }
    }
    else if (AsistenteVip* asistenteVip = dynamic_cast<AsistenteVip*>(usuarioActual))
    {
        switch (opcion)
        {
        case 'a': usuarioActual = nullptr; break;
        case 'b': mostrarUsuarios(usuarios); break;
        case 'c': mostrarEventos(eventos); break;
        case 'd': asistenteVip->comprarEntradas(this); break;
        case 'e': asistenteVip->venderEntradas(this); break;
        case 'f': asistenteVip->verEntradas(); break;
        case 'g': asistenteVip->verArtista(this); break;
        case 'h': asistenteVip->verEventos(eventos, this); break;
        case 'i': asistenteVip->verCartera(); break;
        case 'j': filtrarBusqueda(usuarios, eventos, localizaciones); break;
        case 'k': asistenteVip->misRecompensas();break;
        case 'l': verEstadisticas(usuarios, eventos, localizaciones); break;
        default: cout << "Opción no válida.\n"; break;
        }
    }
}
