#include <stdio.h>
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "input.h"

// #define BLOCK_PRINTF
#ifndef BLOCK_PRINTF
#define printf_d printf
#else
#define printf_d(...)
#endif

#define MINMUM_CARDS_IN_HAND 5

int CheckInvalidValueLetter(char v){
    if ((v != '2') &&  (v != '3') &&  (v != '4') &&  (v != '5') &&  (v != '6')
    &&  (v != '7') &&  (v != '8') &&  (v != '9') &&  (v != '0') &&  (v != 'J')
    &&  (v != 'Q') &&  (v != 'K') &&  (v != 'A')){
        return 1;
    }
    else {
        return 0;
    }    
}

int CheckInvalidSuitLetter(char s){
    if ((s != 's') && (s != 'h') && (s != 'd') && (s != 'c')){
        return 1;
    }
    else {
        return 0;
    }
}

deck_t * hand_from_string(const char * str, future_cards_t * fc){
    printf_d("Start hand_from_string().\n");
    if (str == NULL || fc == NULL){
        return NULL;
    }
    char card_letter_pair[2];
    int value_index = 0;
    int suit_index = 0;
    int str_index = 0;
    int future_card_index = 0;
    int get_value_flag = 0;
    // int get_suit_flag = 0;
    int count_cards = 0;

    card_t card;
    deck_t * deck = malloc(sizeof(* deck));
    deck->cards = malloc(sizeof(deck_t *));
    deck->n_cards = 0;
    while( *str != '\n'){
        // printf_d("%2c", *str);
        /// tack value_letter & suit_letter
        if (get_value_flag == 0){
            if (*str != ' '){
                card_letter_pair[0] = *str;
                get_value_flag = 1;
                value_index = str_index;
            }
        }
        else {
            if (*str != ' '){
                card_letter_pair[1] = *str;
                // get_suit_flag = 1;
                suit_index = str_index;
                if (suit_index == value_index + 1){ ///< correct format
                    if (card_letter_pair[0] == '?'){  ///< unknow card/future card
                        printf_d("  Futuer card %c%c\n", card_letter_pair[0], card_letter_pair[1]);
                        add_empty_card(deck);
                        if (*(str + 1) != ' ' && *(str + 1) != '\n'){
                            printf_d("  Double future characters\n");
                            if (*str > '9' || *str <'0' || *(str + 1) > '9' || *(str + 1) < '0'){
                                return NULL;
                            }
                            future_card_index = (*(str) - '0') * 10 + *(str + 1) - '0';
                            str++;
                            str_index++;
                        }
                        else {
                            if (*str > '9' || *str <'0'){
                                return NULL;
                            }
                            future_card_index = *str - '0';
                        }
                        
                        printf_d("  Future card index = %d\n", future_card_index);
                        add_future_card(fc, future_card_index, deck->cards[deck->n_cards - 1]);
                    }
                    else {
                        if (CheckInvalidValueLetter(card_letter_pair[0])){
                            return NULL;
                        }
                        if (CheckInvalidSuitLetter(card_letter_pair[1])){
                            return NULL;
                        }
                        card = card_from_letters(card_letter_pair[0], card_letter_pair[1]);
                        add_card_to(deck, card);
                    }
                    count_cards++;
                    /// reset data
                    get_value_flag = 0;
                }
            }
        }
        str++;
        str_index++;
    }

    printf_d("End hand_from_string().\n");
    if (count_cards >= MINMUM_CARDS_IN_HAND){
        return deck;
    }
    else {
        /// need more cards
        return NULL;
    }
}


deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
    printf_d("Start read_input()\n");
    if (f == NULL || n_hands == NULL || fc == NULL){
        return NULL;
    }
    int count_hands = 0;
    deck_t ** deck_ts = malloc(sizeof(deck_t *));
    deck_t * deck;
    
    /// get each line in file, calculate h_hands
    char * line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, f)) != -1){
        if ((deck = hand_from_string(line, fc)) != NULL){
            count_hands++;
            deck_ts = realloc(deck_ts, sizeof(* deck_ts) * count_hands);
            deck_ts[count_hands - 1] = deck;
        }
    }
    *n_hands = count_hands;
    /// free line
    free(line);
    printf_d("End read_input()\n");
    return deck_ts;

}

