#ifndef SRC_MODEL_FILE_WRITER_H_
#define SRC_MODEL_FILE_WRITER_H_

#include <fstream>

#include "field.h"

namespace s21 {
template <class T>
class IFileWriter {
 public:
  explicit IFileWriter(const std::string& filepath) : file_(filepath){};
  ~IFileWriter(){};
  virtual auto WriteToFile(const T& field) -> void = 0;

 protected:
  auto WriteSize(Field::Size size) -> void;
  auto WriteMatrix(const Field::Matrix& matrix) -> void;
  std::ofstream file_;
};

template <class T>
auto IFileWriter<T>::WriteSize(Field::Size size) -> void {
  file_ << size.width << " " << size.height << std::endl;
}

template <class T>
auto IFileWriter<T>::WriteMatrix(const Field::Matrix& matrix) -> void {
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      file_ << matrix[i][j];
      if (j < matrix[i].size() - 1) {
        file_ << " ";
      }
    }
    file_ << std::endl;
  }
}
}  // namespace s21

#endif  // SRC_MODEL_FILE_WRITER_H_