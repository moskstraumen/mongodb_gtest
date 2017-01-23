project(mongocxx_testing)
cmake_minimum_required(VERSION 2.8.2)

option(build_func_libs "Build the functions for testing as libraries." OFF)
option(use_built_libs "Build the functions for testing as libraries." ON)

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE})
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories("/home/jiahui/Software/install/include/bsoncxx/v_noabi")
include_directories("/home/jiahui/Software/install/include/mongocxx/v_noabi")
include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
include_directories("/home/jiahui/work/Simmune/mongocxx/analyzerLib") # Simmune analyzer
include_directories("/home/jiahui/work/Simmune_build2/SimmuneRelease/analyzerLib")
include_directories("/home/jiahui/work/Simmune/mongocxx/simShare") # Simmune analyzer

link_directories("/home/jiahui/Software/install/lib") # library of mongo c driver / c++ driver
link_directories("/home/jiahui/work/Simmune_build2/SimmuneRelease/analyzerLib")  # library of analyzer
#link_directories("/home/jiahui/work/Simmune_build2/SimmuneRelease/simShare")  # library of analyzer

enable_testing()

if(use_built_libs)
#include_directories("/home/jiahui/work/include")
#link_directories("/home/jiahui/work/lib")

    add_executable(test_module mongocxx_testing_test.cpp)

    #target_compile_features(test_module PRIVATE cxx_range_for)

    target_link_libraries(test_module bsoncxx mongocxx dbClient mongodbToy analyzerLib)
        
else(use_built_libs)
    add_executable(test_module mongocxx_testing_test.cpp dbClient.cpp mongodbToy.cpp)

    #target_compile_features(test_module PRIVATE cxx_range_for)

    target_link_libraries(test_module bsoncxx mongocxx)

endif(use_built_libs)

target_compile_features(test_module PRIVATE cxx_range_for)

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
      
if(build_func_libs) 
      add_library(mongodbToy SHARED mongodbToy.cpp)
      target_compile_features(mongodbToy PRIVATE cxx_range_for)
      target_link_libraries(mongodbToy bsoncxx mongocxx)
      
      add_library(dbClient SHARED dbClient.cpp mongodbToy.cpp)
      target_compile_features(dbClient PRIVATE cxx_range_for)
      target_link_libraries(dbClient bsoncxx mongocxx)
      
      include(GenerateExportHeader)
      GENERATE_EXPORT_HEADER(mongodbToy
      BASE_NAME mongodbToy
      EXPORT_FILE_NAME mongodbToy.h)
      GENERATE_EXPORT_HEADER(dbClient
      BASE_NAME dbClient
      EXPORT_FILE_NAME dbClient.h)
      
      set(CMAKE_INSTALL_PREFIX /home/jiahui/work)
      install(TARGETS dbClient LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
      install(TARGETS mongodbToy LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
      install(FILES "${PROJECT_BINARY_DIR}/mongodbToy.h" DESTINATION include)
      install(FILES "${PROJECT_BINARY_DIR}/dbClient.h" DESTINATION include) 
endif(build_func_libs) 