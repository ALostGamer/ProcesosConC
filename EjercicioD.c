#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void fManSig1(int sgnl){ //Signal 10
	printf("El proceso %d ha recibido señal %d\n",getpid(),sgnl);
	printf("continuo...\n");
};
void fManSig2(int sgnl){ //Signal 12
	int pid=getpid();
	printf("El proceso %d ha recibido señal %d\n",pid,sgnl);
	printf("proceso con id: %d, finalizando...\n",pid);
	exit(0);
};

void main(void){

	signal(SIGUSR1,fManSig1);
	signal(SIGUSR2,fManSig2);

	int resultadoFork = fork(); //Crear un proceso hijo

	switch(resultadoFork){ //Dividimos lo que realiza cada proceso... (Hijo / Padre)
		case -1: //En caso de error...
			printf("Ha ocurrido un error inesperado\n");
		break;

		case 0: //Hijo
		{
			int ppidP = getppid(); //Almacen de ppid de proceso
			srand(time(0)); //Semilla de numero aleatorio, generada por ejecucion de programa

			while(1){ //Bucle infinido
				sleep(4); //Dormir el proceso hijo durante 4 segundos

				int azar=rand(); //Generamos un numero aleatorio

				if(azar%100==0){ //Signal SIGUSR2
					printf("\tProceso hijo, pid= %d, va a poner fin al proceso padre, pid= %d\n",getpid(),ppidP); //Mensaje

					kill(ppidP,SIGUSR2); //Envio signal SIGUSR2
					printf("\tProceso hijo ha enviado señal SIGUSR2 a padre\n"); //Mensaje
					printf("\tProceso hijo va a finalizar\n"); //Mensaje

					exit(0); //Final de proceso hijo
				}else{ //Signal SIGUSR1
					printf("\tProceso hijo va a enviar la señal SIGUSR1 a padre\n"); //Mensaje
					kill(ppidP,SIGUSR1); //Envio signal SIGUSR1
				}
			}

		}
		break;

		default: //Padre
		{
			int ppidH = resultadoFork; //Almacen de ppid de proceso
			srand(time(0)); //Semilla de numero aleatorio, generada por ejecucion de programa

			while(1){ //Bucle infinido
				sleep(4); //Dormir el proceso hijo durante 4 segundos

				int azar=rand(); //Generamos un numero aleatorio

				if(azar%100==0){ //Signal SIGUSR2
					printf("Proceso padre, pid= %d, va a poner fin al proceso hijo, pid= %d\n",getpid(),ppidH); //Mensaje

					kill(ppidH,SIGUSR2); //Envio signal SIGUSR2
					printf("Proceso padre ha enviado señal SIGUSR2 a hijo\n"); //Mensaje
					printf("Proceso padre va a finalizar\n"); //Mensaje

					wait(NULL); //Espera por el proceso hijo

					exit(0); //Final de proceso padre
				}else{ //Signal SIGUSR1
					printf("Proceso padre va a enviar la señal SIGUSR1 a proceso hijo\n"); //Mensaje
					kill(ppidH,SIGUSR1); //Envio signal SIGUSR1
				}
			}
            
		}
		break;
	}

}
