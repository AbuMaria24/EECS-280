#include "unit_test_framework.hpp"
#include "DiceCounter.hpp"
#include "LectureVector.hpp"

TEST(test01_dice_counter) {
    DiceCounter dc(1);
}

TEST(test02_dice_counter) {
    DiceCounter dc(6);
    dc.record(1);
    dc.record(1);
    dc.record(6);
    ASSERT_EQUAL(dc.mostCommon(), 1);
}

TEST(test03_empty_vector) {
    LectureVector lv;
}

TEST(test04_initial_capacity) {
    LectureVector lv;
    lv.push_back(100);
    int *ptr0 = &lv.at(0);
    lv.push_back(200);

    // Should not have grown
    ASSERT_EQUAL(&lv.at(0), ptr0);
    ASSERT_EQUAL(lv.at(0), 100);
    ASSERT_EQUAL(lv.at(1), 200);
    ASSERT_EQUAL(lv.size(), 2);
    ASSERT_EQUAL(lv.capacity(), 2);
}

TEST(test04_grow) {
    LectureVector lv;
    lv.push_back(100);
    int *ptr0 = &lv.at(0);
    lv.push_back(200);
    lv.push_back(300);

    // Should have grown
    ASSERT_NOT_EQUAL(&lv.at(0), ptr0);
    ASSERT_EQUAL(lv.at(0), 100);
    ASSERT_EQUAL(lv.at(1), 200);
    ASSERT_EQUAL(lv.at(2), 300);
    ASSERT_EQUAL(lv.size(), 3);
    ASSERT_EQUAL(lv.capacity(), 4);
}

TEST(test05_big) {
    LectureVector lv;

    for (int i = 0; i < 1000; i++) {
        lv.push_back(i);
    }
    ASSERT_EQUAL(lv.size(), 1000);
    ASSERT_EQUAL(lv.capacity(), 1024);

    for (int i = 0; i < 1000; i++) {
        ASSERT_EQUAL(lv.at(i), i);
    }
}

TEST_MAIN()