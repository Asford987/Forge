#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#include <map>
#include <CLI/CLI.hpp>
#include <toml++/toml.h>
#include "executables/utils.hpp"


namespace Forge{
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
    "  analyze        Analyze the code for vulnerabilities\n"
    "  config         Set configuration for the project or globally\n"
    "  publish        Publish the project (To be added)\n"
    "  -h, --help     Display this information\n"
    "  -v, --version  Display the version\n"
  );


} // namespace Forge

int main(int argc, char** argv){
  CLI::App app{"forge - A cargo-like C++ Project Manager"};
  std::map<std::string, std::string> config = Forge::get_config();
  app.set_help_flag("--help");
  app.set_version_flag("--version");
  auto new_proj = app.add_subcommand("new", "Create a new project");
  auto build_proj = app.add_subcommand("build", "Build the project");
  auto run_proj = app.add_subcommand("run", "Run the project");
  auto test_proj = app.add_subcommand("test", "Run the tests");
  auto install_proj = app.add_subcommand("install", "Install a package");
  auto bench_proj = app.add_subcommand("bench", "Run the benchmarks");
  auto uninstall_proj = app.add_subcommand("uninstall", "Uninstall a package");
  auto analyze_proj = app.add_subcommand("analyze", "Analyze the code for vulnerabilities");
  auto config_proj = app.add_subcommand("config", "Set configuration for the project or globally");
  auto publish_proj = app.add_subcommand("publish", "Publish the project (To be added)");
  
  bool kubernetes_flag = false, docker_flag = false;
  std::string arch, target, mode;
  build_proj->add_flag("-k", kubernetes_flag);
  build_proj->add_flag("-d", docker_flag);
  build_proj->add_option("--arch", arch, "Architecture of the target system");
  build_proj->add_option("--target", target, "Target directory for the build");
  build_proj->add_option("-m", mode, "Build mode (debug, release)");

  auto run = app.add_subcommand("run", "Run the project");
  run->add_option("--mode", mode, "Build type (Debug, Release)");
    run->callback([&]() {
        // if (mode.empty()) {
        //     mode = get_config("mode", false);
        //     if (mode.empty()) {
        //         mode = "Debug"; // Default build type
        //     }
        // }
        std::cout << "Running the project with build type: " << mode << std::endl;
        // Add code to run the project using the specified build type
    });


    CLI11_PARSE(app, argc, argv);

}