project(mongocxx_testing)
cmake_minimum_required(VERSION 2.8.2)
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/mongocxx/v_noabi")
link_directories("/usr/local/lib")

add_executable(mongocxx_testing test.cpp)
target_compile_features(mongocxx_testing PRIVATE cxx_range_for)
target_link_libraries(mongocxx_testing bsoncxx mongocxx)
