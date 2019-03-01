#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "kv.h"
#include <assert.h>



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
  int equal_flag = 0;
  int len;
  int key_num = 0;
  int value_num = 0;
  char * key;
  char * value;
  len = strlen(line);
  for (int i=0; i<len; i++){
    if (line[i] != '='){
      key_num++;
    }
    else {
      equal_flag = 1;
      break;
    }
  }
  if (equal_flag == 0){
    return -1;
  }
  if (key_num == 0){
    return -1;
  }

  if (line[len-1] == '\n'){

    value_num = len - key_num - 2;
  }
  else {
    value_num = len - key_num - 1;
  }

  key = malloc(sizeof(*key) * (key_num + 1));
  value = malloc(sizeof(*value) * (value_num + 1));
  strncpy(key, line, key_num);
  key[key_num] = '\0';
  strncpy(value, line + key_num + 1, value_num);
  value[value_num] = '\0';
  *key_p = key;
  *value_p = value;

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
  char * key;
  char * value;
  char * line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, f)) > 0){
    if (BreakDownLine(line, &key, &value) != 0){
      continue;
    }
    /// allocate for k, v, kv_pair and kv_array;
    kva->kv_num++;
    kva->kvs = realloc(kva->kvs, sizeof(*(kva->kvs)) * kva->kv_num);
    kva->kvs[kva->kv_num - 1].key = key;
    kva->kvs[kva->kv_num - 1].value = value;
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
  //WRITE ME
  if (pairs != NULL){
    for (int i=0; i<pairs->kv_num; i++){
      printf("key = '%s' value = '%s'\n", pairs->kvs[i].key, pairs->kvs[i].value);
    }
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  if (pairs != NULL && key != NULL){
    for (int i=0; i<pairs->kv_num; i++){
      if (0 == strcmp(pairs->kvs[i].key, key)){
        return pairs->kvs[i].value;
      }
    }
  }

  return NULL;
}

