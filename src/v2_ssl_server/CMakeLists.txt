project(v2_ssl_server)

set(SRCS
        main.cpp
        server_internal/MyServer.cpp
        server_internal/MyServer.h
        ServerManager.cpp ServerManager.h)

add_executable(v2_ssl_server ${SRCS})

target_include_directories(v2_ssl_server
        PUBLIC
        ${GLOG_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )

target_link_directories(v2_ssl_server
        PUBLIC
        ${GLOG_LIBRARY_DIR}
        ${BOOST_LIBRARY_DIR}
        )

target_link_libraries(v2_ssl_server
        PUBLIC
        pthread
        ssl
        crypto
        glog
        boost_system
        )
