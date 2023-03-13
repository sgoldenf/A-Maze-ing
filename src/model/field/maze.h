#ifndef SRC_MODEL_MAZE_
#define SRC_MODEL_MAZE_

#include <memory>
#include <random>
#include <stack>

#include "field.h"

namespace s21 {
struct Coordinate {
  size_t x;
  size_t y;
  bool operator==(const Coordinate& B) const { return x == B.x && y == B.y; };
};

struct Turns {
  bool up;
  bool left;
  bool right;
  bool bottom;
};

class Maze : public Field {
 public:
  using Coordinates = std::stack<Coordinate>;
  explicit Maze(Matrix& rightWalls, Matrix& bottomWalls);

  explicit Maze(Field::Size size);
  ~Maze() override{};

  const Matrix& get_right_walls() const { return rightWalls_; }
  const Matrix& get_bottom_walls() const { return bottomWalls_; }

  auto Solve(Coordinate begin, Coordinate end) -> Coordinates;

  auto get_size() const -> const Size override;

 private:
  auto GenerateMaze(Size size) -> void;
  auto AllocateRows(Size size) -> void;
  auto AssignSets(std::vector<int>& sets, int& count, int row) -> void;
  auto AddRightBorders(std::vector<int>& sets, int row) -> void;
  static auto MergeSet(std::vector<int>& sets, size_t i) -> void;
  auto AddBottomBorders(const std::vector<int>& sets, size_t row) -> void;
  static auto GetRandomBool() -> bool;
  auto CountCellsWithoutBottomBorder(const std::vector<int>& sets, int row,
                                     int value) -> int;
  auto CompleteMaze(std::vector<int>& sets) -> void;
  auto RecursiveSolve(Matrix& visited, Coordinates& path, Coordinate begin,
                      Coordinate end) -> bool;

  Matrix rightWalls_;
  Matrix bottomWalls_;
};

class MazeValidator {
 public:
  static auto Validate(Maze* maze) -> bool;

 private:
  static auto CheckRightBorder(const Field::Matrix& right_walls) -> bool;
  static auto CheckBottomBorder(const Field::Matrix& bottom_walls) -> bool;
  static auto CheckIsolatedSpacesAndCycles(Maze* maze) -> bool;
  static auto TraverseMaze(Maze* maze, int i, int j, Field::Matrix& visited)
      -> bool;
  static auto CheckIfOnlyOneTurnIsVisited(const Field::Matrix& visited, int i,
                                          int j, Turns t) -> bool;
};

}  // namespace s21
#endif  // A1_MAZE_SRC_MODEL_MAZE_
