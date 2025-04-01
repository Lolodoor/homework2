#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <limits>

using namespace std;

class Estudiante {
    private:
        string nombre;
        int legajo;
        vector<pair<string, vector<int>>> cursos;

    public:
        Estudiante(string nombre, int legajo);
        string getNombre() const;
        int getLegajo() const;
        float getPromedio() const;
        void agregarCurso(const string& nombreCurso, const vector<int>& notas);
        
        friend ostream& operator<<(ostream& os, const Estudiante& e);
};


bool operator<(const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b); 

class Curso {
    private:
        string nombre;
        vector<shared_ptr<Estudiante>> estudiantes;
        static const int capacidadCurso = 20;

    public:
        Curso(string nombre);
        string getNombre() const;
        void inscribirEstudiante(shared_ptr<Estudiante> estudiante, const vector<int>& notas);
        void desinscribirEstudiante(int legajo);
        bool seEncuentraElEstudiante(int legajo) const;
        bool cursoCompleto() const;
        void imprimirListaEstudiantes() const;

        friend ostream& operator<<(ostream& os, const Curso& c);
};

// La copia de un curso es una copia superficial, ya que los estudiantes se gestionan con shared_ptr.
// Al copiar un curso, se copian los punteros, no los objetos, por lo que los cursos comparten las mismas
// instancias de estudiantes sin duplicarlos en memoria. Esto permite que los cambios en un estudiante
// se reflejen en todos los cursos donde está inscrito.


// La relación entre `Curso` y `Estudiante` es de agregación.
// Un curso contiene estudiantes, pero no los posee en exclusividad. Los estudiantes existen
// independientemente de los cursos y pueden estar en varios cursos, lo que se gestiona con shared_ptr.

