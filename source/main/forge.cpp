#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#include <map>
#include "../argparse/argparse.hpp"
#include "../executables/createProj.hpp"
#include "../executables/installPackage.hpp"
#include "../executables/publish.hpp"
#include "../executables/runProj.hpp"


namespace Forge{
    std::string version = "0.0.1";
    std::string global_help_msg(
        "Usage: forge <option>\n"
        "Options:\n"
        "  new        Create a new project\n"
        "  build      Build the project\n"
        "  run        Run the project\n"
        "  test       Run the tests\n"
        "  install    Install a package\n"
        "  bench      Run the benchmarks\n"
        "  uninstall  Uninstall a package\n"
        "  publish    Publish the project (To be added)\n"
        "  --help     Display this information\n"
        "  --version  Display the version\n"
    );


    class Parser{
        protected:
            argparse::ArgumentParser parser;
            std::map<std::string, std::vector<std::string>> args;
        public:
            Parser(std::string help_msg): parser(help_msg){
            }
            
            void parse_args(int argc, char** argv){
            }

            std::map<std::string, std::vector<std::string>> retrieve_args(){
                return this->args;
            }
    };


    class NewArgumentParser: public Parser{
        public:
            NewArgumentParser() : Parser("Usage: forge new <project_name> [options]"){
                parser.add_argument("d", "dir", 1, "The directory to create the project", false, "store");
                parser.add_argument("-lib", "lib", 0, "Create a library project", false, "store_true");
            }

            void parse_args(int argc, char** argv){
                std::string project_name;
                if(std::string(argv[2]) == "--help"){
                    parser.print_help();
                    return;
                }
                if(std::string(argv[2]).find("-") == std::string::npos){
                    project_name = argv[2];
                } else{
                    throw std::invalid_argument("Expected project name");
                }
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["name"] = std::vector<std::string>{project_name};
                this->args["dir"] = args["dir"];
                this->args["lib"] = args["lib"];
            }
    };

    class InstallArgumentParser: public Parser{
        public:
            InstallArgumentParser() : Parser("Usage: forge install <package_name> [option]"){
                parser.add_argument("g", "global", 0, "global installation flag", false, "store_true");
            }

            void parse_args(int argc, char** argv){
                std::string package_name;
                if(std::string(argv[2]) == "--help"){
                    parser.print_help();
                    return;
                }
                if(std::string(argv[2]).find("-") == std::string::npos){
                    package_name = argv[2];
                } else{
                    throw std::invalid_argument("Expected package name");
                }
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["name"] = std::vector<std::string>{package_name};
                this->args["global"] = args["global"];
            }        
    };

    class UninstallArgumentParser: public Parser{
        public:
            UninstallArgumentParser(): Parser("Usage: forge uninstall <package_name> [option]"){
                parser.add_argument("g", "global", 0, "global installation flag", false, "store_true");
            }
            
            void parse_args(int argc, char** argv){
                std::string package_name;
                if(std::string(argv[2]) == "--help"){
                    parser.print_help();
                    return;
                }
                if(std::string(argv[2]).find("-") == std::string::npos){
                    package_name = argv[2];
                } else{
                    throw std::invalid_argument("Expected package name");
                }
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["name"] = std::vector<std::string>{package_name};
                this->args["global"] = args["global"];
            }        
    };

    class PublishArgumentParser: public Parser{
        public:
            PublishArgumentParser(): Parser("Usage: forge publish [options]"){
                parser.add_argument("u", "user", 1, "username of the publisher", false);
                parser.add_argument("k", "password", 1, "Password of the user", false);
                parser.add_argument("gc", "globar-register", 0, "Register username and password globally", false, "store_true");

            }
            
            void parse_args(int argc, char** argv){
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["user"] = args["user"];
                this->args["password"] = args["password"];
            }        
    };

    class BuildArgumentParser: public Parser{
        public:
            BuildArgumentParser(): Parser("Usage: forge build [options]"){
                parser.add_argument("a", "arch", 1, "architecture to build on", false);
                parser.add_argument("l", "lang", 1, "Language to associate with", false);
            }
            
            void parse_args(int argc, char** argv){
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["arch"] = args["arch"];
                this->args["lang"] = args["lang"];
            }
    };

    class RunArgumentParser: public Parser{
        public:
            RunArgumentParser(): Parser("Usage: forge run [options]"){
                parser.add_argument("a", "arch", 1, "architecture to build on", false);
                parser.add_argument("t", "target", 1, "target directory, if wasnt specified already", false);
            }
            
            void parse_args(int argc, char** argv){
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this->args["arch"] = args["arch"];
                this->args["target"] = args["target"];
            }
    };

    class TestArgumentParser: public Parser{
        public:
            TestArgumentParser(): Parser("Usage: forge test [options]"){
                parser.add_argument("a", "all", 1, "", false);
            }
            
            void parse_args(int argc, char** argv){
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this -> args["all"] = args["all"];
            }
    };

    class BenchArgumentParser: public Parser{
        public:
            BenchArgumentParser(): Parser("Usage: forge publish [options]"){
                parser.add_argument("a", "all", 1, "", false);
            }
            
            void parse_args(int argc, char** argv){
                argparse::ArgumentNamespace args = parser.parse_args(argc, argv);
                this -> args["all"] = args["all"];
            }
    };

    class ActionTaker{

        using ArgMap = std::map<std::string, std::vector<std::string>>;
        using Lambda = std::function<void(ArgMap)>;

        private:
            ArgMap args;
            std::string option;
            Lambda action;
        public:
            ActionTaker(std::string option, int argc, char** argv){
                std::unique_ptr<Forge::Parser> parser;
                if(option == "new"){
                    parser = std::make_unique<Forge::NewArgumentParser>();
                }
                if(option == "build"){
                    parser = std::make_unique<Forge::BuildArgumentParser>();
                }
                if(option == "run"){
                    parser = std::make_unique<Forge::RunArgumentParser>();
                }
                if(option == "test"){
                    parser = std::make_unique<Forge::TestArgumentParser>();
                }
                if(option == "install"){
                    parser = std::make_unique<Forge::InstallArgumentParser>();
                }
                if(option == "uninstall"){
                    parser = std::make_unique<Forge::UninstallArgumentParser>();
                }
                if(option == "publish"){
                    parser = std::make_unique<Forge::PublishArgumentParser>();
                }
                if(option == "bench"){
                    parser = std::make_unique<Forge::BenchArgumentParser>();
                }
                parser->parse_args(argc, argv);
                this->args = parser->retrieve_args();
            }  

            void act(){
                this->action(this->args);
            }      
    };

    int exec(int argc, char** argv){
        if(argc < 2){
            std::cout << Forge::global_help_msg << std::endl;
            return 1;
        }
        std::string option = argv[1];
        std::vector<std::string> options = {"new", "build", "run", "test", "install", "uninstall", "--help", "--version", "publish", "bench"}; 
        if(std::find(options.begin(), options.end(), option) == options.end()){
            std::cout << "Invalid option: " << option << std::endl;
            std::cout << Forge::global_help_msg << std::endl;
            return 1;
        } 
        if(option == "--help"){
            std::cout << Forge::global_help_msg << std::endl;
            return 0;
        }
        if(option == "--version"){
            std::cout << "Forge version " << Forge::version << std::endl;
            return 0;
        }
        ActionTaker actionTaker(option, argc, argv);
        actionTaker.act();
        return 0;
    }
}

int main(int argc, char** argv){
    return Forge::exec(argc, argv);
}