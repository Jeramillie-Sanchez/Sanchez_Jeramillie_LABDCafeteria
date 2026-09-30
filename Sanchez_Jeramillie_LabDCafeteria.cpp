// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad D: Funciones
//  Laboratorio D: Cafeteria ITPR - Sistema de Pedidos
//  CODIGO BASE PARA EL ESTUDIANTE - LLENE LOS BLANCOS
//
//  Nombre del estudiante: Jeramillie Sanchez Aponte
//  Fecha: 9/30/2026
//
//  INSTRUCCIONES: sustituya cada blanco ____N____ por la palabra
//  o el valor correcto. Un mismo numero = la misma respuesta.
//  NO modifique ninguna otra parte del programa.
// ============================================================
#include <iostream>
#include <iomanip>   // fixed, setprecision, setw
#include <cmath>     // round//tells the computer to include the cmath libarary for the arithmetic fuctions
#include <string>    // string
#include <cctype>  // toupper//allows the computer to use the cctype library for the toupper fuction
using namespace std;

const double TASA_IVU = 0.115;   // IVU de Puerto Rico: 11.5%

// ------------------ PROTOTIPOS ------------------
// Parte A
void mostrarLinea(int largo, char simbolo);//creates a line of symbols for the start menu in a given space
void mostrarMenu();//displays the menu to the user in a given space
void imprimirFactura(string cliente, double subtotal, double ivu, double total);//shows the receipt to the user in a given space

// Parte B
double obtenerPrecio(int codigo);// to obtain the price in decimal format 
void obtenerNombre(int codigo);//for the user to give a name in agiven space
double calcularIVU(double subtotal);
int mayorDenominacion(int centavos);//

// Parte C
double redondear(double cantidad);//rounds the total to 2 decimal places
int    convertirACentavos(double dinero); //to convert the total to cents
string convertirMayusculas(string texto);//to convert the string to all uppercase letters

// Parte D
void mostrarCambio(int centavos);//to show the change to the user in a given space
void contarPiezas(int centavos);//for the user to be shown count the pieces of change in a given space

// ------------------ PROGRAMA PRINCIPAL (NO MODIFICAR) ------------------
int main() {
    char otro;
    do {
        int codigo, cantidad;
        double subtotal = 0;
        string cliente;

        mostrarMenu();
        cout << "Codigo del producto (0 para terminar): ";
        cin >> codigo;
        while (codigo != 0) {
            double precio = obtenerPrecio(codigo);
            if (precio < 0) {
                cout << "Codigo invalido." << endl;
            } else {
                cout << "Cantidad: ";
                cin >> cantidad;
                if (cantidad <= 0) {
                    cout << "La cantidad debe ser mayor que 0." << endl;
                } else {
                    subtotal = subtotal + precio * cantidad;
                    cout << fixed << setprecision(2);
                    cout << "  + " << cantidad << " x " << obtenerNombre(codigo)
                         << " = $" << precio * cantidad << endl;
                }
            }
            cout << "Codigo del producto (0 para terminar): ";
            cin >> codigo;
        }

        if (subtotal > 0) {
            cout << "Nombre del cliente: ";
            cin.ignore();
            getline(cin, cliente);

            subtotal = redondear(subtotal);
            double ivu = calcularIVU(subtotal);
            double total = redondear(subtotal + ivu);
            imprimirFactura(convertirMayusculas(cliente), subtotal, ivu, total);

            double pago;
            cout << "Pago recibido: $";
            cin >> pago;
            while (convertirACentavos(pago) < convertirACentavos(total)) {
                cout << "Pago insuficiente. Pago recibido: $";
                cin >> pago;
            }
            int cambio = convertirACentavos(pago) - convertirACentavos(total);
            cout << "Cambio: $" << cambio / 100.0 << endl;
            if (cambio > 0) {
                cout << "Entregar:" << endl;
                mostrarCambio(cambio);
                cout << "Total de piezas: " << contarPiezas(cambio) << endl;
            }
        } else {
            cout << "No se registro ningun producto." << endl;
        }

        cout << "Atender otro cliente? (S/N): ";
        cin >> otro;
    } while (toupper(otro) == 'S');

    cout << "Cafeteria cerrada. Buen provecho!" << endl;
    return 0;
}

// ------------------ DEFINICIONES ------------------

