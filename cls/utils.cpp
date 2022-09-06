#include "cls_logs.pb.h"
#include <string>
#include <chrono>
#include <ctime>
#include <sys/time.h>
#include "utils.h"
using namespace std::chrono;
using namespace std;

namespace tencent_log_sdk_cpp_v2
{
ErrCode GetLogContentSize(const cls::Log& log,int64_t& sizeInBytes)
{
    sizeInBytes += 4;
    for (int i = 0; i < log.contents_size(); ++i)
    {
        auto content = log.contents(i);
        if (content.value().size() > 1 * 1024 * 1024)
        {
            return ErrCode(ERR_CLS_SDK_CONTENT_LIMIT, "content value can not be than 1M");
        }
        sizeInBytes += content.key().size();
        sizeInBytes += content.value().size();
    }

    if(sizeInBytes > 5242880){
        return ErrCode(ERR_CLS_SDK_PACKAGE_LIMIT, "log size can not be than 5M");
    }
    return ErrCode{};
}

int64_t GetNowTimeMs()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
}

template<class T>
inline std::string SignedToString(const T& n)
{
    long long ll = static_cast<long long>(n);
    char buf[64];
    snprintf(buf, sizeof(buf), "%lld", ll);
    return std::string(buf);
}
std::string ToString(const int32_t& n)
{
    return SignedToString(n);
}

template<class T>
inline std::string UnsignedToString(const T& n)
{
    unsigned long long llu = static_cast<unsigned long long>(n);
    char buf[64];
    snprintf(buf, sizeof(buf), "%llu", llu);
    return std::string(buf);
}


std::string ToString(const uint32_t& n)
{
    return UnsignedToString(n);
}

std::string ToString(const size_t& n)
{
    return UnsignedToString(n);
}
std::string ToString(const int64_t& n)
{
    return SignedToString(n);
}
std::string ToString(const bool& n)
{
    if (n)
        return "true";
    else
        return "false";
}

void GetSelfServerIP(char* pszIP)
{
    struct addrinfo *answer, hint, *curr;
    //char szIP[16];
    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    int iRet = 0;
    char szHostName[128] = {0};
    iRet = gethostname(szHostName, sizeof(szHostName));
    if (iRet != 0)
    {
        fprintf(stderr, "gethostname error! [%s]\n", strerror(errno));
        exit(1);
    }
    printf("hostname [%s]\n", szHostName);

    iRet = getaddrinfo(szHostName, NULL, &hint, &answer);
    if (iRet != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(iRet));
        exit(1);
    }

    for (curr = answer; curr != NULL; curr = curr->ai_next)
    {
        inet_ntop(AF_INET, &(((struct sockaddr_in*)(curr->ai_addr))->sin_addr), pszIP, 16);
        //printf("%s\n", pszIP);
    }

    freeaddrinfo(answer);
}
} // namespace tencent_log_sdk_cpp_v2