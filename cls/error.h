#ifndef __LOGV6_ERROR_H__
#define __LOGV6_ERROR_H__
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <unordered_set>
namespace tencent_log_sdk_cpp_v2
{

const int64_t ERR_CLS_SDK_CONTENT_LIMIT = 0x00000001;
const int64_t ERR_CLS_SDK_TOTALSIZELNBYTES_LIMIT = 0x00000002;
const int64_t ERR_CLS_SDK_TASK_SHUTDOWN = 0x00000003;
const int64_t ERR_CLS_SDK_PARAM_ERROR = 0x00000004;
const int64_t ERR_CLS_SDK_PACKAGE_LIMIT = 0x00000005;

#define    CLS_CURLE_UNSUPPORTED_PROTOCOL       1
#define    CLS_CURLE_FAILED_INIT                2
#define    CLS_CURLE_URL_MALFORMAT              3
#define    CLS_CURLE_NOT_BUILT_IN               4 /*[was obsoleted in August 2007 for
                                    7.17.0  reused in April 2011 for 7.21.5]*/
#define    CLS_CURLE_COULDNT_RESOLVE_PROXY      5
#define    CLS_CURLE_COULDNT_RESOLVE_HOST       6
#define    CLS_CURLE_COULDNT_CONNECT            7
#define    CLS_CURLE_WEIRD_SERVER_REPLY         8
#define    CLS_CURLE_REMOTE_ACCESS_DENIED       9 /*a service was denied by the server
                                     due to lack of access /* when login fails
                                     this is not returned.  */
#define    CLS_CURLE_FTP_ACCEPT_FAILED          10 /*[was obsoleted in April 2006 for
                                     7.15.4  reused in Dec 2011 for 7.24.0]*/
#define    CLS_CURLE_FTP_WEIRD_PASS_REPLY       11
#define    CLS_CURLE_FTP_ACCEPT_TIMEOUT         12 /*timeout occurred accepting server
                                     [was obsoleted in August 2007 for 7.17.0
                                     reused in Dec 2011 for 7.24.0]*/
#define    CLS_CURLE_FTP_WEIRD_PASV_REPLY       13
#define    CLS_CURLE_FTP_WEIRD_227_FORMAT       14
#define    CLS_CURLE_FTP_CANT_GET_HOST          15
#define    CLS_CURLE_HTTP2                      16 /*A problem in the http2 framing layer.
                                     [was obsoleted in August 2007 for 7.17.0
                                     reused in July 2014 for 7.38.0]*/
#define    CLS_CURLE_FTP_COULDNT_SET_TYPE       17
#define    CLS_CURLE_PARTIAL_FILE               18
#define    CLS_CURLE_FTP_COULDNT_RETR_FILE      19
#define    CLS_CURLE_OBSOLETE20                 20 /* NOT USED*/
#define    CLS_CURLE_QUOTE_ERROR                21 /* quote command failure */
#define    CLS_CURLE_HTTP_RETURNED_ERROR        22
#define    CLS_CURLE_WRITE_ERROR                23
#define    CLS_CURLE_OBSOLETE24                 24 /* NOT USED  */
#define    CLS_CURLE_UPLOAD_FAILED              25 /* failed upload "command"  */
#define    CLS_CURLE_READ_ERROR                 26 /* couldn't open/read from file  */
#define    CLS_CURLE_OUT_OF_MEMORY              27
#define    CLS_CURLE_OPERATION_TIMEDOUT         28 /* the timeout time was reached */
#define    CLS_CURLE_OBSOLETE29                 29 /* NOT USED  */
#define    CLS_CURLE_FTP_PORT_FAILED            30 /* FTP PORT operation failed  */
#define    CLS_CURLE_FTP_COULDNT_USE_REST       31 /* the REST command failed  */
#define    CLS_CURLE_OBSOLETE32                 32 /* NOT USED  */
#define    CLS_CURLE_RANGE_ERROR                33 /* RANGE "command" didn't work  */
#define    CLS_CURLE_HTTP_POST_ERROR            34
#define    CLS_CURLE_SSL_CONNECT_ERROR          35 /* wrong when connecting with SSL */
#define    CLS_CURLE_BAD_DOWNLOAD_RESUME        36 /* couldn't resume download  */
#define    CLS_CURLE_FILE_COULDNT_READ_FILE     37
#define    CLS_CURLE_LDAP_CANNOT_BIND           38
#define    CLS_CURLE_LDAP_SEARCH_FAILED         39
#define    CLS_CURLE_OBSOLETE40                 40 /* NOT USED  */
#define    CLS_CURLE_FUNCTION_NOT_FOUND         41 /* NOT USED starting with 7.53.0  */
#define    CLS_CURLE_ABORTED_BY_CALLBACK        42
#define    CLS_CURLE_BAD_FUNCTION_ARGUMENT      43
#define    CLS_CURLE_OBSOLETE44                 44 /* NOT USED  */
#define    CLS_CURLE_INTERFACE_FAILED           45 /* CURLOPT_INTERFACE failed  */
#define    CLS_CURLE_OBSOLETE46                 46 /* NOT USED  */
#define    CLS_CURLE_TOO_MANY_REDIRECTS         47 /* catch endless re/*direct loops  */
#define    CLS_CURLE_UNKNOWN_OPTION             48 /* User specified an unknown option  */
#define    CLS_CURLE_SETOPT_OPTION_SYNTAX       49 /* Malformed setopt option  */
#define    CLS_CURLE_OBSOLETE50                 50 /* NOT USED  */
#define    CLS_CURLE_OBSOLETE51                 51 /* NOT USED  */
#define    CLS_CURLE_GOT_NOTHING                52 /* when this is a specific error  */
#define    CLS_CURLE_SSL_ENGINE_NOTFOUND        53 /* SSL crypto engine not found  */
#define    CLS_CURLE_SSL_ENGINE_SETFAILED       54 /* can not set SSL crypto engine as*/
#define    CLS_CURLE_SEND_ERROR                 55 /* failed sending network data  */
#define    CLS_CURLE_RECV_ERROR                 56 /* failure in receiving network data */
#define    CLS_CURLE_OBSOLETE57                 57 /* NOT IN USE  */
#define    CLS_CURLE_SSL_CERTPROBLEM            58 /* problem with the local certificate */
#define    CLS_CURLE_SSL_CIPHER                 59 /* couldn't use specified cipher  */
#define    CLS_CURLE_PEER_FAILED_VERIFICATION    60 /* peer's certificate or fingerprint
                                      wasn't verified fine  */
