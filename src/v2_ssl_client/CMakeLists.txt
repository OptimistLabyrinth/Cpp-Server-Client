project(v2_ssl_client)

set(SRCS
        main.cpp
        ClientManager.cpp
        ClientManager.h
        client_internal/MyClient.cpp
        client_internal/MyClient.h
        )

add_executable(v2_ssl_client ${SRCS})

target_include_directories(v2_ssl_client
    PUBLIC
        ${GLOG_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )

target_link_directories(v2_ssl_client
    PUBLIC
        ${GLOG_LIBRARY_DIR}
        ${BOOST_LIBRARY_DIR}
        )

target_link_libraries(v2_ssl_client
    PUBLIC
        pthread
        ssl
        crypto
        glog
        boost_system
        )
