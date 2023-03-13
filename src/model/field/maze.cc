#include "maze.h"

namespace s21 {
Maze::Maze(Matrix& rightWalls, Matrix& bottomWalls)
    : rightWalls_(rightWalls), bottomWalls_(bottomWalls) {
  if (!MazeValidator::Validate(this)) {
    throw std::invalid_argument("maze constructor error: invalid maze");
  }
}

Maze::Maze(Field::Size size) {
  if (size.height < 1 || size.width < 1) {
    throw std::invalid_argument("maze constructor error: size out of range");
  };
  GenerateMaze(size);
}

auto Maze::get_size() const -> const Field::Size {
  return Field::Size{static_cast<int>(rightWalls_[0].size()),
                     static_cast<int>(rightWalls_.size())};
}

auto Maze::GenerateMaze(Size size) -> void {
  rightWalls_ = Matrix(size.height);
  bottomWalls_ = Matrix(size.height);
  std::vector<int> sets(size.width);
  AllocateRows(size);
  int sets_count = 0;
  AssignSets(sets, sets_count, 0);
  for (int i = 0; i < size.height; ++i) {
    AddRightBorders(sets, i);
    AddBottomBorders(sets, i);
    if (i < static_cast<int>(rightWalls_.size() - 1)) {
      AssignSets(sets, sets_count, i);
    }
  }
  CompleteMaze(sets);
}

auto Maze::AllocateRows(Size size) -> void {
  for (int i = 0; i < size.height; ++i) {
    rightWalls_[i] = std::vector<bool>(size.width);
    bottomWalls_[i] = std::vector<bool>(size.width);
  }
}

auto Maze::AssignSets(std::vector<int>& sets, int& count, int row) -> void {
  for (size_t i = 0; i < sets.size(); ++i) {
    if (sets[i] == 0 || bottomWalls_[row][i]) {
      ++count;
      sets[i] = count;
    }
  }
}

auto Maze::AddRightBorders(std::vector<int>& sets, int row) -> void {
  for (size_t i = 0; i < sets.size() - 1; ++i) {
    bool wall = GetRandomBool();
    if (wall || sets[i] == sets[i + 1]) {
      rightWalls_[row][i] = true;
    } else {
      MergeSet(sets, i);
    }
  }
  rightWalls_[row][sets.size() - 1] = true;
}

auto Maze::MergeSet(std::vector<int>& sets, size_t i) -> void {
  int set = sets[i + 1];
  for (size_t j = 0; j < sets.size(); ++j) {
    if (sets[j] == set) {
      sets[j] = sets[i];
    }
  }
}

auto Maze::AddBottomBorders(const std::vector<int>& sets, size_t row) -> void {
  for (size_t i = 0; i < sets.size(); ++i) {
    if (row == bottomWalls_.size() - 1) {
      bottomWalls_[row][i] = true;
    } else {
      bool wall = GetRandomBool();
      if (wall && CountCellsWithoutBottomBorder(sets, row, sets[i]) > 1) {
        bottomWalls_[row][i] = true;
      }
    }
  }
}

auto Maze::GetRandomBool() -> bool {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

auto Maze::CountCellsWithoutBottomBorder(const std::vector<int>& sets, int row,
                                         int value) -> int {
  int count = 0;
  for (size_t i = 0; i < sets.size(); ++i) {
    if (sets[i] == value && !bottomWalls_[row][i]) {
      ++count;
    }
  }
  return count;
}

auto Maze::CompleteMaze(std::vector<int>& sets) -> void {
  for (size_t i = 0; i < sets.size() - 1; ++i) {
    if (sets[i] != sets[i + 1]) {
      rightWalls_[rightWalls_.size() - 1][i] = false;
      MergeSet(sets, i);
    }
  }
}

auto Maze::Solve(Coordinate begin, Coordinate end) -> Coordinates {
  Coordinates path;
  Matrix visited(rightWalls_.size());
  for (size_t i = 0; i < visited.size(); ++i) {
    visited[i] = std::vector<bool>(rightWalls_[0].size());
  }
  RecursiveSolve(visited, path, begin, end);
  return path;
}

auto Maze::RecursiveSolve(Matrix& visited, Coordinates& path, Coordinate begin,
                          Coordinate end) -> bool {
  path.push(begin);
  size_t j = path.top().x;
  size_t i = path.top().y;
  if (i != end.y || j != end.x) {
    visited[i][j] = true;
    Turns t{i > 0 && !bottomWalls_[i - 1][j], j > 0 && !rightWalls_[i][j - 1],
            j < rightWalls_[0].size() - 1 && !rightWalls_[i][j],
            i < bottomWalls_.size() - 1 && !bottomWalls_[i][j]};
    if (t.right && !visited[i][j + 1] &&
        RecursiveSolve(visited, path, Coordinate{j + 1, i}, end)) {
      return true;
    }
    if (t.bottom && !visited[i + 1][j] &&
        RecursiveSolve(visited, path, Coordinate{j, i + 1}, end)) {
      return true;
    }
    if (t.left && !visited[i][j - 1] &&
        RecursiveSolve(visited, path, Coordinate{j - 1, i}, end)) {
      return true;
    }
    if (t.up && !visited[i - 1][j] &&
        RecursiveSolve(visited, path, Coordinate{j, i - 1}, end)) {
      return true;
    }
    path.pop();
    return false;
  }
  return true;
}

auto MazeValidator::Validate(Maze* maze) -> bool {
  if (!CheckRightBorder(maze->get_right_walls()) ||
      !CheckBottomBorder(maze->get_bottom_walls()) ||
      !CheckIsolatedSpacesAndCycles(maze)) {
    return false;
  }
  return true;
}

auto MazeValidator::CheckRightBorder(const Field::Matrix& right_walls) -> bool {
  int last_column = right_walls[0].size() - 1;
  for (size_t i = 0; i < right_walls.size(); ++i) {
    if (!right_walls[i][last_column]) {
      return false;
    }
  }
  return true;
}

auto MazeValidator::CheckBottomBorder(const Field::Matrix& bottom_walls)
    -> bool {
  int last_row = bottom_walls.size() - 1;
  for (size_t i = 0; i < bottom_walls[0].size(); ++i) {
    if (!bottom_walls[last_row][i]) {
      return false;
    }
  }
  return true;
}

auto MazeValidator::CheckIsolatedSpacesAndCycles(Maze* maze) -> bool {
  Field::Matrix visited(maze->get_bottom_walls().size());
  for (size_t i = 0; i < visited.size(); ++i) {
    visited[i] = std::vector<bool>(maze->get_bottom_walls()[0].size());
  }
  if (!TraverseMaze(maze, 0, 0, visited)) {
    return false;
  }
  for (size_t i = 0; i < visited.size(); ++i) {
    for (size_t j = 0; j < visited[i].size(); ++j) {
      if (!visited[i][j]) {
        return false;
      }
    }
  }
  return true;
}

auto MazeValidator::TraverseMaze(Maze* maze, int i, int j,
                                 Field::Matrix& visited) -> bool {
  visited[i][j] = true;
  Turns t{i > 0 && !maze->get_bottom_walls()[i - 1][j],
          j > 0 && !maze->get_right_walls()[i][j - 1],
          j < maze->get_size().width - 1 && !maze->get_right_walls()[i][j],
          i < maze->get_size().height - 1 && !maze->get_bottom_walls()[i][j]};
  if (!CheckIfOnlyOneTurnIsVisited(visited, i, j, t)) {
    return false;
  }
  if (t.up && !visited[i - 1][j] && !TraverseMaze(maze, i - 1, j, visited)) {
    return false;
  }
  if (t.left && !visited[i][j - 1] && !TraverseMaze(maze, i, j - 1, visited)) {
    return false;
  }
  if (t.right && !visited[i][j + 1] && !TraverseMaze(maze, i, j + 1, visited)) {
    return false;
  }
  if (t.bottom && !visited[i + 1][j] &&
      !TraverseMaze(maze, i + 1, j, visited)) {
    return false;
  }
  return true;
}

auto MazeValidator::CheckIfOnlyOneTurnIsVisited(const Field::Matrix& visited,
                                                int i, int j, Turns t) -> bool {
  int visited_turns = 0;
  if (t.up && visited[i - 1][j]) {
    ++visited_turns;
  }
  if (t.left && visited[i][j - 1]) {
    ++visited_turns;
  }
  if (t.right && visited[i][j + 1]) {
    ++visited_turns;
  }
  if (t.bottom && visited[i + 1][j]) {
    ++visited_turns;
  }
  return visited_turns < 2;
}
}  // namespace s21
