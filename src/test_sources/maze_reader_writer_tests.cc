#include <gtest/gtest.h>

#include <cstdio>

#include "maze_file_reader.h"
#include "maze_file_writer.h"

class MazeFileReaderWriterTest : public ::testing::Test {
 protected:
  const std::string kFilePath = "test.txt";
  void TearDown() override { std::remove(kFilePath.c_str()); }
  static void CheckException(std::string filepath);
  static void CheckMazeReader(std::string filepath, s21::Maze& test_maze);

 private:
  static void CheckSizeEquality(const s21::Maze& maze,
                                const s21::Maze& test_maze);
};

void MazeFileReaderWriterTest::CheckException(std::string filepath) {
  s21::MazeFileReader maze_reader(filepath);
  EXPECT_ANY_THROW(maze_reader.ReadFile());
}

void MazeFileReaderWriterTest::CheckMazeReader(std::string filepath,
                                               s21::Maze& test_maze) {
  s21::MazeFileReader maze_reader(filepath);
  std::unique_ptr<s21::Maze> maze = maze_reader.ReadFile();
  CheckSizeEquality(*maze, test_maze);
  EXPECT_TRUE(maze->get_right_walls() == test_maze.get_right_walls());
  EXPECT_TRUE(maze->get_bottom_walls() == test_maze.get_bottom_walls());
}

void MazeFileReaderWriterTest::CheckSizeEquality(const s21::Maze& maze,
                                                 const s21::Maze& test_maze) {
  EXPECT_EQ(maze.get_size().width, test_maze.get_size().width);
  EXPECT_EQ(maze.get_size().height, test_maze.get_size().height);
}

TEST_F(MazeFileReaderWriterTest, openFileException) {
  CheckException("noexist");
}

TEST_F(MazeFileReaderWriterTest, sizeException) {
  CheckException("./data_samples/common/empty.txt");
  CheckException("./data_samples/common/onlyRows.txt");
  CheckException("./data_samples/common/sizeInvalid.txt");
  CheckException("./data_samples/common/sizeOutOfRange.txt");
  CheckException("./data_samples/common/sizeThreeArgs.txt");
}

TEST_F(MazeFileReaderWriterTest, matrixException) {
  CheckException("./data_samples/common/charMatrix.txt");
  CheckException("./data_samples/common/emptyMatrix.txt");
  CheckException("./data_samples/common/invalidNumbersMatrix.txt");
  CheckException("./data_samples/common/wrongMatrixSize.txt");
  CheckException("./data_samples/common/missingRows.txt.txt");
  CheckException("./data_samples/common/emptySpace.txt.txt");
  CheckException("./data_samples/common/cycle.txt.txt");
  CheckException("./data_samples/common/isolatedSpace.txt.txt");
}

TEST_F(MazeFileReaderWriterTest, correctMaze) {
  std::vector<std::vector<bool>> right_walls{
      {false, false, false, true},
      {true, false, true, true},
      {false, true, false, true},
      {false, false, false, true},
  };

  std::vector<std::vector<bool>> bottom_walls{{true, false, true, false},
                                              {false, false, true, false},
                                              {true, true, false, true},
                                              {true, true, true, true}};

  s21::Maze test_maze = s21::Maze(right_walls, bottom_walls);
  CheckMazeReader("./data_samples/mazes/correctMaze.txt", test_maze);
  right_walls = std::vector<std::vector<bool>>{{1}};
  bottom_walls = std::vector<std::vector<bool>>{{1}};
  test_maze = s21::Maze(right_walls, bottom_walls);
  CheckMazeReader("./data_samples/mazes/1x1.txt", test_maze);
}

TEST_F(MazeFileReaderWriterTest, writer) {
  std::vector<std::vector<bool>> right_walls{
      {false, false, false, true},
      {true, false, true, true},
      {false, true, false, true},
      {false, false, false, true},
  };

  std::vector<std::vector<bool>> bottom_walls{{true, false, true, false},
                                              {false, false, true, false},
                                              {true, true, false, true},
                                              {true, true, true, true}};

  s21::Maze test_maze = s21::Maze(right_walls, bottom_walls);
  s21::MazeFileWriter w(kFilePath);
  w.WriteToFile(test_maze);
  CheckMazeReader(kFilePath, test_maze);
}
