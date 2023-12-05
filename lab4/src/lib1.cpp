#include "../include/lib.hpp"

extern "C"{

    int PrimeCount(int a, int b){
        size_t count = 0;
        for(size_t i = a; i <= b; ++i){
            bool flag = true;
            for(size_t j = 2; j < i; ++j){
                if(i % j == 0) flag = false;
            }
            if(flag) ++count;
        }
        return count;
    }

    float Square(float a, float b){
        return a * b;
    }

}