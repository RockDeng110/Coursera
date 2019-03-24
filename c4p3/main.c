#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



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
        for (int i=0; i<count_hands-2; i++){
            for (int j=i+1; j<count_hands-1; j++){
                int compare_result = compare_hands(deckts[i], deckts[j]);
                if (compare_result > 0){
                    win_array[i]++;
                }
                else if (compare_result < 0){
                    win_array[j]++;
                }
                else{
                    win_array[count_hands]++;
                }
            }
        }
        /// Increment the win count for the winning hand.
    }
    /// print result and free memory.

    free(fc);
    free_deck(deck_r);
  return EXIT_SUCCESS;
}