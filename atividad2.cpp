/* 
    Universidad del Valle de Guatemala
    Josue Hernández González - 2021111
    Programación de microprocesadores
    fecha:09-08-2025
    Laboratorio 3 - Actividad II
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

    pid_t hijo1= fork();

    if (hijo1 < 0) {
        perror("Error con hijo 1");
        return 1;

    }else if (hijo1 == 0) {
        // Hijo 1
        sleep(2);
        cout << "Hijo1 termina" << endl;
        return 0;

    } else {
        // Hijo 2
        pid_t hijo2 = fork();
        
        if (hijo2 < 0) {
            perror("Error con hijo2");
            return 1;
        }

        if (hijo2 == 0) {
            
            // Hijo 2
            sleep(5);
            cout << "Hijo2 termina en 5s." << endl;
            return 0;

        } else {

            //Padre
            int estado; //tipo de ejecucion
            pid_t primerHijoTerminar;

            primerHijoTerminar = wait(&estado);
            int nombreHijo;
            if (primerHijoTerminar == hijo1) {
                nombreHijo = 1;
            } else if (primerHijoTerminar == hijo2) {
                nombreHijo = 2;
            }
            cout << "Padre: Hijo " << nombreHijo << " terminó primero." << endl;

            // Espera al otro hijo
            wait(nullptr);

            cout << "Padre: Todos los hijos terminaron." << endl;
        }
    }

    return 0;
}
