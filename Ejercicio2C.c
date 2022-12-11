#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


void main(void){

    int tp[2];
    pipe(tp); //Tuberia de mensajes padre hijo

    int th[2];
    pipe(th); //Tuberia de mensajes hijo padre


    int resultadoFork = fork(); //Crear un proceso hijo

        switch(resultadoFork){ //Dividimos lo que realiza cada proceso... (Hijo / Padre)
            case -1: //En caso de error...
                printf("Ha ocurrido un error inesperado\n");
                break;
                
            case 0: //Hijo
                for (int i = 0; i < 10; i++) { //Bucle repetitivo de 10 intentos
                    char buzonH[24];

                    char mensajeH[24] = "Mensaje ";
                    mensajeH[8] = '0'+i;
                    strcat(mensajeH, " hijo a padre");

                    read(tp[0], buzonH, 24); //Leemos la tuberia donde deja mensajes el padre al hijo
                    printf("\tHijo lee: %s\n", buzonH); //Mostramos mensaje
                    
                    write(th[1],mensajeH, 24); //Escribimos la tuberia donde deja mensajes el hijo al padre
                }
                break;
            
            default: //Padre
                for (int i = 0; i < 10; i++) { //Bucle repetitivo de 10 intentos
                    char buzonP[24];

                    char mensajeP[24] = "Mensaje ";
                    mensajeP[8] = '0'+i;
                    strcat(mensajeP, " padre a hijo");

                    write(tp[1], mensajeP, 24); //Escribimos la tuberia donde deja mensajes el padre al hijo

                    read(th[0], buzonP, 24); //Leemos la tuberia donde deja mensajes el hijo al padre
                    printf("Padre lee: %s\n", buzonP); //Mostramos mensaje
                }
                wait(NULL); //Espera por el proceso hijo
        }		
    
}