/* 
    Universidad del Valle de Guatemala
    Josue Hernández González - 2021111
    Programación de microprocesadores
    fecha:09-08-2025
    Laboratorio 3 - Actividad IV
*/


#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main() {

    pid_t hijo;
    
    cout << "Proceso padre PID: " << getpid() << endl << endl;

    
    // Crear 3 procesos hijos
    for (int i = 1; i <= 3; i++) {
        hijo = fork();
        
        if (hijo < 0) {
            // Error al crear proceso
            cout << "Error al crear proceso hijo" << endl;
            exit(1);
        }
        else if (hijo == 0) {
            // Código del proceso hijo
            cout << "Hijo " << i << " PID: " << getpid() << ": Inicio de tarea" << endl;

            // simulacion de calculo pesado
            sleep(5);
            cout << "Hijo " << i << " PID: " << getpid() << ": Fin de tarea" << endl;
            
            // Terminar proceso hijo
            exit(0);
        }
        
        // El proceso padre continúa en el bucle para crear más hijos
    }
    
    // Padre finalizando
    cout << "Padre PID: " << getpid() << ": Tareas enviadas" << endl;

    // Procesos huérfanos
    cout << "Los procesos hijos continuarán ejecutándose como huérfanos" << endl;
    
    return 0;
}