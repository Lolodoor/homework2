#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
class Numero {
public:
    virtual Numero* suma(const Numero& otro) const = 0;
    virtual Numero* resta(const Numero& otro) const = 0;
    virtual Numero* multiplicacion(const Numero& otro) const = 0;
    virtual Numero* division(const Numero& otro) const = 0;
    virtual string toString() const = 0;
    virtual ~Numero() {}
};

class Entero : public Numero {
private:
    int valor;
public:
    Entero(int valor);
    Numero* suma(const Numero& otro) const override;
    Numero* resta(const Numero& otro) const override;
    Numero* multiplicacion(const Numero& otro) const override;
    Numero* division(const Numero& otro) const override;
    string toString() const override;
};

class Real : public Numero {
private:
    double valor;
public:
    Real(double valor);
    Numero* suma(const Numero& otro) const override;
    Numero* resta(const Numero& otro) const override;
    Numero* multiplicacion(const Numero& otro) const override;
    Numero* division(const Numero& otro) const override;
    string toString() const override;
};

class Complejo : public Numero {
private:
    double real;
    double imaginario;
public:
    Complejo(double real, double imaginario);
    Numero* suma(const Numero& otro) const override;
    Numero* resta(const Numero& otro) const override;
    Numero* multiplicacion(const Numero& otro) const override;
    Numero* division(const Numero& otro) const override;
    string toString() const override;
};
