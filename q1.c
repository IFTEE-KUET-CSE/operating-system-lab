#include<stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 2
#define N 3
#define NUM_THREADS 6


int A [M][N] = { {20,30,40},{50,60,70} };
int B [M][N] = { {10,20,30}, {70,80,90} };
int C [M][N];

struct box {
   int i;
   int j;
};

struct box thread_data[NUM_THREADS];


void *runner(void *param) {

    struct box *data;
    int k, n, sum = 0;

    data = (struct box *) param;
	int i = data->i;
	int j = data->j;

   	sum =  A[i][j] + B[i][j];

	C[i][j] = sum;


    pthread_exit(0);
}


void matrix_add()
{
	pthread_t threads[NUM_THREADS];
	int count = 0;

	int i,j,rc;
	for(i = 0; i < M; i++) {
		for(j = 0; j < N; j++) {

			if(count == 6)
				break;
			thread_data[count].i = i;
			thread_data[count].j = j;

			rc = pthread_create(&threads[count], NULL, runner, (void *)&thread_data[count]);
			printf("Thread %d created\n", count);
			count++;
			if (rc){
       			printf("ERROR; return code from pthread_create() is %d\n", rc);
       		exit(-1);
			}

         	pthread_attr_t attr;
         	pthread_attr_init(&attr);

		}
	}

	for(i=0; i<2; i++) {
		for(j=0; j<3; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	printf("addition done\n");
}


int main()
{

int pid,pid1;
pid=fork();

if(pid>0)
{
	printf("parent process\n");


}
else
{
	printf("child1 process\n");
	pid1=fork();
	if(pid==0)
	{
		printf("child2 process");
		matrix_add();
	}

}
return 0;
}






