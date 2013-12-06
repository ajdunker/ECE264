#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "pa12.h"

#define SUCCESS 0
#define FAILURE -1

typedef struct{
  int *set;
  int length;
  int sum;
  void *countaddress;
  void *lockaddress
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
int nextmask(int * mask, int size)
{
  int i;
  for (i = 0; i < size && mask[i]; i++) mask[i] = 0; // clear left most 1s in the mask
  if (i < size) 
    {
      mask[i] = 1; // set next position to 1
      return 1;
    }
  // return 0 if all masks have been enumerated
  return 0;
}
void * isSubSetSum(void * arg)
{
  Task * arguments = (Task *)arg;
  printf("%d\n", arguments->set[0]);
  pthread_mutex_lock(&lock);

  pthread_mutex_unlock(&lock);
  pthread_exit(NULL);
} 

int subsetSum(int * intset, int length, int N, int numThread)
{ 
  printf("Data we're looking for:\nLength: %d / Sum: %d\n\n\n", length, N);
  int i = 0;
  int count = 0;
  Task * doit = malloc(sizeof(Task));
  doit -> length = length;
  doit -> sum = N;
  doit -> countadress = &count;
  doit -> set = intset;
  pthread_t threads[numThread];
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);
  
  for(i = 0; i < numThread; i++)
    {
      pthread_create(&threads[i], NULL, isSubSetSum, (void*)doit);
    }
  for(i = 0; i < numThread; i++)
    {
      pthread_join(threads[i], NULL);
    }
  free(doit);
  pthread_mutex_destroy(&lock);
  printf("Count: %d\n", count);
  return count;
}
