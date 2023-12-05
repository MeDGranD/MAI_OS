#include "../include/myFunctions.hpp"

data::data(int* arr, int64_t l, int64_t r, size_t* sz, size_t max): array(arr), left(l), right(r), threadSize(sz), maxSize(max){}

int openFD(const std::string& fileName){
    int file = open(fileName.c_str(), O_RDONLY, 0644);
    if(file == -1){
        std::cerr << "Error : cannot open this file - " << fileName << std::endl;
        exit(-1);
    }
    return file;
}

void dup2FD(const int oldFD, const int newFD){
    if(dup2(oldFD, newFD) == -1){
        std::cerr << "Error : cannot dup2 this fds - " << oldFD << ' ' << newFD << std::endl;
        exit(-1);
    }
}

void closeFD(const int FD){
    if(close(FD) == -1){
        std::cerr << "Error : cannot close this fd - " << FD << std::endl;
        exit(-1);
    }
}

size_t readArray(const int file, int*& array){

    delete[] array;

    int copy = dup(STDIN_FILENO);
    dup2FD(file, STDIN_FILENO);
    closeFD(file);

    size_t returnSize;
    std::cin >> returnSize;
    array = new int[returnSize];
    for(size_t index = 0; index < returnSize; ++index){
        std::cin >> array[index];
    }

    dup2FD(copy, STDIN_FILENO);
    closeFD(copy);
    return returnSize;
}

void* threadFunc(void* args){
    data* msg = static_cast<data*>(args);
    if(*(msg->threadSize) == msg->maxSize || msg->right - msg->left <= 1 ){
        mergeSort(msg->array, msg->left, msg->right);
    }
    else{
        int64_t midle = (msg->left + msg->right) / 2;
        pthread_t threads[2];

        ++*(msg->threadSize);
        pthread_create(&threads[0], NULL, threadFunc, static_cast<void*>(new data(msg->array, msg->left, midle, msg->threadSize, msg->maxSize)));
        pthread_create(&threads[1], NULL, threadFunc, static_cast<void*>(new data(msg->array, midle + 1, msg->right, msg->threadSize, msg->maxSize)));

        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        merge(msg->array, msg->left, midle, msg->right);
    }
    pthread_exit(NULL);
}

void mergeSort(int* array, int64_t left, int64_t right){

    if(left >= right){
        return;
    }
    if(right - left == 1){
        if(array[right] < array[left]){
            std::swap(array[right], array[left]);
        }
        return;
    }

    int64_t midle = (left + right) / 2;
    mergeSort(array, left, midle);
    mergeSort(array, midle + 1, right);
    merge(array, left, midle, right);
}

void merge(int* array, int64_t left, int64_t midle, int64_t right){
    int* temp = new int[right - left + 1];
    int64_t pLeft = left, pRight = midle + 1, index = 0;

    while(pLeft != midle + 1 && pRight != right + 1){
        temp[index] = array[pLeft] > array[pRight] ? array[pRight] : array[pLeft];
        temp[index] == array[pLeft] ? ++pLeft : ++pRight;
        ++index;
    }
    while(pLeft != midle + 1){
        temp[index] = array[pLeft];
        ++index;
        ++pLeft;
    }
    while(pRight != right + 1){
        temp[index] = array[pRight];
        ++index;
        ++pRight;
    }
    index = 0;
    for(; index < right - left + 1; ++index){
        array[left + index] = temp[index];
    }

    delete temp;
}

void sort(int* array, size_t size, size_t threadSize){
    
    pthread_t initThread;
    size_t sz = 1;
    data msg(array, 0, size - 1, &sz, threadSize);
    if(pthread_create(&initThread, NULL, threadFunc, static_cast<void*>(&msg)) != 0){
        std::cerr << "Error : cannot create initThread" << std::endl;
        exit(-1);
    }
    pthread_join(initThread, NULL);
}