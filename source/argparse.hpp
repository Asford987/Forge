#include <iostream>
#include <vector>
#include <string>


namespace argparse{
    class ArgumentParser{
        public:
            ArgumentParser(int argc, char **argv);
            void add_argument(std::string name, std::string help, std::string type, bool required);
            void parse_args();
            std::string get(std::string name);
            void print_help();
    };
}