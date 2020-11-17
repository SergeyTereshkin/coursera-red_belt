#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T>
class Deque
{
public:

    Deque()=default;

    bool Empty() const {
        return pushb.empty() && pushf.empty();
    }

    size_t Size() const {
        return pushf.size() + pushb.size();
    }

    T& operator[](size_t index) {
        if (index < pushf.size()) {
            auto itr = pushf.end() - index - 1;
            return *itr;
        }
        return pushb[index - pushf.size()];
    }

    const T& operator[](size_t index) const {
        if (index <= pushf.size()) {
            auto itr = pushf.end() - index;
            return *itr;
        }
        return pushb[pushb.size() + pushf.size() - index];
    }

    T& At(size_t index) {
        if (index >= pushb.size() + pushf.size()) {
            throw out_of_range("index is greater than the deque's size");
        }
        else if (index < pushf.size()) {
            auto itr = pushf.end() - index - 1;
            return *itr;
        }
        else {
            return pushb[index - pushf.size()];
        }
    }

    const T& At(size_t index) const {
        if (index >= pushb.size() + pushf.size()) {
            throw out_of_range("index is greater than the deque's size");
        }
        else if (index < pushf.size()) {
            auto itr = pushf.end() - index - 1;
            return *itr;
        }
        else {
            return pushb[index - pushf.size()];
        }
    }

    const T& Front() const {
        if (pushf.empty()) {
            return pushb[0];
        }
        return pushf.back();
    }

    T& Front() {
        if (pushf.empty()) {
            return pushb[0];
        }
        return pushf.back();
    }

    const T& Back() const {
        if (pushb.empty()) {
            return pushf[0];
        }
        return pushb.back();
    }

    T& Back() {
        if (pushb.empty()) {
            return pushf[0];
        }
        return pushb.back();
    }

    void PushFront(const T& element) {
        pushf.push_back(element);
    }

    void PushBack(const T& element) {
        pushb.push_back(element);
    }

private:
    vector<T> pushf, pushb;

};
