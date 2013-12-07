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
*	intset - pointer to an array of a integer set
*	length - size (length) of the integer set
*	N - target sum value
*	numThread - number of threads 
* Return value:
*	numOfSolutions - Number of nonempty subsets in which the subsetSum value 
*	matches with N. This variable should be protected as the critical 
*	sections by using mutex objects.
*
* Hint: The total number of possible subsets is (2^(length)-1). You may use
* 	math library function 'pow()' to assign the index for each thread.
* 	pthread.h and math.h are already included in this file.
*/


Task * Build(int * intset, int length, int N, pthread_mutex_t * mutexsum)
{
	Task * t = malloc(sizeof(Task));
	t-> set = intset;
	t -> length = length;
	t -> sum = 0;
	t -> N = N;
	t -> counter = malloc(sizeof(int));
	t -> mutex = mutexsum;
	*(t->counter)=0;
	return t;
}

void Destroy(Task * t)
{
	if(t==NULL)
	{
		return;
	}
	free (t->counter);
	//free (t-> counter);
	free(t);
}

int Sum(int *intset,int length)
{
	int i =0;
	int sum =0;
	for(i=0; i<length; i++)
	{
		sum+=intset[i];
	}
	return sum;
}
/*
// generate mask in lexicographical order, return 1 if next mask can be generated
int nextmask(int * mask, int size)
{
    int i;
    for (i = 0; i < size && mask[i]; i++) mask[i] = 0; // clear left most 1s in the mask
             if (i < size) {
               mask[i] = 1; // set next position to 1
              return 1;
         }
     // return 0 if all masks have been enumerated
     return 0;
}

int subsetequal(int * setS, int size, int numN)
{
     int * mask = (int*) malloc(sizeof(int) * size);  // build and initialize an array indicating whether the indexed element is in a subset
     //memset(mask, 0, sizeof(int) * size);
     int i = 0, flag = 0, sum = 0; // flag is used to control loop structure, if the sum of a subset equals to numN, the loop stops and result is returned; otherwise it continues until all subsets are enumerated
     while (!flag && nextmask(mask, size)) {
sum = 0; // always reset the sum for each iteration
            for (i = 0; i < size; i++) {
                   if (mask[i]) {
                          sum += setS[i]; // element is included in current subset, add it to current subset' sum
                   }
            }
      if (sum == numN)
            flag = 1;
      }
      free(mask);
     return flag;
}*/

// decrement the bitset
void decrement(unsigned int * bitset, int bsize)
{
     while (--bsize >= 0 && !bitset[bsize]--);
}

// check whether all bits of the bits are zeros, if not, return 1
int hasbits(unsigned int * bitset, int bsize)
{
     unsigned int n = 0;
     while (bsize--)
            n |= bitset[bsize];
     return (n > 0);
}
//DOING SOME CHANGES
// interface for check if there exists a subset of setS whose sum adds up to numN
// setS -- set of elements, size -- number of elements in the set, numN -- integer N
int subsetequal(int * setS, int size, int numN)
{
        //int flag = 0; // flag to control the loop structure
		int count =0;
        int bsize = size / (sizeof(unsigned int) * 8) + 1; // number of unsigned integer needed to represents all the bits of the mask
        unsigned int * bitset = (unsigned int *) malloc(sizeof(unsigned int) * bsize); // create bitset using unsigned integers
        int tmp = size % (sizeof(unsigned int) * 8); // determine how many left-over bits, those bits won't fill in a whole unsigned integer (on most machines this would be 4 bytes or 32 bits)
        bitset[0] = tmp ? (1U << tmp) - 1 : ~0U; // determine whether the left-over is 32 bits
        int i;
        for (i = 1; i < bsize; i++)
                 bitset[i] = ~0U; // fill in rest of bit sets with all 1s

        int sum;
        unsigned int mask;
        while (hasbits(bitset, bsize)) {
                sum = 0;
                tmp = bsize;
                for (i = 0, mask = bitset[--tmp]; mask; i++, mask >>= 1U) { // bits are shifted to right, from the last unsigned ineger of the bitset, and least significant bit is used to determine whether the correspoding element is in the array
                        if (mask & 1U) {
                                  //printf("%d ", setS[i]);
                                  sum += setS[i]; // adds up the element to current subset's su,
                        }
                        if (mask == 0) {
                                  mask = bitset[--tmp]; // if current unsigned integer mask is finished, use next one in bitset
                        }
               }
               //printf("sum=%d\n", sum);
               if (sum == numN) {
                        count+= 1; // find a match
               }
               decrement(bitset, bsize); // decrement the bitset as a whole
        }
        free(bitset);
        return count;
}

