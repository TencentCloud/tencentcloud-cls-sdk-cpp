#include "adapter.h"
#include "utils.h"
#include <iostream>
#include <sys/time.h>

using namespace std;

namespace tencent_log_sdk_cpp_v2
{
extern const char* const DATE_FORMAT_RFC822 = "%a, %d %b %Y %H:%M:%S GMT"; ///< RFC822 date formate, GMT time.
static const uint32_t MD5_BYTES = 16;

extern const char* const LOGE_REQUEST_ERROR = "RequestError";
extern const char* const LOGE_INVALID_HOST = "InvalidHost";
extern const char* const LOGE_UNKNOWN_ERROR = "UnknownError";
extern const char* const LOGE_NOT_IMPLEMENTED = "NotImplemented";
extern const char* const LOGE_SERVER_BUSY = "ServerBusy";
extern const char* const LOGE_INTERNAL_SERVER_ERROR = "InternalServerError";
extern const char* const LOGE_RESPONSE_SIG_ERROR = "ResponseSignatureError";
extern const char* const LOGE_PARAMETER_INVALID = "ParameterInvalid";
extern const char* const LOGE_MISSING_PARAMETER = "MissingParameter";
extern const char* const LOGE_INVALID_METHOD = "InvalidMethod";
extern const char* const LOGE_BAD_RESPONSE = "BadResponse";
extern const char* const LOGE_UNAUTHORIZED = "Unauthorized";
extern const char* const LOGE_QUOTA_EXCEED = "ExceedQuota";
extern const char* const LOGE_REQUEST_TIMEOUT = "RequestTimeout";
extern const char* const LOGE_CLIENT_OPERATION_TIMEOUT = "ClientOpertaionTimeout";
extern const char* const LOGE_CLIENT_NETWORK_ERROR = "ClientNetworkError";
extern const char* const LOGE_USER_NOT_EXIST = "UserNotExist";
extern const char* const LOGE_CATEGORY_NOT_EXIST = "CategoryNotExist";
extern const char* const LOGE_TOPIC_NOT_EXIST = "TopicNotExist";
extern const char* const LOGE_POST_BODY_INVALID = "PostBodyInvalid";
extern const char* const LOGE_INVALID_CONTENTTYPE = "InvalidContentType";
extern const char* const LOGE_INVALID_CONTENLENGTH = "InvalidContentLength";
extern const char* const LOGE_INVALID_APIVERSION = "InvalidAPIVersion";
extern const char* const LOGE_PROJECT_NOT_EXIST = "ProjectNotExist";
extern const char* const LOGE_LOGSTORE_NOT_EXIST = "LogStoreNotExist";
extern const char* const LOGE_INVALID_ACCESSKEYID = "InvalidAccessKeyId";
extern const char* const LOGE_SIGNATURE_NOT_MATCH = "SignatureNotMatch";
extern const char* const LOGE_PROJECT_FORBIDDEN = "ProjectForbidden";
extern const char* const LOGE_WRITE_QUOTA_EXCEED = "WriteQuotaExceed";
extern const char* const LOGE_READ_QUOTA_EXCEED = "ReadQuotaExceed";
extern const char* const LOGE_REQUEST_TIME_EXPIRED = "RequestTimeExpired";
extern const char* const LOGE_INVALID_REQUEST_TIME = "InvalidRequestTime";
extern const char* const LOGE_POST_BODY_TOO_LARGE = "PostBodyTooLarge";
extern const char* const LOGE_INVALID_TIME_RANGE = "InvalidTimeRange";
extern const char* const LOGE_INVALID_REVERSE = "InvalidReverse";
extern const char* const LOGE_LOGSTORE_WITHOUT_SHARD = "LogStoreWithoutShard";
extern const char* const LOGE_SHARD_WRITE_QUOTA_EXCEED = "ShardWriteQuotaExceed";
extern const char* const LOGE_SHARD_READ_QUOTA_EXCEED = "ShardReadQuotaExceed";

extern const char* const STRUCTUREDLOG = "/structuredlog";

extern const char* const HTTP_GET = "GET";
extern const char* const HTTP_POST = "POST";
extern const char* const HTTP_PUT = "PUT";
extern const char* const HTTP_DELETE = "DELETE";

extern const char* const HOST = "Host";
extern const char* const DATE = "Date";
extern const char* const USER_AGENT = "User-Agent";
extern const char* const CLS_LOG_COMPRESSTYPE = "x-cls-compress-type";
extern const char* const CLS_LOG_REQUEST_ID = "x-cls-requestid";
extern const char* const CLS_HASHKEY = "x-cls-hashkey";

extern const char* const HTTP_ACCEPT = "accept";
extern const char* const DEFLATE = "deflate";
extern const char* const HMAC_SHA1 = "hmac-sha1";
extern const char* const CONTENT_TYPE = "Content-Type";
extern const char* const CONTENT_LENGTH = "Content-Length";
extern const char* const CONTENT_MD5 = "Content-MD5";
extern const char* const AUTHORIZATION = "Authorization";
extern const char* const SIGNATURE = "Signature";
extern const char* const ACCEPT_ENCODING = "Accept-Encoding";
extern const char* const ENCONDING_GZIP = "gzip";
extern const char* const TYPE_LOG_PROTOBUF = "application/x-protobuf";
extern const char* const TYPE_LOG_JSON = "application/json";
extern const char* const LOGITEM_TIME_STAMP_LABEL = "__time__";
extern const char* const LOGITEM_SOURCE_LABEL = "__source__";
extern const char* const LOG_API_VERSION = "0.6.0";
extern const char* const MD5_SHA1_SALT_KEYPROVIDER = "md5-sha1-salt";
extern const char* const LOG_TYPE = "type";
extern const char* const LOGE_NOT_SUPPORTED_ACCEPT_CONTENT_TYPE = "InvalidAcceptContentType";
extern const char* const LOGE_NOT_SUPPORTED_ACCEPT_ENCODING = "InvalidAcceptEncoding";
extern const char* const LOGE_SHARD_NOT_EXIST = "ShardNotExist";
extern const char* const LOGE_INVALID_CURSOR = "InvalidCursor";
extern const char* const LOG_LZ4 = "lz4";

extern const char* const LOG_ERROR_CODE = "errorcode";
extern const char* const LOG_ERROR_MESSAGE = "errormessage";

extern const char* const LOG_SHARD_STATUS_READWRITE = "readwrite";
extern const char* const LOG_SHARD_STATUS_READONLY = "readonly";
extern const char* const ERR_LIMIT_LOG_SIZE = "logsizelimit";

static std::string HexToString(const uint8_t md5[16])
{
    static const char* table = "0123456789ABCDEF";
    std::string ss(32, 'a');
    for (int i = 0; i < 16; ++i)
    {
        ss[i * 2] = table[md5[i] >> 4];
        ss[i * 2 + 1] = table[md5[i] & 0x0F];
    }
    return ss;
}

std::string CodecTool::GetDateString(const std::string& dateFormat)
{
    time_t now_time;
    time(&now_time);
    char buffer[128] = {'\0'};
    tm timeInfo;
    gmtime_r(&now_time, &timeInfo);
    strftime(buffer, 128, dateFormat.c_str(), &timeInfo);
    return string(buffer);
}
std::string CodecTool::GetDateString()
{
    return GetDateString(DATE_FORMAT_RFC822);
}
time_t CodecTool::DecodeDateString(const std::string dateString, const std::string& dateFormat)
{
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_sec = -1;
    strptime(dateString.c_str(), dateFormat.c_str(), &t);
    if (t.tm_sec == -1)
    {
        throw LOGException(LOGE_PARAMETER_INVALID,
                           string("Invalid date string:") + dateString + ",format:" + dateFormat);
    }
    struct timezone tz;
    struct timeval tv;
    gettimeofday(&tv, &tz);
    return mktime(&t) - tz.tz_minuteswest * 60;
}

bool CodecTool::StartWith(const std::string& input, const std::string& pattern)
{
    if (input.length() < pattern.length())
    {
        return false;
    }

    size_t i = 0;
    while (i < pattern.length() && input[i] == pattern[i])
    {
        i++;
    }

    return i == pattern.length();
}
string CodecTool::UrlEncode(const string& url)
{
    char* szEncoded;
    szEncoded = curl_escape(url.c_str(), url.size());
    string tmpStr = szEncoded;
    curl_free(szEncoded);
    return tmpStr;
}

void LOGAdapter::GetQueryString(const map<string, string>& parameterList, string& queryString)
{
    queryString.clear();
    for (map<string, string>::const_iterator iter = parameterList.begin(); iter != parameterList.end(); ++iter)
    {
        if (iter != parameterList.begin())
        {
            queryString.append("&");
        }
        queryString.append(iter->first);
        queryString.append("=");
        queryString.append(CodecTool::UrlEncode(iter->second));
    }
}
static size_t data_write_callback(char* buffer, size_t size, size_t nmemb, string* write_buf)
{
    unsigned long sizes = size * nmemb;

    if (buffer == NULL)
    {
        return 0;
    }
    write_buf->append(buffer, sizes);
    return sizes;
}

static size_t header_write_callback(char* buffer, size_t size, size_t nmemb, map<string, string>* write_buf)
{
    unsigned long sizes = size * nmemb;

    if (buffer == NULL)
    {
        return 0;
    }
    unsigned long colonIndex;
    for (colonIndex = 1; colonIndex < sizes - 2; colonIndex++)
    {
        if (buffer[colonIndex] == ':')
            break;
    }
    if (colonIndex < sizes - 2)
    {
        unsigned long leftSpaceNum, rightSpaceNum;
        for (leftSpaceNum = 0; leftSpaceNum < colonIndex - 1; leftSpaceNum++)
        {
            if (buffer[colonIndex - leftSpaceNum - 1] != ' ')
                break;
        }
        for (rightSpaceNum = 0; rightSpaceNum < sizes - colonIndex - 1 - 2; rightSpaceNum++)
        {
            if (buffer[colonIndex + rightSpaceNum + 1] != ' ')
                break;
        }
        (*write_buf)[string(buffer, 0, colonIndex - leftSpaceNum)]
                = string(buffer, colonIndex + 1 + rightSpaceNum, sizes - colonIndex - 1 - 2 - rightSpaceNum);
    }
    return sizes;
}
void LOGAdapter::Send(const string& httpMethod, const string& host, const int32_t port, const string& url,
                      const string& queryString, const map<string, string>& header, const string& body,
                      const int64_t timeout, const int64_t connecttimeout, HttpMessage& httpMessage,
                      const curl_off_t maxspeed)
{
    CURLcode res;
    std::string response;
    int64_t statusCode;
    map<std::string, std::string> responseHeader;
    struct curl_slist* headers = NULL;
    for (map<std::string, std::string>::const_iterator iter = header.begin(); iter != header.end(); iter++)
    {
        headers = curl_slist_append(headers, (iter->first + ":" + iter->second).c_str());
    }
    string queryUrl = host + url;
    if (queryString.empty() == false)
        queryUrl += "?" + queryString;

    CURL* curl = curl_easy_init();

    if (curl)
    {
        if (headers)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        /* keep-alive idle time to 120 seconds */
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
        /* interval time between keep-alive probes: 60 seconds */
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
        curl_easy_setopt(curl, CURLOPT_URL, queryUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &responseHeader);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_write_callback);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, connecttimeout);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, maxspeed);
        if (httpMethod == HTTP_POST)
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, body.size());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        }
        else if (httpMethod == HTTP_DELETE)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, HTTP_DELETE);
        }
        else if (httpMethod == HTTP_PUT)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, HTTP_PUT);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, body.size());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        }

        res = curl_easy_perform(curl);
#define CURL_CLEAN_UP                 \
    curl_easy_cleanup(curl);          \
    if (headers)                      \
    {                                 \
        curl_slist_free_all(headers); \
    }

        switch (res)
        {
            case CURLE_OK:
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
                CURL_CLEAN_UP
                break;
            case CURLE_OPERATION_TIMEDOUT:
                CURL_CLEAN_UP
                statusCode = CURLE_OPERATION_TIMEDOUT;
                response = "Request operation timeout.";
                break;
            case CURLE_COULDNT_CONNECT:
                CURL_CLEAN_UP
                statusCode = CURLE_COULDNT_CONNECT;
                response = "Can not connect to server.";
                break;
            default:
                CURL_CLEAN_UP
                statusCode = res;
                response = "Request operation failed.";
                break;
        }
    }
    else
    {
         LOGException(LOGE_UNKNOWN_ERROR, "Initailizing request failed.");
    }
    httpMessage = HttpMessage(statusCode, responseHeader, response);
}
} // namespace tencent_log_sdk_cpp_v2
