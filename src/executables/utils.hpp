#include <iostream>
#include <cstdlib>
#include <string>
#include <map>


namespace Forge
{

  std::string global_help_msg(
    "Usage: forge <option>\n"
    "Options:\n"
    "  new            Create a new project\n"
    "  build          Build the project\n"
    "  run            Run the project\n"
    "  test           Run the tests\n"
    "  install        Install a package\n"
    "  bench          Run the benchmarks\n"
    "  uninstall      Uninstall a package\n"
    "  analyze        Analyze the code for easy vulnerabilities\n"
    "  config         Set configuration for the project or globally\n"
    "  publish        Publish the project (To be added)\n"
    "  -h, --help     Display this information\n"
    "  -v, --version  Display the version\n"
  );
  
  
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
