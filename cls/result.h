#ifndef __LOGV6_RESULT_H__
#define __LOGV6_RESULT_H__
#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "cls_logs.pb.h"
/*
 * Responses
 */
namespace tencent_log_sdk_cpp_v2
{
struct Response
{
    Response() : statusCode(0), requestId(""), content("") {}
    int32_t statusCode;
    std::string requestId;
    std::map<std::string, std::string> header;
    std::string content;
};


struct PostLogStoreLogsResponse : public Response
{
    int32_t bodyBytes;
    cls::LogGroup loggroup_;
    PostLogStoreLogsResponse() : bodyBytes(0) {}
    std::string Printf()
    {
        std::stringstream ss;
        ss << "statusCode:" << statusCode << " requestId:" << requestId << " content:" << content
           << " bodyBytes:" << bodyBytes;
        for (auto item : header)
        {
            ss << " header:"
               << "key:" << item.first << " value:" << item.second;
        }
        return ss.str();
    }
};

class CallBack
{
public:
    virtual void Success(PostLogStoreLogsResponse result) = 0;
    virtual void Fail(PostLogStoreLogsResponse result) = 0;
    virtual ~CallBack() {}
};

} // namespace tencent_log_sdk_cpp_v2

#endif
