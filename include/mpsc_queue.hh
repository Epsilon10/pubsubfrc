#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>
#include <atomic>

#include <iostream>
template<typename T>
class MpscQueue {
    public:
    MpscQueue() = default;
    MpscQueue(MpscQueue&&) = delete;

    bool wait_and_pop(T& val, std::atomic<bool>& is_running) {
        std::unique_lock<std::mutex> lock(mutex);

        cond_var.wait(lock,
            [this, &is_running]{ return !queue.empty() || !is_running; });    

        if (!is_running) return false;    

        val = std::move(queue.front());
        queue.pop();
        return true;
    }

    void push(T val) {
        auto const is_empty = [&]{
            auto const lock = std::unique_lock(mutex);
            auto const res = queue.empty();

            queue.push(std::move(val));
            //std::cout << "pushed\n";
            return res;
        }();

        if (is_empty) cond_var.notify_one();
    }

    void update() {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.notify_one();
    }

    private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond_var;
};