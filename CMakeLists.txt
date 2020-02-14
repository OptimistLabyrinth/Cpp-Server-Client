cmake_minimum_required(VERSION 3.15)
project(Cpp-Server-Client)

set(CMAKE_CXX_STANDARD 98)

set(BOOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/boost/include)
set(BOOST_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/boost/lib)
set(GLOG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/glog/include)
set(GLOG_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/glog/lib)
set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/gtest/include)
set(GTEST_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/gtest/lib)
set(POCO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/poco/include)
set(POCO_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib/poco/lib)
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/rapidjson/include)

add_subdirectory(src/http_server_v1)
add_subdirectory(src/test_features)
