#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int PrintResult(int * array, int size){
    int sum_rounds = 0;
    float rate = 0;
    for (int i=0; i<size; i++){
        sum_rounds += array[i];
    }
    for (int i=0; i<size-1; i++){
        rate = array[i] / sum_rounds;
        printf("Hand %d won %d / %d times (%.2f%%)\n", i, array[i], sum_rounds, rate);
    }
    printf("And there wrer %u ties\n", array[size-1]);

    return 0;
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
    /// 1, check arguments
    if (argc <= 1 || argc > 3){
        printf("usage: ... input_file_name tiems\n");
        return EXIT_FAILURE;
    }       
    /// 2, open input file - use read_input()
    FILE *f = fopen(argv[1], "r");
    if (f == NULL){
        printf("Can't find this file.\n");
        return EXIT_FAILURE;
    }
    int trial_times = 0;
    if (argc == 2){
        trial_times = 10000;
    }
    else {
        trial_times = atoi(argv[2]);
        if (trial_times == 0){
            printf(" Wong prarme 2\n");
            return EXIT_FAILURE;
        }
    }
    
    deck_t ** deckts;
    size_t count_hands = 0;
    future_cards_t * fc = malloc(sizeof(* fc));
    fc->decks = NULL;
    fc->n_decks = 0;
    deckts = read_input(f, &count_hands, fc);
    /// 3, Create a deck with the remaining cards.
    deck_t * deck_r = malloc(sizeof(* deck_r));
    deck_r->n_cards = 0;
    deck_r->cards = NULL;
    deck_r = build_remaining_deck(deckts, count_hands);
    /// 4, Create an array to count how many times each hand wins
    int win_array_size = count_hands + 1;
    int * win_array = malloc(sizeof(* win_array) * win_array_size);

    /// 5, Do each monte carlo trial
    for (int i=0; i<trial_times; i++){
        /// shuffle the deck of remaining cards
        shuffle(deck_r);
        /// assign unknown cards from the shuffled deck
        future_cards_from_deck(deck_r, fc);
        /// use compare_hands to figure out which hand won.
        // qsort(deckts, count_hands, sizeof(*deckts), compare_hands);
        int maxvalue_index = 0;
        int last_maxvalue_index = 0;
        for (int i=1; i<count_hands; i++){
            if (compare_hands(deckts[maxvalue_index], deckts[i]) <= 0){
                last_maxvalue_index = maxvalue_index;
                maxvalue_index = i;
            }
            
        }
        /// Increment the win count for the winning hand.
        if (last_maxvalue_index != maxvalue_index){
            int result = compare_hands(deckts[maxvalue_index], deckts[last_maxvalue_index]);
            if (result > 0){
                win_array[maxvalue_index]++;
            }
            else {
                win_array[win_array_size - 1]++;
            }
        } 
        // int result;
        // result = compare_hands(deckts[count_hands - 1], deckts[count_hands - 2]);
        // if (result > 0) {

        // }
    }
    /// print result and free memory.
    
    PrintResult(win_array, win_array_size);
    for (int i=0; i<fc->n_decks; i++){
        free_deck(&(fc->decks[i]));
    }
    free(fc);
    for (int i=0; i<count_hands; i++){
        free_deck(deckts[i]);
    }
    free_deck(deck_r);
    free(win_array);
    fclose(f);
  return EXIT_SUCCESS;
}
