cmake_minimum_required(VERSION 3.27.7)

project(forge)

add_subdirectory(libs/CLI11)
add_subdirectory(libs/tomlplusplus)

add_executable(forge source/forge/forge.cpp)
install(TARGETS forge DESTINATION bin)

target_link_libraries(forge PRIVATE CLI11::CLI11)

target_include_directories(forge PRIVATE libs/tomlplusplus/include)