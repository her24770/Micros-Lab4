/* 
    Universidad del Valle de Guatemala
    Josue Hernández González - 2021111
    Programación de microprocesadores
    fecha:09-08-2025
    Laboratorio 3 - Actividad III
*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
    pid_t hijo=fork();
    if (hijo < 0) {
        cout << "Error al crear hijo" << endl;
    }else if(hijo  > 0){
        //Padre
        cout << "Soy el padre, mi PID es: " << getpid() << endl;
        //esperar a su hijo
        wait(nullptr);
        cout << "Padre termina" << endl;
    }else{
        pid_t nieto = fork();
        if(nieto <0){
            cout << "Error al crear nieto" << endl;
        }else if(nieto > 0){
            //Hijo
            cout << "Soy el hijo, mi PID es: " << getpid() << endl;
            //esperar a l nieto
            wait(nullptr);
            cout << "Hijo termina" << endl;
        }else{
            pid_t bisnieto = fork();
            if(bisnieto < 0){
                cout << "Error al crear bisnieto" << endl;
            }else if(bisnieto > 0){
                //Nieto
                cout << "Soy el nieto, mi PID es: " << getpid() << endl;
                //esperar al bisnieto
                wait(nullptr);
                cout << "Nieto termina" << endl;
            }else{
                //Bisnieto
                cout << "Soy el bisnieto, mi PID es: " << getpid() << endl;
                cout << "Bisnieto termina" << endl;
            }
        }
    }
    return 0;
}