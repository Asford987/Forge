#pragma once

#include <nlohmann/json.hpp>
#include "utils.hpp"

using json=nlohmann::json;


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
        if(global_flag){
          json forge_global_configs = get_global_config();
          forge_global_configs[key] = value;
          set_global_config(forge_global_configs);
        } else{
          json forge_local_configs = get_config();
          forge_local_configs[key] = value;
          set_local_config(forge_local_configs);
        }
      }
    private:
      void _set_config(json config, bool is_local){
        if(is_local) set_local_config(config);
        else set_global_config(config);
      }

      std::string key, value;
      bool global_flag;
  };
} // namespace Forge
