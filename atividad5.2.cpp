/* 
    Universidad del Valle de Guatemala
    Josue Hernández González - 2021111
    Programación de microprocesadores
    fecha:09-08-2025
    Laboratorio 3 - Actividad V, - Hijo PID zombie con wait
*/
#include <iostream>
#include <unistd.h>    
#include <sys/wait.h>    

using namespace std;

int main() {
    cout << "Padre PID: " << getpid() << endl;

    pid_t hijo = fork();
    
    // Error al crear proceso
    if (hijo < 0) {
        cout << "ERROR: No pude crear el proceso hijo" << endl;
        return 1;
    }else if (hijo == 0) {
        //Hijo
        cout << "Hijo PID : " << getpid() << endl;
        sleep(1); 
        cout << "Hijo finalizo" << endl;
        exit(0);

    }
    else {
        //Padre hace wait() para evitar zombie
        wait(NULL);
        cout << "PADRE: durmiendo" << endl;
        sleep(15);
        cout << "Padre finaliza" << endl;
        
    }
    return 0;
}