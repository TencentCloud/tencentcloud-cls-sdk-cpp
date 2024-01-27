#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
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
using namespace tencent_log_sdk_cpp_v2;
using namespace std;


class UserResult : public CallBack
{
public:
    UserResult() = default;
    ~UserResult() = default;
    void Success(PostLogStoreLogsResponse result) override { std::cout << result.Printf() << std::endl; }
    void Fail(PostLogStoreLogsResponse result) override { std::cout << result.Printf() << std::endl; }
};
// /*
// 测试：按照负载均衡模式上传日志
// 预期结果：ret.statusCode返回200ok
// */
// // TEST(tencent_log_sdk_test, load_balancing)
// // {
// //     std::cout << "ProducerClient开始启动" << endl;
// //     cls_config::LogProducerConfig config;
// //     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
// //     config.set_acceskeyid("");
// //     config.set_accesskeysecret("");
// //     // config.set_lingerms(0);
// //     auto client = std::make_shared<ProducerClient>(config);
// //     client->Start();
// //     cls::Log log;
// //     log.set_time(time(NULL));
// //     auto content = log.add_contents();
// //     content->set_key("content");
// //     content->set_value("this my test log");
// //     std::string topic = "";
// //     // std::string topic = "123";
// //     auto callback = std::make_shared<UserResult>();
// //     for (int i = 0; i < 2; ++i)
// //     {
// //         PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
// //         std::cout << ret.Printf() << std::endl;
// //     }
// //     client->LogProducerEnvDestroy();
// // }


// /*
// 测试：配置合法性校验，若内存小于等于0
// 预期结果：则使用默认值totalsizelnbytes=104857600
// */
// TEST(tencent_log_sdk_test, config_totalsizelnbytes)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_totalsizelnbytes(0);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.totalsizelnbytes(), 104857600);
// }

// /*
// 测试：配置合法性校验，并发数小于0
// 预期结果：则使用默认的并发配置maxsendworkercount=50
// */
// TEST(tencent_log_sdk_test, config_maxsendworkercount)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_maxsendworkercount(0);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.maxsendworkercount(), 50);
// }

// /*
// 测试：配置合法性校验，累计的batchsize小于等于0
// 预期结果：则使用默认值maxbatchsize=5M
// */
// TEST(tencent_log_sdk_test, config_maxbatchsize_0)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_maxbatchsize(0);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.maxbatchsize(), 5242880);
// }

// /*
// 测试：配置合法性校验，累计的batchsize大小超过5M
// 预期结果：则使用默认值totalsizelnbytes=104857600
// */
// TEST(tencent_log_sdk_test, config_maxbatchsize_max)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_maxbatchsize(5242881);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.maxbatchsize(), 5242880);
// }

// /*
// 测试：配置合法性校验，逗留时间小于100ms
// 预期结果：则使用默认值lingerms=2000
// */
// TEST(tencent_log_sdk_test, config_lingerms)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_lingerms(80);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.lingerms(), 2000);
// }

// /*
// 测试：配置合法性校验，首次重试的退避时间小于等于0
// 预期结果：则使用默认值baseretrybackoffms=100
// */
// TEST(tencent_log_sdk_test, config_baseretrybackoffms)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_baseretrybackoffms(0);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.baseretrybackoffms(), 100);
// }

// /*
// 测试：配置合法性校验，重试的最大退避时间小于等于0
// 预期结果：则使用默认值maxretrybackoffms=50ms
// */
// TEST(tencent_log_sdk_test, config_maxretrybackoffms)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_maxretrybackoffms(0);
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.maxretrybackoffms(), 50000);
// }

// /*
// 测试：未设置的配置
// 预期结果：采用默认值
// */
// TEST(tencent_log_sdk_test, config_default)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     auto client = std::make_shared<ProducerClient>(config);
//     EXPECT_EQ(config.totalsizelnbytes(), 104857600);
//     EXPECT_EQ(config.maxsendworkercount(), 50);
//     EXPECT_EQ(config.maxblocksec(), 60);
//     EXPECT_EQ(config.maxbatchsize(), 5242880);
//     EXPECT_EQ(config.lingerms(), 2000);
//     EXPECT_EQ(config.retries(), 10);
//     EXPECT_EQ(config.baseretrybackoffms(), 100);
//     EXPECT_EQ(config.maxretrybackoffms(), 50000);
//     EXPECT_EQ(config.compressflag(), 1);
//     EXPECT_EQ(config.baseretrybackoffms(), 100);
//     EXPECT_EQ(config.baseretrybackoffms(), 100);
// }

