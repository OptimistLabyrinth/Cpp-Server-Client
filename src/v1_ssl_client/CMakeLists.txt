project(v1_ssl_client)

add_executable(v1_ssl_client main.cpp)

target_include_directories(v1_ssl_client
    PUBLIC
        ${GLOG_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR})

target_link_directories(v1_ssl_client
    PUBLIC
        ${GLOG_LIBRARY_DIR}
        ${BOOST_LIBRARY_DIR})

target_link_libraries(v1_ssl_client
    PUBLIC
        pthread
        ssl
        crypto
        glog
        boost_system)
