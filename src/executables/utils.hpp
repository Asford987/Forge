#include <iostream>
#include <cstdlib>
#include <string>

namespace Forge
{
  void execute_command(const std::string& command) {
    if (std::system(command.c_str()) != 0) {
      std::cerr << "Error executing command: " << command << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  void get_version(){

  }

  
} // namespace Forge
