#include <iostream> 
#include <cstdlib>
#include <string>
#include <fstream>

namespace Forge
{
  
  void add_lib_to_cmakelists();

  void remove_lib_from_cmakelists();

  class Install{
    public:
      Install(std::string library, bool github_flag){
        this->library = library;
        this->github_flag = github_flag;
      }
      void install_package(){
        std::cout << library << " " << github_flag << std::endl;
        if(github_flag){
          std::string command = "git clone " + library;
          execute_command(command.c_str());
          add_lib_to_cmakelists();
        }
      }
    private:
      std::string library;
      bool github_flag;

  };

  class Uninstall{
    public:
      Uninstall(std::string library){
        this->library = library;
      }
      void uninstall_package(){
        std::cout << library << std::endl;
        remove_lib_from_cmakelists();
      }
    private:
      std::string library;
  };

} // namespace Forge
