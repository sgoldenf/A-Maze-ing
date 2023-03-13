#ifndef SRC_MODEL_FILEREADER_H_
#define SRC_MODEL_FILEREADER_H_

#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>

#include "field.h"

namespace s21 {
template <class T>
class IFileReader {
 public:
  explicit IFileReader(const std::string& filepath) { file_.open(filepath); };
  ~IFileReader(){};
  virtual auto ReadFile() -> std::unique_ptr<T> = 0;

 protected:
  auto ReadSize() -> Field::Size;
  static auto AllocateRows(Field::Matrix& matrix, Field::Size size) -> void;
  auto ReadMatrix(Field::Matrix& matrix) -> void;
  std::ifstream file_;
};

template <class T>
auto IFileReader<T>::ReadSize() -> Field::Size {
  std::string size_str;
  if (!std::getline(file_, size_str)) {
    throw std::invalid_argument("error while reading field size");
  }
  std::istringstream s(size_str);
  std::string str;
  if (!std::getline(s, str, ' ')) {
    throw std::invalid_argument("error while reading field size");
  }
  int rows = std::stoi(str);
  if (!std::getline(s, str, ' ')) {
    throw std::invalid_argument("error while reading field size");
  }
  int cols = std::stoi(str);
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("error while reading field size");
  }
  if (std::getline(s, str) && !std::all_of(str.begin(), str.end(), isspace)) {
    throw std::invalid_argument("error while reading field size");
  }
  return Field::Size{rows, cols};
}

template <class T>
auto IFileReader<T>::AllocateRows(Field::Matrix& matrix, Field::Size size)
    -> void {
  for (int i = 0; i < size.height; i++) {
    matrix[i] = std::vector<bool>(size.width);
  }
}

template <class T>
auto IFileReader<T>::ReadMatrix(Field::Matrix& matrix) -> void {
  for (size_t i = 0; i < matrix.size(); ++i) {
    std::string row;
    if (!std::getline(file_, row)) {
      throw std::invalid_argument("matrix reading error");
    }
    std::istringstream s(row);
    std::string cell;
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      if (!std::getline(s, cell, ' ')) {
        throw std::invalid_argument("matrix reading error");
      }
      int val = std::stoi(cell);
      if (val != 0 && val != 1) {
        throw std::invalid_argument("matrix reading error");
      }
      matrix[i][j] = val;
    }
    if (std::getline(s, cell) &&
        !std::all_of(cell.begin(), cell.end(), isspace)) {
      throw std::invalid_argument("matrix reading error");
    }
  }
}
}  // namespace s21

#endif  // SRC_MODEL_FILEREADER_H_
