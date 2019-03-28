#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
// #include "config.h"

//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){
  if (hand == NULL){
    return NULL;
  }
  int matched_count = 1;
  // int value_behind_lastest_card = -1;
  /// fisrt, allocate memory for this matched couts array.
  unsigned * matched_counts_array = malloc(sizeof(unsigned) * hand->n_cards);
  /// second, analyze hand and calculate each member of the array.
  for (int i=0; i<hand->n_cards; i++){
    if (i < hand->n_cards -1){
      if (hand->cards[i]->value != hand->cards[i+1]->value){
        for (int j=0; j<matched_count; j++){
          matched_counts_array[i - j] = matched_count;
        }
        /// reset matched_count 
        matched_count = 1;
      }
      else {
        matched_count++;
      }
    }
    else {
      for (int j=0; j<matched_count; j++){
        matched_counts_array[i - j] = matched_count;
      }
    }
  }
  /// return the pointer of the array.
  return matched_counts_array;
}

hand_eval_t evaluate_hand(deck_t * hand);


int card_ptr_comp(const void * vp1, const void * vp2) {
  #if debug
  printf(">>>>into card_ptr_comp\n");
  #endif
  // const card_t * const * p1 = vp1;
  // const card_t * const * p2 = vp2;
  const card_t * const * p1 = vp1;
  const card_t * const * p2 = vp2;
  // printf(" p1.s = %d, p1.c = %d; p2.s = %d, p2.v = %d\n", (*p1)->suit, (*p1)->value, (*p2)->suit, (*p2)->value);
  assert_card_valid(**p1);
  assert_card_valid(**p2);
  if ((*p1)->value > (*p2)->value){
    return -1;
  }
  else if ((*p1)->value < (*p2)->value){
    return 1;
  }
  else {
    if ((*p1)->suit > (*p2)->suit){
      return -1;
    }
    else if ((*p1)->suit < (*p2)->suit){
      return 1;
    }
    else {
      return 0;
    }
  }
  return 0;
}

suit_t flush_suit(deck_t * hand) {

  #if debug
  printf(">>>>into flush_suit().\n");
  #endif
  suit_t suit;
  int spade_count = 0;
  int heart_count = 0;
  int diamond_count = 0;
  int club_count = 0;
  card_t ** card = hand->cards;
  for (int i=0; i<hand->n_cards; i++){
    switch ((*(card + i))->suit){
    case SPADES:
      spade_count++;
      break;
    case HEARTS:
      heart_count++;
      break;
    case DIAMONDS:
      diamond_count++;
      break;
    case CLUBS:
      club_count++;
      break;
    default:
      break;
    }
  }
  if (spade_count >= 5){
    suit = SPADES;
  }
  else if (heart_count >= 5){
    suit =  HEARTS;
  }
  else if (diamond_count >= 5){
    suit = DIAMONDS;
  }
  else if (club_count >= 5){
    suit = CLUBS;
  }
  else {
    suit = NUM_SUITS;
  }
  return suit;
}


unsigned get_largest_element(unsigned * arr, size_t n) {
  #if debug
  printf(">>>>into get_largets_element().\n");
  #endif
  unsigned max = *arr;
  for (int i=1; i<n; i++){
    if (*(arr + i) > max){
      max = *(arr + i);
    }
  }
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  #if debug
  printf(">>>>into get_match_index().\n");
  #endif
  for (int i=0; i<n; i++){
    if (*(match_counts + i) == n_of_akind)
      return i;
  }

  printf("get_match_index wrong\n");
  return -1;
}



