#include "cave.h"

namespace s21 {
Cave::Cave(Field::Size size, double init_chance) {
  if (size.height < 1 || size.width < 1 || init_chance < 0 || init_chance > 1) {
    throw std::invalid_argument(
        "cave constructor error: size/init_chance out of range");
  }
  GenerateCave(size, init_chance);
}

const Field::Size Cave::get_size() const {
  Size size =
      Size{static_cast<int>(cells_[0].size()), static_cast<int>(cells_.size())};
  return size;
}

auto Cave::GenerateCave(Size size, double init_chance) -> void {
  cells_ = Field::Matrix(size.height);
  AllocateRows(size);
  for (size_t i = 0; i < cells_.size(); ++i) {
    for (size_t j = 0; j < cells_[i].size(); ++j) {
      cells_[i][j] = GetRandomPercentage() < init_chance;
    }
  }
}

auto Cave::GetRandomPercentage() -> double {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_real_distribution<double> dist(0, 1);
  return static_cast<double>(dist(engine));
}

auto Cave::AllocateRows(Field::Size size) -> void {
  for (int i = 0; i < size.height; ++i) {
    cells_[i] = std::vector<bool>(size.width);
  }
}

auto Cave::NextIteration(int birth_limit, int death_limit) -> bool {
  if (!(birth_limit >= 0 && birth_limit <= 7) ||
      !(death_limit >= 0 && death_limit <= 7)) {
    throw std::invalid_argument(
        "birth/death limit out of range, shoul be >= 0 and <=7");
  }
  Field::Matrix new_cells = cells_;
  for (size_t x = 0; x < cells_.size(); ++x) {
    for (size_t y = 0; y < cells_[x].size(); ++y) {
      int alive_neighbours = 0;
      bool first_row = x == 0;
      bool last_row = x == static_cast<size_t>(new_cells.size() - 1);
      bool first_col = y == 0;
      bool last_col = y == new_cells[x].size() - 1;
      if (first_row && last_row && first_col && last_col) {
        alive_neighbours += 8;
      } else if ((first_row && last_row) || (first_col && last_col)) {
        alive_neighbours += 6;
      } else if ((first_row || last_row) && (first_col || last_col)) {
        alive_neighbours += 5;
      } else if (first_row || last_row || first_col || last_col) {
        alive_neighbours += 3;
      }
      int iMax = last_row ? 1 : 2;
      int jMax = last_col ? 1 : 2;
      for (int i = first_row ? 0 : -1; i < iMax; ++i) {
        for (int j = first_col ? 0 : -1; j < jMax; ++j) {
          if (!(i == 0 && j == 0)) {
            alive_neighbours += cells_[x + i][y + j];
          }
        }
      }
      if (cells_[x][y] && alive_neighbours < death_limit) {
        new_cells[x][y] = false;
      } else if (!cells_[x][y] && alive_neighbours > birth_limit) {
        new_cells[x][y] = true;
      }
    }
  }
  bool cave_changed = cells_ != new_cells;
  cells_ = new_cells;
  return cave_changed;
}

auto Cave::CreateCellsMemento() -> MatrixMemento* {
  return new MatrixMemento(cells_);
}

auto Cave::ReinstateCellsMemento(MatrixMemento* meme) -> void {
  cells_ = meme->matrix_;
}
}  // namespace s21