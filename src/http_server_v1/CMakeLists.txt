project(http_server_v1)

add_executable(http_server_v1 main.cpp)

target_include_directories(http_server_v1
    PUBLIC
        ${GLOG_INCLUDE_DIR})

target_link_directories(http_server_v1
    PUBLIC
        ${GLOG_LIBRARY_DIR})

target_link_libraries(http_server_v1
    PUBLIC
        glog)
