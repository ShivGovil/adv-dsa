cmake_minimum_required(VERSION 3.10)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp)

target_compile_options(main PRIVATE -I/usr/local/include)
target_link_directories(main PRIVATE /usr/local/lib)
target_link_libraries(main PRIVATE xxhash)
