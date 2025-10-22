#include <iostream>
#include <locale>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream> // ?? Para guardar facturas en archivo
using namespace std;

struct producto {
    int id;
    string nombre;
    float precio;
    int cantidad;
    bool disponible;
}; producto productos[20];

struct factura {
    string numero;
    string cliente;
    string nit;
    string producto;
    int cantidad;
    float total;
    bool activa;
}; factura facturas[50];

int totalprodu = 0;
int totalfacturas = 0;

// ================= FUNCIONES DE PRODUCTOS =================
void ingresarprodu() {
    cout << "==== INGRESE EL PRODUCTO ====" << endl;
    cout << "Ingrese el ID del producto: ";
    cin >> productos[totalprodu].id;
    cin.ignore();
    cout << "Ingrese el nombre del producto: ";
    getline(cin, productos[totalprodu].nombre);
    cout << "Ingrese el precio: ";
    cin >> productos[totalprodu].precio;
    cout << "Ingrese la cantidad: ";
    cin >> productos[totalprodu].cantidad;

    productos[totalprodu].disponible = true;
    totalprodu++;
    cout << "Producto ingresado correctamente." << endl << endl;
}

void mostrarprodu() {
    cout << "==== LISTA DE PRODUCTOS ====" << endl;
    for (int i = 0; i < totalprodu; i++) {
        if (productos[i].disponible) {
            cout << "ID: " << productos[i].id << endl;
            cout << "Nombre: " << productos[i].nombre << endl;
            cout << "Precio: Q" << productos[i].precio << endl;
            cout << "Cantidad: " << productos[i].cantidad << endl;
            cout << endl;
        }
    }
}

void modificarprodu() {
    int id;
    cout << "Ingrese el ID del producto a modificar: ";
    cin >> id;
    for (int i = 0; i < totalprodu; i++) {
        if (productos[i].id == id && productos[i].disponible) {
            cout << "Ingrese un nuevo nombre: ";
            cin.ignore();
            getline(cin, productos[i].nombre);
            cout << "Ingrese un nuevo precio: ";
            cin >> productos[i].precio;
            cout << "Ingrese una nueva cantidad: ";
            cin >> productos[i].cantidad;
            cout << "Producto modificado correctamente." << endl;
            return;
        }
    }
    cout << "No se encontró el producto." << endl;
}

// ================= FUNCIONES DE FACTURACIÓN =================

// Genera número aleatorio de factura con prefijo y 10 caracteres alfanuméricos
string generarNumeroFactura() {
    string letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string numeros = "0123456789";
    string codigo = "FAC-"; // prefijo fijo

    srand(time(0) + rand());

    for (int i = 0; i < 10; i++) {
        if (rand() % 2 == 0)
            codigo += letras[rand() % letras.size()];  // letra
        else
            codigo += numeros[rand() % numeros.size()]; // número
    }
    return codigo;
}

// Guardar factura en archivo
void guardarFacturaArchivo(factura f) {
    ofstream archivo("facturas.txt", ios::app); // modo append (añadir al final)
    if (archivo.is_open()) {
        archivo << "======================================\n";
        archivo << "Número de Factura: " << f.numero << "\n";
        archivo << "Cliente: " << f.cliente << "\n";
        archivo << "NIT: " << f.nit << "\n";
        archivo << "Producto: " << f.producto << "\n";
        archivo << "Cantidad: " << f.cantidad << "\n";
        archivo << "Total: Q" << f.total << "\n";
        archivo << "======================================\n\n";
        archivo.close();
    } else {
        cout << "?? Error al guardar la factura en el archivo." << endl;
    }
}

