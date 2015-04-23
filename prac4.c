#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n_cars 8

//Array for thread identification
pthread_t thread_table[n_cars];

//Data type thread_param
typedef struct {
	int id;
	char *string;
}threads_param;

//Array for type threads_param data
threads_param parameters[n_cars];

//Function executed by threads
void *function_cars (threads_param *p) {

	int random;
	printf("Start %s %d\n", p->string, p->id);

	fflush(stdout);
	random = rand();
	sleep(1+(random%4));

	printf("Finish %s %d\n", p->string, p->id);

	pthread_exit((void*)p.id);//I need this. Can't get it. How?

	//C O D E 2


}

int main(void){
	
	int i, *res, rc;//rc acts as flag to see if p_thread worked or not
	void *status; //after joining

	printf("Start of thread creation process...\n");

	//Proceeds to create the threads

	for (i=0; i<n_cars; i++) {

		parameters[i].id = i;
		parameters[i].string = "potato"; 
		//writing this arbitrary thing in string because I don't know what to do with it
		
		rc = pthread_create(&thread_table[i],NULL, function_cars, (void *)&parameters[i]);
		if (rc){ //will be true if id is anything but an actual integer (error return value)	
			printf("Error creating thread\n");
			exit(-1);
		}

		//C O D E 1

	}

	printf("End of thread process creation\n");
	printf("CARS INITIATING\n");



	for (i=0; i<n_cars; i++) {

		rc = pthread_join(thread_table[i],&status);
		if (rc) {
			printf("Error joining threads");
			exit(-1);
		}
		printf("Completed join with car %d",(int)status);
	
	
		//C O D E 3

	}

	printf("All cars have REACHED THE FINISH LINE \n");
	return 0;
}
