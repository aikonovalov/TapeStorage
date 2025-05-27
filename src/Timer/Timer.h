#pragma once

#include <chrono>

namespace TapeStorage {

class Timer {
public:
  enum class MSeconds : int64_t;
  Timer(MSeconds mseconds);

  ~Timer() noexcept;

private:
  std::chrono::high_resolution_clock::time_point end_time_;
  bool is_waiting_ = false;
};

} // namespace TapeStorage