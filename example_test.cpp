#include <gtest/gtest.h>
#include "life.h"

TEST(LifeTest, test_construct) {
    Life life(3, 3);
  ASSERT_EQ(life.GetHeight(), 3);
  ASSERT_EQ(life.GetWidth(), 3);
}

TEST(LifeTest, test_construct1) {
    ASSERT_THROW(Life life(2, 2), LifeException);
}

TEST(LifeTest, visual_representation) {
    Life life(3, 3);
    std::string exp = ".......\n"
                      "|- - -|\n"
                      "|- - -|\n"
                      "|- - -|\n"
                      ".......";
    ASSERT_EQ(std::string(life), exp);
}

TEST(LifeTest, visual_representation2) {
    Life life(3, 3);
    life.SetStateAlive(1, 1);
    std::string exp = ".......\n"
                      "|- - -|\n"
                      "|- o -|\n"
                      "|- - -|\n"
                      ".......";
    ASSERT_EQ(std::string(life), exp);
}

TEST(LifeTest, visual_representation3) {
    Life life(3, 3);
    life.SetStateAlive(0, 0);
    life.SetStateAlive(1, 1);
    life.SetStateAlive(2, 2);
    std::string exp = ".......\n"
                      "|o - -|\n"
                      "|- o -|\n"
                      "|- - o|\n"
                      ".......";
    ASSERT_EQ(std::string(life), exp);
}

TEST(LifeTest, mutate_test) {
    Life life(3, 3);
    life.SetStateAlive(0, 0);
    life.Mutate();
    std::string exp = ".......\n"
                      "|- - -|\n"
                      "|- - -|\n"
                      "|- - -|\n"
                      ".......";
    ASSERT_EQ(std::string(life), exp);
}