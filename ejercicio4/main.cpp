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
    // Crear una caja de ahorro y una cuenta corriente asociada
    cajaDeAhorro caja("Juan Perez", 200);
    cuentaCorriente cuenta("Juan Perez", 100, &caja);

    // Estado inicial
    cout << "--- Estado Inicial ---" << endl;
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    // Depósito en la cuenta corriente
    cout << "\n--- Depositando $50 en la cuenta corriente ---" << endl;
    cuenta.depositar(50);
    cuenta.mostrarInfo();

    // Retiro válido desde la cuenta corriente
    cout << "\n--- Retirando $100 desde la cuenta corriente ---" << endl;
    cuenta.retirar(100);
    cuenta.mostrarInfo();

    // Retiro válido que combina fondos de la cuenta corriente y la caja de ahorro
    cout << "\n--- Retirando $150 (combinando fondos de ambas cuentas) ---" << endl;
    cuenta.retirar(150);
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    // Intento de retiro que excede los fondos de ambas cuentas
    cout << "\n--- Intentando retirar $300 (debería fallar) ---" << endl;
    cuenta.retirar(300);
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    // Mostrar información de la caja de ahorro más de 2 veces para aplicar el descuento
    cout << "\n--- Mostrando información de la caja de ahorro más de 2 veces ---" << endl;
    caja.mostrarInfo();
    caja.mostrarInfo();
    caja.mostrarInfo(); // Aquí se aplica el descuento de $20
    caja.mostrarInfo();

    // Depósito en la caja de ahorro
    cout << "\n--- Depositando $100 en la caja de ahorro ---" << endl;
    caja.depositar(100);
    caja.mostrarInfo();

    // Retiro válido desde la caja de ahorro
    cout << "\n--- Retirando $50 desde la caja de ahorro ---" << endl;
    caja.retirar(50);
    caja.mostrarInfo();

    // Intento de retiro inválido (cantidad negativa)
    cout << "\n--- Intentando retirar una cantidad negativa (-$50) ---" << endl;
    cuenta.retirar(-50);

    // Intento de retiro inválido (cantidad mayor al balance de la caja de ahorro)
    cout << "\n--- Intentando retirar $500 desde la caja de ahorro (debería fallar) ---" << endl;
    caja.retirar(500);

    // Estado final
    cout << "\n--- Estado Final ---" << endl;
    cuenta.mostrarInfo();
    caja.mostrarInfo();

    return 0;
}