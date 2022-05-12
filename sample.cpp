
#include "producerclient.h"
#include "common.h"
#include "cls_logs.pb.h"
#include "logproducerconfig.pb.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "result.h"
#include "error.h"
using namespace tencent_log_sdk_cpp_v2;
using namespace std;


class UserResult : public CallBack
{
public:
    UserResult() = default;
    ~UserResult() = default;
    void Success(PostLogStoreLogsResponse result) override { std::cout << result.Printf() << std::endl; }
    void Fail(PostLogStoreLogsResponse result) override 
    { 
        std::cout << result.Printf() << std::endl; 
        std::cout<<result.loggroup_.ShortDebugString().c_str()<<std::endl;
    }
};


int main()
{
    cls_config::LogProducerConfig config;
    config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
    config.set_acceskeyid("");
    config.set_accesskeysecret("");
    std::string topic = "";
    auto client = std::make_shared<ProducerClient>(config);
    auto callback = std::make_shared<UserResult>();
    client->Start();
    cls::Log log;
    log.set_time(time(NULL));
    
    auto content = log.add_contents();
    content->set_key("content");
    content->set_value("this my test");
    PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
    if(ret.statusCode != 0){
        cout<<ret.content<<endl;
    }
    client->LogProducerEnvDestroy();

    return 0;
}
