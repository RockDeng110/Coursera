#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"


// #define BLOCK_PRINTD
#ifdef BLOCK_PRINTD
#define printd(...)
#else
#define printd printf
#endif




counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * fi = fopen(filename, "r");
    if (fi == NULL){
      printd("ERROR: %s.\n", strerror(errno));
      return NULL;
    }
    if (kvPairs == NULL){
      return NULL;
    }

    counts_t * c = createCounts();
    char * key = NULL;
    char * line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fi)) > 0){
      printd(" Get key in line:");
      if (line[linelen -1] == '\n'){
        key = malloc(sizeof(* key) * (linelen));
        strncpy(key, line, (linelen - 1));
        key[linelen - 1] = '\0';
      }
      else{
        key = malloc(sizeof(* key) * (linelen + 1));
        strncpy(key, line, (linelen));
        key[linelen] = '\0';
      }
      printd(" key = %s;", key);
      char * value = lookupValue(kvPairs, key);
      printd("\n    look for the value = %s\n", value);
      if (value != NULL){
        addCount(c, value);
      }
      else {
        addCount(c, NULL);
      }
      free(key);
    }
    free(line);
    fclose(fi);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3){
    perror("Usage : count_values kvs.file input_file0 input_file1 ... input_fileN.\n");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv =  readKVs(argv[1]);
  if (kv == NULL){
    printd("ERROR: %s.\n", strerror(errno));
    return EXIT_FAILURE;
  }
  printd("Print kvs:\n");
  printKVs(kv);
 //count from 2 to argc (call the number you count i)
  for (int i=2; i<argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL){
      return EXIT_FAILURE;
    }

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, stdout);
    printCounts(c, f);
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

