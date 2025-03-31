#include <iostream>
#include <string>

using namespace std;

class cuentaBancaria {
    protected:
    /*
    protected para balance y titularCuenta porque me permite que las clases derivadas accedan a estos atributos sin exponerlos públicamente.
    No uso private porque necesito que CajaDeAhorro y CuentaCorriente los modifiquen directamente.
    */
        string titularCuenta;
        double balance;
    public:
        cuentaBancaria(const string& titular, double saldoInicial);
        void depositar(double cantidad);
        virtual void retirar(double cantidad) = 0;
        virtual void mostrarInfo() const = 0;
        virtual ~cuentaBancaria() {}
};

/*
public para métodos que interactúan con el usuario porque 
depositar(), retirar() y mostrarInfo() deben ser accesibles desde el .cpp. (donde tengo el main)
*/

class cajaDeAhorro : public cuentaBancaria {
    private:
        mutable int vecesMostrarInfo = 0; // mutable porque necesito modificarlo en un método const.
    public:
        cajaDeAhorro(const string& titular, double saldoInicial);
        void retirar(double cantidad) override;
        void mostrarInfo() const override;
        friend class cuentaCorriente; 
        /*
        Uso de friend en CuentaCorriente porque me
        Permite que CuentaCorriente acceda al balance de CajaDeAhorro cuando necesite retirar dinero.
        */
    };

class cuentaCorriente : public cuentaBancaria {
public:
    cajaDeAhorro* cajaAhorro;

    cuentaCorriente(const string& titular, double saldoInicial, cajaDeAhorro* cajaAhorro);
    void retirar(double cantidad) override;
    void mostrarInfo() const override;
};






