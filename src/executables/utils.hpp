#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <array>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

using json=nlohmann::json;

namespace Forge
{

  std::string get_forge_home() {
    char* forge_home = std::getenv("FORGE_HOME");
    if (!forge_home) {
      std::cerr << "FORGE_HOME environment variable is not set." << std::endl;
      exit(1);
    }
    return std::string(forge_home);
  }

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

  json get_global_config(){
    std::string forge_home = get_forge_home();
    std::ifstream config_file(forge_home + "/config/config.json");
    json config;
    if (config_file.is_open()) {
      config_file >> config;
    }
    return config;
  }

  json get_local_config(){
    std::ifstream config_file(".config.json");
    json config;
    if (config_file.is_open()) {
      config_file >> config;
    }
    return config;
  }

  json get_config(){
    auto config = get_local_config();
    auto global_config = get_global_config();
    for (auto it = global_config.begin(); it != global_config.end(); ++it) {
      if (config.find(it.key()) == config.end()) {
        config[it.key()] = it.value();
      }
    }
    return config;
  }

  void set_global_config(json config){
    std::string forge_home = get_forge_home();
    std::ofstream config_file(forge_home + "/config/config.json");
    config_file << config.dump(2);
    config_file.close();
  }

  void set_local_config(json config){
    std::ofstream config_file(".config.json");
    config_file << config.dump(2);
    config_file.close();
  }
  

} // namespace Forge
