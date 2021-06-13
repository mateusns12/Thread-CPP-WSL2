#include <iostream>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
using namespace std;

pthread_t task_handle;
pthread_t task2_handle;

sem_t semaforo;

void * task(void * pvParam);
void * task2(void * pvParam);

int main(){
	sem_init(&semaforo,0,1);
	pthread_create(&task_handle,NULL,task,NULL);
	pthread_create(&task2_handle,NULL,task2,NULL);
	pthread_join(task_handle,NULL);
	pthread_join(task2_handle,NULL);
	sem_destroy(&semaforo);
	return 0;
}

void * task(void * pvParam){
	cout<<"Task 1"<<endl;
	sem_wait(&semaforo);
	int i = 0;
	while(i<10){
		cout<<i+1<<endl;
	i++;
	}
	sem_post(&semaforo);
	pthread_exit(NULL);
}

void * task2(void * pvParam){
	cout<<"Task 2"<<endl;
	sem_wait(&semaforo);
	int i=0;
	for (i = 5; i>=0; i--){
		cout<<"finalizando em: "<<i<<endl;
	}
	sem_post(&semaforo);
	pthread_exit(NULL);
}

