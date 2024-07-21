#include <iostream>
#include <filesystem>



namespace Forge
{
  class New{
    public:
      New(std::string project_name, bool is_library){
        this->project_name = project_name;
        this->_is_library = is_library;
      }
      void create_project(){
        std::string current_directory = std::filesystem::current_path();
        std::string command = "mkdir " + project_name;
        std::system(command.c_str());
        std::filesystem::current_path(project_name);

        git_init();
        create_src();
        create_cmake();
        create_forge_toml();
      }

      void git_init(){
        std::string command = "git init";
        std::system(command.c_str());
      }

      void create_src(){
        std::string command = "mkdir src";
        std::system(command.c_str());
        command = "touch src/";
        if(_is_library) command += "lib.cpp";
        else command += "main.cpp";
        std::system(command.c_str());
      }

      void create_cmake(){
        std::string command = "mkdir CMake";
        std::system(command.c_str());
        command = "touch CMakeLists.txt";
        std::system(command.c_str());
      }

      void create_forge_toml(){
        std::string command = "touch Forge.toml";
        std::system(command.c_str());
      }

    private:
      std::string project_name;
      bool _is_library;
  };

} // namespace Forge
