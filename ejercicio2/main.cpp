#include "main.h"

Estudiante::Estudiante(string nombre, int legajo) : nombre(nombre), legajo(legajo) {}

string Estudiante::getNombre() const { return nombre; }
int Estudiante::getLegajo() const { return legajo; }

float Estudiante::getPromedio() const {
    if (cursos.empty()) return 0.0;
    float suma = 0;
    int totalNotas = 0;
    for (const auto& curso : cursos) {
        for (int nota : curso.second) {
            suma += nota;
            totalNotas++;
        }
    }
    if (totalNotas == 0) return 0.0;
    return suma / totalNotas;
}

void Estudiante::agregarCurso(const string& nombreCurso, const vector<int>& notas) {
    cursos.push_back({nombreCurso, notas});
}

bool Estudiante::operator<(const Estudiante& otro) const {
    return nombre < otro.nombre; 
}

ostream& operator<<(ostream& os, const Estudiante& e) {
    os << "Nombre: " << e.nombre << ", Legajo: " << e.legajo << ", Promedio: " << e.getPromedio();
    return os;
}

Curso::Curso(string nombre) : nombre(nombre) {}

string Curso::getNombre() const { return nombre; }

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
            estudiantes.erase(estudiantes.begin() + i);
            return;
        }
    }
}

bool Curso::seEncuentraElEstudiante(int legajo) const {
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i]->getLegajo() == legajo) {
            return true;
        }
    }
    return false;
}

bool Curso::cursoCompleto() const {
    return estudiantes.size() >= capacidadCurso;
}

void imprimirTodosLosEstudiantes(const vector<shared_ptr<Estudiante>>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    // Ordenar alfabéticamente
    vector<shared_ptr<Estudiante>> copia = estudiantes;
    sort(copia.begin(), copia.end(), [](const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b) {
        return *a < *b;
    });

    // Imprimir cada estudiante con su promedio total
    cout << "Lista de todos los estudiantes:\n";
    for (const auto& estudiante : copia) {
        cout << "Nombre: " << estudiante->getNombre()
             << ", Legajo: " << estudiante->getLegajo()
             << ", Promedio: " << estudiante->getPromedio() << endl;
    }
}



ostream& operator<<(ostream& os, const Curso& c) {
    os << "Curso: " << c.nombre << ", Capacidad: " << c.capacidadCurso << ", Inscritos: " << c.estudiantes.size();
    return os;
}

int main() {
    vector<Curso> cursos;
    vector<shared_ptr<Estudiante>> estudiantes;
    int opcion = 0;

    while (opcion != 6) {
        cout << "Seleccione una opción:\n1. Inscribir estudiante\n2. Desinscribir estudiante\n3. Ver lista de estudiantes\n4. Verificar si un estudiante está inscrito\n5. Verificar si un curso está completo\n6. Salir\nSeleccione una opción: ";
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
                cin >> nombreCurso;
                cout << "Ingrese notas del estudiante (-1 para terminar): ";
                while (cin >> nota && nota != -1) notas.push_back(nota);
            
                // Buscar si el estudiante ya existe
                shared_ptr<Estudiante> estudianteExistente = nullptr;
                for (const auto& est : estudiantes) {
                    if (est->getLegajo() == legajo) {
                        estudianteExistente = est;
                        break;
                    }
                }
            
                // Si no existe, crearlo y agregarlo
                if (!estudianteExistente) {
                    estudianteExistente = make_shared<Estudiante>(nombreEst, legajo);
                    estudiantes.emplace_back(estudianteExistente);
                }
            
                // Inscribirlo en el curso
                bool cursoExiste = false;
                for (Curso& curso : cursos) {
                    if (curso.getNombre() == nombreCurso) {
                        curso.inscribirEstudiante(estudianteExistente, notas);
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
                for (Curso& curso : cursos) {
                    if (curso.getNombre() == nombreCurso) {
                        curso.desinscribirEstudiante(legajo);
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
                imprimirTodosLosEstudiantes(estudiantes);
                break;
            }
            
            
            case 4: {
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                bool encontrado = false;
                for (const Curso& curso : cursos) {
                    if (curso.seEncuentraElEstudiante(legajo)) {
                        cout << "El estudiante está inscrito en el curso " << curso.getNombre() << endl;
                        encontrado = true;
                    }
                }
                if (!encontrado) cout << "El estudiante no está inscrito en ningún curso." << endl;
                break;
            }
            case 5:
                for (const Curso& curso : cursos) {
                    cout << "Curso " << curso.getNombre() << (curso.cursoCompleto() ? " está completo." : " tiene espacio disponible.") << endl;
                }
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    }
    return 0;
}
