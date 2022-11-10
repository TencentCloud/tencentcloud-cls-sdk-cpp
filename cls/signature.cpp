#include "signature.h"
#include <iostream>

namespace tencent_log_sdk_cpp_v2{
std::string sha1(const void *data, size_t len) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, data, len);
    SHA1_Final(digest, &ctx);
    char c_sha1[SHA_DIGEST_LENGTH*2+1];
    for (unsigned i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(&c_sha1[i*2], "%02x", (unsigned int)digest[i]);
    }
    return c_sha1;
}

std::string hmac_sha1(const char *key, const void *data, size_t len) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned digest_len;
    char c_hmacsha1[EVP_MAX_MD_SIZE*2+1];
#if !defined(OPENSSL_VERSION_NUMBER) || OPENSSL_VERSION_NUMBER < 0x10100000L
    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);
    HMAC_Init_ex(&ctx, key, strlen(key), EVP_sha1(), NULL);
    HMAC_Update(&ctx, (unsigned char*)data, len);
    HMAC_Final(&ctx, digest, &digest_len);
    HMAC_CTX_cleanup(&ctx);
#else
    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_CTX_reset(ctx);
    HMAC_Init_ex(ctx, key, strlen(key), EVP_sha1(), NULL);
    HMAC_Update(ctx, (unsigned char *)data, len);
    HMAC_Final(ctx, digest, &digest_len);
    HMAC_CTX_free(ctx);
#endif
    for (unsigned i = 0; i != digest_len; ++i) {
        sprintf(&c_hmacsha1[i*2], "%02x", (unsigned int)digest[i]);
    }
    return c_hmacsha1;
}

std::string urlencode(const char *s) {
    static unsigned char hexchars[] = "0123456789ABCDEF";
    size_t length = strlen(s), pos = 0;
    unsigned char c_url[length*3+1];
    const unsigned char *p = (const unsigned char *)s;
    for (; *p; ++p) {
        if (isalnum((unsigned char)*p) || (*p == '-') ||
            (*p == '_') || (*p == '.') || (*p == '~')) {
            c_url[pos++] = *p;
        } else {
            c_url[pos++] = '%';
            c_url[pos++] = hexchars[(*p)>>4];
            c_url[pos++] = hexchars[(*p)&15U];
        }
    }
    c_url[pos] = 0;
    return (char*)c_url;
}

std::string signature(const std::string &secret_id,
    const std::string &secret_key,
    std::string method,
    const std::string &path,
    const std::map<std::string, std::string> &params,
    const std::map<std::string, std::string> &headers,
    long expire) {

    const size_t SIGNLEN = 1024;
    std::string http_request_info, uri_parm_list,
        header_list, str_to_sign, sign_key;
    transform(method.begin(), method.end(), method.begin(), ::tolower);
    http_request_info.reserve(SIGNLEN);
    http_request_info.append(method).append("\n").append(path).append("\n");
    uri_parm_list.reserve(SIGNLEN);
    std::map<std::string, std::string>::const_iterator iter;
    for (iter = params.begin();
        iter != params.end(); ) {
        uri_parm_list.append(iter->first);
        http_request_info.append(iter->first).append("=")
            .append(urlencode(iter->second.c_str()));
        if (++iter != params.end()) {
            uri_parm_list.append(";");
            http_request_info.append("&");
        }
    }
    http_request_info.append("\n");
    header_list.reserve(SIGNLEN);
    for (iter = headers.begin();
        iter != headers.end(); ++iter) {
        sign_key = iter->first;
        transform(sign_key.begin(), sign_key.end(), sign_key.begin(), ::tolower);
        if (sign_key == "content-type" || sign_key == "content-md5"
              || sign_key == "host" || sign_key[0] == 'x') {
            header_list.append(sign_key);
            http_request_info.append(sign_key).append("=")
                .append(urlencode(iter->second.c_str()));
            header_list.append(";");
            http_request_info.append("&");
        }
    }
    if (!header_list.empty()) {
        header_list[header_list.size() - 1] = 0;
        http_request_info[http_request_info.size() - 1] = '\n';
    }
    //printf("%s\nEOF\n", http_request_info.c_str());
    char signed_time[SIGNLEN];
    memset(signed_time,0,SIGNLEN);
    int64_t nowTime = time(0);
    int signed_time_len = snprintf(signed_time, SIGNLEN,
        "%lu;%lu", nowTime - 60, nowTime + expire);
    std::cout<<"signed_time:"<<signed_time<<"|nowTime:"<<nowTime<<std::endl;
    //snprintf(signed_time, SIGNLEN, "1510109254;1510109314");
    std::string signkey = hmac_sha1(secret_key.c_str(),
        signed_time, signed_time_len);
    str_to_sign.reserve(SIGNLEN);
    str_to_sign.append("sha1").append("\n")
        .append(signed_time).append("\n")
        .append(sha1(http_request_info.c_str(), http_request_info.size()))
        .append("\n");
    //printf("%s\nEOF\n", str_to_sign.c_str());
    char c_signature[SIGNLEN];
    snprintf(c_signature, SIGNLEN,
        "q-sign-algorithm=sha1&q-ak=%s"
        "&q-sign-time=%s&q-key-time=%s"
        "&q-header-list=%s&q-url-param-list=%s&q-signature=%s",
        secret_id.c_str(), signed_time, signed_time,
        header_list.c_str(), uri_parm_list.c_str(),
        hmac_sha1(signkey.c_str(), str_to_sign.c_str(),
            str_to_sign.size()).c_str());
    return c_signature;
}
}
