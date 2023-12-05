#include <iostream>
#include <dlfcn.h>

const char* libs[2] = {"./lib/dynamic/lib1.so", "./lib/dynamic/lib2.so"};

int main(){

    int choiseLib;
    std::cout << "Enter interested lib : ";
    std::cin >> choiseLib;
    if(choiseLib != 1 && choiseLib != 2){
        std::cerr << "incorrect lib number" << std::endl;
        exit(-1);
    }

    --choiseLib;
    void* lib_header = dlopen(libs[choiseLib], RTLD_LAZY);
    if(lib_header == NULL){
        std::cerr << "Cannot load library" << std::endl;
    }

    float (*Square)(float a, float b) = (float (*)(float, float))dlsym(lib_header, "Square");
    int (*PrimeCount)(int a, int b) = (int (*)(int, int))dlsym(lib_header, "PrimeCount");

    if(Square == NULL || PrimeCount == NULL){
        std::cerr << "Cannot load functions" << std::endl;
        exit(-1);
    }

    int choise;
    while(std::cin >> choise){
        switch(choise){
            case(1):
                std::cout << "Enter A and B for function :" << std::endl;
                int a1, b1;
                std::cin >> a1 >> b1;
                std::cout << PrimeCount(a1, b1) << std::endl;
                break;

            case(2):
                std::cout << "Enter A and B for fuctrion : " << std::endl;
                float a2, b2;
                std::cin >> a2 >> b2;
                std::cout << Square(a2, b2) << std::endl;
                break;

            case(0):
                if(dlclose(lib_header) != 0){
                    std::cerr << "Cannot close library" << std::endl;
                    exit(-1);
                }

                choiseLib = 1 - choiseLib;
                
                lib_header = dlopen(libs[choiseLib], RTLD_LAZY);
                if(lib_header == NULL){
                    std::cerr << "Cannot load library" << std::endl;
                }

                Square = (float (*)(float, float))dlsym(lib_header, "Square");
                PrimeCount = (int (*)(int, int))dlsym(lib_header, "PrimeCount");

                if(Square == NULL || PrimeCount == NULL){
                    std::cerr << "Cannot load functions" << std::endl;
                    exit(-1);
                }
                break;

            default:
                std::cout << "unknowned command" << std::endl;
        }
    }

    if(dlclose(lib_header) != 0){
        std::cerr << "Cannot close library" << std::endl;
        exit(-1);
    }

    return 0;
}