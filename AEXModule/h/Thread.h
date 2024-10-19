#pragma once
#include <windows.h>
#include "Byteset.h"
#include "System.h"
typedef class Thread;//��ǰ����
typedef void (*Thread_callback)(Thread *);//�̻߳ص���������
//�߳�״̬
enum Thread_status {
	THREAD_STATUS_NONE,// δ����
	THREAD_STATUS_RUNNING,// ������
	THREAD_STATUS_STOPPED,// ��ֹͣ
};
//�߳�ģʽ
enum Thread_type {
	THREAD_TYPE_NONE,//��ִ��
	THREAD_TYPE_ONE_SHOT,//����ִ��һ��
	THREAD_TYPE_LOOP,//ѭ��ִ��
};
typedef struct _Thread_info {
	Byteset code;//�̱߳�ʶ��
	Thread_status status;//�߳�״̬
	Thread_callback callback;//�̻߳ص�����
	HANDLE handle;//�߳̾��
	Thread_type type;//�߳�ģʽ
	__int64 interval[2];//��ʱ�����
	PVOID none1;//Ԥ��(�ڲ�����)
	/**
	* @brief ���캯��
	* @param code �̱߳�ʶ��,Ĭ��NULL
	* @param callback �̻߳ص�����,Ĭ��NULL
	* @param type �߳�ģʽ,Ĭ��NONE
	* @param interval ��ʱ�����,��λ����,Ĭ��1000ms
	*/
	_Thread_info(Byteset code = NULL, Thread_callback callback = NULL, Thread_type type = Thread_type::THREAD_TYPE_NONE, __int64 interval = 1000)
		: status(Thread_status::THREAD_STATUS_NONE), handle(NULL),
		none1(NULL){
		this -> code = code;
		this -> callback = callback;
		this -> type = type;
		this -> interval[0] = interval;
	}
} Thread_info, *PThread_info;
typedef class Thread{
private:
	std::vector<Thread_info> thread_info_list;//�߳���Ϣ�б�
public:
	PVOID timer;//��ʱ��
	int loop_interval;//��ʱ�����
	bool is_running;//��ʱ���Ƿ���������
public:
	/**
	 * @brief ���캯��
	 * @param loop_interval ��ʱ�����,��λ����,Ĭ��500ms
	 */
	Thread(int loop_interval = 500);
	~Thread();
	/**
	 * @brief �����߳�
	 * @param info �߳���Ϣ
	 * @return �Ƿ�ɹ�,ʧ��ԭ��������̱߳�ʶ���Ѵ���,��callbackΪ��
	 */
	bool add_thread(Thread_info info);
	/**
	 * @brief �����߳�
	 * @param code �̱߳�ʶ��
	 * @return �Ƿ�ɹ�
	 */
	bool remove_thread(Byteset code);
	/**
	 * @brief �����߳�
	 * @param code �̱߳�ʶ��
	 * @param join �Ƿ�ȴ��߳̽���,Ĭ��false
	 * @return �Ƿ�ɹ�,ʧ�����Ҳ����̻߳��Ѿ�������
	 */
	bool start_thread(Byteset code, bool join = false);
	/**
	 * @brief ֹͣ�߳�(�����߳�)
	 * @param code �̱߳�ʶ��
	 * @return �Ƿ�ɹ�,ʧ�����Ҳ����̻߳��Ѿ�ֹͣ
	 */
	bool stop_thread(Byteset code);
}*PThread;