cmake_minimum_required(VERSION 2.6)
project(tencent-log-sdk-cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations" )

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRCS cls/PROTO_HDRS cls/cls_logs.proto cls/logproducerconfig.proto)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_LISTS
    cls/client.cpp
    cls/adapter.cpp
    cls/common.cpp
    lz4/lz4.c
    cls/signature.cpp
    cls/logthreadpool.cpp
    cls/batchloggroup.cpp
    cls/logaccumulator.cpp
    cls/logtimer.cpp
    cls/utils.cpp
    cls/producerclient.cpp
    cls/result.h
    cls/logmemmgr.cpp
    cls/logretryqueue.cpp
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


install(FILES cls/client.h cls/RestfulApiCommon.h cls/common.h 
    cls/producerclient.h cls/result.h cls/common.h cls/logthreadpool.h 
    cls/batchloggroup.h cls/logmemmgr.h cls/logaccumulator.h cls/logtimer.h
    cls/logretryqueue.h cls/logthreadpool.h cls/error.h ${PROTO_HDRS}
    DESTINATION include/cls)

install(DIRECTORY rapidjson
    DESTINATION include)

