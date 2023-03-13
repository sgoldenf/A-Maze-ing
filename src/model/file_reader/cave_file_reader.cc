#include "cave_file_reader.h"

namespace s21 {
CaveFileReader::CaveFileReader(const std::string& filepath)
    : IFileReader(filepath) {}

CaveFileReader::~CaveFileReader() {}

auto CaveFileReader::ReadFile() -> std::unique_ptr<Cave> {
  if (!file_.is_open()) {
    throw std::invalid_argument("file reading error");
  }
  Field::Size size = ReadSize();
  Field::Matrix matrix(size.height);
  AllocateRows(matrix, size);
  ReadMatrix(matrix);
  for (std::string err; std::getline(file_, err);) {
    if (!std::all_of(err.begin(), err.end(), isspace)) {
      throw std::invalid_argument("cave reading error");
    }
  }
  return std::make_unique<Cave>(matrix);
}
}  // namespace s21