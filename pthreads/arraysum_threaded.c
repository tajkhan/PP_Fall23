/*
 * Time code taken from:
 * https://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>                 // srand()
#include <time.h>                   // time()
#include <sys/time.h>               // for gettimeofday()

#define ARRAYSIZE 1000000
#define NUMTHREADS 4

// struct to pass arguments to thread
typedef struct arg_struct {
    int *start;
    int len;
} arg_struct;


// function to run in threads
void * partial_sum (void *arg){

    arg_struct *s_arg = (arg_struct *)arg;
    long long int local_sum = 0;

    for (int i=0; i< s_arg->len; i++)
        local_sum += s_arg->start[i];

    //printf("local_sum = %lld\n", local_sum);

    return (void *)local_sum;
}

int main(void)
{
    struct timeval t1, t2;
    double elapsedTime;

    pthread_t tids[NUMTHREADS];
    arg_struct argvals[NUMTHREADS];
    long long int results[NUMTHREADS];

    int arr[ARRAYSIZE];

    // workload for each thread
    int chunksize = ARRAYSIZE/NUMTHREADS;

    // initialize arguments for each thread
    for (int i=0; i<NUMTHREADS; i++){
        argvals[i].start = arr + i*chunksize;
        argvals[i].len   = chunksize;
    }

    srand(time(NULL));

    // initialize array
    for(int i=0; i<ARRAYSIZE; i++)
        //arr[i] = rand()%1000;
        arr[i] = 1000;


    long long int sum = 0;

    // start timer
    gettimeofday(&t1, NULL);

    // creat threads
    for (int i=0; i<NUMTHREADS; i++)
        pthread_create(&tids[i], NULL, partial_sum, &argvals[i]);

    // wait for threads to finish
    for (int i=0; i<NUMTHREADS; i++)
        pthread_join(tids[i], (void **)&results[i]);

    // stop timer
    gettimeofday(&t2, NULL);

    // rpint result
    for (int i=0; i<NUMTHREADS; i++)
        sum += results[i];
    printf("sum = %lld \n", sum);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%f ms.\n", elapsedTime);

    return 0;
}