#define    CLS_CURLE_BAD_CONTENT_ENCODING       61 /* Unrecognized/bad encoding  */
#define    CLS_CURLE_OBSOLETE62                 62 /* NOT IN USE since 7.82.0  */
#define    CLS_CURLE_FILESIZE_EXCEEDED          63 /* Maximum file size exceeded  */
#define    CLS_CURLE_USE_SSL_FAILED             64 /* Requested FTP SSL level failed */
#define    CLS_CURLE_SEND_FAIL_REWIND           65 /* Sending the data requires a rewind
                                     that failed  */
#define    CLS_CURLE_SSL_ENGINE_INITFAILED      66 /* failed to initialise ENGINE  */
#define    CLS_CURLE_LOGIN_DENIED               67 /* user  password or similar was not
                                     accepted and we failed to login  */
#define    CLS_CURLE_TFTP_NOTFOUND              68 /* file not found on server  */
#define    CLS_CURLE_TFTP_PERM                  69 /* permission problem on server  */
#define    CLS_CURLE_REMOTE_DISK_FULL           70 /* out of disk space on server  */
#define    CLS_CURLE_TFTP_ILLEGAL               71 /* Illegal TFTP operation  */
#define    CLS_CURLE_TFTP_UNKNOWNID             72 /* Unknown transfer ID  */
#define    CLS_CURLE_REMOTE_FILE_EXISTS         73 /* File already exists  */
#define    CLS_CURLE_TFTP_NOSUCHUSER            74 /* No such user  */
#define    CLS_CURLE_CONV_FAILED                75 /* conversion failed  */
#define    CLS_CURLE_OBSOLETE76                 76 /* NOT IN USE since 7.82.0  */
#define    CLS_CURLE_SSL_CACERT_BADFILE         77 /* could not load CACERT file  missing
                                     or wrong format  */
#define    CLS_CURLE_REMOTE_FILE_NOT_FOUND      78 /* remote file not found  */
#define    CLS_CURLE_SSH                        79 /* error from the SSH layer  somewhat
                                     generic so the error message will be of
                                     interest when this has happened  */

#define    CLS_CURLE_SSL_SHUTDOWN_FAILED        80 /* Failed to shut down the SSL
                                     connection  */
#define    CLS_CURLE_AGAIN                      81 /* socket is not ready for send/recv
                                     wait till it's ready and try again (Added
                                     in 7.18.2)  */
#define    CLS_CURLE_SSL_CRL_BADFILE            82 /* could not load CRL file  missing or
                                     wrong format (Added in 7.19.0)  */
