#include "stdio.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"

#define CARD_MAX_NUM 52


extern unsigned * get_match_counts(deck_t * hand);
void PrintMatchedCounts(unsigned int * counts, int num){
    printf(" Print the matched counts:\n");
    for (int i=0; i<num; i++){
        printf("%3d", *(counts + i));
    }
}

int main(void){
    deck_t * d1_p = malloc(sizeof(deck_t));
    deck_t * d2_p = malloc(sizeof(deck_t));

    card_t c;
    d1_p->n_cards = 0;
    d1_p->cards = NULL;
    d2_p->n_cards = 0;
    d2_p->cards = NULL;
    // printf(" d1_p: \n");
    for (int i=3; i<8; i++){
        c = card_from_num(i);
        // print_card(c);
        // printf("\n");
        add_card_to(d1_p, c);
        // print_card(*(d.cards[i]));
        // printf("\n");
    }
    c = card_from_num(18);
    add_card_to(d1_p, c);
    c = card_from_num(31);
    add_card_to(d1_p, c);
    printf(" d1_p: \n");
    print_hand(d1_p);
    unsigned * counts1;
    counts1 = get_match_counts(d1_p);
    PrintMatchedCounts(counts1, d1_p->n_cards);

    // printf(" d2: \n");
    for (int i=14; i<19; i++){
        c = card_from_num(i);
        // print_card(c);
        // printf("\n");
        add_card_to(d2_p, c);
    }
    c = card_from_num(28);
    add_card_to(d2_p, c);
    c = card_from_num(41);
    add_card_to(d2_p, c);
    printf(" d2_p: \n");
    print_hand(d2_p);
    unsigned * counts2;
    counts2 = get_match_counts(d2_p);
    PrintMatchedCounts(counts2, d2_p->n_cards);
    // deck_t * hands[2];
    // hands[0] = d1_p;
    // hands[1] = d2_p;
    // deck_t * d3_p;
    // d3_p = build_remaining_deck(hands, 2);
    // add_empty_card(&d);
    // for (int i=0; i<3; i++){
    //     print_card(*(d.cards[i]));
    //     printf("\n");
    // }
    // printf(" remaining_deck: \n");
    // print_hand(d3_p);
    // free_deck(d1_p);
    // free_deck(d2_p);
    // free_deck(d3_p);
    // deck_t d;
    // d.n_cards = 0;
    // d.cards = NULL;
    // card_t c;
    // c = card_from_num(2);
    // add_card_to(&d, c);
    return 0;
}

