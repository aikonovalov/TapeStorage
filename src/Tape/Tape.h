#pragma once

#include "../Parser/ConfigParser.h"
#include <cstdint>
#include <fstream>
#include <string>

namespace TapeStorage {

class Tape {
public:
  using CellType = char;
  using Index = int64_t;
  using Path = std::string;

  Tape(Path path, Index tape_size, const ConfigData &config_data);

  void MoveHeadForward();
  void MoveHeadBackward();

  using Shift = Index;
  void MoveHead(Shift shift);
  void SetHead(Index new_index);

  CellType Read();
  void Write(const CellType &new_val);

  Index GetSize() const;
  bool AtEnd() const;

private:
  void sync();

  ConfigData config_data_;
  std::fstream file_;
  Index head_position_;
  Index tape_size_;
};

} // namespace TapeStorage