#define    CLS_CURLE_SSL_ISSUER_ERROR           83 /* Issuer check failed.  (Added in
                                     7.19.0)  */
#define    CLS_CURLE_FTP_PRET_FAILED            84 /* a PRET command failed  */
#define    CLS_CURLE_RTSP_CSEQ_ERROR            85 /* mismatch of RTSP CSeq numbers */
#define    CLS_CURLE_RTSP_SESSION_ERROR         86 /* mismatch of RTSP Session Ids */
#define    CLS_CURLE_FTP_BAD_FILE_LIST          87 /* unable to parse FTP file list  */
#define    CLS_CURLE_CHUNK_FAILED               88 /* chunk callback reported error  */
#define    CLS_CURLE_NO_CONNECTION_AVAILABLE    89 /* No connection available  the
                                     session will be queued  */
#define    CLS_CURLE_SSL_PINNEDPUBKEYNOTMATCH    90 /* specified pinned public key did not
                                      match  */
#define    CLS_CURLE_SSL_INVALIDCERTSTATUS      91 /* invalid certificate status  */
#define    CLS_CURLE_HTTP2_STREAM               92 /* stream error in HTTP/2 framing layer*/
#define    CLS_CURLE_RECURSIVE_API_CALL         93 /* an api function was called from
                                     inside a callback  */
#define    CLS_CURLE_AUTH_ERROR                 94 /* an authentication function returned an
                                     error  */
#define    CLS_CURLE_HTTP3                      95 /* An HTTP/3 layer problem  */
#define    CLS_CURLE_QUIC_CONNECT_ERROR         96 /* QUIC connection error  */
#define    CLS_CURLE_PROXY                      97 /* proxy handshake error  */
#define    CLS_CURLE_SSL_CLIENTCERT             98 /* client/*side certificate required  */

