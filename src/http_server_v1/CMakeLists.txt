project(http_server_v1)

add_executable(http_server_v1 main.cpp)

#target_sources(http_server_v1
#    PUBLIC
#        server_main/Connection.cpp
#        server_main/Connection.h
#        server_main/ConnectionManager.cpp
#        server_main/ConnectionManager.h
#        server_main/Header.h
#        server_main/HttpServer.cpp
#        server_main/HttpServer.h
#        server_main/MIME_TYPES.cpp
#        server_main/MIME_TYPES.h
#        server_main/Reply.cpp
#        server_main/Reply.h
#        server_main/Request.cpp
#        server_main/Request.h
#        server_main/RequestHandler.cpp
#        server_main/RequestHandler.h
#        server_main/RequestParser.cpp
#        server_main/RequestParser.h)

target_include_directories(http_server_v1
    PUBLIC
        ${BOOST_INCLUDE_DIR}
        ${GLOG_INCLUDE_DIR})

target_link_directories(http_server_v1
    PUBLIC
        ${BOOST_LIBRARY_DIR}
        ${GLOG_LIBRARY_DIR})

target_link_libraries(http_server_v1
    PUBLIC
        boost_system
        glog)
