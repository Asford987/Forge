#include <iostream>
#include <filesystem>
#include <cstdlib>



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
        generate_init();
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
        std::string command = "mkdir .CMake";
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
        if(_is_library) generate_lib_run();
        else generate_bin_run();
      }

      void generate_bin_run(){
        std::string file_contents = read_file(get_forge_home() + "/src/files/CMake/run.cmake");
        write_file(".CMake/run.cmake", file_contents);
      }

      void generate_lib_run(){
        std::string file_contents = read_file(get_forge_home() + "/src/files/CMake/lib.cmake");
        write_file(".CMake/run.cmake", file_contents);
      }

      void generate_init(){
        std::string file_contents = read_file(get_forge_home() + "/src/files/CMake/init.cmake");
        file_contents = file_contents.replace(file_contents.find("PROJECT_NAME"), 12, project_name);
        write_file(".CMake/init.cmake", file_contents);
      }

      std::string read_file(std::string file){
        std::ifstream base_init(file);
        std::string str;
        std::string file_contents;
        while (std::getline(base_init, str))
        {
          file_contents += str;
          file_contents.push_back('\n');
        }
        base_init.close();
        return file_contents;
      }

      void write_file(std::string file, std::string contents){
        std::ofstream init_cmake(file);
        init_cmake << contents;
        init_cmake.close();
      }

    private:

      std::string project_name;
      bool _is_library;

      std::string get_forge_home() {
        char* forge_home = std::getenv("FORGE_HOME");
        if (!forge_home) {
          std::cerr << "FORGE_HOME environment variable is not set." << std::endl;
          exit(1);
        }
        return std::string(forge_home);
      }
  
  };

} // namespace Forge
