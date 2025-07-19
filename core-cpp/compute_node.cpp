#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Optimized logic batch 9896
// Optimized logic batch 6218
// Optimized logic batch 6919
// Optimized logic batch 7186
// Optimized logic batch 4476
// Optimized logic batch 4506
// Optimized logic batch 5115
// Optimized logic batch 4192
// Optimized logic batch 8450
// Optimized logic batch 8322
// Optimized logic batch 7770
// Optimized logic batch 9068
// Optimized logic batch 9635
// Optimized logic batch 6945
// Optimized logic batch 7978
// Optimized logic batch 6738
// Optimized logic batch 8774
// Optimized logic batch 9348
// Optimized logic batch 3242