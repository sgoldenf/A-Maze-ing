#ifndef SRC_MODEL_FIELD_
#define SRC_MODEL_FIELD_

#include <stdexcept>
#include <vector>

namespace s21 {
class Field {
 public:
  using Matrix = std::vector<std::vector<bool>>;
  struct Size {
    int width;
    int height;
  };
  Field(){};
  virtual ~Field(){};
  virtual const Size get_size() const = 0;
};
}  // namespace s21
#endif  // SRC_MODEL_FIELD_
