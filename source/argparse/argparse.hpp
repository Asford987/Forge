#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <map>


namespace argparse{

    class ArgumentError: public std::exception{
        private:
            std::string message;
        public:
            ArgumentError(std::string message){
                this->message = message;
            }
            const char* what() const throw(){
                return this->message.c_str();
            }
    };

    class Argument{
        private:
            std::string shortName;
            std::string longName;
            int nargs;
            std::string help;
            bool required;
            std::string action_;
            std::vector<std::string> value;
            
            void set_value(std::vector<std::string> value);
            void action();
        public:

            friend class ArgumentParser;
            friend class ArgumentNamespace;

            Argument();
            Argument(std::string shortName, std::string longName, int nargs, std::string help, bool required, std::string action);
            std::vector<std::string> get_value();
    };

    class ArgumentNamespace{
        private:
            std::map<std::string, Argument> arguments;
        public:
            ArgumentNamespace(std::vector<Argument> args);
            ArgumentNamespace(std::map<std::string, Argument> args);
            std::vector<std::string> get_value(std::string longName);
            void print();
            std::vector<std::string> operator[](std::string longName);
    };
    
    class ArgumentParser{
        private:
            std::string help_msg;
            std::map<std::string, Argument> arguments;

        public:
            ArgumentParser(std::string help_msg);
            void add_argument(std::string shortName, std::string longName, int nargs = 0, std::string help = "", bool required = false, std::string action = ""); // if nargs=0, type=action
            void print_help();
            void set_help_msg(std::string help_msg);
            ArgumentNamespace parse_args(int argc, char **argv);
    };
}