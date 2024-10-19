#pragma once
#include <windows.h>
#include <vector>
#include "Byteset.h"
#include "AEXStore.h"
/*
* ע��:���ⲻ����MT���߳�ģʽ,����ģʽ����ʹ��
* ͬԴ����,һ��������,����ͬʱ���ñ����TCP�Ŀͻ��˺ͷ����
*/
namespace Network {
    INT MSG(std::string message, int result = NULL, std::string title = "Error");
	namespace TCP {
        typedef struct _CLIENT {
            SOCKET handle;
            sockaddr_in addr;
            int state; //�ͻ�״̬,��Ӧ _SERVER ö��״̬��
            PVOID server;//����˶���
        } CLIENT, * PCLIENT;
        enum _SPEED_UNIT {
            SPEED_BIT,
            SPEED_KB,
            SPEED_MB,
            SPEED_GB,
        };
        typedef struct _SERVER_MSG_INFO {
            PCLIENT client;//�ͻ�����
            PFile file = new File();//������/��������(���ļ�Ϊ��λ)
            PSIZE_T size = nullptr;//�ѷ���/�������ݴ�С
            DOUBLE speed = NULL;//�ٶ�
            INT unit = SPEED_BIT;//�ٶȵ�λ(�����ٶȴ�С���е�λ�任)(1:BIT -> 2:KB -> 3:MB -> 4:GB)
            int timeout = -1;//��ʱʱ��
            bool is_end = false;//�Ƿ����
        } SERVER_MSG_INFO, * PSERVER_MSG_INFO;
        typedef struct _CLIENTS_MSG_INFO {
            PFile file = new File();//������/��������(���ļ�Ϊ��λ)��ÿ�ν�������ǰ����Ҫ�ֶ��������,Recvs���������Զ���ա�
            PSIZE_T size = nullptr;//�ѷ���/�������ݴ�С
            DOUBLE speed = NULL;//�ٶ�
            INT unit = SPEED_BIT;//�ٶȵ�λ(�����ٶȴ�С���е�λ�任)(1:BIT -> 2:KB -> 3:MB -> 4:GB)
            int timeout = -1;//��ʱʱ��
            bool is_end = false;//�Ƿ����
        } CLIENTS_MSG_INFO, * PCLIENTS_MSG_INFO;
        enum _SERVER {//������
            SERVER_CLIENT_DISCONNECTION,//�ͻ��Ͽ�
            SERVER_CLIENT_CONNECTION,//�ͻ�����
            SERVER_DATA_RECV,//���ݽ���
            SERVER_DATA_RECV_FAILED,//���ݽ���ʧ��
            SERVER_DATA_SEND,//���ݷ���
            SERVER_DATA_SEND_FAILED,//���ݷ���ʧ��
            SERVER_TIMEOUT,//��ʱ
        };
        // �������
        typedef class Server {
        private:
            std::string ip;
            int port;
            SOCKET _socket_;
            sockaddr_in _serverAddr_;
            std::vector<CLIENT> clients;
        public:
            bool started;//�����Ƿ�������
        public:
            Server();
            ~Server();
            // ������ֵ������
            Network::TCP::Server& operator=(const Server& other);
            /*
            * ��������
            * @param port ����˿�
            * @return �����ɹ�����true�����򷵻�false
            */
            bool start(int port);
            /*
            * ֹͣ����
            */
            void stop();
            /*
            * ����
            * @param timeout ��ʱʱ�䣬��λΪ���룬-1��ʾ���޵ȴ�
            * @return �������ӵĿͻ�����
            */
            CLIENT Listen(int timeout = -1);
            /*
            * �Ͽ�����
            * @param client �ͻ�����
            * @return �ɹ�����true�����򷵻�false
            */
            bool disconnect(PCLIENT client);
            /*
            * ��������(����10KB)���������͹������ֻ������һ����
            * @param client �ͻ�����
            * @param data �����͵�����
            * @param timeout ��ʱʱ�䣬��λΪ���룬-1��ʾ���޵ȴ�
            * @return �ɹ�����true�����򷵻�false
            */
            bool Send(PCLIENT client,Byteset data,int timeout = -1) const;
            /*
            * ��������(����������,�������нϴ�Ӱ��)���������͹������ֻ������һ����
            * @param info ������Ϣ
            * @return �ɹ�����true�����򷵻�false
            */
            bool Sends(PSERVER_MSG_INFO info) const;
            /*
            * ��������(����10KB)���������չ������ֻ������һ����
            * @param client �ͻ�����
            * @param timeout ��ʱʱ�䣬��λΪ���룬-1��ʾ���޵ȴ�
            * @return ���յ�������
            */
            Byteset Recv(PCLIENT client, int timeout = -1) const;
            /*
            * ��������(����������,�������нϴ�Ӱ��)���������չ������ֻ������һ����
            * @param info ������Ϣ
            * @return �ɹ�����true�����򷵻�false
            */
            bool Recvs(PSERVER_MSG_INFO info) const;
            /*
            * ��ȡ�ͻ�����
            * @return �ͻ�����
            */
            size_t GetClientCount();
            /*
            * ��ȡ�ͻ�����
            * @param index �ͻ�����
            * @return �ͻ�����
            */
            PCLIENT GetClient(int index);
            /*
            * ȡ������/�¼�״̬
            * @return ������/�¼�״̬
            */
            int GetLastError() const;
        } * PSERVER;
        // �ͻ�����
        class Client {
        private:
            SOCKET _socket_;
            sockaddr_in _serverAddr_;
        public:
            bool started;//�ͻ����Ƿ�������
        public:
            Client();
            ~Client();
            // ������ֵ������
            Network::TCP::Client& operator=(const Client& other);
            /*
            * ���ӷ����
            * @param ip �����IP��ַ
            * @param port ����˶˿�
            * @return ���ӳɹ�����true�����򷵻�false
            */
            bool Connect(const std::string& ip, int port);
            /*
            * �Ͽ�����
            * @return �ɹ�����true�����򷵻�false
            */
            bool disconnect();
            /*
            * �������ݡ��������͹������ֻ������һ����
            * @param data �����͵�����
            * @param timeout ��ʱʱ�䣬��λΪ���룬-1��ʾ���޵ȴ�
            * @return �ɹ�����true�����򷵻�false
            */
            bool Send(Byteset data, int timeout = -1) const;
            /*
            * ��������(����������,�������нϴ�Ӱ��)���������͹������ֻ������һ����
            * @param info ������Ϣ
            * @return �ɹ�����true�����򷵻�false
            */
            bool Sends(PCLIENTS_MSG_INFO info) const;
            /*
            * ��������(����10KB)
            * @param timeout ��ʱʱ�䣬��λΪ���룬-1��ʾ���޵ȴ�
            * @return ���յ�������
            */
            Byteset Recv(int timeout = -1) const;
            /*
            * ��������(����������,�������нϴ�Ӱ��)���������͹������ֻ������һ����
            * @param info ������Ϣ
            * @return �ɹ�����true�����򷵻�false
            */
            bool Recvs(PCLIENTS_MSG_INFO info) const;
            /*
            * ȡ������/�¼�״̬
            * @return ������/�¼�״̬
            */
            int GetLastError() const;
        };

	};
};
// TCPʾ������
/*
static void handleClient(Network::TCP::PCLIENT client) {
    Network::TCP::PSERVER server = reinterpret_cast<Network::TCP::PSERVER>(client->server);
    while (server->started) {
        Byteset data = server->Recv(client);
        if (client->state == Network::TCP::_SERVER::SERVER_CLIENT_DISCONNECTION ||
            client->state == Network::TCP::_SERVER::SERVER_DATA_RECV_FAILED ||
            client->state == Network::TCP::_SERVER::SERVER_DATA_SEND_FAILED
            ) {
            std::cout << "Client disconnected" << std::endl;
            server->disconnect(client);
            break;
        }
        std::cout << "1Received data: " << (char*)data.data() << std::endl;
        server->Send(client, "Hello World!");
    }
}

int main()
{

    //Network::TCP::Server server;
    //if (!server.start(4001)) {
    //    std::cerr << "Failed to start server" << std::endl;
    //    return 1;
    //}
    //std::cout << "Server started on port 4001" << std::endl;
    //while (true) {
    //    Network::TCP::CLIENT client = server.Listen(-1);
    //    if (client.state == Network::TCP::_SERVER::SERVER_CLIENT_CONNECTION) {
    //        std::cout << "Client connected" << std::endl;
    //        std::thread clientThread(handleClient, &client);
    //        clientThread.detach();
    //    }
    //}
    //return 0;

    Network::TCP::Client client;
    if (!client.Connect("127.0.0.1", 4001)) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }
    std::cout << "Connected to server" << std::endl;
    Byteset response;
    do {
        std::string dd;
        std::cin >> dd;
        client.Send(dd);
        response = client.Recv();
        std::cout << "Received data: " << response << std::endl;
    } while (response != "end");
    client.disconnect();
    std::cin.get();
    return 0;
}
*/