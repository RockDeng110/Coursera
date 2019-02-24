#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "kv.h"



/**
 * @brief 
 * 
 * @param line - in
 * @param key - out
 * @param value - out
 * @return int - 0 means successful
 */

int BreakDownLine(char * line, char ** key_p, char ** value_p){
  if (line == NULL){
    return -1;
  }
  int len;
  int key_num = 0;
  int value_num = 0;
  len = strlen(line);
  for (int i=0; i<len; i++){
    if (line[i] != '='){
      key_num++;
    }
    else {
      break;
    }
  }
  if (key_num == 0){
    return -1;
  }
  value_num = len - key_num - 1;
  *key_p = malloc(sizeof(** key_p) * (key_num + 1));
  *value_p = malloc(sizeof(** value_p) * (value_num + 1));
  strncpy(*key_p, line, key_num);
  *key_p[key_num] = '\0';
  strncpy(*value_p, line + key_num + 1, value_num);
  *value_p[value_num] = '\0';
  
  return 0;
}

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
    
    /// caculate how many characters of key and value 
    char ** key_p = NULL;
    char ** value_p = NULL;
    if (BreakDownLine(line, key_p, value_p) != 0){
      continue;
    }
    /// allocate for k, v, kv_pair and kv_array;
    kva->kv_num++;
    kva->kvs = realloc(kva->kvs, sizeof(*(kva->kvs)) * kva->kv_num);
    kva->kvs[kva->kv_num - 1].key = *key_p;
    kva->kvs[kva->kv_num - 1].value = *value_p;
  }
  free(line);
  
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





