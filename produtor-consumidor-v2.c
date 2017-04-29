#include	<pthread.h>
#include	<semaphore.h>
#include	<stdlib.h>
#include	<stdio.h>

#define	N 2
#define	TRUE 1

int	buffer[N], in = 0, out = 0;
sem_t	vazio, cheio, mutexProducao;

void *produtor(void *arg) 
{
	while(TRUE) 
	{
		sleep(rand()%5); 
		// SÓ PODE SEGUIR SE HOUVER SLOTS VAZIOS
	      	sem_wait(&vazio);
		sem_wait(&mutexProducao);
   
	      	buffer[in] = rand() % 100;
	      	printf("Produzindo buffer[%d] = %d\n", in, buffer[in]);
	      	in= (in+1) % N;
	
	      	// SINALIZA PARA LIBERAR O SEMÁFORO CHEIO
		sem_post(&mutexProducao);
	      	sem_post(&cheio);  
	}
}

void *consumidor(void *arg) {

	while(TRUE) 
	{
	  	sleep(rand()%5); 

	 	// SÓ PODE SEGUIR SE HOUVER SLOT CHEIO
		sem_wait(&cheio); 
	   
     		printf("Consumindo buffer[%d] = %d\n", out, buffer[out]);
      		out = (out+1) % N;
	   
      		// DA UNLOCK NO SEMÁFORO
      		sem_post(&vazio);
	   
   	}
}

int main(int argc, char *argv[ ]) 
{
    	pthread_t cons, prod;

    	// Segundo atributo: 0 indica que funciona só pra Threads e não para processos
    	// Terceiro atributo: Indica o valor inicial do semáforo
    	sem_init(&vazio, 0, N);
    	sem_init(&cheio, 0, 0);
	sem_init(&mutexProducao, 0, 1);
	
    	pthread_create(&prod, NULL, produtor, NULL);
	pthread_create(&cons, NULL, consumidor, NULL);
	pthread_create(&prod, NULL, produtor, NULL);

    	pthread_exit(0);
}
