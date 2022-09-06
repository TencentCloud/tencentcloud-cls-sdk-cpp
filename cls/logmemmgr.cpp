
#include "logmemmgr.h"

namespace tencent_log_sdk_cpp_v2
{

int64_t LogMemMgr::AddLogMemSize(const int64_t size)
{
    memtotalsize_ += size;
    return memtotalsize_;
}
int64_t LogMemMgr::Subtraction(const int64_t size)
{
    memtotalsize_ -= size;
    return memtotalsize_;
}
int64_t LogMemMgr::GetMemTotalSize()
{
    return memtotalsize_;
}
} // namespace tencent_log_sdk_cpp_v2
