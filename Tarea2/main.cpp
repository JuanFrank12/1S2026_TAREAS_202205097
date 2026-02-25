#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void mostrarArchivosInventario(){
    ifstream archivo("1inventario.inv");

    if(!archivo.is_open()){
        cout << "Ocurrio un error con el archivo."<<endl;
        return;
    }

    string producto, ubicacion;
    int cantidad;
    double precio;

    cout << "\n Productos en Inventario: " << endl;
    cout << "\n--------------------------" << endl;

    while (archivo >> producto >> cantidad >> precio >> ubicacion){
        cout << "Producto: " << producto
         << ", Cantidad: " << cantidad
         << ", Precio: " << precio
         << ", Ubicacion: " << ubicacion << endl;        
    }

}

int main() {
    int opcion;
    do {
        cout << "Menu de opciones: " << endl;
        cout << "1. Ver Inventario" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarArchivosInventario();
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 2);

    return 0;
}




