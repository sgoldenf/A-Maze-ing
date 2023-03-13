#include <gtest/gtest.h>

#include <vector>

#include "maze.h"

TEST(MazeTest, sizeTest) {
  s21::Maze test_maze(s21::Field::Size{3, 3});
  EXPECT_TRUE(test_maze.get_size().height == 3);
  EXPECT_TRUE(test_maze.get_size().width == 3);
}

TEST(MazeTest, validatorGenerate) {
  for (int i = 1; i <= 50; i++) {
    for (int j = 1; j <= 50; j++) {
      s21::Maze test_maze(s21::Field::Size{i, j});
      ASSERT_TRUE(s21::MazeValidator::Validate(&test_maze));
    }
  }
}

TEST(MazeTest, solve) {
  s21::Maze::Coordinates test_solve;
  test_solve.push(s21::Coordinate{0, 9});
  test_solve.push(s21::Coordinate{1, 9});
  test_solve.push(s21::Coordinate{1, 8});
  test_solve.push(s21::Coordinate{2, 8});
  test_solve.push(s21::Coordinate{3, 8});
  test_solve.push(s21::Coordinate{4, 8});
  test_solve.push(s21::Coordinate{4, 9});
  test_solve.push(s21::Coordinate{5, 9});
  test_solve.push(s21::Coordinate{5, 8});
  test_solve.push(s21::Coordinate{5, 7});
  test_solve.push(s21::Coordinate{5, 6});
  test_solve.push(s21::Coordinate{6, 6});
  test_solve.push(s21::Coordinate{7, 6});
  test_solve.push(s21::Coordinate{7, 5});
  test_solve.push(s21::Coordinate{8, 5});
  test_solve.push(s21::Coordinate{8, 6});
  test_solve.push(s21::Coordinate{9, 6});
  test_solve.push(s21::Coordinate{9, 5});

  s21::Field::Matrix right = {
      {false, false, true, false, false, false, false, true, false, true},
      {false, true, true, true, false, false, false, true, true, true},
      {true, false, true, false, false, true, true, true, true, true},
      {true, false, false, true, false, false, true, false, true, true},
      {false, false, true, false, true, false, true, false, true, true},
      {true, false, false, false, false, true, true, false, true, true},
      {false, false, false, true, true, false, false, true, false, true},
      {false, false, false, false, true, false, true, true, false, true},
      {true, false, false, false, true, true, true, false, false, true},
      {false, true, false, true, false, true, false, false, false, true}};

  s21::Field::Matrix bottom = {
      {false, true, false, false, false, true, true, true, false, false},
      {true, true, false, false, true, true, true, false, false, false},
      {false, false, true, true, true, false, false, false, false, false},
      {false, true, true, false, false, true, false, false, true, false},
      {true, false, true, true, true, false, true, true, true, false},
      {false, true, true, true, false, true, false, false, false, false},
      {true, true, false, true, false, false, true, false, true, true},
      {false, true, true, true, true, false, false, false, true, false},
      {true, false, true, false, false, false, false, true, true, true},
      {true, true, true, true, true, true, true, true, true, true}};

  s21::Maze maze(right, bottom);

  ASSERT_EQ(maze.Solve(s21::Coordinate{0, 9}, s21::Coordinate{9, 5}),
            test_solve);

  right = s21::Field::Matrix{{1}};
  bottom = s21::Field::Matrix{{1}};
  maze = s21::Maze(right, bottom);
  while (test_solve.size() > 0) {
    test_solve.pop();
  }
  test_solve.push(s21::Coordinate{0, 0});
  ASSERT_EQ(maze.Solve(s21::Coordinate{0, 0}, s21::Coordinate{0, 0}),
            test_solve);
}