#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream> 
#include <algorithm>

using namespace std;

struct Item {
    string nombre;
    double precio;
};

struct Factura {
    string numero;
    string nombreCliente;
    string telefonoCliente;
    vector<Item> items;
    double total;
};

vector<Factura> facturas;

void registrar_factura() {
    const double precioCerdo = 2.50;
    const double precioPollo = 1.50;
    const double precioCarne = 2.00;
    const double precioMatahambre = 2.75;
    
    string numero, nombreCliente, telefonoCliente;
    vector<Item> items;
    double total = 0.0;
    int opcion, cantidad;

    cout << "Ingresar los datos del cliente\n";
    cout << "Ingrese el numero de factura: ";
    cin >> numero;
    cout << "Nombre: ";
    cin.ignore(); 
    getline(cin, nombreCliente);
    cout << "Telefono: ";
    cin >> telefonoCliente;

    while (true) {
        cout << "\nSeleccione el s�ndwich\n";
        cout <<"------ Todos los combos incluyen gaseosa ------\n";
        cout << "1) S�ndwich cerdo + papas fritas = $2.50\n";
        cout << "2) S�ndwich pollo + papas fritas = $1.50\n";
        cout << "3) S�ndwich carne + papas fritas = $2.00\n";
        cout << "4) S�ndwich mathambre + papas fritas = $2.75\n";
        cout << "5) Salir y Calcular Total\n";
        
        cout << "Ingrese la opci�n: ";
        cin >> opcion;

        if (opcion == 5) {
            break;
        }

        cout << "Ingrese la cantidad: ";
        cin >> cantidad;

        switch (opcion) {
            case 1:
                items.push_back({"S�ndwich cerdo + papas fritas", precioCerdo * cantidad});
                total += precioCerdo * cantidad;
                break;
            case 2:
                items.push_back({"S�ndwich pollo + papas fritas", precioPollo * cantidad});
                total += precioPollo * cantidad;
                break;
            case 3:
                items.push_back({"S�ndwich carne + papas fritas", precioCarne * cantidad});
                total += precioCarne * cantidad;
                break;
            case 4:
                items.push_back({"S�ndwich matahambre + papas fritas", precioMatahambre * cantidad});
                total += precioMatahambre * cantidad;
                break;
            default:
                cout << "Ingrese un n�mero v�lido\n";
                continue;
        }
    }

    Factura factura = { numero, nombreCliente, telefonoCliente, items, total };
    facturas.push_back(factura);
}

string formatear_facturas() {
    stringstream ss;
    if (facturas.empty()) {
        ss << "No existen facturas registradas\n";
    } else {
        for (const auto& factura : facturas) {
            ss << "Datos del cliente\n";
            ss << "Nombre: " << factura.nombreCliente << "\n";
            ss << "Telefono: " << factura.telefonoCliente << "\n";
            ss << "Numero de factura: " << factura.numero << "\n\n";
            ss << "Items:\n";
            for (const auto& item : factura.items) {
                ss << item.nombre << " - $" << fixed << setprecision(2) << item.precio << "\n";
            }
            ss << "\nTotal a pagar: $" << fixed << setprecision(2) << factura.total << "\n\n";
        }
    }
    return ss.str();
}

void guardar_facturas_en_archivo(const string& ruta) {
    ofstream archivo(ruta, ios::out | ios::trunc); 
    if (archivo.is_open()) {
        archivo << formatear_facturas();
        archivo.close();
        cout << "Facturas guardadas exitosamente en " << ruta << endl;
    } else {
        cerr << "Error al tratar de abrir el archivo\n";
    }
}

void mostrar_detalle_factura() {
    string numeroFactura;
    cout << "�Qu� n�mero de factura desea ver?: ";
    cin >> numeroFactura;

    for (const auto& factura : facturas) {
        if (factura.numero == numeroFactura) {
            cout << "Datos del cliente\n";
            cout << "Nombre: " << factura.nombreCliente << "\n";
            cout << "Telefono: " << factura.telefonoCliente << "\n";
            cout << "Numero de factura: " << factura.numero << "\n\n";
            cout << "Items:\n";
            for (const auto& item : factura.items) {
                cout << item.nombre << " - $" << fixed << setprecision(2) << item.precio << "\n";
            }
            cout << "\nTotal a pagar: $" << fixed << setprecision(2) << factura.total << "\n\n";
            return; 
        }
    }
    cout << "Factura no encontrada.\n";
}

void eliminar_factura() {
    string numeroFactura;
    cout << "Ingrese el n�mero de factura que desea eliminar: ";
    cin >> numeroFactura;

    auto it = remove_if(facturas.begin(), facturas.end(), [&](const Factura& f) {
        return f.numero == numeroFactura;
    });

    if (it != facturas.end()) {
        facturas.erase(it, facturas.end());
        cout << "Factura eliminada exitosamente.\n";
        guardar_facturas_en_archivo("factura.txt"); 
    } else {
        cout << "Factura no encontrada.\n";
    }
}

void principal() {
    while (true) {
        int opcion;
        cout << "----------------RESTAURANTE MATHAMBRE----------\n";
        cout << "\n** Bienvenido(a) **\n";
        cout << "\n�Qu� acci�n desea realizar?\n";
        cout << "1) Registrar factura\n";
        cout << "2) Mostrar facturas\n";
        cout << "3) Mostrar detalle de una factura\n";
        cout << "4) Guardar facturas en archivo\n";
        cout << "5) Actualizar/Eliminar factura\n";
        cout << "6) Salir\n";
        cout << "\nIngrese la opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar_factura();
                break;
            case 2:
                cout << formatear_facturas();
                break;
            case 3:
                mostrar_detalle_factura();
                break;
            case 4:
                guardar_facturas_en_archivo("factura.txt");
                break;
            case 5:
                eliminar_factura();
                break;
            case 6:
                cout << "Usted sali� del sistema\n";
                return;
            default:
                cout << "Ingrese una opci�n del 1 al 6\n";
        }
    }
}

int main() {
    principal();
    return 0;
}

