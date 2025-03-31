#include "main.h"

Time::Time() : hour(0), minutes(0), seconds(0), period("a.m.") {}

Time::Time(int h) : Time() { 
    setHour(h);
}
Time::Time(int h, int m) : Time() { 
    setHour(h);
    setMinutes(m);
}
Time::Time(int h, int m, int s) : Time() { 
    setHour(h);
    setMinutes(m);
    setSeconds(s);
}
Time::Time(int h, int m, int s, const string &p) {
    setHour(h);
    setMinutes(m);
    setSeconds(s);
    setPeriod(p);
}

void Time::setHour(int h) { 
    while (h < 1 || h > 12) {
        cout << "Hora inválida. Ingrese una hora entre 1 y 12: ";
        cin >> h;
    }
    hour = h;
}
void Time::setMinutes(int m) { 
    while (m < 0 || m > 59) {
        cout << "Minutos inválidos. Ingrese una cantidad de minutos entre 0 y 59: ";
        cin >> m;
    }
    minutes = m;
}
void Time::setSeconds(int s) { 
    while (s < 0 || s > 59) {
        cout << "Segundos inválidos. Ingrese una cantidad de segundos entre 0 y 59: ";
        cin >> s;
    }
    seconds = s;
}
void Time::setPeriod(const string &p) { 
    string new_p = p;
    while (new_p!= "a.m." && new_p != "p.m.") {
        cout << "Periodo inválido. Ingrese 'a.m.' o 'p.m.': ";
        cin >> new_p;
    }

    period = new_p;
}

int Time::getHour() const { 
    return hour; 
}
int Time::getMinutes() const { 
    return minutes; 
}
int Time::getSeconds() const { 
    return seconds; 
}
string Time::getPeriod() const { 
    return period; 
}

string Time::get12hFormat() const {
    ostringstream oss; 
    oss << setfill('0') << setw(2) << hour << "h, "
        << setw(2) << minutes << "m, "
        << setw(2) << seconds << "s "
        << period;
    return oss.str();
}

string Time::get24hFormat() const {
    int h24 = hour;
    if (period == "a.m." && hour == 12) h24 = 0;
    if (period == "p.m." && hour != 12) h24 += 12;

    ostringstream oss;
    oss << setfill('0') << setw(2) << h24 << ":"
        << setw(2) << minutes << ":"
        << setw(2) << seconds;
    return oss.str();
}

int main() {
    Time t;
    int opcion = 0; 
    
    while(opcion != 8){
        cout <<"1. Inicializar por defecto\n";
        cout <<"2. Inicializar con hora\n";
        cout <<"3. Inicializar con hora y minutos\n";
        cout <<"4. Inicializar con hora, minutos y segundos\n";
        cout <<"5. Inicializar con hora, minutos, segundos y periodo\n";
        cout <<"6. Leer tiempo\n";
        cout <<"7. Cambiar tiempo\n";
        cout <<"8. Salir\n";
        cout <<"Seleccione una opción: ";
        cin >> opcion;

        int h, m, s;
        string p;
        
        switch(opcion){
            case 1:
                t = Time();
                break;
            case 2:
                cout << "Ingrese la hora: ";
                cin >> h;
                t = Time(h);
                break;
            case 3:
                cout << "Ingrese la hora: ";
                cin >> h;
                cout << "Ingrese los minutos: ";
                cin >> m;
                t = Time(h, m);
                break;
            case 4:
                cout << "Ingrese la hora: ";
                cin >> h;
                cout << "Ingrese los minutos: ";
                cin >> m;
                cout << "Ingrese los segundos: ";
                cin >> s;
                t = Time(h, m, s);
                break;
            case 5:
                cout << "Ingrese la hora: ";
                cin >> h;
                cout << "Ingrese los minutos: ";
                cin >> m;
                cout << "Ingrese los segundos: ";
                cin >> s;
                cout << "Ingrese el periodo (a.m. / p.m.): ";
                cin >> p;
                t = Time(h, m, s, p);
                break;
            case 6: {
                int sub_opcion;
                cout << "¿Qué desea ver?\n";
                cout << "1. Ver hora\n";
                cout << "2. Ver minutos\n";
                cout << "3. Ver segundos\n";
                cout << "4. Ver periodo\n";
                cout << "5. Ver todo el tiempo (12h y 24h)\n";
                cout << "Seleccione una opción: ";
                cin >> sub_opcion;
                
                if (t.getHour() == 0 && t.getMinutes() == 0 && t.getSeconds() == 0 && t.getPeriod() == "a.m.") {
                    cout << "El tiempo aún no ha sido asignado.\n";
                    break;
                }

                switch(sub_opcion) {
                    case 1: cout << "Hora: " << t.getHour() << endl; break;
                    case 2: cout << "Minutos: " << t.getMinutes() << endl; break;
                    case 3: cout << "Segundos: " << t.getSeconds() << endl; break;
                    case 4: cout << "Periodo: " << t.getPeriod() << endl; break;
                    case 5:
                        cout << "Formato 12h: " << t.get12hFormat() << endl;
                        cout << "Formato 24h: " << t.get24hFormat() << endl;
                        break;
                    default: cout << "Opción inválida.\n"; break;
                }
                break;
            }
            case 7: {
                int sub_opcion;
                cout << "¿Qué desea cambiar?\n";
                cout << "1. Cambiar hora\n";
                cout << "2. Cambiar minutos\n";
                cout << "3. Cambiar segundos\n";
                cout << "4. Cambiar periodo\n";
                cout << "Seleccione una opción: ";
                cin >> sub_opcion;

                switch(sub_opcion) {
                    case 1:
                        cout << "Ingrese la hora: ";
                        cin >> h;
                        t.setHour(h);
                        break;
                    case 2:
                        cout << "Ingrese los minutos: ";
                        cin >> m;
                        t.setMinutes(m);
                        break;
                    case 3:
                        cout << "Ingrese los segundos: ";
                        cin >> s;
                        t.setSeconds(s);
                        break;
                    case 4:
                        cout << "Ingrese el periodo (a.m. / p.m.): ";
                        cin >> p;
                        t.setPeriod(p);
                        break;
                    default:
                        cout << "Opción inválida.\n";
                        break;
                }
                break;
            }
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
                break;
        }
    }
    return 0;
}