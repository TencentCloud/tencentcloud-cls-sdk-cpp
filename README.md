# 描述

tencent-log-sdk-cpp 是C++用户日志结构化上传的SDK，采用轻量的设计模式，简单易用可快速上手.支持同步模式以及异步模式。具体参见如下的demo

## 如何使用

### 依赖

- `protobuf` require version protobuf 2.6.1
  - PB 描述文件是通信双方约定的数据交换格式，上传日志时须将规定的协议格式编译成对应语言版本的调用接口，然后添加到工程代码里。参见[文档](https://cloud.tencent.com/document/product/614/16873)
- curl 可使用系统自带的工具或者自己安装即可
- boost 依赖boot库
- `openssl` 签名的计算依赖openssl,这里建议使用[官网](https://www.openssl.org/source/) 提供的1.1.1版本，签名的方式参见[文档](https://cloud.tencent.com/document/product/614/12445)



### 异步模式


#### 使用步骤

- step1:cd到当前工程目录下面
- step2:执行命令 cmake .
- step3:执行命令 make
  以上命令执行完了之后，会在当前工程目录下面生成如下文件
  - 生成ibclssdk.a、libclssdk.so
  - cls_log.pb.h和cls_log.pb.cc文件,cls_log.pb.h和cls_log.pb.cc文件是日志上传的协议格式。
  - logproducerconfig.pb.h 和logproducerconfig.pb.cc文件，该文件是配置相关的设置信息。具体使用可参考demo中的使用
- step3:执行命令 make install 进行安装

#### 配置说明logproducerconfig.proto

| 参数               | 类型  | 描述                                                         |
| ------------------ | ----- | ------------------------------------------------------------ |
| TotalSizeLnBytes   | Int64 | 实例能缓存的日志大小上限，默认为 100MB。                     |
| MaxSendWorkerCount | Int64 | client能并发的最多"goroutine"的数量，默认为50                |
| MaxBlockSec        | Int   | 如果client可用空间不足，调用者在 send 方法上的最大阻塞时间，默认为 60 秒。 如果超过这个时间后所需空间仍无法得到满足，send 方法会抛出TimeoutException。如果将该值设为0，当所需空间无法得到满足时，send 方法会立即抛出 TimeoutException。如果您希望 send 方法一直阻塞直到所需空间得到满足，可将该值设为负数。 |
| MaxBatchSize       | Int64 | 当一个Batch中缓存的日志大小大于等于 batchSizeThresholdInBytes 时，该 batch 将被发送，默认为 512 KB，最大可设置成 5MB。 |
| LingerMs           | Int64 | Batch从创建到可发送的逗留时间，默认为 2 秒，最小可设置成 100 毫秒。 |
| Retries            | Int   | 如果某个Batch首次发送失败，能够对其重试的次数，默认为 10 次。 如果 retries 小于等于 0，该 ProducerBatch 首次发送失败后将直接进入失败队列。 |
| BaseRetryBackoffMs | Int64 | 首次重试的退避时间，默认为 100 毫秒。 client采样指数退避算法，第 N 次重试的计划等待时间为 baseRetryBackoffMs * 2^(N-1)。 |
| MaxRetryBackoffMs  | Int64 | 重试的最大退避时间，默认为 50 秒。                           |


#### 异步demo:  sample.cpp文件

- SecretId和SecretKey为云API密钥，密钥信息获取请前往[密钥获取](https://console.cloud.tencent.com/cam/capi)。并请确保密钥关联的账号具有相应的[SDK上传日志权限](https://cloud.tencent.com/document/product/614/68374#.E4.BD.BF.E7.94.A8-api-.E4.B8.8A.E4.BC.A0.E6.95.B0.E6.8D.AE)


```
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

```

- 编译

  ```
  g++ -o sample sample.cpp -std=c++11  -O2  -L. -lclssdk -lcurl -lprotobuf -lssl -lcrypto -lboost_thread
  ```

- 执行./sample 运行生成的二进制程序包，可登陆[腾讯云平台](https://console.cloud.tencent.com/cls/search)查看日志是否上传成功

### 同步模式

#### 使用说明

- step1:cd到当前工程目录下面
- step2:执行命令 cmake .
- step3:执行命令 make 以上命令执行完了之后，会在当前工程目录下面生成libclssdk.a、libclssdk.so以及相应的cls_log.pb.h和cls_log.pb.cc文件方便项目中使用
- step3:执行命令 make install 进行安装

#### 同步demo: syncsample.cpp 

```c++
#include "client.h"
#include "common.h"
#include "cls_logs.pb.h"
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
    try{
        for(int i = 0; i < 10; ++i){
            ret = ptr -> PostLogStoreLogs(topic,loggroup);
            printf("%s\n",ret.Printf().c_str());
        }
    }
    catch(LOGException & e)
    {
        cout<<e.GetErrorCode()<<":"<<e.GetMessage()<<endl;
    }
    return 0;
}

```

- 编译

```
  g++ -o syncsample  syncsample.cpp -std=c++11  -O2  -L. -lclssdk -lcurl -lprotobuf -lssl -lcrypto -lboost_thread
```

## FAQ

- ### 安装protobuf出现报错

  ```shell
  error while loading shared libraries: libprotobuf.so.9: cannot open shared object file: No such file or directory
  ```

  - 解决

    - 查看protobuf.so文件是在哪里，执行命令

      ```shell
      whereis libprotobuf.so.9
      ```

    - 执行cat /etc/ld.so.conf 查看是否有第一步的路径

    - 如果发现没有的话，把第一步输出的路径，则添加到ld.so.conf

    - 执行ldconfig加载文件

      ```shell
      ldconfig
      ```

- ### 代码说明

  ```
  .
  ├── adapter.cpp                #适配器 主要是发送网络请求
  ├── adapter.h
  ├── batchloggroup.cpp          #对聚合的数据抽象
  ├── batchloggroup.h
  ├── client.cpp
  ├── client.h                   #内存发起网络请求的client
  ├── cls_logs.pb.cc
  ├── cls_logs.pb.h
  ├── cls_logs.proto
  ├── CMakeLists.txt
  ├── common.cpp
  ├── common.h
  ├── error.h
  ├── logaccumulator.cpp         #负责数据的聚合
  ├── logaccumulator.h
  ├── logmemmgr.cpp              #内存管理类
  ├── logmemmgr.h
  ├── logproducerconfig.pb.cc
  ├── logproducerconfig.pb.h
  ├── logproducerconfig.proto    #配置相关的协议
  ├── logretryqueue.cpp
  ├── logretryqueue.h            #重试队列
  ├── logthreadpool.cpp
  ├── logthreadpool.h            #线程池
  ├── logtimer.cpp
  ├── logtimer.h                 #定时器
  ├── lz4
  │   ├── lz4.c
  │   └── lz4.h
  ├── producerclient.cpp
  ├── producerclient.h           #对外提供能力的类
  ├── rapidjson
  │   ├── allocators.h
  │   ├── document.h
  │   ├── encodedstream.h
  │   ├── encodings.h
  │   ├── error
  │   │   ├── en.h
  │   │   └── error.h
  │   ├── filereadstream.h
  │   ├── filewritestream.h
  │   ├── fwd.h
  │   ├── internal
  │   │   ├── biginteger.h
  │   │   ├── diyfp.h
  │   │   ├── dtoa.h
  │   │   ├── ieee754.h
  │   │   ├── itoa.h
  │   │   ├── meta.h
  │   │   ├── pow10.h
  │   │   ├── regex.h
  │   │   ├── stack.h
  │   │   ├── strfunc.h
  │   │   ├── strtod.h
  │   │   └── swap.h
  │   ├── istreamwrapper.h
  │   ├── memorybuffer.h
  │   ├── memorystream.h
  │   ├── msinttypes
  │   │   ├── inttypes.h
  │   │   └── stdint.h
  │   ├── ostreamwrapper.h
  │   ├── pointer.h
  │   ├── prettywriter.h
  │   ├── rapidjson.h
  │   ├── reader.h
  │   ├── schema.h
  │   ├── stream.h
  │   ├── stringbuffer.h
  │   └── writer.h
  ├── README.md
  ├── RestfulApiCommon.h
  ├── result.h
  ├── sample.cpp
  ├── signature.cpp         #签名算法，使用的是腾讯sdk能力
  ├── signature.h
  ├── test
  │   ├── CMakeLists.txt
  │   ├── tencentclssdk_benchmark.cpp
  │   └── tencentclssdk_test.cpp
  ├── utils.cpp
  └── utils.h
  ```

  
