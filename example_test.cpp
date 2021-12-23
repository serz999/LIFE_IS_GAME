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