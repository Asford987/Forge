cmake_minimum_required(VERSION 3.28.3)

project(forge)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(libs/CLI11)
add_subdirectory(libs/tomlplusplus)
add_subdirectory(libs/json)

add_executable(forge src/main/forge.cpp)
# install(TARGETS forge DESTINATION bin)

target_link_libraries(forge PRIVATE CLI11::CLI11)

target_include_directories(forge PRIVATE libs/tomlplusplus/include)
target_link_libraries(forge PRIVATE nlohmann_json::nlohmann_json)