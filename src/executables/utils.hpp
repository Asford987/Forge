#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <array>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json=nlohmann::json;

namespace Forge
{

  void execute_command(const std::string& command) {
    if (std::system(command.c_str()) != 0) {
      std::cerr << "Error executing command: " << command << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // Handle memory allocation failures
        return 0;
    }
    return newLength;
  }

  std::string fetch_repo_latest_version(std::string repo){
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        std::string url = "https://api.github.com/repos/" + repo + "/releases/latest";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    auto js = json::parse(readBuffer);
    return js["tag_name"].get<std::string>();
  }

  std::string get_version(){
    return "0.0.1"; 
  }

  std::map<std::string, std::string> get_global_config(){

  }

  std::map<std::string, std::string> get_local_config(){
    
  }

  std::map<std::string, std::string> get_config(){
    auto config = get_local_config();
    auto global_config = get_global_config();

    for (const auto& [key, value] : global_config) {
      if (config.find(key) == config.end()) {
        config[key] = value;
      }
    }

    return config;
  }

} // namespace Forge
