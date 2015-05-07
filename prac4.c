#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //was missing, we need it to call sleep!
#define n_cars 8

//Array for thread identification
pthread_t thread_table[n_cars];
//Global mutex definition
pthread_mutex_t mutexsum;
//Global variable to store sum of randoms
int sum=0;
//Data type thread_param
typedef struct {
	int id;
	char *string;
}threads_param;

//Array for type threads_param data
threads_param parameters[n_cars];

//Function executed by threads
void *function_cars (void *aux) {
	threads_param *p = (threads_param*)aux;
	//Since the function can only be called with void, we cast it back to the parameters

	int random;
	printf("Start %s %d\n", p->string, p->id);

	fflush(stdout);
	random = rand();
	pthread_mutex_lock (&mutexsum); //lock mutex before global value change
	sum+=(1+(random%4));
	pthread_mutex_unlock(&mutexsum);
	sleep(1+(random%4));

	printf("Finish %s %d\n", p->string, p->id);

	pthread_exit((void*)p->id);
}

int main(void){
	
	int i, rc;//rc acts as flag to see if p_thread worked or not
	//int  *res; //unsure of what this is for, commenting it out as I don't use it
	void *status; //after joining, it gives the thread's status
	sum=0; //initialize global sum

	printf("Start of thread creation process...\n");

	//Proceeds to create the threads
	pthread_mutex_init(&mutexsum,NULL);//Create mutex first

	for (i=0; i<n_cars; i++) {

		parameters[i].id = i;
		parameters[i].string = "car"; 
		rc = pthread_create(&thread_table[i],NULL, function_cars, (void *)&parameters[i]);
		if (rc){ //will be true if id is anything but an actual integer (error return value)	
			printf("Error creating thread\n");
			exit(-1);
		}
	}

	printf("End of thread process creation\n");
	printf("CARS INITIATING\n");
	
	for (i=0; i<n_cars; i++) {
		rc = pthread_join(thread_table[i],&status);
		if (rc) {
			printf("Error joining threads\n");
			exit(-1);
		}
	}
	printf("All cars have REACHED THE FINISH LINE \n");
	printf("Sum of randoms is = %d \n",sum);
	pthread_mutex_destroy(&mutexsum);//we should destroy it before terminating
	return 0;
}
