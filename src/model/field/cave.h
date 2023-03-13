#ifndef SRC_MODEL_CAVE_
#define SRC_MODEL_CAVE_

#include <random>

#include "field.h"

namespace s21 {
class Cave;
class MatrixMemento {
 public:
  explicit MatrixMemento(const Field::Matrix& matrix) : matrix_(matrix){};

 private:
  friend class Cave;
  Field::Matrix matrix_;
};

class Cave : public Field {
 public:
  explicit Cave(Matrix& cells) : cells_(cells){};
  explicit Cave(Field::Size size, double init_chance);
  ~Cave() override{};

  const Matrix& get_cells() const { return cells_; }
  const Size get_size() const override;

  auto NextIteration(int birth_limit, int death_limit) -> bool;
  auto CreateCellsMemento() -> MatrixMemento*;
  auto ReinstateCellsMemento(MatrixMemento* meme) -> void;

 private:
  auto GenerateCave(Size size, double init_chance) -> void;
  auto AllocateRows(Field::Size size) -> void;
  auto GetRandomPercentage() -> double;

  Matrix cells_;
};
}  // namespace s21
#endif  // SRC_MODEL_CAVE_
