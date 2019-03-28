#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

// #define BLOCK_PRINTF
#ifndef BLOCK_PRINTF
#define printf_d printf
#else
#define printf_d(...)
#endif

int PrintResult(int * array, int size){
    int sum_rounds = 0;
    float rate = 0;
    for (int i=0; i<size; i++){
        sum_rounds += array[i];
        printf_d("array[%d] = %d\n", i, array[i]);
    }
    printf_d("sum_rounds = %d; array_size = %d\n", sum_rounds, size);
    for (int i=0; i<size-1; i++){
        rate = (float)array[i] / sum_rounds;
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
    printf_d("Opend file: %s\n", argv[1]);
    
    deck_t ** deckts;
    size_t count_hands = 0;
    future_cards_t * fc = malloc(sizeof(* fc));
    fc->decks = NULL;
    fc->n_decks = 0;
    deckts = read_input(f, &count_hands, fc);
    printf_d("Completed read_input(). count_hands = %zu\n", count_hands);
    /// 3, Create a deck with the remaining cards.
    deck_t * deck_r;
    // deck_t * deck_r = malloc(sizeof(* deck_r));
    // deck_r->n_cards = 0;
    // deck_r->cards = NULL;
    deck_r = build_remaining_deck(deckts, count_hands);
    printf_d("Completed build_remaining_deck()\n");
    print_hand(deck_r);
    printf_d("\n\n");
    /// 4, Create an array to count how many times each hand wins
    int win_array_size = count_hands + 1;
    int * win_array = malloc(sizeof(* win_array) * win_array_size);
    for (int i=0; i<win_array_size; i++){
        win_array[i] = 0;
    }

    /// 5, Do each monte carlo trial
    printf_d("Game start:\n");
    for (int i=0; i<trial_times; i++){
        printf_d("Round %d\n", i);
        /// shuffle the deck of remaining cards
        shuffle(deck_r);
        printf_d("Shuffled...\n");
        print_hand(deck_r);
        printf_d("\n");
        /// assign unknown cards from the shuffled deck
        future_cards_from_deck(deck_r, fc);
        printf_d("Assign unknown cards. decks: \n");
        for (int i=0; i<count_hands; i++){
            print_hand(deckts[i]);
            printf_d("\n");
        }
        printf_d("\n");
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
        printf_d("Sord completed. maxvalue_index = %d; last_maxvalue_index = %d \n", maxvalue_index, last_maxvalue_index);
        for (int i=0; i<count_hands; i++){
            printf_d("  Hands %d :\n", i);
            print_hand(deckts[i]);
            printf_d("\n");
        }
        printf_d("\n");
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
        else {
            win_array[0]++;
        }
        printf_d("Wins calculate completed:\n");
        for (int i=0; i<win_array_size; i++){
            printf_d("  win_array[%d] = %d", i, win_array[i]);
        }
        printf_d("\n");
        
    }
    /// print result and free memory.
    
    PrintResult(win_array, win_array_size);
    /// free fc
    for (int i=0; i<fc->n_decks; i++){
        free(fc->decks[i].cards);
    }
    free(fc->decks);
    free(fc);
    /// free deckts
    for (int i=0; i<count_hands; i++){
        free_deck(deckts[i]);
    }
    free(deckts);
    free_deck(deck_r);
    free(win_array);
    fclose(f);
  return EXIT_SUCCESS;
}
