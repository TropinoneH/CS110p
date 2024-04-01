#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char ** argv){
  if(argc<3){
    printf("Usage:\n");
    printf("./main <input file> <output file>\n");
    exit(0);
  }

  char * input_file_name = argv[1];
  char * output_file_name = argv[2];

  FILE * input_file = fopen(input_file_name,"r");
  FILE * output_file = fopen(output_file_name,"w");
  
  if(input_file == NULL){
    printf("Error: unable to open input file %s\n",input_file_name);
    exit(0);
  }

  if(output_file == NULL){
    printf("Error: unable to open output file %s\n",output_file_name);
    fclose(input_file);
    exit(0);
  }

  /* YOUR CODE HERE */

  fclose(input_file);
  fclose(output_file);

  return 0;
}
