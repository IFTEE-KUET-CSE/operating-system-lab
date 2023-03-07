#include <stdio.h>
#include <pthread.h>
#define array_size 1000
#define no_threads 100

int a[array_size];
int global_index = 0;
int sum = 0;
pthread_mutex_t mutex1;

void *slave(void *ignored)
{
    int local_index, partial_sum = 0;
    do {
     pthread_mutex_lock(&mutex1);
          local_index = global_index;
          global_index++;
     pthread_mutex_unlock(&mutex1);

        if (local_index < array_size)
            partial_sum += a[local_index];
    } while (local_index < array_size);

    pthread_mutex_lock(&mutex1);
    sum += partial_sum;
    pthread_mutex_unlock(&mutex1);

    return 0;
}

void *slave2(void *threadid)
{
    int local_index, partial_sum = 0;
    long tid;
    tid = (long)threadid;
    printf("Thread %ld\n", tid);
    int c=10;
    do {
     pthread_mutex_lock(&mutex1);
          local_index = global_index;
          global_index++;
     pthread_mutex_unlock(&mutex1);

        if (local_index < array_size)
            partial_sum += a[local_index];
        c--;
    } while (local_index < array_size && c);

    pthread_mutex_lock(&mutex1);
    sum += partial_sum;
    pthread_mutex_unlock(&mutex1);

    return 0;
}

void main()
{
    int i;
    pthread_t thread[100];
    pthread_mutex_init(&mutex1, NULL);

    for (i = 0; i < array_size; i++)
        a[i] = i+1;

    for (i = 0; i < no_threads; i++)
        if (pthread_create(&thread[i], NULL, slave2, (void *) thread[i]) != 0)
            perror("Pthread create fails");

    for (i = 0; i < no_threads; i++)
        if (pthread_join(thread[i], NULL) != 0)
            perror("Pthread join fails");

    printf("The sum of 1 to %i is %d\n", array_size, sum);
}
