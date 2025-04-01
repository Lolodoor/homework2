#include "main.h"

Estudiante::Estudiante(string nombre, int legajo) : nombre(nombre), legajo(legajo) {}

string Estudiante::getNombre() const {
    return nombre;
}

int Estudiante::getLegajo() const {
    return legajo;
}

float Estudiante::getPromedio() const {
    if (cursos.empty()) return 0.0;
    float suma = 0;
    int totalNotas = 0;
    for (size_t i = 0; i < cursos.size(); i++) {
        for(size_t j = 0; j < cursos[i].second.size(); j++) {
            suma += cursos[i].second[j];
            totalNotas++;
        }
    }
    if (totalNotas == 0) return 0.0;
    return suma / totalNotas;
}

void Estudiante::agregarCurso(const string& nombreCurso, const vector<int>& notas) {
    cursos.push_back({nombreCurso, notas}); 
}


ostream& operator<<(ostream& os, const Estudiante& e) {
    os << "Nombre: " << e.nombre << ", Legajo: " << e.legajo 
       << ", Promedio: " << e.getPromedio();
    return os;
}

Curso::Curso(string nombre) : nombre(nombre) {}

string Curso::getNombre() const {
    return nombre;
}

void Curso::inscribirEstudiante(shared_ptr<Estudiante> estudiante, const vector<int>& notas) {
    if (cursoCompleto()) {
        cout << "El curso está completo" << endl;
        return;
    }
    if (seEncuentraElEstudiante(estudiante->getLegajo())) {
        cout << "El estudiante ya está inscrito en el curso" << endl;
        return;
    }
    estudiante->agregarCurso(nombre, notas);
    estudiantes.push_back(estudiante); 
}


void Curso::desinscribirEstudiante(int legajo) {
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i]->getLegajo() == legajo) {
            cout << "Se desinscribió a " << estudiantes[i]->getNombre() << " del curso " << nombre << endl;
            estudiantes.erase(estudiantes.begin() + i);
            return;
        }
    }
    cout << "No se encontró al estudiante con legajo " << legajo << " en el curso " << nombre << endl;
}

bool Curso::seEncuentraElEstudiante(int legajo) const {
    for(size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i]->getLegajo() == legajo) return true;
    }
    return false;
}

bool Curso::cursoCompleto() const {
    return estudiantes.size() >= capacidadCurso;
}

void Curso::imprimirListaEstudiantes() const {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes inscritos en el curso " << nombre << endl;
        return;
    }
    
    vector<shared_ptr<Estudiante>> copia = estudiantes;
    sort(copia.begin(), copia.end());
    
    cout << "Curso: " << nombre << "\nLista de estudiantes (orden alfabético):" << endl;
    for(size_t i = 0; i < copia.size(); i++) {
        cout << *copia[i] << endl;
    }    
}

ostream& operator<<(ostream& os, const Curso& c) {
    os << "Curso: " << c.nombre << ", Capacidad: " << c.capacidadCurso << ", Inscritos: " << c.estudiantes.size();
    return os;
}

bool operator<(const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b) {
    return a->getNombre() < b->getNombre();
}


int main() {
    vector<Curso> cursos;
    vector<shared_ptr<Estudiante>> estudiantes;
    int opcion = 0;

    while (opcion != 6) {
        cout << "Seleccione una opción:\n"
             << "1. Inscribir estudiante\n"
             << "2. Desinscribir estudiante\n"
             << "3. Ver lista de estudiantes\n"
             << "4. Verificar si un estudiante está inscrito\n"
             << "5. Verificar si un curso está completo\n"
             << "6. Salir\n"
             << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombreEst, nombreCurso;
                int legajo;
                vector<int> notas;
                int nota;

                cout << "Ingrese nombre del estudiante: ";
                cin >> nombreEst;
                cout << "Ingrese legajo: ";
                cin >> legajo;
                cout << "Ingrese nombre del curso: ";
                cin.ignore(); 
                getline(cin, nombreCurso); 

                shared_ptr<Estudiante> estudianteExistente = nullptr;
                for (size_t i = 0; i < estudiantes.size(); i++) {
                    if (estudiantes[i]->getLegajo() == legajo) {
                        estudianteExistente = estudiantes[i];
                        break;
                    }
                }


                if (!estudianteExistente) {
                    estudianteExistente = make_shared<Estudiante>(nombreEst, legajo);
                    estudiantes.push_back(estudianteExistente);
                }

      
                cout << "Ingrese notas del estudiante (-1 para terminar): ";
                while (cin >> nota && nota != -1) {
                    notas.push_back(nota);
                }

            
                bool cursoExiste = false;
                for (size_t i = 0; i < cursos.size(); i++) {
                    if (cursos[i].getNombre() == nombreCurso) {
                        // Inscribir al estudiante en el curso
                        cursos[i].inscribirEstudiante(estudianteExistente, notas);
                        cursoExiste = true;
                        break;
                    }
                }

            
                if (!cursoExiste) {
                    cursos.emplace_back(nombreCurso);
                    cursos.back().inscribirEstudiante(estudianteExistente, notas); 
                }

                break;


            }
            case 2: {
                int legajo;
                string nombreCurso;
                cout << "Ingrese el legajo del estudiante a desinscribir: ";
                cin >> legajo;
                cout << "Ingrese el nombre del curso: ";
                cin >> nombreCurso;
            
                bool cursoEncontrado = false;
                for (size_t i = 0; i < cursos.size(); i++) {
                    if (cursos[i].getNombre() == nombreCurso) {
                        cursos[i].desinscribirEstudiante(legajo);
                        cursoEncontrado = true;
                        break;
                    }
                }
            
                if (!cursoEncontrado) {
                    cout << "El curso no existe o el estudiante no está inscrito en él." << endl;
                }
                break;
            }
            case 3: {
                for (size_t i = 0; i < cursos.size(); i++) {
                    cursos[i].imprimirListaEstudiantes();
                }
                break;
            }
            case 4: {
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                bool encontrado = false;
                for (size_t i = 0; i < cursos.size(); i++) {
                    if (cursos[i].seEncuentraElEstudiante(legajo)) {
                        cout << "El estudiante está inscrito en el curso " << cursos[i].getNombre() << endl;
                        encontrado = true;
                    }
                }
                if (!encontrado) {
                    cout << "El estudiante no está inscrito en ningún curso." << endl;
                }
                break;
            }
            case 5: {
                for (size_t i = 0; i < cursos.size(); i++) {
                    cout << cursos[i] << endl;
                }
                break;
            }
        }
    }
    return 0;
}
