#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}


TEST(test_player_insertion_operator) {
    Player * human = Player_factory("NotRobot", "Human");
    Player * simple = Player_factory("Bob", "Simple");

    ostringstream oss1;
    oss1 << *human;
    ASSERT_EQUAL(oss1.str(), "NotRobot");

    ostringstream oss2;
    oss2 << *simple;
    ASSERT_EQUAL(oss2.str(), "Bob");

    delete human;
    delete simple;
}


TEST(test_simple_make_trump_round1_orders_up) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(NINE, DIAMONDS));

    Suit trump;
    bool orderup = bob->make_trump(Card(NINE, SPADES), false,1,trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(test_simple_make_trump_round1_pass) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));

    Suit trump = HEARTS; 
    bool orderup = bob->make_trump(Card(NINE, SPADES), false, 1, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, HEARTS);

    delete bob;
}


TEST(test_simple_make_trump_screw_dealer) {
    Player * dealer = Player_factory("Dealer", "Simple");

    dealer->add_card(Card(NINE, SPADES));
    dealer->add_card(Card(NINE, CLUBS));
    dealer->add_card(Card(TEN, SPADES));
    dealer->add_card(Card(TEN, CLUBS));
    dealer->add_card(Card(NINE, HEARTS));

    Suit trump;
    bool orderup = dealer->make_trump(Card(NINE, HEARTS), true, 2, trump);

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, DIAMONDS);

    delete dealer;
}
TEST(test_simple_lead_card_highest_non_trump) {
    Player * alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(ACE, SPADES));   
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, HEARTS));  
    alice->add_card(Card(TEN, HEARTS));   
    alice->add_card(Card(NINE, CLUBS));

    Card led = alice->lead_card(HEARTS);
    ASSERT_EQUAL(led, Card(ACE, SPADES));

    delete alice;
}

TEST(test_simple_play_card_follow_suit_highest) {
    Player * alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(ACE, CLUBS));   
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, HEARTS));

    Card played = alice->play_card(Card(TEN, CLUBS), HEARTS);
    ASSERT_EQUAL(played, Card(ACE, CLUBS));

    delete alice;
}


TEST(test_simple_play_card_no_follow_lowest) {
    Player * alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, SPADES)); 
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(KING, CLUBS));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(NINE, HEARTS));

    Card played = alice->play_card(Card(TEN, DIAMONDS), HEARTS);

    ASSERT_EQUAL(played, Card(NINE, SPADES));

    delete alice;
}

TEST(test_simple_make_trump_left_bower_counts) {
    Player* p = Player_factory("Alice", "Simple");
    Card upcard(NINE, HEARTS);

    p->add_card(Card(JACK, DIAMONDS));  
    p->add_card(Card(QUEEN, HEARTS));   
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, SPADES));

    Suit trump;
    bool decision = p->make_trump(upcard, false, 1, trump);
    ASSERT_TRUE(decision);
    ASSERT_EQUAL(HEARTS, trump);

    delete p;
}

TEST(test_simple_make_trump_round2_non_dealer_pass) {
    Player* p = Player_factory("Alice", "Simple");
    Card upcard(NINE, HEARTS); 

    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, SPADES));

    Suit trump;
    bool decision = p->make_trump(upcard, false, 2, trump);
    ASSERT_FALSE(decision);

    delete p;
}

TEST(test_simple_make_trump_round1_exactly_one_face) {
    Player* p = Player_factory("Alice", "Simple");
    Card upcard(NINE, SPADES);

    p->add_card(Card(QUEEN, SPADES)); 
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, CLUBS));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, HEARTS));

    Suit trump;
    bool decision = p->make_trump(upcard, false, 1, trump);
    ASSERT_FALSE(decision);

    delete p;
}
TEST_MAIN()
