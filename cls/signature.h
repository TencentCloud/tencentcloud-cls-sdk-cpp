#include <string>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/ossl_typ.h>

namespace tencent_log_sdk_cpp_v2{
std::string sha1(const void *data, size_t len);

std::string hmac_sha1(const char *key, const void *data, size_t len);

std::string urlencode(const char *s);

std::string signature(const std::string &secret_id,
    const std::string &secret_key,
    std::string method,
    const std::string &path,
    const std::map<std::string, std::string> &params,
    const std::map<std::string, std::string> &headers,
    long expire);
}
