/*
 * Time code taken from:
 * https://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c
 */

#include <stdio.h>
#include <stdlib.h>                 // for srand()
#include <time.h>                   // for time()
#include <sys/time.h>               // for gettimeofday()

// define the size of the array
#define ARRAYSIZE 1000000


int main(void)
{
    struct timeval t1, t2;
    double elapsedTime;

    // declare the array
    int arr[ARRAYSIZE];


    srand(time(NULL));

    // initialize the array
    for(int i=0; i<ARRAYSIZE; i++)
        //arr[i] = rand()%1000;
        arr[i] = 1000;


    long long int sum = 0;

    // start timer
    gettimeofday(&t1, NULL);

    // do the sum
    for (int i=0; i<ARRAYSIZE; i++)
        sum += arr[i];

    // stop timer
    gettimeofday(&t2, NULL);

    // rpint result
    printf("sum = %lld \n", sum);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%f ms.\n", elapsedTime);

    return 0;
}
