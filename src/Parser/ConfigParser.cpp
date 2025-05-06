#include "ConfigParser.h"
#include <fstream>
#include <stdexcept>

namespace TapeStorage {

ConfigData ParseConfig() {
  ConfigData config_data;

  std::ifstream file(kCONFIG_FILE_NAME);
  if (!file) {
    throw std::runtime_error("Cannon open config file!");
  }

  std::string curr_word;
  ConfigMeasure curr_measure;

  while (file >> curr_word) {
    curr_measure = 0;
    if (curr_word == "OP_MEM_SIZE") {
      file >> curr_measure;
      config_data.op_mem_size = curr_measure;
    } else if (curr_word == "READ_DELAY") {
      file >> curr_measure;
      config_data.read_delay = curr_measure;
    } else if (curr_word == "WRITE_DELAY") {
      file >> curr_measure;
      config_data.write_delay = curr_measure;
    } else if (curr_word == "SWITCH_TAPE_DELAY") {
      file >> curr_measure;
      config_data.switch_tape_delay = curr_measure;
    } else if (curr_word == "MOVE_HEAD_DELAY") {
      file >> curr_measure;
      config_data.move_head_delay = curr_measure;
    }
  }

  return config_data;
}

} // namespace TapeStorage