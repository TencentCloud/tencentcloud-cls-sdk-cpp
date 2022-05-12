#ifndef __LOGV6_ERROR_H__
#define __LOGV6_ERROR_H__
#include <string>
#include <sstream>
namespace tencent_log_sdk_cpp_v2
{

const int64_t ERR_CLS_SDK_CONTENT_LIMIT = 0x00000001;
const int64_t ERR_CLS_SDK_TOTALSIZELNBYTES_LIMIT = 0x00000002;
const int64_t ERR_CLS_SDK_TASK_SHUTDOWN = 0x00000003;
const int64_t ERR_CLS_SDK_PARAM_ERROR = 0x00000004;
const int64_t ERR_CLS_SDK_PACKAGE_LIMIT = 0x00000005;

typedef struct ErrCode
{
    int64_t retCode;
    std::string errMsg;
    ErrCode() : retCode(0), errMsg("") {}
    ErrCode(int64_t retcode, const std::string& errmsg) : retCode(retcode), errMsg(errmsg) {}

    std::string DebugStringErrCode()
    {
        std::stringstream ss;
        ss << "retCode: " << retCode << "|"
           << " errMsg: " << errMsg;
        return ss.str();
    }
} ErrCode;
} // namespace tencent_log_sdk_cpp_v2


#endif