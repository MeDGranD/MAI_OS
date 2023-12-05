#include "../include/lib.hpp"

bool prime[10000];

extern "C"{

    void initPrime(){
        prime[0] == 1;
        for(size_t i = 2; i <= 10000; ++i){
            if(prime[i] == 0){
                for(size_t j = i * 2; j <= 10000; j += i){
                    prime[j] = 1;
                }
            }
        }
    }

    int PrimeCount(int a, int b){
        if(prime[0] == 0){
            initPrime();
        }
        size_t counter = 0;
        for(size_t i = a; i <= b; ++i){
            if(!prime[i]) ++counter;
        }
        return counter;
    }

    float Square(float a, float b){
        return a * b / 2;
    }

}