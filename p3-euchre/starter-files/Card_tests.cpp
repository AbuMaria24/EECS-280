#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_ctor_different_values) {
    Card c(NINE, SPADES);
    ASSERT_EQUAL(NINE, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());

    Card c2(KING, CLUBS);
    ASSERT_EQUAL(KING, c2.get_rank());
    ASSERT_EQUAL(CLUBS, c2.get_suit());
}

TEST(test_card_ctor_all_suits) {
    Card s(TEN, SPADES);
    Card h(TEN, HEARTS);
    Card c(TEN, CLUBS);
    Card d(TEN, DIAMONDS);

    ASSERT_EQUAL(SPADES, s.get_suit());
    ASSERT_EQUAL(HEARTS, h.get_suit());
    ASSERT_EQUAL(CLUBS, c.get_suit());
    ASSERT_EQUAL(DIAMONDS, d.get_suit());
}

TEST(test_card_ctor_face_cards) {
    Card j(JACK, DIAMONDS);
    Card q(QUEEN, SPADES);
    Card k(KING, HEARTS);
    Card a(ACE, CLUBS);

    ASSERT_EQUAL(JACK, j.get_rank());
    ASSERT_EQUAL(QUEEN, q.get_rank());
    ASSERT_EQUAL(KING, k.get_rank());
    ASSERT_EQUAL(ACE, a.get_rank());
}

TEST(test_card_equality_same) {
    Card c1(ACE, HEARTS);
    Card c2(ACE, HEARTS);

    ASSERT_TRUE(c1 == c2);
}

TEST(test_card_equality_different_rank) {
    Card c1(ACE, HEARTS);
    Card c2(KING, HEARTS);

    ASSERT_FALSE(c1 == c2);
}

TEST(test_card_equality_different_suit) {
    Card c1(ACE, HEARTS);
    Card c2(ACE, SPADES);

    ASSERT_FALSE(c1 == c2);
}

TEST(test_card_not_equal) {
    Card c1(ACE, HEARTS);
    Card c2(KING, CLUBS);

    ASSERT_TRUE(c1 != c2);
}

TEST(test_card_is_face_or_ace_true) {
    Card c1(JACK, HEARTS);
    Card c2(QUEEN, SPADES);
    Card c3(KING, CLUBS);
    Card c4(ACE, DIAMONDS);

    ASSERT_TRUE(c1.is_face_or_ace());
    ASSERT_TRUE(c2.is_face_or_ace());
    ASSERT_TRUE(c3.is_face_or_ace());
    ASSERT_TRUE(c4.is_face_or_ace());
}

TEST(test_card_is_face_or_ace_false) {
    Card c(NINE, HEARTS);
    ASSERT_FALSE(c.is_face_or_ace());
}

TEST(test_card_is_trump_basic) {
    Card c1(ACE, HEARTS);
    Card c2(KING, SPADES);

    ASSERT_TRUE(c1.is_trump(HEARTS));
    ASSERT_FALSE(c2.is_trump(HEARTS));
}

TEST(test_card_left_bower_is_trump) {
    Card left(JACK, DIAMONDS); 

    ASSERT_TRUE(left.is_trump(HEARTS));
}

TEST(test_card_less_with_trump) {
    Card low(NINE, HEARTS);
    Card high(ACE, HEARTS);

    ASSERT_TRUE(Card_less(low, high, HEARTS));
}

TEST(test_card_less_with_led) {
    Card led(NINE, CLUBS);
    Card low(TEN, CLUBS);
    Card high(ACE, CLUBS);

    ASSERT_TRUE(Card_less(low, high, led, HEARTS));
}

TEST(test_card_not_equal_false) {
    Card c1(ACE, HEARTS);
    Card c2(ACE, HEARTS);

    ASSERT_FALSE(c1 != c2);
}

TEST(test_left_bower_get_suit_trump) {
    Card left(JACK, DIAMONDS); 

    ASSERT_EQUAL(HEARTS, left.get_suit(HEARTS));
}

TEST(test_left_bower_beats_ace) {
    Card left(JACK, DIAMONDS);   
    Card ace(ACE, HEARTS);

    ASSERT_FALSE(Card_less(left, ace, HEARTS));
}

TEST(test_right_bower_highest) {
    Card right(JACK, HEARTS);
    Card left(JACK, DIAMONDS);

    ASSERT_FALSE(Card_less(right, left, HEARTS));
}

TEST(test_trump_beats_led_suit) {
    Card led_card(NINE, CLUBS);
    Card trump_card(NINE, HEARTS);

    ASSERT_TRUE(Card_less(led_card, trump_card, led_card, HEARTS));
}

TEST(test_non_trump_compare) {
    Card low(NINE, CLUBS);
    Card high(KING, CLUBS);

    ASSERT_TRUE(Card_less(low, high, CLUBS));
}

TEST_MAIN()
