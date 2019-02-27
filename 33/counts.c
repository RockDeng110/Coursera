#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

char * unknown = "<unknown> ";

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(* counts));
  counts->counts_arr = NULL;
  counts->size = 0;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int has_named = 0;
  int i = 0;
  if (c != NULL){
    for (i=0; i<c->size; i++){
      if (name == NULL){
        if (strcmp(c->counts_arr[i].name, unknown) == 0){
          has_named = 1;
          break;
        }
      }
      else {
        if (strcmp(c->counts_arr[i].name, name) == 0){
          has_named = 1;
          break;
        }
      }
    }
    if (has_named){
      c->counts_arr[i].count++;
    }
    else{
      /// relloc c->counts_arr and add a count
      c->counts_arr = realloc(c->counts_arr, sizeof(*(c->counts_arr)) * c->size);
      c->counts_arr[c->size].count = 1;
      if (name == NULL){
        c->counts_arr[c->size].name = malloc(11);
        strcpy(c->counts_arr[c->size].name, unknown);
      }
      else {
        c->counts_arr[c->size].name = malloc(sizeof(name));
        strcpy(c->counts_arr[c->size].name, name);
      }
      
      
    }

    c->size++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int unknown_index = -1;
  if (c != NULL && outFile != NULL){
    for (int i=0; i<c->size; i++){
      if (strcmp(c->counts_arr[i].name, unknown) != 0){
        fprintf(outFile, "%s = %d\n", c->counts_arr[i].name, c->counts_arr[i].count);
      }
      else {
        unknown_index = i;
      }
    }
    if (unknown_index >= 0){
      fprintf(outFile, "%s = %d\n", c->counts_arr[unknown_index].name, c->counts_arr[unknown_index].count);
    }
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c != NULL){
    for (int i=0; i<c->size; i++){
      free(c->counts_arr[i].name);
    }
    free(c->counts_arr);
    free(c);
  }
}
