#include <iostream> 
#include <cstdlib>
#include <string>
#include <fstream>

namespace Forge
{
  
  // void add_lib_to_cmakelists();

  // void remove_lib_from_cmakelists();

  class Install{
    public:
      Install(std::string library, bool github_flag, bool global_flag){
        this->library = library; // If github_flag is true, then library is a github link. Preceeding with https://github.com is not necessary. If "=tag" is present, then the tag is used, otherwise the latest version is used.
        this->github_flag = github_flag;
        this->global_flag = global_flag;
      }
      void install_package(){
        std::cout << library << " " << github_flag << std::endl;
        // if(github_flag){
        //   std::string command = "git clone " + library;
        //   execute_command(command.c_str());
        //   add_lib_to_cmakelists();
        // }
      }
    private:
      std::string library;
      bool github_flag;
      bool global_flag;
  };

  class Uninstall{
    public:
      Uninstall(std::string library, bool global_flag){
        this->library = library; // local first then global if global_flag is false. Otherwise order is reversed
        this->global_flag = global_flag;
      }
      void uninstall_package(){
        std::cout << library << std::endl;
        // remove_lib_from_cmakelists();
      }

    private:
      std::string library;
      bool global_flag;
      
      bool uninstall_global_package(){
        std::cout << library << std::endl;
        // remove_lib_from_cmakelists();
      }

      bool uninstall_local_package(){
        std::cout << library << std::endl;
        // remove_lib_from_cmakelists();
      }
  };

} // namespace Forge
