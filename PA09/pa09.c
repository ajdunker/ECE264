#include <stdio.h>
#include <stdlib.h>
#include "pao9.h"

int main ( int argc , char ** argv )
{
  int i; //index
  //check arguments
  if (argc != 3)
    {
      printf("usage: ./pa04 <input file> <output file>\n");
      return EXIT_FAILURE;
    }
  
  //initializing input file
  FILE * fptr = NULL;
  fptr = fopen(argv[1], "r");
  if (fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }
 
  
  fclose(fptr);
  return EXIT_SUCCESS ;
}
