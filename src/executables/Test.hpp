


namespace Forge
{
  class Test{
    public:
      Test(std::string test_name, std::string test_type){
        this->test_name = test_name;
        this->test_type = test_type;
      }
      void run_test(){
        std::cout << test_name << " " << test_type << std::endl;
      }
    private:
      std::string test_name, test_type;
  };

  class Bench{
    public:
      Bench(std::string bench_name, std::string bench_type){
        this->bench_name = bench_name;
        this->bench_type = bench_type;
      }
      void run_bench(){
        std::cout << bench_name << " " << bench_type << std::endl;
      }
    private:
      std::string bench_name, bench_type;
  };
  
} // namespace Forge
