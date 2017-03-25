cmake_minimum_required(VERSION 2.8.10)
include(ExternalProject)

set(base "${CMAKE_BINARY_DIR}/ExternalProjects")
set_property(DIRECTORY PROPERTY EP_BASE "${CMAKE_BINARY_DIR}/ExternalProjects")


set(install_dir "${base}/Install")
message("install dir : ${install_dir}" )
#set(boost "/home/jiahui/work/Simmune/mongo_gtest_build/ExternalProjects/Source/Boost")

set(boost "${base}/Source/Boost")
set(BOOST_BUILD_COMMAND ./b2 -sNO_BZIP2=1 -sNO_ZLIB=1 --with-graph --with-serialization --with-program_options --with-thread --with-filesystem --with-system --with-random)
###########################################################
# Boost
###########################################################
ExternalProject_Add(Boost
        GIT_REPOSITORY "https://github.com/boostorg/boost.git"
        GIT_TAB "master"
 # URL "http://localhost:10080/resources/Boost/boost_1_60_0.tar.gz"
          UPDATE_COMMAND ""
   CONFIGURE_COMMAND ""
  BUILD_COMMAND ${BOOST_BUILD_COMMAND}
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE 1
) 
SET(boostbootstrap bootstrap.sh )
ExternalProject_Add_Step(Boost booststrap 
  COMMAND  ./${boostbootstrap}     
  COMMENT "bootstrapping boost"    
  DEPENDEES download    
  DEPENDERS configure
  WORKING_DIRECTORY ${boost}
  )
  
###########################################################
# BSON
###########################################################
ExternalProject_Add(libBSON
  GIT_REPOSITORY "https://github.com/mongodb/libbson.git"
  GIT_TAG "master" 
  UPDATE_COMMAND ""
  CMAKE_GENERATOR ${gen}
  LOG_INSTALL FALSE
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${install_dir}/libBSON
    -DCMAKE_BUILD_TYPE:STRING=${build_type}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    ${cxx11_flag}
    -DCMAKE_SKIP_RPATH:BOOL=OFF
#    ${mac_args}
)

##if(UNIX)
  set(BSON_LIB_flag -DBSON_LIBRARY:FILEPATH=${install_dir}/libBSON/lib/libbson-1.0.so)
##endif()
##
###########################################################
# Mongo C Driver
###########################################################
ExternalProject_Add(mongo-c-driver
  GIT_REPOSITORY "https://github.com/mongodb/mongo-c-driver.git"
  GIT_TAG "1.3.6" 
  UPDATE_COMMAND ""
  CMAKE_GENERATOR ${gen}
  LOG_INSTALL FALSE
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${install_dir}/mongo-c-driver
    -DCMAKE_BUILD_TYPE:STRING=${build_type}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DBSON_ROOT_DIR=${install_dir}/libBSON/
    ${BSON_LIB_flag}
    ${cxx11_flag}
    -DCMAKE_SKIP_RPATH:BOOL=OFF
#    ${mac_args}
    DEPENDS libBSON
)

###########################################################
# Mongo C++ Driver
###########################################################
message("boost dir : ${boost}") 
set(MONGOCXX_SOURCE_DIR "${base}/ExternalProjects/Source/mongo-cxx-driver")
set(MONGOCXX_BINARY_DIR "${base}/ExternalProjects/Build/mongo-cxx-driver")
set(MONGOC_LIB_flag -DMONGOC_LIBRARY:FILEPATH=${install_dir}/mongo-c-driver/lib/libmongoc-1.0.so)
ExternalProject_Add(mongo-cxx-driver
  GIT_REPOSITORY "https://github.com/mongodb/mongo-cxx-driver.git"
  GIT_TAG "r3.0.2" 
  UPDATE_COMMAND ""
  CMAKE_GENERATOR ${gen}
  LOG_INSTALL FALSE
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${install_dir}/mongo-cxx-driver
    -DCMAKE_BUILD_TYPE:STRING=${build_type}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DBSONCXX_POLY_USE_BOOST=1
    -DBoost_INCLUDE_DIR:FILEPATH=${boost}
    -DLIBBSON_DIR=${install_dir}/libBSON/
    -DLIBMONGOC_DIR=${install_dir}/mongo-c-driver/
    ${cxx11_flag}
    ${MONGOC_LIB_flag}
    -DCMAKE_SKIP_RPATH:BOOL=OFF
##    ${mac_args}
    DEPENDS mongo-c-driver

   )


