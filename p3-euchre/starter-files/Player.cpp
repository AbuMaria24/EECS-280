#include "Player.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Simple : public Player {
public:
  Simple(const string &name_in) : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                   int round, Suit &order_up_suit) const override {
    Suit up_suit = upcard.get_suit();

    if (round == 1) {
      int count = 0;
      for (const Card &c : hand) {
        if (c.is_trump(up_suit) && c.is_face_or_ace()) {
          count++;
        }
      }
      if (count >= 2) {
        order_up_suit = up_suit;
        return true;
      }
      return false;
    }

    
    Suit same_color = Suit_next(up_suit);

    int count = 0;
    for (const Card &c : hand) {
      if (c.is_trump(same_color) && c.is_face_or_ace()) {
        count++;
      }
    }
    if (count >= 1 || is_dealer) {  
      order_up_suit = same_color;
      return true;
    }
    return false;
  }

  void add_and_discard(const Card &upcard) override {
    Suit trump = upcard.get_suit();
    hand.push_back(upcard);

    int min_i = 0;
    for (int i = 1; i < (int)hand.size(); i++) {
      if (Card_less(hand[i], hand[min_i], trump)) {
        min_i = i;
      }
    }
    hand.erase(hand.begin() + min_i);
  }

  Card lead_card(Suit trump) override {
    int best = -1;

    
    for (int i = 0; i < (int)hand.size(); i++) {
      if (!hand[i].is_trump(trump)) {
        if (best == -1 || Card_less(hand[best], hand[i], trump)) {
          best = i;
        }
      }
    }

    
    if (best == -1) {
      best = 0;
      for (int i = 1; i < (int)hand.size(); i++) {
        if (Card_less(hand[best], hand[i], trump)) {
          best = i;
        }
      }
    }

    Card c = hand[best];
    hand.erase(hand.begin() + best);
    return c;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    Suit led_suit = led_card.get_suit(trump);

    int best_follow = -1;
    for (int i = 0; i < (int)hand.size(); i++) {
      if (hand[i].get_suit(trump) == led_suit) {
        if (best_follow == -1 ||
            Card_less(hand[best_follow], hand[i], led_card, trump)) {
          best_follow = i;
        }
      }
    }

    int choice = -1;

    if (best_follow != -1) {
      choice = best_follow;
    } else {
      
      choice = 0;
      for (int i = 1; i < (int)hand.size(); i++) {
        if (Card_less(hand[i], hand[choice], led_card, trump)) {
          choice = i;
        }
      }
    }

    Card c = hand[choice];
    hand.erase(hand.begin() + choice);
    return c;
  }

private:
  string name;
  vector<Card> hand;
};

class Human : public Player {
public:
  Human(const string &name_in) : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) const override {

    print_hand();

    cout << "Human player " << name
         << ", please enter a suit, or \"pass\":" << endl;

    string input;
    cin >> input;

    if (input != "pass") {
      order_up_suit = string_to_suit(input);
      return true;
    }
    return false;
  }

  void add_and_discard(const Card &upcard) override {
    hand.push_back(upcard);

    print_hand();
    cout << "Discard upcard: [-1]" << endl;
    cout << "Human player " << name
         << ", please select a card to discard:" << endl;

    int index;
    cin >> index;

    hand.erase(hand.begin() + index);
  }

  Card lead_card(Suit trump) override {
    print_hand();

    cout << "Human player " << name
         << ", please select a card:" << endl;

    int index;
    cin >> index;

    Card c = hand[index];
    hand.erase(hand.begin() + index);
    return c;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    print_hand();

    cout << "Human player " << name
         << ", please select a card:" << endl;

    int index;
    cin >> index;

    Card c = hand[index];
    hand.erase(hand.begin() + index);
    return c;
  
  }
  

private:
  string name;
  vector<Card> hand;

  void print_hand() const {
    for (int i = 0; i < (int)hand.size(); ++i) {
      cout << "Human player " << name
           << "'s hand: [" << i << "] "
           << hand[i] << endl;
    }
  }
};

Player * Player_factory(const string &name, const string &strategy) {
  if (strategy == "Simple") return new Simple(name);
  if (strategy == "Human")  return new Human(name);
  assert(false);
  return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
