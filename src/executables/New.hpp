

namespace Forge
{
  class New{
    public:
      New(std::string project_name, bool is_library){
        this->project_name = project_name;
        this->_is_library = is_library;
      }
      void create_project(){
        std::cout << project_name << " " << _is_library << std::endl;
      }
    private:
      std::string project_name;
      bool _is_library;
  };

} // namespace Forge