// /*
// 测试：TotalSizeLnBytes大小使用默认值100M上线，且使用默认值
// MaxBlockSec=0s.用户使用的
// memtotalsize_大于TotalSizeLnBytes
// 预期：返回错误码，并返回文案信息TotalSizeLnBytes limit 内存大小限制
// */
// TEST(tencent_log_sdk_test, limit_totalsizelnbyte_0)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_totalsizelnbytes(10); //设置内存的大小h是10K
//     config.set_maxblocksec(0); //该值设为0，当所需空间无法得到满足时，立即返回
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     client->PostLogStoreLogs(topic, log, callback);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     EXPECT_EQ(ret.statusCode, 2);
//     EXPECT_STREQ(ret.content.c_str(), "TotalSizeLnBytes limit");
//     sleep(3); //模拟3s处理网络延时的情况
//     client->LogProducerEnvDestroy();
// }

// /*
// 测试：TotalSizeLnBytes大小使用默认值100M上线，且使用默认值
// MaxBlockSec=60s.用户使用的
// memtotalsize_大于TotalSizeLnBytes
// 预期：等待60s之后返回错误码，并返回文案信息TotalSizeLnBytes limit 内存大小限制
// */
// TEST(tencent_log_sdk_test, limit_totalsizelnbyte_default)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_totalsizelnbytes(10); //设置内存的大小h是10K
//     config.set_maxblocksec(3); //该值设为0，当所需空间无法得到满足时，立即返回
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     client->PostLogStoreLogs(topic, log, callback);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     EXPECT_EQ(ret.statusCode, 2);
//     EXPECT_STREQ(ret.content.c_str(), "TotalSizeLnBytes limit");
//     sleep(5); //模拟10s处理网络延时的情况
//     client->LogProducerEnvDestroy();
// }

// /*
// 测试：TotalSizeLnBytes大小使用默认值100M上线，用户设置的MaxBlockSec = -1
// memtotalsize_大于TotalSizeLnBytes
// 预期：一直等待，直到内存释放（依赖逗留的时间点,当前模拟等待3s，然后继续发送数据）
// */
// TEST(tencent_log_sdk_test, limit_totalsizelnbyte_block)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid("");
//     config.set_accesskeysecret("");
//     config.set_totalsizelnbytes(10); //设置内存的大小h是10K
//     config.set_maxblocksec(-1); //该值设为0，当所需空间无法得到满足时，立即返回
//     config.set_lingerms(3000);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     client->PostLogStoreLogs(topic, log, callback);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     EXPECT_EQ(ret.statusCode, 0);
//     sleep(8); //模拟10s处理网络延时的情况
//     client->LogProducerEnvDestroy();
// }


/*
测试：程序shutdown
预期：无法添加数据,返回错误码ERR_CLS_SDK_TASK_SHUTDOWN
*/
// TEST(tencent_log_sdk_test, shutdown)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     config.set_maxbatchsize(300);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     client->PostLogStoreLogs(topic, log, callback);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);

//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 3);
// }

/*
测试场景：AddLogToProducerBatch函数如果topic可以找到，如果超过了maxbatchsize但是小于5M
预期结果：可正常发送数据。并且支持聚合
*/

// TEST(tencent_log_sdk_test, maxbatchsize_0)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     config.set_maxbatchsize(300);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     client->PostLogStoreLogs(topic, log, callback);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);

//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 0);
// }

/*
测试场景：AddLogToProducerBatch函数如果topic可以找到，如果未超过maxbatchsize
预期：只需添加数据到ma中，等待数据超过maxbatchsize则发送数据，或者达到逗留时间则发送数据
*/
// TEST(tencent_log_sdk_test, maxbatchsize_1)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     config.set_maxbatchsize(1024 * 1024); //这里设置成1M
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     for (int i = 0; i < 10; ++i)
//     {
//         auto content = log.add_contents();
//         content->set_key("content");
//         content->set_value("this my test log");
//     }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     sleep(3);
//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 0);
// }

/*
测试场景：AddLogToProducerBatch函数如果topic可以找到，如果超过5M(延长逗留的时间，不影响当前策略)
预期：先把之前的数据发送完成，再重新创建新的batchloggroup
*/
// TEST(tencent_log_sdk_test, maxbatchsize_2)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     // config.set_maxbatchsize(1024 * 1024); //这里设置成1M
//     config.set_lingerms(10000);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     // for (int i = 0; i < 10; ++i)
//     // {
//     //     auto content = log.add_contents();
//     //     content->set_key("content");
//     //     content->set_value("this my test log");
//     // }
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     // PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     auto content = log.add_contents();
//     content->set_key("content");
//     std::string tmp = "this my test log";
//     for (int i = 0; i < 130000; ++i)
//     {
//         tmp += "add data";
//     }
//     content->set_value(tmp);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     sleep(5);
//     client->LogProducerEnvDestroy();
//     // EXPECT_EQ(ret.statusCode, 0);
// }


