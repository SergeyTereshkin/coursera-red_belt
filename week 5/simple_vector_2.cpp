#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

// Р РµР°Р»РёР·СѓР№С‚Рµ С€Р°Р±Р»РѕРЅ SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        data = nullptr;
        current_size = 0;
        capacity = 0;
    }
    explicit SimpleVector(size_t size) {
        data = new T[size];
        current_size = size;
        capacity = size;
    }
    ~SimpleVector() {
        delete [] data;
    }

    SimpleVector(SimpleVector&& other) :
            data(other.data),
            current_size(other.current_size),
            capacity(other.capacity)
    {
        move(other.begin(), other.end(), begin());
    }


    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {return data;}
    T* end() {return data + current_size;}

    const T* begin() const {return data;}
    const T* end() const {return data + current_size;}

    size_t Size() const {return current_size; }
    size_t Capacity() const {return capacity; }
    void PushBack(const T& value) {
        if (current_size == 0) {
            capacity = 1;
            current_size += 1;
            delete [] data;
            data = new T[1];
            data[0] = value;
        }
        else if (current_size == capacity) {

            auto new_data = new T[current_size];
            for (int i = 0; i < current_size; i++) {
                new_data[i] = data[i];
            }
            capacity *= 2;
            delete[] data;
            data = new T[capacity];
            for (int i = 0; i < current_size; i++) {
                data[i] = new_data[i];
            }
            delete [] new_data;
            data[current_size] = value;
            current_size += 1;
        }
        else {
            data[current_size] = value;
            current_size += 1;
        }

    }

    void PushBack(T&& value) {
        if (current_size == 0) {
            capacity = 1;
            current_size += 1;
            delete [] data;
            data = new T[1];
            data[0] = move(value);
        }
        else if (current_size == capacity) {

            auto new_data = new T[current_size];
            for (int i = 0; i < current_size; i++) {
                new_data[i] = move(data[i]);
            }
            capacity *= 2;
            delete[] data;
            data = new T[capacity];
            for (int i = 0; i < current_size; i++) {
                data[i] = move(new_data[i]);
            }
            delete [] new_data;
            data[current_size] = move(value);
            current_size += 1;
        }
        else {
            data[current_size] = move(value);
            current_size += 1;
        }

    }


private:
    T* data;
    size_t current_size;
    size_t capacity;
};
