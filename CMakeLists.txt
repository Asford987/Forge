cmake_minimum_required(VERSION 3.28.3)

project(forge)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.3
)


FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG v2.4.2
)
  
FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus
  GIT_TAG v3.4.0
)
  
FetchContent_Declare(
  curl
  GIT_REPOSITORY https://github.com/curl/curl
  GIT_TAG curl-8_8_0
)
    
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(json CLI11 tomlplusplus curl)

add_executable(forge src/main/forge.cpp)
# install(TARGETS forge DESTINATION bin)

target_link_libraries(forge PRIVATE CLI11::CLI11)
target_link_libraries(forge PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(forge PRIVATE tomlplusplus::tomlplusplus)