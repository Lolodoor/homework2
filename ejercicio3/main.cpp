#include "main.h"

// Implementación de Entero
Entero::Entero(int valor) : valor(valor) {}

Numero* Entero::suma(const Numero& otro) const {
    const Entero& otroEntero = dynamic_cast<const Entero&>(otro);
    return new Entero(valor + otroEntero.valor);
}

Numero* Entero::resta(const Numero& otro) const {
    const Entero& otroEntero = dynamic_cast<const Entero&>(otro);
    return new Entero(valor - otroEntero.valor);
}

Numero* Entero::multiplicacion(const Numero& otro) const {
    const Entero& otroEntero = dynamic_cast<const Entero&>(otro);
    return new Entero(valor * otroEntero.valor);
}

Numero* Entero::division(const Numero& otro) const {
    const Entero& otroEntero = dynamic_cast<const Entero&>(otro);
    if (otroEntero.valor == 0) {
        throw runtime_error("No se puede dividir por 0");
    }
    return new Entero(valor / otroEntero.valor);
}

string Entero::toString() const {
    return to_string(valor);
}

// Implementación de Real
Real::Real(double valor) : valor(valor) {}

Numero* Real::suma(const Numero& otro) const {
    const Real& otroReal = dynamic_cast<const Real&>(otro);
    return new Real(valor + otroReal.valor);
}

Numero* Real::resta(const Numero& otro) const {
    const Real& otroReal = dynamic_cast<const Real&>(otro);
    return new Real(valor - otroReal.valor);
}

Numero* Real::multiplicacion(const Numero& otro) const {
    const Real& otroReal = dynamic_cast<const Real&>(otro);
    return new Real(valor * otroReal.valor);
}

Numero* Real::division(const Numero& otro) const {
    const Real& otroReal = dynamic_cast<const Real&>(otro);
    if (otroReal.valor == 0) {
        throw runtime_error("No se puede dividir por 0");
    }
    return new Real(valor / otroReal.valor);
}

string Real::toString() const {
    return to_string(valor);
}

// Implementación de Complejo
Complejo::Complejo(double real, double imaginario) : real(real), imaginario(imaginario) {}

Numero* Complejo::suma(const Numero& otro) const {
    const Complejo& otroComplejo = dynamic_cast<const Complejo&>(otro);
    return new Complejo(real + otroComplejo.real, imaginario + otroComplejo.imaginario);
}

Numero* Complejo::resta(const Numero& otro) const {
    const Complejo& otroComplejo = dynamic_cast<const Complejo&>(otro);
    return new Complejo(real - otroComplejo.real, imaginario - otroComplejo.imaginario);
}

Numero* Complejo::multiplicacion(const Numero& otro) const {
    const Complejo& otroComplejo = dynamic_cast<const Complejo&>(otro);
    double nuevaReal = real * otroComplejo.real - imaginario * otroComplejo.imaginario;
    double nuevaImag = real * otroComplejo.imaginario + imaginario * otroComplejo.real;
    return new Complejo(nuevaReal, nuevaImag);
}

Numero* Complejo::division(const Numero& otro) const {
    const Complejo& otroComplejo = dynamic_cast<const Complejo&>(otro);
    if (otroComplejo.real == 0 && otroComplejo.imaginario == 0) {
        throw runtime_error("No se puede dividir por 0");
    }
    double denominador = otroComplejo.real * otroComplejo.real + otroComplejo.imaginario * otroComplejo.imaginario;
    double parteReal = (real * otroComplejo.real + imaginario * otroComplejo.imaginario) / denominador;
    double parteImaginaria = (imaginario * otroComplejo.real - real * otroComplejo.imaginario) / denominador;
    return new Complejo(parteReal, parteImaginaria);
}

string Complejo::toString() const {
    return to_string(real) + (imaginario >= 0 ? " + " : " - ") + to_string(abs(imaginario)) + "i";
}



int main() {
    try {
        Entero entero1(10);
        Entero entero2(2);

        cout << "\n===== ENTEROS =====\n";
        cout << "Numero 1: " << entero1.toString() << endl;
        cout << "Numero 2: " << entero2.toString() << endl;

        Numero* sumaEntero = entero1.suma(entero2);
        cout << "Suma: " << sumaEntero->toString() << endl;
        delete sumaEntero;

        Numero* restaEntero = entero1.resta(entero2);
        cout << "Resta: " << restaEntero->toString() << endl;
        delete restaEntero;

        Numero* multiEntero = entero1.multiplicacion(entero2);
        cout << "Multiplicacion: " << multiEntero->toString() << endl;
        delete multiEntero;

        Numero* divEntero = entero1.division(entero2);
        cout << "Division: " << divEntero->toString() << endl;
        delete divEntero;

        Real real1(5.5);
        Real real2(2.0);

        cout << "\n===== REALES =====\n";
        cout << "Numero 1: " << real1.toString() << endl;
        cout << "Numero 2: " << real2.toString() << endl;

        Numero* sumaReal = real1.suma(real2);
        cout << "Suma: " << sumaReal->toString() << endl;
        delete sumaReal;

        Numero* restaReal = real1.resta(real2);
        cout << "Resta: " << restaReal->toString() << endl;
        delete restaReal;

        Numero* multiReal = real1.multiplicacion(real2);
        cout << "Multiplicacion: " << multiReal->toString() << endl;
        delete multiReal;

        Numero* divReal = real1.division(real2);
        cout << "Division: " << divReal->toString() << endl;
        delete divReal;

        Complejo complejo1(2, 3); // 2 + 3i
        Complejo complejo2(1, 4); // 1 + 4i

        cout << "\n===== COMPLEJOS =====\n";
        cout << "Numero 1: " << complejo1.toString() << endl;
        cout << "Numero 2: " << complejo2.toString() << endl;

        Numero* sumaComplejo = complejo1.suma(complejo2);
        cout << "Suma: " << sumaComplejo->toString() << endl;
        delete sumaComplejo;

        Numero* restaComplejo = complejo1.resta(complejo2);
        cout << "Resta: " << restaComplejo->toString() << endl;
        delete restaComplejo;

        Numero* multiComplejo = complejo1.multiplicacion(complejo2);
        cout << "Multiplicacion: " << multiComplejo->toString() << endl;
        delete multiComplejo;

        Numero* divComplejo = complejo1.division(complejo2);
        cout << "Division: " << divComplejo->toString() << endl;
        delete divComplejo;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}