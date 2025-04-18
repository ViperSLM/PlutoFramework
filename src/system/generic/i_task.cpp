/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Threaded task class [Generic implementation, uses C++ Standard library]
*/
#include "../../c_task.h"

#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <chrono>

namespace Pluto {
constexpr const int MS_DELAY = 1;

class ThreadedTask::ThreadedTask_Impl {
public:
  ThreadedTask_Impl(ThreadedTask *publicInst) : _publicInst(publicInst), _running(false) {}

  void start(void) {
    _running = true;
    _taskThread = std::thread(&ThreadedTask_Impl::taskLoop, this);
    _requestThread = std::thread(&ThreadedTask_Impl::requestLoop, this);
  }
  void stop(void) {
    _running = false;
    _queueCv.notify_all();
    if(_taskThread.joinable())
      _taskThread.join();

    if(_requestThread.joinable())
      _requestThread.join();
  }
  void request(void) {
    std::lock_guard<std::mutex> lock(_queueMtx);

    // Ensure task queue is empty beforehand
    if(_taskQueue.empty()) {
      _taskQueue.push([this]() { _publicInst->Process(); });
    }
  }
private:
  ThreadedTask *_publicInst;
  std::atomic<bool> _running;
  std::thread _taskThread;
  std::thread _requestThread;
  std::queue<std::function<void(void)>> _taskQueue;
  std::mutex _queueMtx;
  std::condition_variable _queueCv;

  void taskLoop(void) {
    while(_running) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(_queueMtx);
        _queueCv.wait(lock, [this] { return !_taskQueue.empty() || !_running; });

        if(!_running && _taskQueue.empty())
          break;

        task = std::move(_taskQueue.front());
        _taskQueue.pop();
      }

      if(task)
        task();
    }
  }

  void requestLoop(void) {
    auto nextRequestTime = std::chrono::steady_clock::now();
    while(_running) {
      nextRequestTime += std::chrono::milliseconds(MS_DELAY);

      // Don't add tasks too quickly
      std::this_thread::sleep_until(nextRequestTime);
      request();
    }
  }
};
#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
ThreadedTask::ThreadedTask(void) : _impl(new ThreadedTask_Impl(this)) {}
ThreadedTask::~ThreadedTask(void) {
  Stop();
  delete _impl;
  _impl = nullptr;
}
#else
ThreadedTask::ThreadedTask(void) : _impl(PLUTO_PIMPL_CREATE<ThreadedTask_Impl>(this)) {}
ThreadedTask::~ThreadedTask(void) {
  Stop();
  _impl.reset();
}
#endif
void ThreadedTask::Start(void) { _impl->start(); }
void ThreadedTask::Stop(void) { _impl->stop(); }
void ThreadedTask::Request(void) { _impl->request(); }
}
