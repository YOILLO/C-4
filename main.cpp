#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

#include "myVector.h"
#include "myMatrix.h"

#include <chrono>

int main() {
    const size_t SIZE = 10000;
    
    std::vector<int> v1(SIZE, 0), v2(SIZE, 0);
    v1[100] = 5;
    v2[100] = 10;
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = standardVectorAddition(v1, v2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> stdDuration = end - start;
    
    std::cout << "Standard vector addition time: " << stdDuration.count() << " seconds\n";

    MyVector<int> My1(SIZE), My2(SIZE);
    My1.set(100, 5);
    My2.set(100, 10);

    start = std::chrono::high_resolution_clock::now();
    auto result2 = add(My1, My2);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> MyDuration = end - start;

    std::cout << "My vector addition time: " << MyDuration.count() << " seconds\n";
    return 0;
}
