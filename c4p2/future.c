
#include "future.h"
#include "cards.h"
#include "deck.h"
#include "eval.h"

// struct deck_tag {
//   card_t ** cards;
//   size_t n_cards;
// };
// typedef struct deck_tag deck_t;

// struct future_cards_tag {
//   deck_t * decks;
//   size_t n_decks;
// };

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
    if (fc != NULL && ptr != NULL){
        if (index > fc->n_decks - 1){
            /// realloc more memory
            fc->n_decks = index + 1;
            fc->decks = realloc(fc->decks, sizeof(deck_t) * fc->n_decks );
        }
        /// realloc memory for the deck to hold ptr
        fc->decks[index].n_cards++;
        fc->decks[index].cards = realloc(fc->decks[index].cards,  fc->decks[index].n_cards * sizeof(card_t *));
        fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
    }
}


void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
    int num_cards_deck = deck->n_cards;
    int num_cards_future = fc->n_decks;
    int num_move_cards = 0;
    // for (int i=0; i<fc->n_decks; i++){
    //     num_cards_future += fc->decks[i].n_cards;
    // }
    if (num_cards_deck > num_cards_future){
        num_move_cards = num_cards_future;
    }
    else{
        num_move_cards = num_cards_deck;
        /// need more cards from deck
    }

    // int count_cards = 0;
    // int count_decks = 0;
    for (int i=0; i<num_move_cards; i++){
        for (int j=0; j<fc->decks[i].n_cards; j++){
            fc->decks[i].cards[j] = deck->cards[i];
        }
    }

}

