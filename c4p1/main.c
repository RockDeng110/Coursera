#include "stdio.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"

#define CARD_MAX_NUM 52

int main(void){
    deck_t d;
    card_t c;
    d.n_cards = 0;
    d.cards = NULL;
    for (int i=0; i<13; i++){
        c = card_from_num(i);
        print_card(c);
        printf("\n");
        add_card_to(&d, c);
        print_card(*(d.cards[i]));
        printf("\n");
    }
    print_hand(&d);

    // deck_t d;
    // d.n_cards = 0;
    // d.cards = NULL;
    // card_t c;
    // c = card_from_num(2);
    // add_card_to(&d, c);
    return 0;
}

