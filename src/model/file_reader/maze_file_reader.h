#ifndef SRC_MODEL_MAZE_FILE_READER_
#define SRC_MODEL_MAZE_FILE_READER_

#include "file_reader.h"
#include "maze.h"

namespace s21 {
class MazeFileReader : public IFileReader<Maze> {
 public:
  explicit MazeFileReader(const std::string& filepath)
      : IFileReader(filepath){};
  ~MazeFileReader(){};
  auto ReadFile() -> std::unique_ptr<Maze> override;
};
}  // namespace s21
#endif  // SRC_MODEL_MAZE_FILE_READER_
