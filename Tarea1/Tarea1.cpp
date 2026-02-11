#include <iostream> 
#include <string> 
using namespace std; 

class Perro{
private:
    string nombre;
    string raza;
    int energia;

public:
    Perro(string n, string r){
        nombre = n;
        raza = r;
        energia = 100;
}

    void jugar(int minutos){
        energia -= minutos;
        if (energia<0){
            energia = 0;
        }
        cout << nombre << " jugo " << minutos
        << " minutos. pero parece que le queda " << energia <<" '%' total de energia" <<endl;
    }

    void descansa(int minutos){
        energia += minutos;
        if (energia >100){
            energia = 100;
        }
        cout << nombre <<" lleva dormido " << minutos
        <<" minutos. ya tendra como " << energia << " '%' total de energia"<< endl;
    }

    void trucos() {
        cout << nombre << " sabe dar la pata." << endl;
    }

    void verInformacion(){
        cout << "Datos del Perro " << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Raza: " << raza << endl;
        cout << "Energia: " << energia << "total" << endl;
    };

};
int main() {
    Perro perro1("Luna", "Galgo");
    Perro perro2("volg", "Pastor Belga");
    perro1.verInformacion();
    perro1.trucos();
    perro1.jugar(30);
    perro1.descansa(15);


    perro2.verInformacion();
    perro2.trucos();
    perro2.jugar(60);
    perro2.descansa(40);

    return 0;
}
