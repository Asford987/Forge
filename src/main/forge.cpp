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


namespace Forge{
    std::string version = "0.0.1";
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
        "  publish        Publish the project (To be added)\n"
        "  -h, --help     Display this information\n"
        "  -v, --version  Display the version\n"
    );


} // namespace Forge
