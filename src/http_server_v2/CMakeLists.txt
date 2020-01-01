project(http_server_v2)

add_executable(http_server_v2 main.cpp server_main/ServerManager.cpp server_main/ServerManager.h)

target_sources(http_server_v2
    PUBLIC
        server_main/BasicHandler.cpp
        server_main/BasicHandler.h
        server_main/HandlerFactory.cpp
        server_main/HandlerFactory.h
        server_main/PostRequestHandler.cpp
        server_main/PostRequestHandler.h)

target_include_directories(http_server_v2
    PUBLIC
        ${GLOG_INCLUDE_DIR}
        ${POCO_INCLUDE_DIR})

target_link_directories(http_server_v2
    PUBLIC
        ${GLOG_LIBRARY_DIR}
        ${POCO_LIBRARY_DIR})

target_link_libraries(http_server_v2
    PUBLIC
        glog
        PocoFoundation
        PocoNet)
