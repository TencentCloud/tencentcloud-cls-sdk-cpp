#pragma once
#include <string>
#include "cls_logs.pb.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // inet_ntop
#include <netdb.h>
#include <string.h> // bzero
#include <errno.h>
#include "error.h"


namespace tencent_log_sdk_cpp_v2
{
ErrCode GetLogContentSize(const cls::Log& log,int64_t& sizeInBytes);
int64_t GetNowTimeMs();
std::string ToString(const int32_t& n);
std::string ToString(const uint32_t& n);
std::string ToString(const size_t& n);
std::string ToString(const time_t& n);
std::string ToString(const int64_t& n);
std::string ToString(const bool& n);
void GetSelfServerIP(char* pszIP);
} // namespace tencent_log_sdk_cpp_v2