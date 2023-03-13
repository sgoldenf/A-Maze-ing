#include "maze_file_reader.h"

namespace s21 {
auto MazeFileReader::ReadFile() -> std::unique_ptr<Maze> {
  if (!file_.is_open()) {
    throw std::invalid_argument("file reading error");
  }
  Field::Size size = ReadSize();
  Field::Matrix right_walls(size.height);
  AllocateRows(right_walls, size);
  ReadMatrix(right_walls);
  std::string empty_string;
  if (!std::getline(file_, empty_string) && !empty_string.empty()) {
    throw std::invalid_argument("maze reading error");
  }
  Field::Matrix bottom_walls(size.height);
  AllocateRows(bottom_walls, size);
  ReadMatrix(bottom_walls);
  for (std::string err; std::getline(file_, err);) {
    if (!std::all_of(err.begin(), err.end(), isspace)) {
      throw std::invalid_argument("maze reading error");
    }
  }
  std::unique_ptr<Maze> maze_ptr =
      std::make_unique<Maze>(right_walls, bottom_walls);
  return maze_ptr;
}
}  // namespace s21