<template>
    <div class="network">
        <div class="info">
            <div class="item" style="flex: 100%;">
                <h2>main方法使用</h2>
                <pre v-html="utils.highlightCppKeywords(text[0])"></pre>
            </div>
            <div class="item" style="flex: 100%;padding: 5px;">
                <h2>TCP</h2>
                <div style="display: flex;flex-wrap: wrap;">
                    <div class="item">
                        <h2>TCP服务端</h2>
                        <pre v-html="utils.highlightCppKeywords(text[1])"></pre>
                    </div>
                    <div class="item">
                        <h2>TCP客户端</h2>
                        <pre v-html="utils.highlightCppKeywords(text[2])"></pre>
                    </div>
                </div>
                <div class="item">
                    <h2>描述</h2>
                    <p>TCP服务端、客户端,可用于实现网络通信。目前通讯限制大小为10KB。</p>
                    <p>用途广泛,搭建网络验证完全OK,什么? 数据存储? 用AEXStore数据仓库对象!</p>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    props: ['utils'],
    data() {
        return {
            text: [
                `
    //TCP 服务器示例:

    #include "AEXModule.h"
    #include <iostream>
    #include <thread>
    /*
    * 处理客户端请求

    * @param client 客户端对象
    */
    static void handleClient(Network::TCP::PCLIENT client) {
        Network::TCP::PSERVER server = reinterpret_cast<Network::TCP::PSERVER>(client->server);
        while (server->started) {
            Byteset data = server->Recv(client);
            if (client->state == (Network::TCP::_SERVER::SERVER_CLIENT_DISCONNECTION | Network::TCP::_SERVER::SERVER_DATA_RECV_FAILED)) {
                std::cout << "Client disconnected" << std::endl;
                server->disconnect(client);
                break;
            }
            std::cout << "Received data: " << (char*)data.data() << std::endl;
            server->Send(client, data); // Echo back the data
        }
    }
    int main() {
        Network::TCP::Server server;
        if (!server.start(4001)) {
            std::cerr << "Failed to start server" << std::endl;
            return 1;
        }
        std::cout << "Server started on port 4001" << std::endl;
        while (true) {
            Network::TCP::CLIENT client = server.Listen();
            if (client.state == Network::TCP::_SERVER::SERVER_CLIENT_CONNECTION) {
                std::cout << "Client connected" << std::endl;
                std::thread clientThread(handleClient, &client);
                clientThread.detach();
            }
        }
    };

    //TCP 客户端示例:

    #include "AEXModule.h"
    #include <iostream>

    int main() {
        Network::TCP::Client client;
        if (!client.Connect("127.0.0.1", 4001)) {
            std::cerr << "Failed to connect to server" << std::endl;
            return 1;
        }
        std::cout << "Connected to server" << std::endl;
        Byteset data;
        LPCSTR str = "Hello World!";
        for (size_t i = 0; i < 1000*strlen(str); i++)
        {
            data.append(str[i % strlen(str)]);
        }
        client.Send(data);
        Byteset response = client.Recv();
        std::cout << "Received data: " << response << std::endl;
        client.Send(data);
        response = client.Recv();
        std::cout << "Received data: " << response << std::endl;

        client.disconnect();
        std::cout << "Disconnected from server" << std::endl;
    };
                `,
                `
        typedef struct _CLIENT {
            SOCKET handle;
            sockaddr_in addr;
            int state; //客户状态,对应 _SERVER 枚举状态码
            PVOID server;//服务端对象
        } CLIENT, * PCLIENT;
        enum _SERVER {//服务码
            SERVER_CLIENT_DISCONNECTION,//客户断开
            SERVER_CLIENT_CONNECTION,//客户连接
            SERVER_DATA_RECV,//数据接收
            SERVER_DATA_RECV_FAILED,//数据接收失败
            SERVER_DATA_SEND,//数据发送
            SERVER_DATA_SEND_FAILED,//数据发送失败
            SERVER_TIMEOUT,//超时
        };
        // 服务端类
        typedef class Server {
        private:
            std::string ip;
            int port;
            SOCKET _socket_;
            sockaddr_in _serverAddr_;
            std::vector<CLIENT> clients;
        public:
            bool started;//服务是否启动中
        public:
            Server();
            ~Server();
            // 拷贝赋值操作符
            Network::TCP::Server& operator=(const Server& other);
            /*
            * 启动服务
            * @param port 服务端口
            * @return 启动成功返回true，否则返回false
            */
            bool start(int port);
            /*
            * 停止服务
            */
            void stop();
            /*
            * 监听
            * @param timeout 超时时间，单位为毫秒，-1表示无限等待
            * @return 返回连接的客户对象
            */
            CLIENT Listen(int timeout = -1);
            /*
            * 断开连接
            * @param client 客户对象
            * @return 成功返回true，否则返回false
            */
            bool disconnect(PCLIENT client);
            /*
            * 发送数据
            * @param client 客户对象
            * @param data 待发送的数据
            * @param timeout 超时时间，单位为毫秒，-1表示无限等待
            * @return 成功返回true，否则返回false
            */
            bool Send(PCLIENT client,Byteset& data,int timeout = -1) const;
            /*
            * 接收数据(限制10KB)
            * @param client 客户对象
            * @param timeout 超时时间，单位为毫秒，-1表示无限等待
            * @return 接收到的数据
            */
            Byteset Recv(PCLIENT client, int timeout = -1) const;
            /*
            * 获取客户数量
            * @return 客户数量
            */
            size_t GetClientCount();
            /*
            * 获取客户对象
            * @param index 客户索引
            * @return 客户对象
            */
            PCLIENT GetClient(int index);
            /*
            * 取错误码/事件状态
            * @return 错误码/事件状态
            */
            int GetLastError() const;
        } * PSERVER;
                `,
                `
        // 客户端类
        class Client {
        private:
            SOCKET _socket_;
            sockaddr_in _serverAddr_;
        public:
            bool started;//客户端是否连接中
        public:
            Client();
            ~Client();
            // 拷贝赋值操作符
            Network::TCP::Client& operator=(const Client& other);
            /*
            * 连接服务端
            * @param ip 服务端IP地址
            * @param port 服务端端口
            * @return 连接成功返回true，否则返回false
            */
            bool Connect(const std::string& ip, int port);
            /*
            * 断开连接
            * @return 成功返回true，否则返回false
            */
            bool disconnect();
            /*
            * 发送数据
            * @param data 待发送的数据
            * @param timeout 超时时间，单位为毫秒，-1表示无限等待
            * @return 成功返回true，否则返回false
            */
            bool Send(const Byteset& data, int timeout = -1) const;
            /*
            * 接收数据(限制10KB)
            * @param timeout 超时时间，单位为毫秒，-1表示无限等待
            * @return 接收到的数据
            */
            Byteset Recv(int timeout = -1) const;
            /*
            * 取错误码/事件状态
            * @return 错误码/事件状态
            */
            int GetLastError() const;
        };
                `
            ]
        }
    }
};
</script>
<style lang="scss" scoped>
.network {
    .info {
        display: flex;
        justify-content: center;
        flex-wrap: wrap;


        * {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        .item {
            position: relative;
            overflow: hidden;
            line-height: 2em;
            padding: 10px 0;
            box-sizing: border-box;

            h2 {
                font-style: oblique;
                background-color: #8111cb;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #8111cb;
                    left: -10px;
                    top: 2.15em;
                }
            }

            h3 {
                background-color: #9b62c2;
                padding: 5px 10px;
                display: inline-block;
                border-top-left-radius: 5px;
                border-top-right-radius: 5px;

                &::before {
                    position: absolute;
                    content: "";
                    width: 110%;
                    height: 2px;
                    background-color: #9b62c2;
                    left: -10px;
                    margin-top: 2em;
                }
            }

            .comment {
                font-size: 1.2em;
                text-indent: 0.5em;
                margin: 5px 0;
            }

            pre {
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                line-height: 1em;
                display: block;
                width: 100%;
                border-radius: 5px;
                padding: 15px 0;
                background-color: #1c1c1c;
                overflow: auto;
                font-size: 1.3rem;
            }

            .params-table {
                display: block;
                border-collapse: collapse;
                width: 100%;
                overflow: auto;


                th,
                td {
                    border: 1px solid #9b62c2;
                    padding: 8px;
                    text-align: left;
                    text-wrap: nowrap;
                }

                .top th {
                    user-select: none;
                    font-size: 1.2em;
                    font-style: oblique;
                    background-color: #8648b0;
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                    }
                }

                .dict {
                    background-color: #795c8c;
                    padding: 5px 10px;
                    font-weight: bold;
                    border-radius: 100px;
                }

                .param td,
                .ret td {
                    text-align: center;

                    &:nth-child(3) {
                        text-align: left;
                        width: 100%;
                    }
                }
            }
        }
    }
}
</style>
