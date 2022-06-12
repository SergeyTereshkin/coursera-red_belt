#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!deallocated.empty()) {
            allocated.insert(deallocated.front());
            T* x = deallocated.front();
            deallocated.pop();
            return x;
        }
        T* x = new T;
        allocated.insert(x);
        return x;
    }
    T* TryAllocate() {
        if (!deallocated.empty()) {
            allocated.insert(deallocated.front());
            auto x = deallocated.front();
            deallocated.pop();
            return x;
        }
        return nullptr;
    }

    void Deallocate(T* object) {
        auto itr = allocated.find(object);
        if (itr == end(allocated)) {
            throw invalid_argument("invalid argument");
        }
        deallocated.push(object);
        allocated.erase(itr);
    }

    ~ObjectPool() {
        for (auto item : allocated) {
            delete item;
        };
        while (!deallocated.empty()) {
            auto item = deallocated.front();
            delete item;
            deallocated.pop();
        }
    }

private:
    set<T*> allocated;
    queue<T*> deallocated;
    // Р”РѕР±Р°РІСЊС‚Рµ СЃСЋРґР° РїРѕР»СЏ
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
