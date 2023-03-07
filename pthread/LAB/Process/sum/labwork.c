#include<stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
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

int main()
{

int pid,pid1;
pid=fork();

if(pid>0)
{
printf("From parent process\n");
printf("Parent process %d \n",getpid());

int i;
    pthread_t thread[100];
    pthread_mutex_init(&mutex1, NULL);

    for (i = 0; i < array_size; i++)
        a[i] = i+1;

    for (i = 0; i < no_threads; i++)
        if (pthread_create(&thread[i], NULL, slave, NULL) != 0)
            perror("Pthread create fails");

    for (i = 0; i < no_threads; i++)
        if (pthread_join(thread[i], NULL) != 0)
            perror("Pthread join fails");

    printf("The sum of 1 to %i is %d\n", array_size, sum);
}
else
{


printf("From child process\n");
printf("child process %d \n",getpid());

    

}
return 0;
}

