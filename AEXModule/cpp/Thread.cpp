#include "../h/Thread.h"
#include <thread>
#include <mutex>
static std::mutex mtx;
static void controll_thread(PThread thread, std::vector<Thread_info>* thread_info_list) {
	while (thread->is_running) {
		std::lock_guard<std::mutex> lock(mtx); // ��ס�Թ�����Դ�ķ���
		for (int i = 0, size = thread_info_list->size(); i < size; i++) {
			if ((*thread_info_list)[i].type == Thread_type::THREAD_TYPE_LOOP &&
				(*thread_info_list)[i].interval[1] <= System::GetRunTime()) {

				(*thread_info_list)[i].interval[1] = System::GetRunTime() + (*thread_info_list)[i].interval[0];

				// ʹ�� copy ��ִֵ�лص�
				std::thread callback_thread([=]() {
					(*thread_info_list)[i].callback(thread);
					});
				callback_thread.detach(); // �̷߳��룬ע�����
			}
		}
		Sleep(thread->loop_interval);
	}
	thread->timer = nullptr;
}

Thread::Thread(int loop_interval) {
	this->is_running = true;
	this->loop_interval = loop_interval;
	this->timer = new std::thread(controll_thread, this, &this->thread_info_list);
}

Thread::~Thread() {
	this->is_running = false;
	if (this->timer != nullptr) {
		((std::thread*)this->timer)->join(); // �ȴ������߳̽���
		delete timer;  // �ͷ���Դ
	}
}


bool Thread::add_thread(Thread_info info)
{
	if(info.callback == nullptr) return false;
	for (auto it = this->thread_info_list.begin(); it != this->thread_info_list.end(); it++) if (it->code == info.code) return false;
	this->thread_info_list.push_back(info);
	if (info.type == Thread_type::THREAD_TYPE_ONE_SHOT) {
		std::thread callback_thread([&]() {
			std::lock_guard<std::mutex> lock(mtx);
			info.callback(this);
			});
		callback_thread.detach();
	}
	return true;
}

bool Thread::remove_thread(Byteset code)
{
	for (auto it = this->thread_info_list.begin(); it!= this->thread_info_list.end(); it++)
	{
		if (it->code == code)
		{
			this->thread_info_list.erase(it);
			return true;
		}
	}
	return false;
}

bool Thread::start_thread(Byteset code, bool join) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& info : thread_info_list) {
        if (info.code == code && info.status == Thread_status::THREAD_STATUS_NONE) {
            info.status = Thread_status::THREAD_STATUS_RUNNING;
            info.none1 = CreateThread(
                nullptr,        // Ĭ�ϰ�ȫ����
                0,             // Ĭ�϶�ջ��С
				(LPTHREAD_START_ROUTINE)info.callback, // �̺߳���
                &info,         // ��������
                0,             // Ĭ�ϴ�����־
                nullptr);      // �߳� ID

            if (info.none1 != nullptr) {
                if (join) {
                    WaitForSingleObject(info.none1, INFINITE); // �ȴ��߳̽���
                    CloseHandle(info.none1); // �رվ��
                }
                return true;
            }
        }
    }
    return false;
}

bool Thread::stop_thread(Byteset code) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& info : thread_info_list) {
        if (info.code == code && info.status == Thread_status::THREAD_STATUS_RUNNING) {
            TerminateThread(info.none1, 0);
            CloseHandle(info.none1);
            info.status = Thread_status::THREAD_STATUS_NONE;
            return true;
        }
    }
    return false;
}
