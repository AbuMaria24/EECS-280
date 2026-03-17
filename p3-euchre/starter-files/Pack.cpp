#include <cassert>
#include "Pack.hpp"

void Pack::reset() {
  next = 0;
}

bool Pack::empty() const {
  return next == PACK_SIZE;
}

Card Pack::deal_one() {
  assert(!empty());
  Card c = cards[next];
  next++;
  return c;
}

Pack::Pack() {
  next = 0;

  int index = 0;
  Rank ranks[] = {NINE, TEN, JACK, QUEEN, KING, ACE};
  Suit suits[] = {SPADES, HEARTS, CLUBS, DIAMONDS};

  for (Suit s : suits) {
    for (Rank r : ranks) {
      cards[index] = Card(r, s);
      index++;
    }
  }
}

Pack::Pack(std::istream &pack_input) {
  next = 0;
  for (int i = 0; i < PACK_SIZE; i++) {
    pack_input >> cards[i];
  }
}

void Pack::shuffle() {
  for (int t = 0; t < 7; t++) {

    std::array<Card, PACK_SIZE> shuffled;

    int top = 0;
    int bottom = PACK_SIZE / 2;

    for (int i = 0; i < PACK_SIZE; i++) {
      if (i % 2 == 0) {
        shuffled[i] = cards[bottom];
        bottom++;
      } else {
        shuffled[i] = cards[top];
        top++;
      }
    }

    cards = shuffled;
  }

  next = 0;
}

