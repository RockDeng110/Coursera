#include "stdio.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"

#define CARD_MAX_NUM 52

int main(void){
    deck_t d1, d2;
    card_t c;
    d1.n_cards = 0;
    d1.cards = NULL;
    d2.n_cards = 0;
    d2.cards = NULL;
    printf(" d1: \n");
    for (int i=3; i<13; i++){
        c = card_from_num(i);
        print_card(c);
        printf("\n");
        add_card_to(&d1, c);
        // print_card(*(d.cards[i]));
        // printf("\n");
    }
    printf(" d2: \n");
    for (int i=14; i<19; i++){
        c = card_from_num(i);
        print_card(c);
        printf("\n");
        add_card_to(&d2, c);
    }
    deck_t * hands[2];
    hands[0] = &d1;
    hands[1] = &d2;
    deck_t * d3_p;
    d3_p = build_remaining_deck(hands, 2);
    // add_empty_card(&d);
    // for (int i=0; i<3; i++){
    //     print_card(*(d.cards[i]));
    //     printf("\n");
    // }
    printf(" remaining_deck: \n");
    print_hand(d3_p);

    // deck_t d;
    // d.n_cards = 0;
    // d.cards = NULL;
    // card_t c;
    // c = card_from_num(2);
    // add_card_to(&d, c);
    return 0;
}

