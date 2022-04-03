#include <iostream>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_t task_handle;
pthread_t task2_handle;

sem_t semaforo;

void * task(void * pvParam)
{
	std::cout<<"Task 1"<<std::endl;
	sem_wait(&semaforo);
	int i = 0;
	while(i<10){
		std::cout<<i+1<<std::endl;
	i++;
	}
	sem_post(&semaforo);
	pthread_exit(NULL);
}

void * task2(void * pvParam)
{
	std::cout<<"Task 2"<<std::endl;
	sem_wait(&semaforo);
	int i=0;
	for (i = 5; i>=0; i--){
		std::cout<<"Finishing in: "<<i<<std::endl;
	}
	sem_post(&semaforo);
	pthread_exit(NULL);
}

int main(){
	sem_init(&semaforo,0,1);
	pthread_create(&task_handle,NULL,task,NULL);
	pthread_create(&task2_handle,NULL,task2,NULL);
	pthread_join(task_handle,NULL);
	pthread_join(task2_handle,NULL);
	sem_destroy(&semaforo);
	return 0;
}