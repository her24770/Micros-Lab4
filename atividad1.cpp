/* 
    Universidad del Valle de Guatemala
    Josue Hernández González - 2021111
    Programación de microprocesadores
    fecha:09-08-2025
    Laboratorio 3 - Actividad I
*/

#include <iostream>
#include <unistd.h> 
#include <sys/types.h> 

using namespace std;

int main() {
    // Crear un proceso hijo
    pid_t hijo = fork();

    // respuesta de fork si hay un error
    if (hijo < 0) { 
        cerr << "Error en el proceso del hijo" << endl;
        return 1;

    } else if (hijo > 0) {

        // ciclo del padre
        for (int i = 0; i < 3; i++) {
            cout << "Soy el padre" << endl;
            sleep(2); // cada 2 segundos
        }

    } else {

        // ciclo del hijo
        for (int i = 0; i < 6; i++) {
            cout << "Soy el hijo" << endl;
            sleep(1); // cada segundo
        }
    }

    return 0;
}
