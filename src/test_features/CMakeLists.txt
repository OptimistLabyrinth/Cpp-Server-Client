project(test_features)

add_executable(test_features main.cpp)

target_include_directories(test_features
    PUBLIC
        ${GLOG_INCLUDE_DIR})

target_link_directories(test_features
    PUBLIC
        ${GLOG_LIBRARY_DIR})

target_link_libraries(test_features
    PUBLIC
        glog)
