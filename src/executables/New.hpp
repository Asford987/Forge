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
        execute_command(command);
        std::filesystem::current_path(project_name);

        git_init();
        create_src();
        create_cmake();
        create_forge_toml();
        create_test();
        create_bench();
        create_docs();
        create_run_cmake();
      }

      void git_init(){
        std::string command = "git init";
        execute_command(command);
      }

      void create_src(){
        std::string command = "mkdir src";
        execute_command(command);
        command = "touch src/";
        if(_is_library) command += "lib.cpp";
        else command += "main.cpp";
        execute_command(command);
      }

      void create_cmake(){
        std::string command = "mkdir CMake";
        execute_command(command);
        command = "touch CMakeLists.txt";
        execute_command(command);
      }

      void create_forge_toml(){
        std::string command = "touch Forge.toml";
        execute_command(command);
      }

      void create_test(){
        std::string command = "mkdir tests";
        execute_command(command);
        command = "touch tests/test.cpp";
        execute_command(command);
      }

      void create_bench(){
        std::string command = "mkdir bench";
        execute_command(command);
        command = "touch bench/bench.cpp";
        execute_command(command);
      }

      void create_docs(){
        std::string command = "mkdir docs";
        execute_command(command);
        command = "touch docs/README.md";
        execute_command(command);
      }

      void create_run_cmake(){
        std::string command = "touch CMake/run.cmake";
        execute_command(command);
        if(_is_library) generate_lib_run();
        else generate_bin_run();
      }

      void generate_lib_run(){

      }

      void generate_bin_run(){

      }

    private:
      std::string project_name;
      bool _is_library;
  };

} // namespace Forge
