#pragma once

#include <cstddef>
#include <memory>

namespace TapeStorage {

class MemoryLayout {
public:
  explicit MemoryLayout(char *base_ptr, std::size_t size);

  template <typename T> T *allocate(std::size_t count = 1) {
    void *aligned_ptr = static_cast<void *>(ptr_);
    std::size_t space = remaining_;

    if (!std::align(alignof(T), sizeof(T) * count, aligned_ptr, space)) {
      throw std::bad_alloc();
    }

    T *result = reinterpret_cast<T *>(aligned_ptr);
    ptr_ = reinterpret_cast<char *>(aligned_ptr) + sizeof(T) * count;
    remaining_ = size_ - (ptr_ - base_);
    return result;
  }

private:
  char *base_;
  char *ptr_;
  std::size_t remaining_;
  std::size_t size_;
};

} // namespace TapeStorage