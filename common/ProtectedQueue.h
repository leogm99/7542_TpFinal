#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <utility>
#include "Exception.h"

template<typename T>
class ProtectedQueue{
private:
    std::queue<T> q;
    std::mutex queueMutex;
public:
    ProtectedQueue() {}

    ProtectedQueue(const ProtectedQueue& other) = delete;
    ProtectedQueue& operator=(const ProtectedQueue& other) = delete;

    ProtectedQueue(ProtectedQueue &&other)
    : q(std::move(other.q)) {
    }

    ProtectedQueue &operator=(ProtectedQueue &&other)   {
        if (this == &other) {
            return *this;
        }
        q = std::move(other.q);
        return *this;
    }

    T pop() {
        std::unique_lock<std::mutex> lock1(queueMutex);
        // si la q esta vacia no popeo nada
        if (q.empty()) {
            throw Exception("Queue empty exception\n");
        }
        T elem = std::move(q.front());
        q.pop(); // bye bye
        return elem;
    }

    void push(T queueElement) {
        std::unique_lock<std::mutex> lock1(queueMutex);
        q.push(std::move(queueElement));
    }

    void clear() {
        std::unique_lock<std::mutex> lock1(queueMutex);
        std::queue<T> empty;
        std::swap(q, empty);
    }
};

#endif
