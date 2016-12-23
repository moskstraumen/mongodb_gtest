project(mongocxx_testing)
cmake_minimum_required(VERSION 2.8.2)

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE})
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
link_directories("/usr/local/lib")

add_executable(mongocxx_testing main.cpp mongodbToy.cpp)
target_compile_features(mongocxx_testing PRIVATE cxx_range_for)
target_link_libraries(mongocxx_testing bsoncxx mongocxx)
target_link_libraries(mongocxx_testing
        pthread)
target_link_libraries(mongocxx_testing
        gmock
        gmock_main)
target_link_libraries(mongocxx_testing
        gtest
        gtest_main)