/*
int Add(intset, length,N)
{
	int ** sets;
	int i =0;
	for(i = 0; i< pow(2,length-1);i++)
	{
		

	}*/
	//return 1 if you should increment the counter
	//return 0;
//}


void * calc(void * x)
{




	//if sum matches whatever, counter++
	Task * t =(Task *) x;
	pthread_mutex_init(t->mutex,NULL);
	//int	* count = t ->  counter;
	int * setS = t -> set;
	int size = t-> length;
	int numN = t-> N;
	//int count =0;
        int bsize = size / (sizeof(unsigned int) * 8) + 1; // number of unsigned integer needed to represents all the bits of the mask
        unsigned int * bitset = (unsigned int *) malloc(sizeof(unsigned int) * bsize); // create bitset using unsigned integers
        int tmp = size % (sizeof(unsigned int) * 8); // determine how many left-over bits, those bits won't fill in a whole unsigned integer (on most machines this would be 4 bytes or 32 bits)
        bitset[0] = tmp ? (1U << tmp) - 1 : ~0U; // determine whether the left-over is 32 bits
        int i;
        for (i = 1; i < bsize; i++)
                 bitset[i] = ~0U; // fill in rest of bit sets with all 1s

        int sum;
        unsigned int mask;
        while (hasbits(bitset, bsize)) {
                sum = 0;
                tmp = bsize;
                for (i = 0, mask = bitset[--tmp]; mask; i++, mask >>= 1U) { // bits are shifted to right, from the last unsigned ineger of the bitset, and least significant bit is used to determine whether the correspoding element is in the array
                        if (mask & 1U) {
                                  //printf("%d ", setS[i]);
                                  sum += setS[i]; // adds up the element to current subset's su,
                        }
                        if (mask == 0) {
                                  mask = bitset[--tmp]; // if current unsigned integer mask is finished, use next one in bitset
                        }
               }
               //printf("sum=%d\n", sum);
               if (sum == numN) {
						pthread_mutex_lock(t->mutex);
                        *(t->counter)+= 1; // find a match
						pthread_mutex_unlock(t->mutex);
               }
               decrement(bitset, bsize); // decrement the bitset as a whole
        }
        free(bitset);
		pthread_mutex_destroy(t->mutex);
		pthread_exit(NULL);
        









/*


//printf("subsetequal: %d \n",subsetequal(t->set,t->length,t->N));
	int a = subsetequal(t->set,t->length,t->N);
	if(a)
	{
	
		//lock here
		pthread_mutex_lock(t->mutex);
		//printf("Old value: %d\n",*(t->counter));

		//increment
		*(t->counter)=a;
		//printf("New value: %d\n",*(t->counter));
		//unlock here	
		pthread_mutex_unlock(t->mutex);
		//(*count)++;
		//printf("Incrementing counter. Value: %d\n",*(t->counter));
	}
	pthread_exit(NULL);
*/
}






























void * DoStuff(void * x)
{
	//if sum matches whatever, counter++
	Task * t =(Task *) x;
	//int	* count = t ->  counter;

	//printf("subsetequal: %d \n",subsetequal(t->set,t->length,t->N));
	int a = subsetequal(t->set,t->length,t->N);
	if(a)
	{
	
		//lock here
		pthread_mutex_lock(t->mutex);
		//printf("Old value: %d\n",*(t->counter));

		//increment
		*(t->counter)=a;
		//printf("New value: %d\n",*(t->counter));
		//unlock here	
		pthread_mutex_unlock(t->mutex);
		//(*count)++;
		//printf("Incrementing counter. Value: %d\n",*(t->counter));
	}
	pthread_exit(NULL);

}

int subsetSum(int * intset, int length, int N, int numThread)
{


	//printf("Answer: %d\n\n",subsetequal(intset,length, N)); 
 	pthread_mutex_t mutexsum;
	int i =0;
	int r =0;
	Task * t = Build(intset, length,N,&mutexsum);
	//int * counter = t->counter;
	pthread_t threads[numThread];
	for(i=0;i<numThread;i++)
	{
		r = pthread_create(&threads[i],NULL, calc, (void *) t); 
		if (r)
        {
			printf("ERROR; return code from pthread_create() is %d\n", r);
         	//exit(-1);
		}
	}
	for(i=0;i<numThread;i++)
	{
		pthread_join(threads[i],NULL);
	}
	//printf("Counter: %d\n",*(t->counter));
	//Destroy(t);
	int x = *(t->counter)/numThread;
	Destroy(t);
	//printf("Final count: %d\n",x);
	//printf("ANSWER***************************** %d \n\n", x);
	return (x);
}
