#include "Parser/ConfigParser.h"
#include "Sorting/Sorting.h"
#include "Tape/Tape.h"
#include <stdexcept>
#include <string>

using namespace TapeStorage;

int main(int argc, char **argv) {
  if (argc != 4) {
    throw std::runtime_error(
        "Wrong args count!\nUsage: ./* <input tape> <output tape> <tape size>");
  }

  ConfigData config_data = ParseConfig();

  Tape input_tape{argv[1], std::stoll(argv[3]), config_data};
  Tape output_tape{argv[2], std::stoll(argv[3]), config_data};

  SortManager sort_manager(config_data);

  sort_manager.Sort(input_tape, output_tape);

  return 0;
}
