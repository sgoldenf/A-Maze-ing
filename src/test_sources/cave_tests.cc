#include <gtest/gtest.h>

#include <vector>

#include "cave.h"

class CaveTest : public ::testing::Test {
 protected:
  static void CompareCaves(s21::Cave& test_cave, s21::Field::Matrix test_data);
};
void CaveTest::CompareCaves(s21::Cave& test_cave,
                            s21::Field::Matrix test_data) {
  EXPECT_EQ(test_cave.get_cells(), test_data);
}

TEST_F(CaveTest, sizeTest) {
  s21::Cave test_cave = s21::Cave(s21::Field::Size{3, 3}, 1);
  EXPECT_TRUE(test_cave.get_size().height == 3);
  EXPECT_TRUE(test_cave.get_size().width == 3);
}

TEST_F(CaveTest, iterationTest) {
  s21::Field::Matrix test_matrix{
      {true, false, true, false, false, false, false, true, true, false},
      {false, false, true, true, false, false, false, false, false, true},
      {false, false, true, false, true, false, true, true, false, true},
      {false, true, true, true, true, true, true, false, false, false},
      {false, false, false, true, true, false, false, true, true, true},
      {false, true, false, true, false, true, false, false, false, false},
      {true, true, false, false, false, false, false, true, false, false},
      {false, false, false, false, false, false, true, false, true, true},
      {true, false, false, false, false, true, true, false, false, false},
      {false, true, true, false, false, true, true, false, false, false}};

  s21::Field::Matrix expected_matrix{
      {true, true, true, true, true, true, true, true, true, true},
      {true, true, true, true, true, true, true, true, true, true},
      {true, true, true, true, true, true, true, true, true, true},
      {true, true, true, true, true, true, true, true, true, true},
      {true, true, true, true, true, true, false, false, true, true},
      {true, true, false, false, false, false, false, false, false, true},
      {true, false, false, false, false, false, false, false, false, true},
      {true, false, false, false, false, false, false, false, true, true},
      {true, true, false, false, false, true, true, true, true, true},
      {true, true, true, true, true, true, true, true, true, true}};
  s21::Cave test_cave = s21::Cave(test_matrix);

  for (size_t i = 0; i < 100; i++) {
    test_cave.NextIteration(4, 3);
  }

  CompareCaves(test_cave, expected_matrix);
}

TEST_F(CaveTest, OneCellCave) {
  s21::Field::Matrix test_matrix{{1}};
  s21::Field::Matrix matrix{{0}};
  s21::Cave cave(matrix);
  bool i1 = cave.NextIteration(7, 7);
  bool i2 = cave.NextIteration(7, 7);
  ASSERT_TRUE(i1);
  ASSERT_FALSE(i2);
  CompareCaves(cave, test_matrix);
}
