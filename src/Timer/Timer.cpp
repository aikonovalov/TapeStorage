#include "Timer.h"
#include <chrono>
#include <thread>

namespace TapeStorage {

Timer::Timer(MSeconds milliseconds) {
  std::chrono::high_resolution_clock::time_point curr_time =
      std::chrono::high_resolution_clock::now();

  end_time_ =
      curr_time + std::chrono::milliseconds(static_cast<int64_t>(milliseconds));
}

Timer::~Timer() noexcept {
  is_waiting_ = true;
  std::this_thread::sleep_until(end_time_);
  is_waiting_ = false;
};

} // namespace TapeStorage