ssize_t  find_secondary_pair(deck_t * hand,
                             unsigned * match_counts,
                             size_t match_idx) {
  #if debug
  printf(">>>>into find_secondary_pair().\n");
  #endif
  //  int three_tail_index = -1;
  //  int two_tail_index = -1;
  int n_cards = hand->n_cards;
  //  int two_kind_count = 0;
  if (*(match_counts + match_idx) == 4){
    for (int i=0; i<n_cards; i++){
      if (*(match_counts + i) == 2){
        return i;
      }
    }
  }
  else if (*(match_counts + match_idx) == 3){
    for (int i=0; i<n_cards; i++){
      if (*(match_counts + i) == 2){
        return i;
      }
      else if(*(match_counts + i) == 3){
        if ((i != match_idx) && (i != match_idx + 1) && (i != match_idx + 2)){
          return i;
        }
      }
    }
  }
  else {
    for (int i=(match_idx+2); i<n_cards; i++){
      if (*(match_counts + i) ==2){
        return i;
      }
    }
  }
  return -1;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n){
  #if debug
  printf(">>>>into is_n_length_straight_at().\n");
  #endif
  int n_cards = hand->n_cards;
  card_t ** cards = hand->cards;
  int straight_count = 1;
  int process_count = 0;
  int value_diff = 0;
  int suit_count = 0;
  for (int i=index; i<n_cards-1; i++){
    process_count++;
    value_diff = (*(cards + i))->value - (*(cards + i + 1))->value;
    if (value_diff == 1){
      if (++straight_count >= n){
        break;
      }
    }
    else if (value_diff == 0){

    }
    else {
      return 0;
    }

  }/// end for
  /// got n straight
  if (fs == NUM_SUITS){
    if (straight_count >= n){
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    for (int i=index; i<index+process_count+1; i++){
      if ((*(cards + i))->suit == fs){
        suit_count++;
      }
    }
    if ((suit_count == n)
        && ((*(cards + index))->suit == fs)){
      return 1;
    }
    else {
      return 0;
    }
  }
}

int has_a_2_straight(deck_t * hand, suit_t fs){
  #if debug
  printf(">>>>has_a_2_straight().\n");
  #endif
  unsigned n_cards = hand->n_cards;
  card_t ** cards = hand->cards;
  unsigned flag_2 = 0;
  unsigned flag_a = 0;
  if (fs == NUM_SUITS){
    if ((*(cards + n_cards -1))->value == 2){
      flag_2 =1 ;
    }
    if ((*(cards))->value == 14){
      flag_a = 1;
    }
    if (flag_2 + flag_a == 2){
      return 1;
    }

    return 0;
  }
  else {
    int i = n_cards -1 ;
    while (((**(cards + i)).value) == 2){
      if ((**(cards + i)).suit == fs){
        flag_2 = 1;
        break;
      }
      i--;
    }
    int j = 0;
    while(((**(cards + j)).value) == 14){
      if ((**(cards + j)).suit == fs){
        flag_a =1 ;
        break;
      }
      j++;
    }
    if (flag_2 + flag_a ==2){
      return 1;
    }
    return 0;
  }

}


int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  #if debug
  printf(">>>>into is_straight_at().\n");
  #endif

  int n_cards = hand->n_cards;
  if (is_n_length_straight_at(hand, index, fs, 5)){
      return 1;
  }
  else{
    if (index ==0){
      if (is_n_length_straight_at(hand, n_cards-4, fs, 4)){
        if (has_a_2_straight(hand, fs)){
          return -1;
        }
      }
    }
    return 0;
  }
  return 0;
}


