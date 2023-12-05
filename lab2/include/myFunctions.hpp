#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>

struct data{
    data(int*, int64_t, int64_t, size_t*, size_t);

    int* array;
    int64_t left;
    int64_t right;
    size_t* threadSize;
    size_t maxSize;
};



int openFD(const std::string&);
void dup2FD(const int, const int);
void closeFD(const int);
size_t readArray(const int, int*&);

void* threadFunc(void*);
void sort(int*, size_t, size_t);
void merge(int*, int64_t, int64_t, int64_t);
void mergeSort(int*, int64_t, int64_t);