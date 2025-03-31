#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

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
    bool operator<(const Estudiante& otro) const;
    friend ostream& operator<<(ostream& os, const Estudiante& e);
};



class Curso {
private:
    string nombre;
    vector<std::shared_ptr<Estudiante>> estudiantes;
    static constexpr int capacidadCurso = 20;

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