hand_eval_t build_hand_from_match(deck_t * hand,
                                  unsigned n,
                                  hand_ranking_t what,
                                  size_t idx) {
  #if debug
  printf(">>>>into build_hand_from_match().\n");
  #endif

  hand_eval_t ans;
  ans.ranking = what;
  unsigned n_cards = hand->n_cards;
  card_t * first_card = *(hand->cards + idx);
  unsigned * match_counts = get_match_counts(hand);

  if (what == STRAIGHT_FLUSH){
    ans.cards[0] = first_card;
    int y = 1;
    for (int i=idx+1; i<n_cards; i++){
      if ((*(hand->cards + i))->suit == first_card->suit
          &&(*(hand->cards + i))->value +1 == first_card->value){
        ans.cards[y++] = *(hand->cards + i);
        if (y >= 5){
          return ans;
        }
        first_card = *(hand->cards + i);
      }
    }


  }
  else if (what == FOUR_OF_A_KIND){

    ans.cards[0] = *(hand->cards + idx);
    ans.cards[1] = *(hand->cards + idx + 1);
    ans.cards[2] = *(hand->cards + idx + 2);
    ans.cards[3] = *(hand->cards + idx + 3);
    int j = 4;
    int i = 0;
    for (; i<n_cards; i++){
      if ((*(hand->cards + i))->value != (*(hand->cards + idx))->value){
        ans.cards[j++] = *(hand->cards + i);
        if (j >= 5){
          return ans;
        }
      }
    }
  }
  else if (what == FULL_HOUSE){
    ssize_t second_pair_idx;
    second_pair_idx = find_secondary_pair(hand, match_counts, idx);
    ans.cards[0] = *(hand->cards + idx);
    ans.cards[1] = *(hand->cards + idx + 1);
    ans.cards[2] = *(hand->cards + idx + 2);
    ans.cards[3] = *(hand->cards + second_pair_idx);
    ans.cards[4] = *(hand->cards + second_pair_idx +1 );

  }
  else if (what == FLUSH){
    ans.cards[0] = first_card;
    int y = 1;
    for (int i=idx+1; i<n_cards; i++){
      if ((*(hand->cards + i))->suit == first_card->suit){
        ans.cards[y++] = *(hand->cards + i);
        if (y >= 5){
          return ans;
        }
        first_card = *(hand->cards + i);
      }
    }
  }
  else if (what == STRAIGHT){
    ans.cards[0] = first_card;
    int y = 1;
    for (int i=idx+1; i<n_cards; i++){
      if ((*(hand->cards + i))->value +1 == first_card->value){
        ans.cards[y++] = *(hand->cards + i);
        if (y >= 5){
          return ans;
        }
        first_card = *(hand->cards + i);
      }
    }
  }
  else if (what == THREE_OF_A_KIND){
    ans.cards[0] = *(hand->cards + idx);
    ans.cards[1] = *(hand->cards + idx + 1);
    ans.cards[2] = *(hand->cards + idx + 2);
    int j = 3;
    int i = 0;
    for (; i<n_cards; i++){
      if ((*(hand->cards + i))->value != (*(hand->cards + idx))->value){
        ans.cards[j++] = *(hand->cards + i);
        if (j >= 5){
          return ans;
        }
      }
    }
  }
  else if (what == TWO_PAIR){
    ssize_t second_pair_idx;
    second_pair_idx = find_secondary_pair(hand, match_counts, idx);
    ans.cards[0] = *(hand->cards + idx);
    ans.cards[1] = *(hand->cards + idx + 1);
    ans.cards[2] = *(hand->cards + second_pair_idx);
    ans.cards[3] = *(hand->cards + second_pair_idx + 1);
    int j = 4;
    int i = 0;
    for (; i<n_cards; i++){
      if ((*(hand->cards + i))->value != (*(hand->cards + idx))->value
          && (*(hand->cards + i))->value != (*(hand->cards + second_pair_idx))->value){
        ans.cards[j++] = *(hand->cards + i);
        if (j >= 5){
          return ans;
        }
      }
    }
  }
  else if (what == PAIR){
    ans.cards[0] = *(hand->cards + idx);
    ans.cards[1] = *(hand->cards + idx + 1);
    int j = 2;
    int i = 0;
    for (; i<n_cards; i++){
      if ((*(hand->cards + i))->value != (*(hand->cards + idx))->value){
        ans.cards[j++] = *(hand->cards + i);
        if (j >= 5){
          return ans;
        }
      }
    }
  }
  else if (what == NOTHING){
    ans.cards[0] = *(hand->cards);
    ans.cards[1] = *(hand->cards + 1);
    ans.cards[2] = *(hand->cards + 2);
    ans.cards[3] = *(hand->cards + 3);
    ans.cards[4] = *(hand->cards + 4);

  }

  free(match_counts);

  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  #if debug
  printf(">>>>into compare_hands().\n");
  #endif
  qsort(hand1->cards, hand1->n_cards, sizeof(card_t *), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(card_t *), card_ptr_comp);

  hand_eval_t hand1_eval;
  hand_eval_t hand2_eval;
  hand1_eval = evaluate_hand(hand1);
  hand2_eval = evaluate_hand(hand2);
  if (hand1_eval.ranking != hand2_eval.ranking){
    if (hand1_eval.ranking < hand2_eval.ranking){
      return 1;
    }
    else {
      return -1;
    }
  }
  else {
    for (int i=0; i<5; i++){
      if (hand1_eval.cards[i]->value > hand2_eval.cards[i]->value){
        return 1;
      }
      else if (hand1_eval.cards[i]->value < hand2_eval.cards[i]->value){
        return -1;
      }
    }
  }
  return 0;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
        (fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}



//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
        assert(hand->cards[i]->value == VALUE_ACE &&
               (fs == NUM_SUITS || hand->cards[i]->suit == fs));
        ans->cards[4] = hand->cards[i];
        size_t cpind = i+1;
        while(hand->cards[cpind]->value != 5 ||
              !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
          cpind++;
          assert(cpind < hand->n_cards);
        }
        copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
        copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}



//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
        ans.cards[copy_idx] = hand->cards[i];
        copy_idx++;
        if (copy_idx >=5){
          break;
        }
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}