static std::unordered_set <int> curl_errcode{
   CLS_CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
   CLS_CURLE_FAILED_INIT,             /* 2 */
   CLS_CURLE_URL_MALFORMAT,           /* 3 */
   CLS_CURLE_NOT_BUILT_IN,            /* 4 - [was obsoleted in August 2007 for
                                    7.17.0, reused in April 2011 for 7.21.5] */
   CLS_CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
   CLS_CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
   CLS_CURLE_COULDNT_CONNECT,         /* 7 */
   CLS_CURLE_WEIRD_SERVER_REPLY,      /* 8 */
   CLS_CURLE_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
                                    due to lack of access - when login fails
                                    this is not returned. */
   CLS_CURLE_FTP_ACCEPT_FAILED,       /* 10 - [was obsoleted in April 2006 for
                                    7.15.4, reused in Dec 2011 for 7.24.0]*/
   CLS_CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
   CLS_CURLE_FTP_ACCEPT_TIMEOUT,      /* 12 - timeout occurred accepting server
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in Dec 2011 for 7.24.0]*/
   CLS_CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
   CLS_CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
   CLS_CURLE_FTP_CANT_GET_HOST,       /* 15 */
   CLS_CURLE_HTTP2,                   /* 16 - A problem in the http2 framing layer.
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in July 2014 for 7.38.0] */
   CLS_CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
   CLS_CURLE_PARTIAL_FILE,            /* 18 */
   CLS_CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
   CLS_CURLE_OBSOLETE20,              /* 20 - NOT USED */
   CLS_CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
   CLS_CURLE_HTTP_RETURNED_ERROR,     /* 22 */
   CLS_CURLE_WRITE_ERROR,             /* 23 */
   CLS_CURLE_OBSOLETE24,              /* 24 - NOT USED */
   CLS_CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
   CLS_CURLE_READ_ERROR,              /* 26 - couldn't open/read from file */
   CLS_CURLE_OUT_OF_MEMORY,           /* 27 */
   CLS_CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
   CLS_CURLE_OBSOLETE29,              /* 29 - NOT USED */
   CLS_CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
   CLS_CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
   CLS_CURLE_OBSOLETE32,              /* 32 - NOT USED */
   CLS_CURLE_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
   CLS_CURLE_HTTP_POST_ERROR,         /* 34 */
   CLS_CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
   CLS_CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
   CLS_CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
   CLS_CURLE_LDAP_CANNOT_BIND,        /* 38 */
   CLS_CURLE_LDAP_SEARCH_FAILED,      /* 39 */
   CLS_CURLE_OBSOLETE40,              /* 40 - NOT USED */
   CLS_CURLE_FUNCTION_NOT_FOUND,      /* 41 - NOT USED starting with 7.53.0 */
   CLS_CURLE_ABORTED_BY_CALLBACK,     /* 42 */
   CLS_CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
   CLS_CURLE_OBSOLETE44,              /* 44 - NOT USED */
   CLS_CURLE_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
   CLS_CURLE_OBSOLETE46,              /* 46 - NOT USED */
   CLS_CURLE_TOO_MANY_REDIRECTS,      /* 47 - catch endless re-direct loops */
   CLS_CURLE_UNKNOWN_OPTION,          /* 48 - User specified an unknown option */
   CLS_CURLE_SETOPT_OPTION_SYNTAX,    /* 49 - Malformed setopt option */
   CLS_CURLE_OBSOLETE50,              /* 50 - NOT USED */
   CLS_CURLE_OBSOLETE51,              /* 51 - NOT USED */
   CLS_CURLE_GOT_NOTHING,             /* 52 - when this is a specific error */
   CLS_CURLE_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
   CLS_CURLE_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as
                                    default */
   CLS_CURLE_SEND_ERROR,              /* 55 - failed sending network data */
   CLS_CURLE_RECV_ERROR,              /* 56 - failure in receiving network data */
   CLS_CURLE_OBSOLETE57,              /* 57 - NOT IN USE */
   CLS_CURLE_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
   CLS_CURLE_SSL_CIPHER,              /* 59 - couldn't use specified cipher */
   CLS_CURLE_PEER_FAILED_VERIFICATION, /* 60 - peer's certificate or fingerprint
                                     wasn't verified fine */
   CLS_CURLE_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized/bad encoding */
   CLS_CURLE_OBSOLETE62,              /* 62 - NOT IN USE since 7.82.0 */
   CLS_CURLE_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
   CLS_CURLE_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
   CLS_CURLE_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind
                                    that failed */
   CLS_CURLE_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
   CLS_CURLE_LOGIN_DENIED,            /* 67 - user, password or similar was not
                                    accepted and we failed to login */
   CLS_CURLE_TFTP_NOTFOUND,           /* 68 - file not found on server */
   CLS_CURLE_TFTP_PERM,               /* 69 - permission problem on server */
   CLS_CURLE_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
   CLS_CURLE_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
   CLS_CURLE_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
   CLS_CURLE_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
   CLS_CURLE_TFTP_NOSUCHUSER,         /* 74 - No such user */
   CLS_CURLE_CONV_FAILED,             /* 75 - conversion failed */
   CLS_CURLE_OBSOLETE76,              /* 76 - NOT IN USE since 7.82.0 */
   CLS_CURLE_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing
                                    or wrong format */
   CLS_CURLE_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
   CLS_CURLE_SSH,                     /* 79 - error from the SSH layer, somewhat
                                    generic so the error message will be of
                                    interest when this has happened */

   CLS_CURLE_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL
                                    connection */
   CLS_CURLE_AGAIN,                   /* 81 - socket is not ready for send/recv,
                                    wait till it's ready and try again (Added
                                    in 7.18.2) */
   CLS_CURLE_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or
                                    wrong format (Added in 7.19.0) */
   CLS_CURLE_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in
                                    7.19.0) */
   CLS_CURLE_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
   CLS_CURLE_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
   CLS_CURLE_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Ids */
   CLS_CURLE_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
   CLS_CURLE_CHUNK_FAILED,            /* 88 - chunk callback reported error */
   CLS_CURLE_NO_CONNECTION_AVAILABLE, /* 89 - No connection available, the
                                    session will be queued */
   CLS_CURLE_SSL_PINNEDPUBKEYNOTMATCH, /* 90 - specified pinned public key did not
                                     match */
   CLS_CURLE_SSL_INVALIDCERTSTATUS,   /* 91 - invalid certificate status */
   CLS_CURLE_HTTP2_STREAM,            /* 92 - stream error in HTTP/2 framing layer
                                    */
   CLS_CURLE_RECURSIVE_API_CALL,      /* 93 - an api function was called from
                                    inside a callback */
   CLS_CURLE_AUTH_ERROR,              /* 94 - an authentication function returned an
                                    error */
   CLS_CURLE_HTTP3,                   /* 95 - An HTTP/3 layer problem */
   CLS_CURLE_QUIC_CONNECT_ERROR,      /* 96 - QUIC connection error */
   CLS_CURLE_PROXY,                   /* 97 - proxy handshake error */
   CLS_CURLE_SSL_CLIENTCERT          /* 98 - client-side certificate required */
};

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
