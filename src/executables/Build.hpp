#pragma once



namespace Forge
{
  class Build{
    public:
      Build(bool kubernetes_flag, bool docker_flag, std::string arch, std::string target, std::string mode){
        this->kubernetes_flag = kubernetes_flag;
        this->docker_flag = docker_flag;
        this->arch = arch;
        this->target = target;
        this->mode = mode;
      }
      void build_project(){
        std::cout << kubernetes_flag << " " << docker_flag << " " << arch << " " << target << " " << mode << std::endl;
      }
    protected:
      bool kubernetes_flag, docker_flag;
      std::string arch, target, mode;
  };
  class Run: public Build{
    public:
      Run(bool kubernetes_flag, bool docker_flag, std::string arch, std::string target, std::string mode):
        Build(kubernetes_flag, docker_flag, arch, target, mode){}
        
      void run_project(){        
        build_project();
        run();
      }

      void run(){
        
      }
  };
  
} // namespace Forge
