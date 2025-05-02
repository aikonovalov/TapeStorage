#include "Tape.h"
#include <cassert>

namespace TapeStorage {

Tape::Tape(Path path, Index tape_size)
    : file_(path, std::ios::in | std::ios::out), tape_size_(tape_size),
      head_position_(0) {}

void Tape::MoveHeadForward() {
  ++head_position_;
  assert(head_position_ < tape_size_ && "Head move is out of range");

  file_.seekp(1, std::ios::cur);
}

void Tape::MoveHeadBackward() {
  --head_position_;
  assert(head_position_ >= 0 && "Head move is out of range");

  file_.seekp(-1, std::ios::cur);
}

void Tape::MoveHead(Shift shift) {
  if (shift < 0) {
    for (Index i = 0; i < -shift; ++i) {
      MoveHeadBackward();
    }

  } else {
    for (Index i = 0; i < shift; ++i) {
      MoveHeadForward();
    }
  }
}

Tape::CellType Tape::Read() {
  CellType value;
  file_.read(&value, sizeof(value));
  return value;
}

void Tape::Write(const CellType &new_val) {
  file_.write(&new_val, sizeof(new_val));
}

} // namespace TapeStorage