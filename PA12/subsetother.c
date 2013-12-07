#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa12.h"

#define SUCCESS 0
#define FAILURE -1

typedef struct{
  int * start; //starting point of current part of start
  int count; //number of elements in the given array slice
  int tid; //thread id
  pthread_mutex_t * mutexSum; //pointer of the actual mutex object
  int * totalSum; //pointer to totalSum the overall sum of elements
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
void * isSubSet(void * args)
{
  Task * t = (Task *)args;
  return t;
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
  int totalSum = 0; //overall sum, calculated by collecting partial sums from each thread
  pthread_t threads[numThread];
  pthread_mutex_t mutexSum; //mutext object fro controlling access to shared resources among threads
  pthread_mutex_init(&mutexSum, NULL); //initializes mutex object
  Task * t = Build(intset, length, N, pthread_mutex_t * mutexsum);
  int i;
  for(i = 0; i < numThread; i++)
    {
      pthread_create(&threads[i], NULL, isSubSet, (void *) t);
    }
  for(i = 0; i < numThread; i++)
    {
      
    }
  printf("Overall sum = %d\n", totalSum);
  pthread_mutex_destroy(&mutexSum);//destroys mutex object
  return 0;
}
