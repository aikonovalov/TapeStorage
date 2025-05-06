#include "Sorting.h"
#include "../Utils/MemoryLayout.h"
#include "Tape.h"
#include <filesystem>
#include <memory>

namespace TapeStorage {

SortManager::SortManager(const ConfigData &config_data)
    : config_data_(config_data),
      op_mem_(std::make_unique<char[]>(config_data.op_mem_size)),
      mem_layout_(MemoryLayout(op_mem_.get(), config_data.op_mem_size)) {}

void SortManager::CopyTapes(Tape &tape_from, Tape &tape_to,
                            ExtendedBuffer &buf_1, ExtendedBuffer &buf_2) {
  tape_from.SetHead(0);
  tape_to.SetHead(0);

  buf_1.size = 0;
  buf_2.size = 0;

  Index curr_load_index = 0;
  Index end_load_index = tape_from.GetSize();

  LoadToBuffer(buf_1, curr_load_index, end_load_index, tape_from);
  LoadToBuffer(buf_2, curr_load_index, end_load_index, tape_from);
  while (buf_1.counter < buf_1.size || buf_2.counter < buf_2.size) {
    while (buf_1.counter < buf_1.size) {
      tape_to.Write(buf_1.buf[buf_1.counter++]);
      tape_to.MoveHeadForward();
    }
    while (buf_2.counter < buf_2.size) {
      tape_to.Write(buf_2.buf[buf_2.counter++]);
      tape_to.MoveHeadForward();
    }
    LoadToBuffer(buf_1, curr_load_index, end_load_index, tape_from);
    LoadToBuffer(buf_2, curr_load_index, end_load_index, tape_from);
  }
}

void SortManager::LoadToBuffer(ExtendedBuffer &result, Index &curr_load_index,
                               Index end_load_index, Tape &tape) {
  if (result.counter >= result.size) {
    tape.SetHead(curr_load_index);
    result.counter = 0;
    Index loaded_data_count = 0;
    for (; loaded_data_count < result.max_size &&
           curr_load_index < end_load_index && !tape.AtEnd();
         ++loaded_data_count) {
      result.buf[loaded_data_count] = tape.Read();
      tape.MoveHeadForward();

      ++curr_load_index;
    }

    result.size = loaded_data_count;
  }
}

void SortManager::Merge(ExtendedBuffer &buf_1, ExtendedBuffer &buf_2,
                        Tape &out_tape) {
  if (buf_1.size == 0 || buf_2.size == 0) {
    while (buf_1.counter < buf_1.size) {
      out_tape.Write(buf_1.buf[buf_1.counter++]);
      out_tape.MoveHeadForward();
    }
    while (buf_2.counter < buf_2.size) {
      out_tape.Write(buf_2.buf[buf_2.counter++]);
      out_tape.MoveHeadForward();
    }
    return;
  }
  while (buf_1.counter < buf_1.size && buf_2.counter < buf_2.size) {
    if (buf_1.buf[buf_1.counter] <= buf_2.buf[buf_2.counter]) {
      out_tape.Write(buf_1.buf[buf_1.counter++]);
    } else {
      out_tape.Write(buf_2.buf[buf_2.counter++]);
    }
    out_tape.MoveHeadForward();
  }
}

void SortManager::MergeSort(Tape &input_tape, Tape &output_tape) {
  size_t max_cells = config_data_.op_mem_size / sizeof(CellType);
  if (max_cells < 2) {
    throw std::runtime_error("OP_MEM_SIZE is too few for MergeSort");
  }

  std::filesystem::create_directories("tmp");
  Tape tape_from("tmp/tmp_tape1.dat", input_tape.GetSize(), config_data_);
  Tape tape_to("tmp/tmp_tape2.dat", input_tape.GetSize(), config_data_);

  Index half_cells = max_cells / 2;
  CellType *buf_1 = mem_layout_.allocate<CellType>(half_cells);
  CellType *buf_2 = mem_layout_.allocate<CellType>(half_cells);

  ExtendedBuffer copy_buf_1{buf_1, 0, half_cells, 0};
  ExtendedBuffer copy_buf_2{buf_2, 0, half_cells, 0};
  CopyTapes(input_tape, tape_from, copy_buf_1, copy_buf_2);

  for (Index step_size = 1; step_size < input_tape.GetSize(); step_size *= 2) {
    tape_to.SetHead(0);
    tape_from.SetHead(0);

    for (Index start = 0; start < input_tape.GetSize();
         start += 2 * step_size) {
      Index mid = std::min(start + step_size, input_tape.GetSize());
      Index end = std::min(start + 2 * step_size, input_tape.GetSize());

      ExtendedBuffer merge_buf_1{buf_1, 0, half_cells, 0};
      ExtendedBuffer merge_buf_2{buf_2, 0, half_cells, 0};
      Index idx1 = start, idx2 = mid;

      LoadToBuffer(merge_buf_1, idx1, mid, tape_from);
      LoadToBuffer(merge_buf_2, idx2, end, tape_from);

      while (merge_buf_1.counter < merge_buf_1.size ||
             merge_buf_2.counter < merge_buf_2.size) {
        Merge(merge_buf_1, merge_buf_2, tape_to);
        LoadToBuffer(merge_buf_1, idx1, mid, tape_from);
        LoadToBuffer(merge_buf_2, idx2, end, tape_from);
      }
    }
    std::swap(tape_from, tape_to);
  }

  CopyTapes(tape_from, output_tape, copy_buf_1, copy_buf_2);
}

void SortManager::Sort(Tape &input_tape, Tape &output_tape) {
  MergeSort(input_tape, output_tape);
}

} // namespace TapeStorage