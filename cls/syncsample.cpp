
#include "cls/client.h"
#include "cls/common.h"
#include "cls/cls_logs.pb.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>
using namespace tencent_log_sdk_cpp_v2;
using namespace std;
int main(int argc,char ** argv)
{
    //eg:内网域名：ap-guangzhou.cls.tencentyun.com
    //eg:外网域名：ap-guangzhou.cls.tencentcs.com
    string endpoint = "ap-guangzhou.cls.tencentcs.com";
    string accessKeyId = "";
    string accessKey = "";
    string topic = "";
    string token = "";
    std::shared_ptr<LOGClient> ptr= std::make_shared<LOGClient>(endpoint,accessKeyId,accessKey,LOG_REQUEST_TIMEOUT,LOG_CONNECT_TIMEOUT,token,"127.0.0.1",true);
    cls::LogGroup loggroup;
    auto log = loggroup.add_logs();
    log->set_time(time(NULL));
    auto content = log->add_contents();
    content->set_key("content");
    content->set_value("this my test log");
    loggroup.set_source("127.0.0.1");
    PostLogStoreLogsResponse ret;
    for(int i = 0; i < 10; ++i){
        ret = ptr -> PostLogStoreLogs(topic,loggroup);
        printf("%s\n",ret.Printf().c_str());
    }
    return 0;
}
