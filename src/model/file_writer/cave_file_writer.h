#ifndef SRC_MODEL_CAVE_FILE_WRITER_
#define SRC_MODEL_CAVE_FILE_WRITER_

#include "cave.h"
#include "file_writer.h"

namespace s21 {
class CaveFileWriter : public IFileWriter<Cave> {
 public:
  explicit CaveFileWriter(const std::string& filepath);
  ~CaveFileWriter();
  auto WriteToFile(const Cave& cave) -> void override;
};
}  // namespace s21
#endif  // SRC_MODEL_CAVE_FILE_WRITER_
