#include "cave_file_writer.h"

namespace s21 {
CaveFileWriter::CaveFileWriter(const std::string& filepath)
    : IFileWriter(filepath) {}

CaveFileWriter::~CaveFileWriter() {}

auto CaveFileWriter::WriteToFile(const Cave& cave) -> void {
  if (!file_.is_open()) {
    throw std::invalid_argument("file reading error");
  }
  WriteSize(cave.get_size());
  WriteMatrix(cave.get_cells());
}
}  // namespace s21