/*
测试场景：AddLogToProducerBatch为超过maxbatchsize,但是逗留时间触达
预期：把数据添加到线程池中
*/
// TEST(tencent_log_sdk_test, linems_1)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     // config.set_maxbatchsize(1024 * 1024); //这里设置成1M
//     config.set_lingerms(500);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     // PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     auto content = log.add_contents();
//     content->set_key("content");
//     std::string tmp = "this my test log";
//     for (int i = 0; i < 130000; ++i)
//     {
//         tmp += "add data";
//     }
//     content->set_value(tmp);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     ret = client->PostLogStoreLogs(topic, log, callback);
//     sleep(5);
//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 0);
// }

/*
测试场景：AddLogToProducerBatch为超过maxbatchsize，并且逗留时间触达
预期：把数据添加到线程池中且数据不错乱
*/
// TEST(tencent_log_sdk_test, linems_2)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     // config.set_maxbatchsize(1024 * 1024); //这里设置成1M
//     config.set_lingerms(1);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     std::string topic = "";
//     auto callback = std::make_shared<UserResult>();
//     // PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     auto content = log.add_contents();
//     content->set_key("content");
//     std::string tmp = "this my test log";
//     for (int i = 0; i < 130000; ++i)
//     {
//         tmp += "add data";
//     }
//     content->set_value(tmp);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     for (int i = 0; i < 10; ++i)
//     {
//         sleep(1);
//         ret = client->PostLogStoreLogs(topic, log, callback);
//     }
//     sleep(5);
//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 0);
// }

/*
测试场景：数据发送失败，加入到重试队列中
预期：数据按照从小到大排列组合
*/
// TEST(tencent_log_sdk_test, retry_1)
// {
//     cls_config::LogProducerConfig config;
//     config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
//     config.set_acceskeyid(“”);
//     config.set_accesskeysecret("");
//     // config.set_maxbatchsize(1024 * 1024); //这里设置成1M
//     config.set_lingerms(1);
//     auto client = std::make_shared<ProducerClient>(config);
//     client->Start();
//     cls::Log log;
//     log.set_time(time(NULL));
//     std::string topic = "0b31137-c547-4676-a19e-eaf1e5888921";
//     auto callback = std::make_shared<UserResult>();
//     // PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     auto content = log.add_contents();
//     content->set_key("content");
//     std::string tmp = "this my test log";
//     for (int i = 0; i < 130000; ++i)
//     {
//         tmp += "add data";
//     }
//     content->set_value(tmp);
//     PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
//     for (int i = 0; i < 10; ++i)
//     {
//         ret = client->PostLogStoreLogs(topic, log, callback);
//         sleep(2);
//     }
//     sleep(20);
//     client->LogProducerEnvDestroy();
//     EXPECT_EQ(ret.statusCode, 0);
// }


/*
测试场景：数据发送失败，加入到重试队列中,重试retryes后依旧失败
预期：回调用户失败
*/
TEST(tencent_log_sdk_test, retry_2)
{
    cls_config::LogProducerConfig config;
    config.set_endpoint("ap-guangzhou.cls.tencentcs.com");
    config.set_acceskeyid("");
    config.set_accesskeysecret("");
    // config.set_maxbatchsize(1024 * 1024); //这里设置成1M
    config.set_lingerms(1);
    config.set_retries(5);
    auto client = std::make_shared<ProducerClient>(config);
    client->Start();
    cls::Log log;
    log.set_time(time(NULL));
    std::string topic = "0b31137-c547-4676-a19e-eaf1e5888921";
    auto callback = std::make_shared<UserResult>();
    // PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
    auto content = log.add_contents();
    content->set_key("content");
    std::string tmp = "this my test log";
    for (int i = 0; i < 130000; ++i)
    {
        tmp += "add data";
    }
    content->set_value(tmp);
    PostLogStoreLogsResponse ret = client->PostLogStoreLogs(topic, log, callback);
    sleep(20);
    client->LogProducerEnvDestroy();
    EXPECT_EQ(ret.statusCode, 0);
}