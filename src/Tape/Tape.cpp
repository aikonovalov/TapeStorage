#include "Tape.h"
#include <cassert>
#include <iostream>

namespace TapeStorage {

Tape::Tape(Path path, Index tape_size, const ConfigData &config_data)
    : config_data_(config_data),
      file_(path, std::ios::binary | std::ios::in | std::ios::out),
      tape_size_(tape_size), head_position_(0) {}

void Tape::MoveHeadForward() {
  ++head_position_;
  assert(head_position_ <= tape_size_ && "Head move is out of range");

  sync();
}

void Tape::MoveHeadBackward() {
  --head_position_;
  assert(head_position_ >= 0 && "Head move is out of range");

  sync();
}

void Tape::MoveHead(Shift shift) {
  sync();
  if (shift < 0) {
    for (Index i = 0; i < -shift; ++i) {
      MoveHeadBackward();
    }

  } else {
    for (Index i = 0; i < shift; ++i) {
      MoveHeadForward();
    }
  }
  sync();
}

void Tape::SetHead(Index new_index) {
  MoveHead(new_index - head_position_);
  sync();
}

Tape::CellType Tape::Read() {
  sync();
  CellType value;
  file_.read(&value, sizeof(value));
  sync();
  return value;
}

void Tape::Write(const CellType &new_val) {
  sync();
  file_.write(&new_val, sizeof(new_val));
  file_.flush();
  sync();
}

Tape::Index Tape::GetSize() const { return tape_size_; }

bool Tape::AtEnd() const { return head_position_ >= tape_size_; }

void Tape::sync() {
  file_.clear();
  std::streamoff pos =
      static_cast<std::streamoff>(head_position_) * sizeof(CellType);
  file_.seekg(pos, std::ios::beg);
  file_.seekp(pos, std::ios::beg);
}

} // namespace TapeStorage