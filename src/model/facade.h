#ifndef SRC_MODEL_FACADE_
#define SRC_MODEL_FACADE_

#include "cave.h"
#include "cave_file_reader.h"
#include "cave_file_writer.h"
#include "maze.h"
#include "maze_file_reader.h"
#include "maze_file_writer.h"

namespace s21 {
class Facade {
 public:
  Facade(){};
  ~Facade(){};

  const Maze* get_maze() const { return maze_.get(); }
  const Cave* get_cave() const { return cave_.get(); }

  auto LoadMaze(const std::string& filepath) -> void;
  auto GenerateMaze(Field::Size size) -> void;
  auto SaveMaze(const std::string& filepath) -> void;
  auto SolveMaze(Coordinate begin, Coordinate end) -> Maze::Coordinates*;

  auto LoadCave(const std::string& filepath) -> void;
  auto GenerateCave(Field::Size size, double chance) -> void;
  auto SaveCave(const std::string& filepath) -> void;
  auto CaveIteration(int birth_limit, int death_limit) -> bool;
  auto ResetCave() -> void;

 private:
  std::unique_ptr<Maze> maze_;
  Maze::Coordinates solution_;
  std::unique_ptr<Cave> cave_;
  MatrixMemento* cave_memento_ = nullptr;

  auto ReplaceMemento() -> void;
};
}  // namespace s21

#endif  // SRC_MODEL_FACADE_
