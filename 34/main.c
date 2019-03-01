#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  return NULL;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3){
    printf("Please input: command kv_file count_file1 count_file2 ...");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv =  readKVs(argv[1]);
  if (kv == NULL){
    printf("ERROR: %s.\n", strerror(errno));
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for (int i=2; i<argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    FILE * fi = fopen(argv[i], 'r');
    if (fi == NULL){
      printf("ERROR: %s.\n", strerror(errno));
      return EXIT_FAILURE;
    }
    counts_t * c = createCounts();
    char * line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fi)) > 0){
      addCount(c, line);
    }
    free(line);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, 'r');
    //print the counts from c into the FILE f
    printCounts(c, outName);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);    
  }

 //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}