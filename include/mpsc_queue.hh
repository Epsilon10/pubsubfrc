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
        
        val = std::move(queue.front());
        queue.pop();
    }

    template<typename U>
    void push(U&& val) {
        auto const is_empty = [&]{
            auto const lock = std::unique_lock(mutex);
            auto const res = queue.empty();

            queue.push(std::forward<U>(val));

            return res;
        }();

        if (is_empty) cond_var.notify_one();
    }

    private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond_var;
};