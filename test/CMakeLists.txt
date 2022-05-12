cmake_minimum_required(VERSION 2.6)
project(tencent-log-sdk-cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#添加头文件的依赖路径
include_directories(../)

#开启测试
enable_testing()

##benchmark测试
#find_package(benchmark REQUIRED)

find_package(Threads REQUIRED)
#find_package(Protobuf REQUIRED)

#boost头文件查找路径
INCLUDE_DIRECTORIES(/usr/local/Cellar/boost/1.78.0_1/include)
INCLUDE_DIRECTORIES(/Users/herrylv/Desktop/cls_team/tencentcloud-cls-sdk-cpp/)
#添加库查找路径
link_directories(
    "../../tencentcloud-cls-sdk-cpp/"
    "/usr/local/lib"
    "/usr/local/Cellar/openssl@3/3.0.2/lib"
    "/usr/local/Cellar/boost/1.78.0_1/lib")

# GTest 的头文件
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(tencentclssdk_test tencentclssdk_test.cpp)
add_executable(tencentclssdk_benchmark tencentclssdk_benchmark.cpp)
# 链接测试库
#target_link_libraries( tencentclssdk_test
#        ${GTEST_BOTH_LIBRARIES}
#        pthread
#        clssdk
#        curl
#        protobuf 
#        ssl
#        crypto
#        boost_chrono
#        boost_date_time
#        boost_thread-mt
#        boost_system
#        benchmark)

# 链接测试库
target_link_libraries( tencentclssdk_benchmark
        ${GTEST_BOTH_LIBRARIES}
        pthread
        clssdk
        curl
        protobuf 
        ssl
        crypto
        boost_chrono
        boost_date_time
        boost_thread
        boost_system)




