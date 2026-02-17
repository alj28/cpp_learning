#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(Hey, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hey", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

