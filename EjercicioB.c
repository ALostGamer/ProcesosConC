#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>


void main(void){
    int resultadoFork;

    srand(time(0)); //Semilla de numero aleatorio, generada por ejecucion de programa
    system("touch canal"); //Creamos un archivo temporal llamado "canal"


    resultadoFork = fork(); //Crear un proceso hijo

    switch(resultadoFork){ //Dividimos lo que realiza cada proceso... (Hijo / Padre)
        case -1: //En caso de error...
            printf("Ha ocurrido un error inesperado\n");
            break;

        case 0: //Hijo
            char cadenaAzarH[11];
            int descLeer = open("canal",0); //Generamos un descriptor con el archivo a leer, abriendolo en modo lectura

            int resLeer;
            
            while((resLeer = read(descLeer, cadenaAzarH, 11)) == 0){}; //Lectura... si no hay nada a leer el proceso se queda buscando que leer
            
            printf("\tHijo lee: %s\n"), cadenaAzarH; //Una vez ya leido se termina el proceso de busqueda y se muestra la lectura
            close(descLeer); //Cerramos el descriptor de lectura
            
            break;
        
        default: //Padre
            char cadenaAzarP[11];
            int numAzar = rand(); //Generamos un numero aleatorio

            sprintf(cadenaAzarP,"%d",numAzar); //Convertir a formato de tipo texto

            cadenaAzarP[10]='\0'; //Al finalizar la escritura colocamos un signo de cierre para que se sepa donde se cierra la cadena

            int descEscritura = open("canal", 1); //Generamos un descriptor con el archivo a escribir, abriendolo en modo escritura

            write(descEscritura, cadenaAzarP, 11); //Escribimos sobre el archivo
            printf("Padre escribe: %s\n", cadenaAzarP); //Mostramos mensaje

            wait(NULL); //Espera por el proceso hijo
            
            close(descEscritura); //Cerramos el descriptor de escritura
            system("rm canal"); //Eliminamos el archivo temporal llamado "canal"
    }		

}	