// Crear factura
void crearFactura() {
    string cliente, nit;
    int idProd, cantidad;
    bool encontrado = false;

    cout << "==== CREAR FACTURA ====" << endl;
    cout << "Ingrese el nombre del cliente: ";
    cin.ignore();
    getline(cin, cliente);
    cout << "Ingrese el NIT: ";
    getline(cin, nit);

    mostrarprodu();
    cout << "Ingrese el ID del producto a facturar: ";
    cin >> idProd;
    cout << "Ingrese la cantidad: ";
    cin >> cantidad;

    for (int i = 0; i < totalprodu; i++) {
        if (productos[i].id == idProd && productos[i].disponible) {
            if (cantidad > productos[i].cantidad) {
                cout << "No hay suficiente inventario." << endl;
                return;
            }

            productos[i].cantidad -= cantidad;

            facturas[totalfacturas].numero = generarNumeroFactura();
            facturas[totalfacturas].cliente = cliente;
            facturas[totalfacturas].nit = nit;
            facturas[totalfacturas].producto = productos[i].nombre;
            facturas[totalfacturas].cantidad = cantidad;
            facturas[totalfacturas].total = productos[i].precio * cantidad;
            facturas[totalfacturas].activa = true;

            // Guardar en archivo
            guardarFacturaArchivo(facturas[totalfacturas]);

            totalfacturas++;

            cout << "\n=== FACTURA GENERADA ===" << endl;
            cout << "Número: " << facturas[totalfacturas - 1].numero << endl;
            cout << "Cliente: " << cliente << endl;
            cout << "NIT: " << nit << endl;
            cout << "Producto: " << productos[i].nombre << endl;
            cout << "Cantidad: " << cantidad << endl;
            cout << "Total a pagar: Q" << facturas[totalfacturas - 1].total << endl;
            cout << "==========================" << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        cout << "No se encontró el producto." << endl;
}

// Eliminar factura
void eliminarFactura() {
    string codigo;
    cout << "Ingrese el número de factura a eliminar: ";
    cin.ignore();
    getline(cin, codigo);

    for (int i = 0; i < totalfacturas; i++) {
        if (facturas[i].numero == codigo && facturas[i].activa) {
            facturas[i].activa = false;
            cout << "Factura eliminada correctamente." << endl;
            return;
        }
    }
    cout << "No se encontró la factura." << endl;
}

// Buscar factura por cliente
void buscarFacturaCliente() {
    string cliente;
    cout << "Ingrese el nombre del cliente: ";
    cin.ignore();
    getline(cin, cliente);

    bool encontrado = false;
    for (int i = 0; i < totalfacturas; i++) {
        if (facturas[i].cliente == cliente && facturas[i].activa) {
            cout << "\nFactura No: " << facturas[i].numero << endl;
            cout << "Cliente: " << facturas[i].cliente << endl;
            cout << "Producto: " << facturas[i].producto << endl;
            cout << "Cantidad: " << facturas[i].cantidad << endl;
            cout << "Total: Q" << facturas[i].total << endl;
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontraron facturas para este cliente." << endl;
}

// Buscar factura por producto
void buscarFacturaProducto() {
    string nombreProd;
    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, nombreProd);

    bool encontrado = false;
    for (int i = 0; i < totalfacturas; i++) {
        if (facturas[i].producto == nombreProd && facturas[i].activa) {
            cout << "\nFactura No: " << facturas[i].numero << endl;
            cout << "Cliente: " << facturas[i].cliente << endl;
            cout << "Producto: " << facturas[i].producto << endl;
            cout << "Cantidad: " << facturas[i].cantidad << endl;
            cout << "Total: Q" << facturas[i].total << endl;
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontraron facturas para este producto." << endl;
}

// Menú de facturación
void facturar() {
    int opcion;
    do {
        cout << "\n==== MENÚ DE FACTURACIÓN ====" << endl;
        cout << "1. Crear factura" << endl;
        cout << "2. Eliminar factura" << endl;
        cout << "3. Buscar factura por cliente" << endl;
        cout << "4. Buscar factura por producto" << endl;
        cout << "0. Regresar" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: crearFactura(); break;
        case 2: eliminarFactura(); break;
        case 3: buscarFacturaCliente(); break;
        case 4: buscarFacturaProducto(); break;
        case 0: cout << "Regresando al menú principal..." << endl; break;
        default: cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);
}

// ================= MENÚ PRINCIPAL =================
int main() {
    setlocale(LC_ALL, "");
    int opcion;
    do {
        cout << "\n===== TIENDA ELECTRÓNICA =====" << endl;
        cout << "1. Ingresar productos" << endl;
        cout << "2. Mostrar productos" << endl;
        cout << "3. Modificar producto" << endl;
        cout << "4. Facturación" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: ingresarprodu(); break;
        case 2: mostrarprodu(); break;
        case 3: modificarprodu(); break;
        case 4: facturar(); break;
        case 0: cout << "Saliendo del programa..." << endl; break;
        default: cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);

    return 0;
}

