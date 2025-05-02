#pragma once

#include <cstdint>
#include <string>

namespace TapeStorage {

using ConfigMeasure = int64_t;
const std::string kCONFIG_FILE_NAME = "config.txt";

struct ConfigData {
  static constexpr ConfigMeasure kDEFAULT_VALUE = 100;

  ConfigMeasure op_mem_size = kDEFAULT_VALUE;

  ConfigMeasure read_delay = kDEFAULT_VALUE;
  ConfigMeasure write_delay = kDEFAULT_VALUE;

  ConfigMeasure switch_tape_delay = kDEFAULT_VALUE;
  ConfigMeasure move_head_delay = kDEFAULT_VALUE;
};

ConfigData ParseConfig();

} // namespace TapeStorage