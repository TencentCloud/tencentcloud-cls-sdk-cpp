#ifndef __LOGV6_LOGMEMMGR_H__
#define __LOGV6_LOGMEMMGR_H__
#include <string>
#include <atomic>

namespace tencent_log_sdk_cpp_v2
{
class LogMemMgr
{
public:
    LogMemMgr() : memtotalsize_(0){};
    ~LogMemMgr() = default;
    int64_t AddLogMemSize(const int64_t size);
    int64_t Subtraction(const int64_t size);
    int64_t GetMemTotalSize();

private:
    std::atomic<std::uint64_t> memtotalsize_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif
