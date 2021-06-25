#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_SEAT 3
#define MAX_SLEEP 5

sem_t sem_student;	// semaphore for student
sem_t sem_ta;		// semaphore to wake TA

pthread_mutex_t mutex;	//mutex to protect critical section


int waiting = 0; 	// students waiting for help
int chairs[3];		// three chairs either empty (0) or full (1)

int next_seat = 0;	// index of the next seat a student should sit in
int next_meet = 0;	// id of the next student who will meet with the TA

void wait_sleep(void);	// called when TA needs to sleep or when students need to wait
			// before checking if TA is available

void* student(void* student_id); 	// thread to handle the students finding a seat and checking for TA
void* ta_help();			 // thread to handle TA helping students or sleeping

void wait_sleep(void){
	int time = rand() % MAX_SLEEP + 1;
	sleep(time);
}

int main(){

	int* sids;				// pointer to list of sids
	int total_students;			// total number of students given by user
	int i;					// loop counter
	pthread_t *students;			// pointer to list of student threads
	pthread_t ta;				// pointer to the single TA thread

	srand(time(NULL));			// seed the RNG

	printf("How many students will visit the TA?: ");
	scanf("%d", &total_students);

	students = (pthread_t*) malloc(sizeof(pthread_t) * total_students); // initialize number of students   //creates array of student PIDS
	sids = (int*) malloc(sizeof(int) * total_students);		    // initialize ids for students

	memset(sids, 0, total_students);	// set the value of sid for each student to 0

	sem_init(&sem_student, 0, 0);		// initialize semaphore at address for students
						// semaphore is shared between threads of a process
						// initial value for the semaphore is 0

	sem_init(&sem_ta, 0, 1);		// initialize semaphore at address for TA
						// semaphore is shared between threads of a process
						// initial value for the semaphore is 1

	pthread_mutex_init(&mutex, NULL);	// initialize pthread mutex
	pthread_create(&ta, NULL, ta_help, NULL);	// create TA thread first, NULL (default attributes)
							// use the ta() function, and no parameters sent

	//  create each student thread one by one - send sid + 1 because 0 indicates an empty seat
	for(i = 0; i < total_students; i++){
		sids[i] = i+1;
		pthread_create(&students[i], NULL, student, (void*) &sids[i]);
	}

	pthread_join(ta, NULL);			// wait for the TA thread to finish

	// join each student thread one by one
	for(i = 0; i < total_students; i++){
		pthread_join(students[i], NULL);
	}

	return 0;
}

void* student(void* student_id)
{

	wait_sleep();

	int sid = *(int*)student_id;

	printf("Student-Thread: Sid %d is checking available seats\n",sid);

	while(1)
	{
		wait_sleep();
		pthread_mutex_lock(&mutex);
		printf("Student-Thread: Sid %d is waiting\n",sid);

		if(waiting < NUM_SEAT){
			chairs[next_seat] = sid;
			waiting++;
			next_seat = (next_seat+1)%3;
			printf("Student-Thread_Seat Status: (S1) %d (S2) %d (S3) %d\n",chairs[0],chairs[1],chairs[2]);
            sem_post(&sem_student);
			pthread_mutex_unlock(&mutex);
			sem_wait(&sem_ta);
		}
		else {
			printf("Student-Thread: no seats available, Sid %d will come back later\n",sid);
			pthread_mutex_unlock(&mutex);
		}
	}

}

void* ta_help()
{
	while(1)
	{
		if(waiting >0)
		{
			sem_wait(&sem_student);
			pthread_mutex_lock(&mutex);

			printf("TA-Thread: Currently meeting with Sid %d\n",chairs[next_meet]);

			chairs[next_meet] =0;
			waiting--;
			next_meet = (next_meet+1)%3;
			sem_post(&sem_ta);
			wait_sleep();

			printf("TA-Thread_Seat Status: (S1) %d (S2) %d (S3) %d\n",chairs[0],chairs[1],chairs[2]);

			pthread_mutex_unlock(&mutex);
			if(waiting==0)
			{
				printf("TA-Thread: TA has finished helping the student\n");
			}
		}
		else
		{
			wait_sleep();
		}
	}
}
