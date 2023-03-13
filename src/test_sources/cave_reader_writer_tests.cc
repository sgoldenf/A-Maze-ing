#include <gtest/gtest.h>

#include <cstdio>

#include "cave_file_reader.h"
#include "cave_file_writer.h"

class CaveFileReaderWriterTest : public ::testing::Test {
 protected:
  const std::string kFilePath = "test.txt";
  void TearDown() override { std::remove(kFilePath.c_str()); }
  static void CheckException(std::string filepath);
  static void CheckCaveReader(std::string filepath, s21::Cave& test_cave);

 private:
  static void CheckSizeEquality(const s21::Cave& cave,
                                const s21::Cave& test_cave);
};

void CaveFileReaderWriterTest::CheckException(std::string filepath) {
  s21::CaveFileReader cave_reader(filepath);
  EXPECT_ANY_THROW(cave_reader.ReadFile());
}

void CaveFileReaderWriterTest::CheckCaveReader(std::string filepath,
                                               s21::Cave& test_cave) {
  s21::CaveFileReader cave_reader(filepath);
  std::unique_ptr<s21::Cave> cave = cave_reader.ReadFile();
  CheckSizeEquality(*cave, test_cave);
  EXPECT_TRUE(cave->get_cells() == test_cave.get_cells());
}

void CaveFileReaderWriterTest::CheckSizeEquality(const s21::Cave& cave,
                                                 const s21::Cave& test_cave) {
  EXPECT_EQ(cave.get_size().width, test_cave.get_size().width);
  EXPECT_EQ(cave.get_size().height, test_cave.get_size().height);
}

TEST_F(CaveFileReaderWriterTest, openFileException) {
  CheckException("noexist");
}

TEST_F(CaveFileReaderWriterTest, sizeException) {
  CheckException("./data_samples/common/empty.txt");
  CheckException("./data_samples/common/onlyRows.txt");
  CheckException("./data_samples/common/sizeInvalid.txt");
  CheckException("./data_samples/common/sizeOutOfRange.txt");
  CheckException("./data_samples/common/sizeThreeArgs.txt");
}

TEST_F(CaveFileReaderWriterTest, matrixException) {
  CheckException("./data_samples/common/charMatrix.txt");
  CheckException("./data_samples/common/emptyMatrix.txt");
  CheckException("./data_samples/common/invalidNumbersMatrix.txt");
  CheckException("./data_samples/common/wrongMatrixSize.txt");
  CheckException("./data_samples/common/missingRows.txt");
}

TEST_F(CaveFileReaderWriterTest, correctCave) {
  std::vector<std::vector<bool>> cells{
      {true, true, false, false, true}, {true, true, false, true, true},
      {true, false, false, true, true}, {false, true, true, true, true},
      {false, false, true, true, true},
  };

  s21::Cave test_cave = s21::Cave(cells);
  CheckCaveReader("./data_samples/caves/correctCave.txt", test_cave);

  cells = std::vector<std::vector<bool>>{{1}};
  test_cave = s21::Cave(cells);
  CheckCaveReader("./data_samples/caves/1x1.txt", test_cave);
}

TEST_F(CaveFileReaderWriterTest, writer) {
  std::vector<std::vector<bool>> cells{
      {true, true, false, false, true}, {true, true, false, true, true},
      {true, false, false, true, true}, {false, true, true, true, true},
      {false, false, true, true, true},
  };
  s21::Cave test_cave = s21::Cave(cells);
  s21::CaveFileWriter w(kFilePath);
  w.WriteToFile(test_cave);
  CheckCaveReader(kFilePath, test_cave);
}
