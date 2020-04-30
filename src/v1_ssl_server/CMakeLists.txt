project(v1_ssl_server)

add_executable(v1_ssl_server main.cpp)

target_include_directories(v1_ssl_server
    PUBLIC
        ${GLOG_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )

target_link_directories(v1_ssl_server
    PUBLIC
        ${GLOG_LIBRARY_DIR}
        ${BOOST_LIBRARY_DIR})

target_link_libraries(v1_ssl_server
    PUBLIC
        pthread
        ssl
        crypto
        glog
        boost_system)
