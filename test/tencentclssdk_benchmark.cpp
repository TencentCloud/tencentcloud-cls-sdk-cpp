#include <string>
#include <iostream>
#include <unistd.h>

#include "producerclient.h"
#include "common.h"
#include "cls_logs.pb.h"
#include "logproducerconfig.pb.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "result.h"
#include "error.h"
#include <array>
#include <chrono>
// using namespace chrono;
using namespace std::chrono;
using namespace tencent_log_sdk_cpp_v2;
using namespace std;


/*
缓存：100MB
聚合时间：2秒 
聚合数据包大小：5MB
发送线程：50
*/

class UserResult : public CallBack
{
public:
    UserResult() = default;
    ~UserResult() = default;
    void Success(PostLogStoreLogsResponse result) override { std::cout << result.Printf() << std::endl; }
    void Fail(PostLogStoreLogsResponse result) override { std::cout << result.Printf() << std::endl; }
};
double total;
void thread_task(int send_count,std::shared_ptr<ProducerClient> client)
{
    cls::Log log;
    for(int i = 0; i < send_count; ++i){
        auto start = system_clock::now();
        log.set_time(time(NULL));
        auto content = log.add_contents();
        content->set_key("content");
        content->set_value("this my test log");
        std::string topic = "";
        auto callback = std::make_shared<UserResult>();
        //成功返回0，代表数据入队成功，最终是否发送
        PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
        if (ret.statusCode != 0)
        {
            std::cout << ret.content << std::endl;
        }
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        total += double(duration.count()) * microseconds::period::num / microseconds::period::den;
        cout << "耗时统计:"<< double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒"
                << endl;
    }

}
int main(int argc,char **argv)
{
    cout << "开始执行性能测试" << endl;
    cls_config::LogProducerConfig config;
    config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
    config.set_acceskeyid("");
    config.set_accesskeysecret("");
    auto client = std::make_shared<ProducerClient>(config);
    client->Start();
    int send_count = 20000;
    int thread_count = 50;
    if(argc == 3){
        thread_count = atoi(argv[1]);
        send_count = atoi(argv[2]);
    }
    std::thread threads[thread_count];
    for(int i = 0; i < thread_count; ++i){
        threads[i] = std::thread(thread_task,send_count,client);
    }
    for(auto& t : threads){
        t.join();
    }
    cout<<"平均耗时统计："<<total/send_count<<endl;
    client->LogProducerEnvDestroy();
    return 0;
}

        
