#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  /// first, open the file
  FILE * f = fopen(fname, "r");
  if (f == NULL){
    printf("ERROR: %s.\n", strerror(errno));
    return NULL;
  }
  /// 2nd, read from the file
  kvarray_t * kva =  malloc(sizeof(*kva));
  kva->kv_num = 0;
  kva->kvs = NULL;
  char * line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, f)) > 0){
    /// allocate for k, v, kv_pair and kv_array;
    kva->kv_num++;
    kva->kvs = realloc(kva->kvs, sizeof(*(kva->kvs)) * kva->kv_num);
    /// caculate how many characters of key and value 
    int size_key = 0;
    int size_value =0;
    int equal_flag = 0;
    for (int i=0; i<linelen; i++){
      if (line[i] != '='){
        size_key++;
      }
      else {
        equal_flag = 1;
        break;
      }
    }
    if (equal_flag == 0){
      continue;
    }
    size_value = linelen - size_key - 2;
    char * key = malloc(sizeof(* key) * (size_key + 1));
    char * value = malloc(sizeof(* value) * (size_value + 1));
    strncpy(key, line, size_key);
    key[size_key] = '\0';
    strncpy(value, line + size_key + 1, size_value);
    value[size_value] = '\0';
    kva->kvs[kva->kv_num - 1].key = key;
    kva->kvs[kva->kv_num - 1].value = value;
  }
  
  /// 3rd, cloes the file.
  if (fclose(f) != 0){
    printf("ERROR: %s\n", strerror(errno));
    return NULL;
  }

  return kva;

}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs != NULL){
    /// first free kvs
    for (int i=0; i<pairs->kv_num; i++){
      free(pairs->kvs[i].key);
      free(pairs->kvs[i].value);
    }
    /// then free kv_array
    free(pairs->kvs);
    /// 3rd, free pairs
    free(pairs);
  }
}

void printKVs(kvarray_t * pairs) {
  assert(pairs != NULL);
  //WRITE ME
  for (int i=0; i<pairs->kv_num; i++){
    printf("key = '%s' value = '%s'\n", pairs->kvs[i].key, pairs->kvs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  assert(pairs != NULL && key != NULL);
  //WRITE ME
  for (int i=0; i<pairs->kv_num; i++){
    if (0 == strcmp(pairs->kvs[i].key, key)){
      return pairs->kvs[i].key;
    }
  }

  return NULL;
}


// int main(int argc, char ** argv){
//   if (argc != 3){
//     printf("Wrong input\n");
//     return EXIT_FAILURE;
//   }
//   char * fName = argv[1];
//   char * input_value = argv[2];
//   kvarray_t * kva = readKVs(fName);
//   if (NULL == kva){
//     return EXIT_FAILURE;
//   }
//   printf("%s is show as below:\n", fName);
//   printKVs(kva);
//   printf("look for %s:\n", input_value);
//   char * result = lookupValue(kva, input_value);
//   printf("found %s \n", result);

//   freeKVs(kva);
// }





