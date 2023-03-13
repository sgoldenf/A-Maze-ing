#ifndef SRC_CONTROLLER_
#define SRC_CONTROLLER_

#include "facade.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(Facade* f) : facade_(f) {}
  ~Controller() {}

  const Maze* get_maze() const { return facade_->get_maze(); }
  const Cave* get_cave() const { return facade_->get_cave(); }

  auto LoadMaze(const std::string& filepath) -> void {
    facade_->LoadMaze(filepath);
  };
  auto GenerateMaze(Field::Size size) -> void { facade_->GenerateMaze(size); };
  auto SaveMaze(const std::string& filepath) -> void {
    facade_->SaveMaze(filepath);
  };
  auto SolveMaze(Coordinate begin, Coordinate end) -> Maze::Coordinates* {
    return facade_->SolveMaze(begin, end);
  };

  auto LoadCave(const std::string& filepath) -> void {
    facade_->LoadCave(filepath);
  };
  auto GenerateCave(Field::Size size, double chance) -> void {
    facade_->GenerateCave(size, chance);
  };
  auto SaveCave(const std::string& filepath) -> void {
    facade_->SaveCave(filepath);
  };
  auto CaveIteration(int birth_limit, int death_limit) -> bool {
    return facade_->CaveIteration(birth_limit, death_limit);
  };
  auto ResetCave() -> void { facade_->ResetCave(); };

 private:
  Facade* facade_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_
