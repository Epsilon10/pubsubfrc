#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

template<typename T>
class MpscQueue {
    public:
    MpscQueue() = default;
    MpscQueue(MpscQueue&&) = delete;

    void wait_and_pop(T& val) {
        std::unique_lock<std::mutex> lock(mutex);

        cond_var.wait(lock,
            [this]{ return queue.size() > 0; });
        
        val = queue.front();
        queue.pop();
    }

    void push(T const& val) {
        std::unique_lock<std::mutex> lock(mutex);
        auto const was_empty = queue.empty();
        queue.push(val);

        lock.unlock();

        if (was_empty)
            cond_var.notify_one();
    }

    private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond_var;
};