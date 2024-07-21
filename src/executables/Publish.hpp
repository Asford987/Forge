#pragma once



namespace Forge
{
  class Publish{
    public:
      Publish(std::string library){
        this->library = library;
      }
      void publish_package(){
        std::cout << library << std::endl;
      }
    private:
      std::string library;
  };
} // namespace Forge
