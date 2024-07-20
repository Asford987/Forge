#include <iostream>
#include <cstdlib>
#include <string>
#include <map>


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

  std::map<std::string, std::string> get_global_config(){

  }

  std::map<std::string, std::string> get_local_config(){
    
  }

  std::map<std::string, std::string> get_config(){
    auto config = get_local_config();
    auto global_config = get_global_config();

    for (const auto& [key, value] : global_config) {
      if (config.find(key) == config.end()) {
        config[key] = value;
      }
    }

    return config;
  }
  
} // namespace Forge
