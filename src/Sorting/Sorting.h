#pragma once

#include "../Parser/ConfigParser.h"
#include "../Tape/Tape.h"
#include "MemoryLayout.h"
#include <memory>

namespace TapeStorage {

class SortManager {
  using CellType = Tape::CellType;
  using Index = Tape::Index;

public:
  SortManager(const ConfigData &config_data);

  struct ExtendedBuffer {
    CellType *buf;
    Index size;
    Index max_size;
    Index counter;
  };

  void CopyTapes(Tape &tape_from, Tape &tape_to, ExtendedBuffer &buf);

  void BubbleSort(Tape &input_tape, Tape &output_tape);

  void LoadToBuffer(ExtendedBuffer &result, Index &curr_load_index,
                    Index end_load_index, Tape &tape);
  void Merge(ExtendedBuffer &buf_1, ExtendedBuffer &buf_2, Tape &out_tape);
  void MergeSort(Tape &input_tape, Tape &output_tape);

  void Sort(Tape &input_tape, Tape &output_tape);

private:
  ConfigData config_data_;
  std::unique_ptr<char[]> op_mem_;
  MemoryLayout mem_layout_;
};

} // namespace TapeStorage
