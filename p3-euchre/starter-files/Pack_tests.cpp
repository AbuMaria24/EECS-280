#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_second_card) {
    Pack pack;
    pack.deal_one(); 
    Card second = pack.deal_one();
    ASSERT_EQUAL(second, Card(TEN, SPADES));
}

TEST(test_pack_reset_restores_first_card) {
    Pack pack;
    pack.deal_one(); 
    pack.reset();    
    Card first = pack.deal_one();
    ASSERT_EQUAL(first, Card(NINE, SPADES));
}

TEST(test_pack_empty_after_all_cards_dealt) {
    Pack pack;
    for (int i = 0; i < 24; i++) {
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(test_pack_shuffle_first_card) {
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    ASSERT_EQUAL(first, Card(KING, CLUBS));
}

TEST_MAIN()
