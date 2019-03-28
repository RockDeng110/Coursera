#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include <string.h>
// #include "config.h"


void print_hand(deck_t * hand){
  #if debug
  printf(">>>>into print_hand().\n");
  #endif
  // card_t ** cards = hand->cards;
  for (int i=0; i<hand->n_cards; i++){
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  #if debug
  printf(">>>>into deck_contains().\n");
  #endif
  card_t ** cards = (d->cards);
  for (int i=0; i<d->n_cards; i++){
    if ((**cards).value == c.value
        && (**cards).suit == c.suit){
      return 1;
    }

    cards++;
  }
  return 0;
}

void shuffle(deck_t * d){
  #if debug
  printf(">>>>into shuffle().\n");
  #endif
  card_t ** cards = (d->cards);
  size_t n_cards = d->n_cards;
  int random_value;
  card_t * temp;

  for (int i=0; i<n_cards; i++){
    random_value = random() % n_cards;
    temp =  *cards;
    *cards = *(cards + random_value);
    *(cards + random_value) = temp;


  }
}

void assert_full_deck(deck_t * d) {
  #if debug
  printf(">>>>into assert_full_deck();\n");
  #endif
  card_t  card_temp;
  int contain_check_result;
  for (int i=0; i<52; i++){
    card_temp = (card_from_num(i));
    contain_check_result = deck_contains(d, card_temp);
    if (contain_check_result == 0){
      printf("assert_full_deck failed at %d.\n", i);
      assert(0);
    }
  }
}

void add_card_to(deck_t * deck, card_t c){

  if (deck != NULL){
    int x = sizeof(card_t);
    // printf("x = %d", x);
    card_t * card = malloc(x);
    memcpy(card, &c, x);
    deck->n_cards++;
    deck->cards = realloc(deck->cards, (deck->n_cards) * sizeof(card_t *));
    deck->cards[deck->n_cards -1] = card;
  }
}

card_t * add_empty_card(deck_t * deck){

  card_t c;
  c.suit = 0;
  c.value = 0;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards - 1];
}


deck_t * make_deck_exclude(deck_t * excluded_cards){
  card_t card;
  deck_t * deck = malloc(sizeof(* deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  for (int i=0; i<52; i++){
    card = card_from_num(i);
    if (deck_contains(excluded_cards, card)){

    }
    else{
      add_card_to(deck, card);
    }
    
  }

  return deck;
}


deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  if (hands == NULL || n_hands == 0){
    return NULL;
  }
  /// define a deck.
  deck_t has_cards;
  has_cards.n_cards = 0;
  has_cards.cards = NULL;
  for (int i=0; i<n_hands; i++){
    // printf(" hands = %d\n", i);
    // print_hand(hands[i]);
    // printf("\n");
    for (int j=0; j<hands[i]->n_cards; j++){
      // printf(" i = %d; j = %d\n", i, j);
      // printf(" hands[i]->cards[j]->value = %d, hands[i]->cards[j]->suit = %d,", hands[i]->cards[j]->value, hands[i]->cards[j]->suit);
      /// if this card is not a empty card, add it to a deck.
      if (((hands[i]->cards[j]->value >= 2) &&  (hands[i]->cards[j]->value <= VALUE_ACE))
          && ((hands[i]->cards[j]->suit >= SPADES) && (hands[i]->cards[j]->suit <= CLUBS))){
        add_card_to(&has_cards, *(hands[i]->cards[j]));
        // printf(" add card to has_cards: card = ");
        // print_card(*(hands[i]->cards[j]));
        // printf("\n");
      }
      
    }
    // printf("has cards:\n");
    // print_hand(&has_cards);
    // printf("\n");
  }
  /// create the remaining deck.
  deck_t * p_deck;
  p_deck = make_deck_exclude(&has_cards);
  for (int i=0; i<has_cards.n_cards; i++){
    free(has_cards.cards[i]);
  }
  free(has_cards.cards);
  return p_deck;
  
}

void free_deck(deck_t * deck){
  if (deck != NULL){
    /// first, free all cards
    for (int i=0; i<deck->n_cards; i++){
      free(deck->cards[i]);
    }

    /// second, free the pointer array point to every cards.
    free(deck->cards);
    /// third, free the deck
    free(deck);
  }
}
