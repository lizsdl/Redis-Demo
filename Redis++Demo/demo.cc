#include <sw/redis++/redis++.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <functional>

// 回调函数，处理接收到的消息
void messageCallback(const std::string &channel, const std::string &message)
{
    std::cout << "Received message from channel " << channel << ": " << message << std::endl;
}

int main()
{

    // 在这里可以执行其他逻辑，订阅事件循环会在后台运行
    // 无限循环，保持订阅事件处理

    try
    {
        // 创建 Redis 对象
        // sw::redis::Redis redis("tcp://127.0.0.1:6379");

        std::shared_ptr<sw::redis::Redis> redis_;

        std::string url("tcp://127.0.0.1:6379");
        // sw::redis::ConnectionOptions conn_opts(url);

        sw::redis::ConnectionOptions connection_options;
        // 设置 Redis 服务器的连接信息
        connection_options.host = "127.0.0.1";
        connection_options.port = 6379;

        redis_ = std::make_shared<sw::redis::Redis>(connection_options);

        std::shared_ptr<sw::redis::Subscriber> subscriber_;
        subscriber_ = std::make_shared<sw::redis::Subscriber>(redis_->subscriber());

        subscriber_->on_message(std::bind(messageCallback, std::placeholders::_1, std::placeholders::_2));

        std::cout << "Before subscribe" << std::endl;

        subscriber_->subscribe("mychannel");

        std::cout << "After subscribe" << std::endl;

        // 使用 on_message 设置消息处理函数

        std::cout << "Test  " << std::endl;


        // 这里需要一直循环调用consume，用于处理接收到的消息队列中的消息。这样可以确保及时处理订阅频道上的消息，并且保持订阅事件循环一直在运行。
        while(true){
            subscriber_->consume();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 可以适当加入短暂的睡眠
        }
    }
    catch (const sw::redis::Error &e)
    {
        std::cerr << "Redis error: " << e.what() << std::endl;
        return 1;
    }
}
