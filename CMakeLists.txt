cmake_minimum_required(VERSION 2.6)
project(tencent-log-sdk-cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations" )

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS cls_logs.proto logproducerconfig.proto)

set(SRC_LISTS
    client.cpp
    adapter.cpp
    common.cpp
    lz4/lz4.c
    signature.cpp
    logthreadpool.cpp
    batchloggroup.cpp
    logaccumulator.cpp
    logtimer.cpp
    utils.cpp
    producerclient.cpp
    result.h
    logmemmgr.cpp
    logretryqueue.cpp
    ${PROTO_SRCS}
)
add_library(clssdk_static
    STATIC
    ${SRC_LISTS})

add_library(clssdk_shared
    SHARED
    ${SRC_LISTS})

set_target_properties (clssdk_static PROPERTIES OUTPUT_NAME "clssdk")
set_target_properties (clssdk_shared PROPERTIES OUTPUT_NAME "clssdk")

install(TARGETS clssdk_static clssdk_shared
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES client.h RestfulApiCommon.h common.h 
    producerclient.h result.h common.h logthreadpool.h 
    batchloggroup.h logmemmgr.h logaccumulator.h logtimer.h
    logretryqueue.h logthreadpool.h error.h ${PROTO_HDRS}
    DESTINATION include)

install(DIRECTORY rapidjson
    DESTINATION include)

