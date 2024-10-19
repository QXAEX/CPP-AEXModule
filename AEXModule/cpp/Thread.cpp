#include "../h/Thread.h"
#include <thread>
#include <mutex>
static std::mutex mtx;
static void controll_thread(PThread thread, std::vector<Thread_info>* thread_info_list) {
	while (thread->is_running) {
		std::lock_guard<std::mutex> lock(mtx); // 锁住对共享资源的访问
		for (int i = 0, size = thread_info_list->size(); i < size; i++) {
			if ((*thread_info_list)[i].type == Thread_type::THREAD_TYPE_LOOP &&
				(*thread_info_list)[i].interval[1] <= System::GetRunTime()) {

				(*thread_info_list)[i].interval[1] = System::GetRunTime() + (*thread_info_list)[i].interval[0];

				// 使用 copy 的值执行回调
				std::thread callback_thread([=]() {
					(*thread_info_list)[i].callback(thread);
					});
				callback_thread.detach(); // 线程分离，注意管理
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
		((std::thread*)this->timer)->join(); // 等待控制线程结束
		delete timer;  // 释放资源
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
                nullptr,        // 默认安全属性
                0,             // 默认堆栈大小
				(LPTHREAD_START_ROUTINE)info.callback, // 线程函数
                &info,         // 参数传递
                0,             // 默认创建标志
                nullptr);      // 线程 ID

            if (info.none1 != nullptr) {
                if (join) {
                    WaitForSingleObject(info.none1, INFINITE); // 等待线程结束
                    CloseHandle(info.none1); // 关闭句柄
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
