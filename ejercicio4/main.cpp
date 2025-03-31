#include "main.h"

cuentaBancaria::cuentaBancaria(const string& titular, double saldoInicial) : titularCuenta(titular), balance(saldoInicial) {}

void cuentaBancaria::depositar(double cantidad) {
    balance += cantidad;
}

cajaDeAhorro::cajaDeAhorro(const string& titular, double saldoInicial)
    : cuentaBancaria(titular, saldoInicial) {}

void cajaDeAhorro::retirar(double cantidad) {
    if (cantidad <= 0 || cantidad > balance) {
        cout << "Error: No se puede retirar más dinero del que hay en el balance." << endl;
    } else {
        balance -= cantidad;
    }
}

void cajaDeAhorro::mostrarInfo() const {
    cout << "Titular: " << titularCuenta << endl;
    cout << "Tipo de cuenta: Caja de Ahorro" << endl;
    cout << "Balance: $" << balance << endl;

    vecesMostrarInfo++;
    if (vecesMostrarInfo > 2) {
        cout << "Se ha descontado $20 del balance por mostrar la información más de 2 veces." << endl;
        const_cast<cajaDeAhorro*>(this)->balance -= 20;
    }
}

cuentaCorriente::cuentaCorriente(const string& titular, double saldoInicial, cajaDeAhorro* cajaAhorro) : cuentaBancaria(titular, saldoInicial), cajaAhorro(cajaAhorro) {}

void cuentaCorriente::retirar(double cantidad) {
    if (cantidad <= 0) {
        cout << "Error: La cantidad a retirar debe ser mayor a 0." << endl;
        return;
    }

    if (cantidad <= balance) {
        balance -= cantidad;
    } else if (cajaAhorro->balance >= cantidad) {
        cout << "Fondos insuficientes en cuenta corriente. Retirando de Caja de Ahorro..." << endl;
        cajaAhorro->balance -= cantidad;
    } else {
        cout << "Error: No hay suficiente dinero en ninguna de las cuentas." << endl;
    }
}

void cuentaCorriente::mostrarInfo() const {
    cout << "Titular: " << titularCuenta << endl;
    cout << "Tipo de cuenta: Cuenta Corriente" << endl;
    cout << "Balance: $" << balance << endl;
}


int main() {
    cajaDeAhorro caja("Juan Perez", 200);
    cuentaCorriente cuenta("Juan Perez", 100, &caja);

    cout << "--- Estado Inicial ---" <<endl;
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    cout << "\n--- Retirando $150 ---" <<endl;
    cuenta.retirar(150);
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    cout << "\n--- Retirando $200 (debería fallar) ---" <<endl;
    cuenta.retirar(200);

    cout << "\n--- Mostrando información más de 2 veces ---" <<endl;
    caja.mostrarInfo();
    caja.mostrarInfo();
    caja.mostrarInfo(); // Aquí se aplica el descuento de $20

    return 0;
}
