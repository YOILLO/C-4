#include <iostream>
#include <unordered_map>
#include <cmath>
#include <stdexcept>

#include <utility>
#include <vector>

template <typename T>
class MyVector {
private:
    std::unordered_map<size_t, T> data;
    size_t size;

public:
    MyVector(size_t size) : size(size) {}

    T get(size_t index) const {
        auto it = data.find(index);
        if (it != data.end()) {
            return it->second;
        }
        return T(0);
    }

    void set(size_t index, const T& value) {
        if (value == T(0)) {
            data.erase(index);
        } else {
            data[index] = value;
        }
    }

    size_t getSize() const { return size; }
    void setSize(size_t _size){
        size = _size;
    }
};

