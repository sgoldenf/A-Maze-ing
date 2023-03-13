#ifndef SRC_MODEL_MAZE_FILE_WRITER_
#define SRC_MODEL_MAZE_FILE_WRITER_

#include "file_writer.h"
#include "maze.h"

namespace s21 {
class MazeFileWriter : public IFileWriter<Maze> {
 public:
  explicit MazeFileWriter(const std::string& filepath);
  ~MazeFileWriter();
  auto WriteToFile(const Maze& cave) -> void override;
};
}  // namespace s21
#endif  // SRC_MODEL_MAZE_FILE_WRITER_
