cmake_minimum_required(VERSION 3.10)
project(Cpp-Server-Client)

set(CMAKE_CXX_STANDARD 98)

set(BOOST_ROOT_DIR /home/ksyoo/ksyooF/third_party/boost-1.72.0)
set(GLOG_ROOT_DIR /home/ksyoo/ksyooF/third_party/glog-0.4.0)
set(RAPIDJSON_ROOT_DIR /home/ksyoo/ksyooF/third_party/rapidjson-1.1.0)

set(BOOST_INCLUDE_DIR ${BOOST_ROOT_DIR}/include)
set(BOOST_LIBRARY_DIR ${BOOST_ROOT_DIR}/lib)
set(GLOG_INCLUDE_DIR ${GLOG_ROOT_DIR}/include)
set(GLOG_LIBRARY_DIR ${GLOG_ROOT_DIR}/lib)
set(RAPIDJSON_INCLUDE_DIR ${RAPIDJSON_ROOT_DIR}/include)

add_subdirectory(src/http_server_v1)
add_subdirectory(src/test_features)
