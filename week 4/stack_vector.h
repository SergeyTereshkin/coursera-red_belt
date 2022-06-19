#pragma once

#include <stdexcept>
#include <array>
#include <algorithm>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > N) {
            throw invalid_argument("greater than capacity");
        }
        data = {};
        size = a_size;
    }

    T& operator[](size_t index) {
        return data[index];
    }
    const T& operator[](size_t index) const {
        return data[index];
    }

    T* begin() {return data.begin(); }
    T* end() {return data.begin() + size;}
    const T* begin() const {return data.begin(); }
    const T* end() const {return data.begin() + size; }

    size_t Size() const {return size; }
    size_t Capacity() const {return N; }

    void PushBack(const T& value) {
        if (size == N) {
            throw overflow_error("no more space in vector");
        }
        else {
            data[size] = value;
            size += 1;
        }
    }
    T PopBack() {
        if (size == 0) {
            throw underflow_error("no elements in vector");
        }
        else {
            auto elem = data[size - 1];
            size -= 1;
            return elem;
        }
    }

private:
    array<T, N> data;
    size_t size;
};
