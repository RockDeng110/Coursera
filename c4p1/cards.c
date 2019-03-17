#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"
// #include "config.h"

const char straight_flush[] = "straight slush";
const char four_of_a_kind[] = "four of a kind";

void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  #if debug
  printf(">>>>into ranking_to_string().\n");
  #endif
  switch(r){
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  }

  return "invalid rank value";
}

char value_letter(card_t c) {
  #if debug
  printf(">>>>into value_letter();\n");
  #endif
  //assert_card_valid(c);
  assert(c.value >= 2 && c.value <= 14);
  if (c.value < 10){
    return c.value + '0';
  }
  else if (c.value == 10){
    return '0';
  }
  else if (c.value == 11){
    return 'J';
  }
  else if (c.value == 12){
    return 'Q';
  }
  else if (c.value == 13){
    return 'K';
  }
  else if (c.value == 14){
    return 'A';
  }
  else{

    return 'x';
  }
}

char suit_letter(card_t c) {
  #if debug
  printf(">>>>into suit_letter()\n");
  #endif
  //assert_card_valid(c);
  assert(c.suit >= SPADES && c.suit < NUM_SUITS);
  switch (c.suit){
  case SPADES:
    return 's';
  case HEARTS:
    return 'h';
  case DIAMONDS:
    return 'd';
  case CLUBS:
    return 'c';
  default:
  return 'x';
  }
}
void print_card(card_t c) {
  #if debug
  printf(">>>>into print_card().card.c\n");
  #endif
  char s, v;
  s = suit_letter(c);
  v = value_letter(c);
  printf("%c", v);
  printf("%c", s);
}

card_t card_from_letters(char value_let, char suit_let) {
  #if debug
  printf(">>>>card_from_letters().cards.c\n");
  #endif
  assert((value_let >= '2' && value_let <= '9')
         || value_let == '0'
         || value_let == 'J'
         || value_let == 'Q'
         || value_let == 'K'
         || value_let == 'A');
  assert(suit_let == 's'
         || suit_let == 'h'
         || suit_let == 'd'
         || suit_let == 'c');
  card_t temp;
    if (value_let >= '2' && value_let <= '9'){
      temp.value = value_let - '0';
    }
    else if ( value_let == '0'){
      temp.value = 10;
    }
    else if (value_let == 'J'){
      temp.value = 11;
    }
    else if (value_let == 'Q'){
      temp.value = 12;
    }
    else if (value_let == 'K'){
      temp.value = 13;
    }
    else if (value_let == 'A'){
      temp.value = 14;
    }
    else{

    }

      if (suit_let == 's'){
        temp.suit = SPADES;
      }
      else if (suit_let == 'h'){
        temp.suit = HEARTS;
      }
      else if (suit_let == 'd'){
        temp.suit = DIAMONDS;
      }
      else if (suit_let == 'c'){
        temp.suit = CLUBS;
      }
      else {

      }

  return temp;
}

card_t card_from_num(unsigned c) {
  #if debug
  printf(">>>>card_from_num().cards.c\n");
  #endif
  card_t temp;
  int v, s;
  v = c % 13;
  s = c / 13;

  v = v +2;
  temp.value = v;
  temp.suit = (suit_t)s;

  return temp;
}
