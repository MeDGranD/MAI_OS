#include "../include/myFunctions.hpp"
#include <chrono>

int main(int argc, char** argv){
    size_t size;
    int file = openFD("test.txt");
    int* array;

    size_t threadSize;
    std::cout << "Enter amount of threads to use : ";
    std::cin >> threadSize;

    auto begin = std::chrono::high_resolution_clock::now();
    sort(array, size = readArray(file, array), threadSize);
    auto end = std::chrono::high_resolution_clock::now();

    /*for(size_t index = 0; index < size; ++index){
        std::cout << array[index] << ' ';
    }
    std::cout << std::endl;*/
    std::cout << "Time passed = " << (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()/1000 << "[s]" << std::endl;

    delete[] array;

    return 0;
}