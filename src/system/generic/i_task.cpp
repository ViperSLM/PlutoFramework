/*
  Pluto Framework
  Copyright (C) 2023-2025 ViperSLM

  3-Clause BSD License

  Redistribution and use in source and binary forms,
  with or without modification, are permitted provided
  that the following conditions are met:

  1. Redistributions of source code must retain the above
     copyright notice, this list of conditions and the
     following disclaimer.

  2. Redistributions in binary form must reproduce the
     above copyright notice, this list of conditions
     and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names
     of its contributors may be used to endorse or promote
     products derived from this software without specific
     prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
