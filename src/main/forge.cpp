#include <iostream>

#include <CLI/CLI.hpp>
#include <toml++/toml.h>
#include <nlohmann/json.hpp>

#include "executables/utils.hpp"
#include "executables/Analyze.hpp"
#include "executables/Build.hpp"
#include "executables/Config.hpp"
#include "executables/New.hpp"
#include "executables/Test.hpp"
#include "executables/Install.hpp"
#include "executables/Publish.hpp"


int main(int argc, char** argv){
  CLI::App app{"forge - A cargo-like C++ Project Manager"};
  
  app.set_help_flag("-h, --help", "Display this information");
  app.set_version_flag("-v, --version", Forge::get_version());
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
  

  bool lib_flag = false;
  std::string proj_name;
  new_proj->add_option("name", proj_name, "Create a library project");
  new_proj->add_flag("--lib", lib_flag, "Create a library project");
  
  new_proj->callback([&]() {
    std::cout << new_proj->get_option("name")->as<std::string>() << std::endl;
    std::cout << lib_flag << std::endl;
  });

  
  bool kubernetes_flag = false, docker_flag = false;
  std::string arch("auto"), target("build"), mode("release");
  build_proj->add_flag("-k", kubernetes_flag, "Build for kubernetes");
  build_proj->add_flag("--kubernetes", kubernetes_flag, "Build for kubernetes");
  build_proj->add_flag("-d", docker_flag, "Build for docker");
  build_proj->add_flag("--docker", docker_flag, "Build for docker");
  build_proj->add_option("--arch", arch, "Architecture of the target system");
  build_proj->add_option("-t", target, "Target directory for the build");
  build_proj->add_option("--target", target, "Target directory for the build");
  build_proj->add_option("-m", mode, "Build mode (debug, release)");
  build_proj->add_option("--mode", mode, "Build mode (debug, release)");

  build_proj->callback([&]() {
    std::cout << kubernetes_flag << " " << docker_flag << " " << arch << " " << target << " " << mode << std::endl;
  });


  run_proj->add_flag("-k", kubernetes_flag, "Build for kubernetes");
  run_proj->add_flag("--kubernetes", kubernetes_flag, "Build for kubernetes");
  run_proj->add_flag("-d", docker_flag, "Build for docker");
  run_proj->add_flag("--docker", docker_flag, "Build for docker");
  run_proj->add_option("--arch", arch, "Architecture of the target system");
  run_proj->add_option("-t", target, "Target directory for the build");
  run_proj->add_option("--target", target, "Target directory for the build");
  run_proj->add_option("-m", mode, "Build mode (debug, release)");
  run_proj->add_option("--mode", mode, "Build mode (debug, release)");
  
  run_proj->callback([&]() {
    std::cout << kubernetes_flag << " " << docker_flag << " " << arch << " " << target << " " << mode << std::endl;
  });


  test_proj->callback([&]() {});
  bench_proj->callback([&]() {});


  bool github_flag = false;
  std::string package_name;
  install_proj->add_flag("-g", github_flag, "Install from github"); // with or without https://github.com is fine
  install_proj->add_option("library")->required();

  install_proj->callback([&]() {
    std::cout << install_proj->get_option("library")->as<std::string>() << " " << github_flag << std::endl;
  });


  uninstall_proj->add_option("library")->required();
  uninstall_proj->callback([&]() {
    std::cout << uninstall_proj->get_option("library")->as<std::string>() << std::endl;
  });


  analyze_proj->callback([&]() {});


  bool global_flag = false;
  std::string key, value;
  config_proj->add_flag("-g", global_flag, "Set global configuration");
  config_proj->add_option("key", key, "Key for the configuration");
  config_proj->add_option("value", value, "Value for the configuration");
  config_proj->callback([&]() {
    std::cout << key << " " << value << " " << global_flag << std::endl;
  });


  publish_proj->callback([&]() {});


  CLI11_PARSE(app, argc, argv);

}