// dibuja una linea de simbolos
void mostrarLinea(int largo, char simbolo) {
    for (int i = 0; i < largo; i++)
        cout << simbolo;
    cout << endl;
}//Draws a line for the start menu in a given space

// muestra el menu de la cafeteria
void mostrarMenu() {
    cout << endl;
    mostrarLinea(42, '=');
    cout << "        CAFETERIA ITPR - MANATI" << endl;
    mostrarLinea(42, '=');
    cout << fixed << setprecision(2);
    for (int c = 1; c <= 5; c++)
        cout << c << ". " << left << setw(28) << obtenerNombre(c)
             << "$" << right << setw(5) << obtenerPrecio(c) << endl;
    mostrarLinea(42, '-');
}

// imprime la factura
void imprimirFactura(string cliente, double subtotal, double ivu, double total) {// This fuction gives the recept to the user in a given space
    mostrarLinea(42, '-');
    cout << "Cliente:   " << cliente << endl;
    cout << fixed << setprecision(2);
    cout << "Subtotal:  $" << setw(8) << subtotal << endl;
    cout << "IVU 11.5%: $" << setw(8) << ivu << endl;
    cout << "TOTAL:     $" << setw(8) << total << endl; //displays the total to the user
    mostrarLinea(42, '-');
}

// precio del producto, o un valor especial si el codigo no existe
double obtenerPrecio (int codigo) {//fuction to give the price of the product based on the case number in the switch codition
    switch (codigo) {
        case 1: return 1.25;
        case 2: return 3.50;
        case 3: return 1.75;
        case 4: return 1.50;
        case 5: return 6.95;
        default: return -1;//in case no case number is givin the computer will default to this line and display -1 to the user 
    }
}

// nombre del producto
string obtenerNombre (int codigo) { //fuction to give the name of the product based on the case number in the switch codition
    switch (codigo) {
        case 1: return "Cafe con leche"; 
        case 2: return "Sandwich de jamon y queso";
        case 3: return "Empanadilla de pizza";
        case 4: return "Jugo de china";
        case 5: return "Almuerzo del dia";
        default: return "Desconocido";//What the computer will show you based on the case number if return isn't present the computer shows nothing
    }
}

// IVU redondeado al centavo
double calcularIVU(double subtotal) {// This fuction calculates the tax based on the subtotal and the tax rate and rounds it to 2 decimal places
    return redondear(subtotal * TASA_IVU);
}

// la denominacion mas grande (en centavos) que cabe en 'centavos'
int mayorDenominacion(int centavos) {//shows the change based on the cents calculated by the system and then is displayed to the user
    if (centavos >= 2000) return 2000;   // billete de $20
    if (centavos >= 1000) return 1000;   // billete de $10
    if (centavos >= 500)  return 500;    // billete de $5 //shows the varible for 5 dollors in change
    if (centavos >= 100)  return 100;    // billete de $1
    if (centavos >= 25)   return 25;     // peseta
    if (centavos >= 10)   return 10;     // vellon de 10
    if (centavos >= 5)    return 5;      // vellon de 5
    return 1;                            // chavito
}

// redondea a 2 decimales
double redondear(double cantidad) {
    return round(cantidad * 100) / 100.0; //this fuction rounds the total by taking the total multiplying by 100 then diving by 100.0 to get 2 decimal places 
}

// convierte dolares a centavos enteros
int convertirACentavos(double dinero) {
    return (int)redondear(dinero * 100);//converts the total to cents by multiplying by 100 and rounding it to the nearest whole number 
}

// convierte a mayusculas
string convertirMayusculas(string texto) {
    for (size_t i = 0; i < texto.length(); i++)
        texto[i] = toupper(texto[i]);
    return texto;// returns the string in all uppercase letters
}

// RECURSIVA: muestra cada billete o moneda del cambio
// Caso base: ya no queda cambio por entregar
void mostrarCambio(int centavos) {
    if (centavos == 0) //if cents = 0 show nothing                  // caso base
        return;
    int d = mayorDenominacion(centavos);
    cout << "  - $" << d / 100.0 << endl;
    mostararCambio(centavos - d);         // caso recursivo
}

// RECURSIVA: cuenta cuantas piezas tiene el cambio
// Caso base: ya no queda cambio por contar
int contarPiezas(int centavos) {
    if (centavos == 0)                   // caso base
        return 0;
    return 1 + contarPiezas(centavos - mayorDenominacion(centavos)); // caso recursivo
}
