#pragma once

#include <cstdint>
#include <fstream>
#include <string>

namespace TapeStorage {

class Tape {
public:
  using CellType = char;
  using Index = int64_t;
  using Path = std::string;

  Tape(Path path, Index tape_size);

  void MoveHeadForward();
  void MoveHeadBackward();

  using Shift = Index;
  void MoveHead(Shift shift);

  CellType Read();
  void Write(const CellType &new_val);

private:
  std::fstream file_;
  Index head_position_;
  Index tape_size_;
};

} // namespace TapeStorage