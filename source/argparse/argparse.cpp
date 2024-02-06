#include "argparse.hpp"

namespace argparse{
    ArgumentParser::ArgumentParser(std::string help_msg){
        this->help_msg = help_msg;
    }

    void ArgumentParser::add_argument(std::string shortName, std::string longName, int nargs, std::string help, bool required, std::string action){
        Argument arg = Argument(shortName, longName, nargs, help, required, action);
        this->arguments[longName] = arg;
    }

    void ArgumentParser::set_help_msg(std::string help_msg){
        this->help_msg = help_msg;
    }

    void ArgumentParser::print_help(){
        std::cout << this->help_msg << std::endl;
        std::cout << "Arguments:" << std::endl;
        for(auto const& [key, val] : this->arguments){
            std::string complement;
            if(val.nargs == 0){
                complement = "<action>";
            } else{
                complement = "<args>";
            } 
            
            if(val.required){
                complement += " (required)";
            }

            std::cout << "-" << val.shortName << ", --" << val.longName << " " << complement<< " : " << val.help << std::endl;
        }
    }

    ArgumentNamespace ArgumentParser::parse_args(int argc, char **argv){
        for(size_t i=0; i<argc; i++){
            std::string arg = argv[i];
            if(arg[0] == '-'){
                if(arg[1] == '-'){
                    std::string longName = arg.substr(2);
                    if(this->arguments.find(longName) != this->arguments.end()){
                        if(this->arguments[longName].nargs == 0){
                            arguments[longName].action();
                        } else{
                            std::vector<std::string> value;
                            for(size_t j=i+1; j<=i+arguments[longName].nargs; j++){
                                if(j == argc) break;
                                std::string nextArg = argv[j];
                                if(nextArg[0] == '-'){
                                    break;
                                } else{
                                    value.push_back(nextArg);
                                }
                            }
                            arguments[longName].set_value(value); 
                        }
                    }
                } else{
                    std::string shortName = arg.substr(1);
                    for(auto const& [key, val] : this->arguments){    
                        if(val.shortName == shortName){
                            if(this->arguments[key].nargs == 0){
                                arguments[key].action();
                            } else{
                                std::vector<std::string> value;
                                for(size_t j=i+1; j<=i+arguments[key].nargs; j++){
                                    std::string nextArg = argv[j];
                                    if(nextArg[0] == '-'){
                                        break;
                                    } else{
                                        value.push_back(nextArg);
                                    }
                                }
                                arguments[val.longName].set_value(value); 
                            }
                        }
                    }
                }
            }
        }  

        for(auto const& [key, val] : this->arguments){
            if(val.required && (val.value.size() == 0)){
                throw ArgumentError(std::string("Error: Argument --") + val.longName + " is required");
            }
        }

        return ArgumentNamespace(this->arguments);
    }

    Argument::Argument() : shortName(""), longName(""), nargs(0), help(""), required(false), action_(""){
        this->value = std::vector<std::string>();
    }

    Argument::Argument(std::string shortName, std::string longName, int nargs, std::string help, bool required, std::string action): shortName(shortName), longName(longName), nargs(nargs), help(help), required(required), action_(action){
        this->value = std::vector<std::string>();
    }

    std::vector<std::string> Argument::get_value(){
        return this->value;
    }

    void Argument::set_value(std::vector<std::string> value){
        this->value = value;
    }

    void Argument::action(){
        if(this->action_ == "store_true"){
            this->value.push_back("1");
        } else if(this->action_ == "store_false"){
            this->value.push_back("0");
        } 
    }

    ArgumentNamespace::ArgumentNamespace(std::vector<Argument> args){
        for(auto arg: args){
            this->arguments[arg.longName] = arg;
        }
    }

    ArgumentNamespace::ArgumentNamespace(std::map<std::string, Argument> args){
        this->arguments = args;
    }

    std::vector<std::string> ArgumentNamespace::get_value(std::string longName){
        return this->arguments[longName].value;
    }

    std::vector<std::string> ArgumentNamespace::operator[](std::string longName){
        return this->arguments[longName].value;
    }

        void
        ArgumentNamespace::print()
    {
        for(auto const& [key, val] : this->arguments){
            std::cout << key << " : ";
            for(auto v: val.value){
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
}