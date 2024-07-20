


namespace Forge
{
  class Config{
    public:
      Config(std::string key, std::string value, bool global_flag){
        this->key = key;
        this->value = value;
        this->global_flag = global_flag;
      }
      void set_config(){
        std::cout << key << " " << value << " " << global_flag << std::endl;
      }
    private:
      std::string key, value;
      bool global_flag;
  };
} // namespace Forge
