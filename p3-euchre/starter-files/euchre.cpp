#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

class Game {
public:
Game(Pack pack_in,
     const vector<Player*> &players_in,
     int points,
     bool shuffle_in)
  : pack(pack_in),
    players(players_in),
    dealer(0),
    hand_number(0),
    teamA_points(0),
    teamB_points(0),
    points_to_win(points),
    shuffle_on(shuffle_in) {}

  void play() {

    while (teamA_points < points_to_win && 
           teamB_points < points_to_win) {
              pack.reset();
    if (shuffle_on) {
        pack.shuffle();
    }

      cout << "Hand " << hand_number << endl;
      cout << players[dealer]->get_name() << " deals" << endl;
      
      for (int i = 0; i < 4; i++) {
        int player_index = (dealer + 1 + i) % 4;
        int cards_to_deal = (i % 2 == 0) ? 3 : 2;
        for (int j = 0; j < cards_to_deal; j++) {
          players[player_index]->add_card(pack.deal_one());
        }
      }
 
      for (int i = 0; i < 4; i++) {
        int player_index = (dealer + 1 + i) % 4;
        int cards_to_deal = (i % 2 == 0) ? 2 : 3;

        for (int j = 0; j < cards_to_deal; j++) {
          players[player_index]->add_card(pack.deal_one());
        }
      }
      Card upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      
      Suit trump;
      bool ordered_up = false;
      int round_ordered = 0;
      int maker_player = -1;

      for (int i = 0; i < 4; i++) {
        int player_index = (dealer + 1 + i) % 4;
        bool decision = 
        players[player_index]->make_trump(upcard, player_index
           == dealer, 1, trump);
        if (decision) {
          cout << players[player_index]->get_name()
          << " orders up " << trump << endl;
          cout << endl;
          ordered_up = true;
          round_ordered = 1;
          maker_player = player_index;
          break;
        }
        else 
        {
          cout << players[player_index]->get_name() << " passes" << endl;
        }
      }

      if (!ordered_up){
        for (int i = 0; i < 4; i++){
          int player_index = (dealer + 1 + i) % 4;
          bool decision = 
          players[player_index]->make_trump(upcard, player_index
            == dealer, 2, trump);

          if (decision){
            cout << players[player_index]->get_name() << " orders up " << trump << endl;
            cout << endl;
            ordered_up = true;
            round_ordered = 2;
            maker_player = player_index;
            break;
          }
          else
          {
            cout << players[player_index]->get_name() << " passes" << endl;
          }
          
        }
      }
      if (round_ordered == 1) {
      players[dealer]->add_and_discard(upcard);
        }
      


      int leader = (dealer + 1) % 4;
      int teamA_tricks = 0;
      int teamB_tricks = 0;

      for (int trick = 0; trick < 5; trick++) {
        Card led_card = players[leader]->lead_card(trump);
        cout << led_card << " led by "
            << players[leader]->get_name() << endl;
        Card winning_card = led_card;

        int winner = leader;
        for (int i = 1; i < 4; i++) {
          int player_index = (leader + i) % 4;
          Card played =
            players[player_index]->play_card(led_card, trump);
          cout << played << " played by "
              << players[player_index]->get_name()
              << endl;

          if (Card_less(winning_card, played, led_card, trump)) {
            winning_card = played;
            winner = player_index;
          }
        }

        cout << players[winner]->get_name()
          << " takes the trick" << endl;
        if (winner == 0 || winner == 2) {
          teamA_tricks++;
        } 
        else {
          teamB_tricks++;
        }
        cout << endl;
        leader = winner;   
    }

    int maker_team = (maker_player == 0 || maker_player == 2) ? 0 : 1;
    int maker_tricks = (maker_team == 0) ? teamA_tricks : teamB_tricks;
    if (maker_tricks >= 3) {

  if (maker_tricks == 5) {
    if (maker_team == 0) teamA_points += 2;
    else teamB_points += 2;

    if (maker_team == 0) {
      cout << players[0]->get_name() << " and "
           << players[2]->get_name()
           << " win the hand" << endl;
    } else {
      cout << players[1]->get_name() << " and "
           << players[3]->get_name()
           << " win the hand" << endl;
    }

    cout << "march!" << endl;
  }
  else {
    if (maker_team == 0) teamA_points += 1;
    else teamB_points += 1;

    if (maker_team == 0) {
      cout << players[0]->get_name() << " and "
           << players[2]->get_name()
           << " win the hand" << endl;
    } else {
      cout << players[1]->get_name() << " and "
           << players[3]->get_name()
           << " win the hand" << endl;
    }
  }

}
else {

  if (maker_team == 0) {
    teamB_points += 2;
    cout << players[1]->get_name() << " and "
         << players[3]->get_name()
         << " win the hand" << endl;
  } else {
    teamA_points += 2;
    cout << players[0]->get_name() << " and "
         << players[2]->get_name()
         << " win the hand" << endl;
  }

  cout << "euchred!" << endl;
}
    cout << players[0]->get_name() << " and "
        << players[2]->get_name()
        << " have " << teamA_points
        << " points" << endl;

    cout << players[1]->get_name() << " and "
        << players[3]->get_name()
        << " have " << teamB_points
        << " points" << endl;

    cout << endl;

        dealer = (dealer + 1) % 4;
        hand_number++;

      }
      if (teamA_points >= points_to_win) {
      cout << players[0]->get_name() << " and "
          << players[2]->get_name()
          << " win!" << endl;
    }
    else {
      cout << players[1]->get_name() << " and "
          << players[3]->get_name()
          << " win!" << endl;
    }
    }

    private:
      Pack pack;
      vector<Player*> players;
      int dealer;
      int hand_number;
      int teamA_points = 0;
      int teamB_points = 0;
      int points_to_win;
      bool shuffle_on;
    };

  int main(int argc, char **argv) {

    if (argc != 12) {
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
          << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
          << "NAME4 TYPE4" << endl;
      return 1;
    }

    string pack_filename = argv[1];
    string shuffle_option = argv[2];
    bool shuffle_on = (shuffle_option == "shuffle");
    int points_to_win = stoi(argv[3]);

    if (points_to_win < 1 || points_to_win > 100) {
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
          << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
          << "NAME4 TYPE4" << endl;
      return 1;
    }

    if (shuffle_option != "shuffle" &&
        shuffle_option != "noshuffle") {
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
          << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
          << "NAME4 TYPE4" << endl;
      return 1;
    }

    for (int i = 5; i <= 11; i += 2) {
      string type = argv[i];
      if (type != "Simple" && type != "Human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
      }
  }

  ifstream fin(pack_filename);
  if (!fin.is_open()) {
    cout << "Error opening " << pack_filename << endl;
    return 1;
  }

  for (int i = 0; i < argc; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;
  Pack pack(fin);

  vector<Player*> players;
  for (int i = 0; i < 4; i++) {
    string name = argv[4 + i*2];
    string type = argv[5 + i*2];
    players.push_back(Player_factory(name, type));
  }

  Game game(pack, players, points_to_win, shuffle_on);
  game.play();
  for (Player* p : players) {
    delete p;
  }

  return 0;
}