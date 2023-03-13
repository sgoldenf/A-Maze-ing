#ifndef SRC_MODEL_CAVE_FILE_READER_
#define SRC_MODEL_CAVE_FILE_READER_

#include "cave.h"
#include "file_reader.h"

namespace s21 {
class CaveFileReader : public IFileReader<Cave> {
 public:
  explicit CaveFileReader(const std::string& filepath);
  ~CaveFileReader();
  auto ReadFile() -> std::unique_ptr<Cave> override;
};
}  // namespace s21
#endif  // SRC_MODEL_CAVE_FILE_READER_
