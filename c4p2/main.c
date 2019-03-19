#include "stdio.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

#define CARD_MAX_NUM 52


int main(void){
    deck_t * d1_p = malloc(sizeof(deck_t));
    deck_t * d2_p = malloc(sizeof(deck_t));
    deck_t * d3_p = malloc(sizeof(deck_t));
    card_t c;
    d3_p->n_cards = 0;
    d3_p->cards = NULL;
    d1_p->n_cards = 0;
    d1_p->cards = NULL;
    d2_p->n_cards = 0;
    d2_p->cards = NULL;
    c = card_from_num(11);
    add_card_to(d1_p, c);
    c = card_from_num(12);
    add_card_to(d1_p, c);
    printf(" hand1:\n");
    print_hand(d1_p);
    printf("\n");
    c = card_from_num(25);
    add_card_to(d2_p, c);
    c = card_from_num(26);
    add_card_to(d2_p, c);
    printf(" hand2:\n");
    print_hand(d2_p);
    printf("\n");
    c = card_from_num(41);
    add_card_to(d3_p, c);
    c = card_from_num(43);
    add_card_to(d3_p, c);
    c = card_from_num(44);
    add_card_to(d3_p, c);
    printf(" hand3:\n");
    print_hand(d3_p);
    printf("\n");
    add_empty_card(d1_p);
    add_empty_card(d1_p);    
    add_empty_card(d2_p);
    add_empty_card(d2_p);

    future_cards_t fc;
    fc.decks = NULL;
    fc.n_decks = 0;
    add_future_card(&fc, 0, d1_p->cards[2]);
    add_future_card(&fc, 0, d2_p->cards[2]);
    add_future_card(&fc, 1, d1_p->cards[3]);
    add_future_card(&fc, 2, d2_p->cards[3]);

    future_cards_from_deck(d3_p, &fc);
    printf(" After get future cards from deck:\n");
    printf(" hand1:\n");
    print_hand(d1_p);
    printf("\n");

    printf(" hand2:\n");
    print_hand(d2_p);
    printf("\n");
}


#if 0
extern unsigned * get_match_counts(deck_t * hand);
void PrintMatchedCounts(unsigned int * counts, int num){
    printf(" Print the matched counts:\n");
    for (int i=0; i<num; i++){
        printf("%3d", *(counts + i));
    }
}

int main_cp41(void){
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
#endif
