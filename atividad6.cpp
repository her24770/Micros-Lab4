    /* 
        Universidad del Valle de Guatemala
        Josue Hernández González - 2021111
        Programación de microprocesadores
        fecha:09-08-2025
        Laboratorio 3 - Actividad VI
    */

    #include <iostream>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <cstdlib>

    using namespace std;

    int main() {
        // Crear dos pipes
        int pipe_p_h[2];
        int pipe_h_p[2];

        cout << "Padre PID: " << getpid() << endl;
        
        // Crear el primer pipe (padre -> hijo)
        if (pipe(pipe_p_h) == -1 || pipe(pipe_h_p) == -1) {
            perror("Error creando pipes");
            return 1;
        }
        
        pid_t hijo = fork();
        
        if (hijo < 0) {
            perror("Error creando hijo");
            return 1;
        }
        else if (hijo == 0) {
            cout << "Hijo PID:" << getpid() << endl;

            // Cerrar extremos sin usar
            close(pipe_p_h[1]); //escritura
            close(pipe_h_p[0]); //lectura

            // Leer el número enviado por el padre
            int dato;
            if (read(pipe_p_h[0], &dato, sizeof(int)) == -1) {
                perror("HIJO: Error leyendo del pipe");
                exit(1);
            }
            // Calcular el cuadrado
            int resultadto = dato * dato;
            cout << "HIJO: Calculé el cuadrado: " << resultadto << endl;

            // Enviar el resultado al padre
            cout << "HIJO: Enviando resultado al padre..." << endl;
            if (write(pipe_h_p[1], &resultadto, sizeof(int)) == -1) {
                perror("HIJO: Error escribiendo al pipe");
                exit(1);
            }
            
            // Cerrar pipes restantes
            close(pipe_p_h[0]);
            close(pipe_h_p[1]);
            
            cout << "Hijo termino" << endl;
            exit(0);
        }
        else {
            //Padre
            
            // Cerrar extremos que no uso
            close(pipe_p_h[0]); //lectura
            close(pipe_h_p[1]); //escritura

            // Número a enviar (puedes cambiarlo)
            int enviar = 7;
            cout << "PADRE: Enviando número " << enviar << " al hijo..." << endl;

            // Enviar número al hijo
            if (write(pipe_p_h[1], &enviar, sizeof(int)) == -1) {
                perror("PADRE: Error escribiendo al pipe");
                return 1;
            }
            
            // Leer la respuesta del hijo
            int resultado;
            if (read(pipe_h_p[0], &resultado, sizeof(int)) == -1) {
                perror("PADRE: Error leyendo del pipe");
                return 1;
            }
            
            // Mostrar el resultado
            cout << "PADRE: El cuadrado de " << enviar << " es: " << resultado << endl;
            
            // Cerrar pipes restantes
            close(pipe_p_h[1]);
            close(pipe_h_p[0]);
            
            // wait
            wait(NULL);
            cout << "Padre termina" << endl;
        }
        
        return 0;
    }