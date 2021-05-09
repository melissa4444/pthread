#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
/**
 * THESE DEFINE VALUES CANNOT BE CHANGED.
 * DOING SO WILL CAUSE POINTS TO BE DEDUCTED
 * FROM YOUR GRADE
 */
/** BEGIN VALUES THAT CANNOT BE CHANGED */
#define MAX_THREADS 36
#define MAX_ITERATIONS 22
/** END VALUES THAT CANNOT BE CHANGED */


/**
 * use this struct as a parameter for the
 * nanosleep function.
 * For exmaple : nanosleep(&ts, NULL);
 */
struct timespec ts = {0, 150000};

int globalsharedvar=0;


struct thread_info {
    int id;
    pthread_t tid;
    int count;
};
/*
 Adder threads will execute the following steps:
 1. Read global value and store it into temp
 2. add 10 to the temp value
 3. store temp value into global variable
 4. print the following to the console:
 “Current Value written to Global Variables by ADDER thread id: tid is val” Were tid is the thread id and val is the value of the temporary variable AFTER adding 10 to it.
 5. repeats steps 1 through 4 for MAXITERATIONS (this is a defined constant in the given source code).
 
 Subtractor Threads: (Subtracting threads WILL have their own thread function)
 Subtractor threads will execute the following steps:
 1. Read global value and store it into temp
 2. subtract 10 from the temp value
 3. store temp value into global variable
 4. print the following to the console:
 “Current Value written to Global Variables by SUBTRACTOR thread id: tid is val”
 Were tid is the thread id and val is the value of the temporary variable AFTER subtracting 10 from it.
 5. repeats steps 1 through 4 for MAXITERATIONS (this is a defined constant in the given source code).
 */
int val;
void* add_thread(void* arg){
    struct thread_info* args=(struct thread_info*) arg;
    int val=0;
    for (int i=0; i<args->count; ++i) {
        nanosleep(&ts, NULL);

        val=globalsharedvar;
        val+=10;
        globalsharedvar=val;
        
        
        
        printf("Current Value written to Global Variables by ADDER thread id: %d is %d\n", args->id, val);
    }
    return NULL;
}
void* sub_thread(void* arg){
    struct thread_info* args=(struct thread_info*) arg;
    int val=0;
    for (int i=0; i<args->count; ++i) {
        nanosleep(&ts, NULL);

        val=globalsharedvar;
        val-=10;
        globalsharedvar=val;
        
        
        
        printf("Current Value written to Global Variables by SUBTRACTOR thread id: %d is %d\n", args-> id, val);
    }
    
    return NULL;
}

int
main(int argc, char** argv)
{
    
    struct thread_info thread_args[MAX_THREADS];
    
    for (int i=0; i<MAX_THREADS; ++i) {
        thread_args[i].id=i;
        thread_args[i].count=MAX_ITERATIONS;
        pthread_create(&thread_args[i].tid, NULL, add_thread, (void*) &thread_args[i]);
        pthread_create(&thread_args[i].tid, NULL, sub_thread, (void*) &thread_args[i]);
    }
    
    for (int j=0; j<MAX_THREADS; ++j) {
        pthread_join(thread_args[j].tid, NULL);
    }
    
    
    printf("\nFinal Value of Shared Variable :  %d \n", globalsharedvar);
    
    return 0;
}



//resources: class lecture and code
//https://www.geeksforgeeks.org/multithreading-c-2/
// Insert nanosleep() commands into your thread code to induce as many race conditions as possible by forcing an (in)appropriate interleaved execution sequence.
//book section 4.7 Operating System Exs
//pthread_t pthread_self(void)
//Returns the thread ID of the calling thread.
//I did use the Pthread Programming book by Dick Buttlar, Jacqueline Farrell and Bradford Nicholas
