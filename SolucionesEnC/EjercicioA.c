#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main(void){
    int fork1;
    int fork2;

    fork1 = fork(); //Crear un primer proceso hijo


    switch(fork1){ //Dividimos lo que realiza cada proceso... (Hijo / Padre)
        case -1: //En caso de error...
            printf("Ha ocurrido un error inesperado\n");
            break;
            
        case 0: //Hijo 1
            sleep(10); //Dormir el proceso hijo durante 10 segundos
            printf("Hijo 1 finaliza \n"); //Mensaje del primer hijo
            break;

        default: //Padre
            fork2 = fork(); //Crear un segundo proceso hijo

            switch(fork2){ //Dividimos lo que realiza cada proceso... (Hijo / Padre)
                case -1: //En caso de error...
                    printf("Ha ocurrido un error inesperado\n");
                    break;

                case 0: // Hijo 2	
                    sleep(10); //Dormir el proceso hijo durante 10 segundos
                    printf("Hijo 2 finaliza \n"); //Mensaje del segundo hijo
                    break;

                default: //Padre
                    wait(NULL); //Espera por uno de los dos hijos
                    wait(NULL); //Espera por el otro de los dos hijos
                    printf("Padre finaliza\n"); //Mensaje del padre
            }		
        }	

}
