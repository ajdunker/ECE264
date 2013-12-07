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
*    N - target sum value //
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

void * isSubSetSum(void * arg)
{
  Task * t = (Task *)arg;
  //lock here
  //pthread_mutex_lock(t->mutex);
  //*(t->counter) += 1;
  //pthread_mutex_unlock(t->mutex);
  pthread_exit(NULL);
  return t;
} 
void Destroy(Task * t)
{
  if(t == NULL)
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
  t -> N = N;
  t -> counter = malloc(sizeof(int));
  *(t -> counter) = 0;
  t -> mutex = mutexsum;
  return t;
}
int subsetSum(int * intset, int length, int N, int numThread)
{ 
  pthread_mutex_t mutexsum;
  Task * t = Build(intset, length, N, &mutexsum);
  *(t->counter) = 0;
  pthread_t threads[numThread];
  int i;
  for(i = 0; i < numThread; i++)
    {
      pthread_create(&threads[i], NULL, isSubSetSum, (void *)t);
    }
  for(i = 0; i < numThread; i++)
    {
      pthread_join(threads[i], NULL);
    }
  Destroy(t);
  pthread_mutex_destroy(&mutexsum);
  return 0;
}
