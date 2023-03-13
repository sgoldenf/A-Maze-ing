#include "maze_file_writer.h"

namespace s21 {
MazeFileWriter::MazeFileWriter(const std::string& filepath)
    : IFileWriter(filepath) {}

MazeFileWriter::~MazeFileWriter() {}

auto MazeFileWriter::WriteToFile(const Maze& maze) -> void {
  if (!file_.is_open()) {
    throw std::invalid_argument("file reading error");
  }
  WriteSize(maze.get_size());
  WriteMatrix(maze.get_right_walls());
  file_ << std::endl;
  WriteMatrix(maze.get_bottom_walls());
}
}  // namespace s21