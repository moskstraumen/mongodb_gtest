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

enable_testing()
add_executable(test_module mongocxx_testing_test.cpp dbClient.h mongodbToy.h)

target_compile_features(test_module PRIVATE cxx_range_for)

target_link_libraries(test_module bsoncxx mongocxx)

target_link_libraries(test_module
        pthread)
target_link_libraries(test_module
        gmock
        gmock_main)
target_link_libraries(test_module
        gtest
        gtest_main)

add_test(testing test_module)

set_target_properties(test_module
      PROPERTIES
      COMPILE_DEFINITIONS "GTEST_LINKED_AS_SHARED_LIBRARY=1")
