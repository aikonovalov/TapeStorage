#include "Parser/ConfigParser.h"
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

  Tape input_tape{argv[1], std::stoll(argv[3])};
  Tape output_tape{argv[2], std::stoll(argv[3])};

  return 0;
}
