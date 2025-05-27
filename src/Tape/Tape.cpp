#include "Tape.h"
#include "Timer.h"
#include <cassert>
#include <iostream>

namespace TapeStorage {

Tape *Tape::current_tape_ = nullptr;

Tape::Tape(Path path, Index tape_size, const ConfigData &config_data)
    : config_data_(config_data),
      file_(path, std::ios::binary | std::ios::in | std::ios::out),
      tape_size_(tape_size), head_position_(0) {}

void Tape::MoveHeadForward() {
  TapeChangeCheck();
  ++head_position_;
  assert(head_position_ <= tape_size_ && "Head move is out of range");

  Timer move_head_timer(Timer::MSeconds{config_data_.move_head_delay});

  sync();
}

void Tape::MoveHeadBackward() {
  TapeChangeCheck();
  --head_position_;
  assert(head_position_ >= 0 && "Head move is out of range");

  Timer move_head_timer(Timer::MSeconds{config_data_.move_head_delay});

  sync();
}

void Tape::MoveHead(Shift shift) {
  TapeChangeCheck();
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
  TapeChangeCheck();
  MoveHead(new_index - head_position_);
  sync();
}

Tape::CellType Tape::Read() {
  TapeChangeCheck();
  Timer read_timer{Timer::MSeconds{config_data_.read_delay}};

  sync();
  CellType value;
  file_.read(&value, sizeof(value));

  sync();
  return value;
}

void Tape::Write(const CellType &new_val) {
  TapeChangeCheck();
  Timer write_timer{Timer::MSeconds{config_data_.write_delay}};

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

void Tape::TapeChangeCheck() {
  if (this != current_tape_) {
    Timer tape_change_timer{Timer::MSeconds{config_data_.switch_tape_delay}};
    current_tape_ = this;
  }
}

} // namespace TapeStorage