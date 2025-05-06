#include "MemoryLayout.h"
#include <cstddef>

namespace TapeStorage {

MemoryLayout::MemoryLayout(char *base_ptr, std::size_t size)
    : base_(base_ptr), ptr_(base_ptr), size_(size), remaining_(size){};

} // namespace TapeStorage