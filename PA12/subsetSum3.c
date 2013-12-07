#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa12.h"

#define SUCCESS 0
#define FAILURE -1

typedef struct{
	int * set;
	int length;
	int N;
	int sum;
	int * counter;	
	pthread_mutex_t * mutex;
}Task;

/*
* Write a parallel C program that returns the answer for the following problem:
* Given a nonempty set S, with elements {a1, a2, a3, ...}, and a integer N, 
* find the number of nonempty subsets of S, such that the sum of all elements
* in this subset equals to N.
*
* Arguments:
*    intset - pointer to an array of a integer set
*    length - size (length) of the integer set
*    N - target sum value
*    numThread - number of threads 
* Return value:
* numOfSolutions - Number of nonempty subsets in which the subsetSum value 
* matches with N. This variable should be protected as the critical 
* sections by using mutex objects.
*
* Hint: The total number of possible subsets is (2^(length)-1). You may use
* math library function 'pow()' to assign the index for each thread.
* pthread.h and math.h are already included in this file.
*/
void Destroy(Task * t)
{
  if(t==NULL)
    {
      return;
    }
  free(t->counter);
  free(t);
}
Task * Build(int * intset, int length, int N, pthread_mutex_t * mutexsum)
{
  Task * t = malloc(sizeof(Task));
  t -> set = intset;
  t -> length = length;
  t -> sum = 0;
  t -> N = N;
  t -> counter = malloc(sizeof(int));
  t -> mutex = mutexsum;
  *(t -> counter) = 0;
  return t;
}

void * isSubSetSum(void * arg)
{
  Task * t = (Task *)arg;
  //lock here
  pthread_mutex_lock(t->mutex);
  printf("Old value: %d\n", *(t->counter));
  //increment
  *(t->counter) += 1;
  printf("New value: %d\n", *(t->counter));
  //unlock here
  pthread_mutex_unlock(t->mutex);
  printf("Incrementing counter. Value %d\n", *(t->counter));
  pthread_exit(NULL);
} 

int subsetSum(int * intset, int length, int N, int numThread)
{ 
  pthread_mutex_t mutexsum;
  int i = 0;
  int r = 0;
  Task * t = Build(intset, length, N, &mutexsum);
  //int * counter = t -> counter;
  pthread_t threads[numThread];
  for(i = 0; i < numThread; i++)
    {
      r = pthread_create(&threads[i], NULL, isSubSetSum, (void *)t);
      if(r)
	{
	  printf("ERROR: return code from pthread_create() is %d\n", r);
	  //exit(-1);
	}
    }
  for(i = 0; i < numThread; i++)
    {
      pthread_join(threads[i], NULL);
    }
  printf("Counter: %d\n", *(t->counter));
  //Destroy(t);
  int x = *(t->counter);
  Destroy(t);
  printf("Final count %d\n", x);
  return x;
}
