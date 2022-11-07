#ifndef __LOGV6_CLIENT_H__
#define __LOGV6_CLIENT_H__
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "RestfulApiCommon.h"
#include "cls_logs.pb.h"

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include <pthread.h>
#include "curl/curl.h"
#include "result.h"

namespace tencent_log_sdk_cpp_v2
{
#define ERRCODE_LIMIT_LOG_SIZE 1
void ExtractJsonResult(const std::string& response, rapidjson::Document& document);

void JsonMemberCheck(const rapidjson::Value& value, const char* name);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, int32_t& number);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, uint32_t& number);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, int64_t& number);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, uint64_t& number);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, bool& boolean);

void ExtractJsonResult(const rapidjson::Value& value, const char* name, std::string& dst);

const rapidjson::Value& GetJsonValue(const rapidjson::Value& value, const char* name);

/** Struct which is the definition of the log item.
*/
extern const char* const LOG_SDK_IDENTIFICATION;

class JsonException : public std::exception
{
    /** Constructor with error code and message. 
* @param errorCode LOG error code. 
* @param message Detailed information for the exception.
* @return The objcect pointer.
*/
public:
    JsonException(const std::string& errorCode, const std::string& message) : mErrorCode(errorCode), mMessage(message)
    {
    }
    ~JsonException() throw() {}
    /** Function that return error code. 
* @param void None. 
* @return Error code string.
*/
    std::string GetErrorCode(void) const { return mErrorCode; }
    /** Function that return error message. 
* @param void None. 
* @return Error message string.
*/
    std::string GetMessage(void) const { return mMessage; }

private:
    std::string mErrorCode;
    std::string mMessage;
};

class LOGClient
{
public:
    LOGClient(const std::string& clsHost, const std::string& accessKeyId, const std::string& accessKey, int64_t timeout,
              int64_t connecttimeout, const std::string& token = "",const std::string& source = "", bool compressFlag = true);
    ~LOGClient() throw();

    PostLogStoreLogsResponse PostLogStoreLogs(const std::string& topic, const cls::LogGroup& loggroup_);

    void SetClsHost(const std::string& clsHost);
    std::string GetClsHost();

    void SetMaxSendSpeed(const curl_off_t speed) { mMaxSendSpeedInBytePerSec = speed; }

protected:
    std::string mClsHost;
    std::string mAccessKeyId;
    std::string mAccessKey;
    std::string mSecurityToken;
    std::string mSource;
    bool mCompressFlag;
    int64_t mTimeout;
    int64_t mConnectTimeout;
    int32_t mLogMaxSize;
    std::string mUserAgent;
    pthread_mutex_t mMutexLock;
    std::string (*mGetDateString)();
    void (*mLOGSend)(const std::string& httpMethod, const std::string& host, const int32_t port, const std::string& url,
                     const std::string& queryString, const std::map<std::string, std::string>& header,
                     const std::string& body, const int64_t timeout, const int64_t connecttimeout,
                     HttpMessage& httpMessage, const curl_off_t maxspeed);
    curl_off_t mMaxSendSpeedInBytePerSec;
    void SendRequest(const std::string& httpMethod, const std::string& url, const std::string& body,
                     const std::map<std::string, std::string>& parameterList,
                     std::map<std::string, std::string>& header, HttpMessage& httpMessage);

private:
    void SetCommonHeader(std::map<std::string, std::string>& httpHeader, int32_t contentLength);
    void SetCommonParameter(std::map<std::string, std::string>& parameterList);
    int LogSizeCalculate(const cls::LogGroup& loggroup_);
};
} // namespace tencent_log_sdk_cpp_v2
#endif
