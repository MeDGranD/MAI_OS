#include <iostream>

extern "C"{
    int PrimeCount(int, int);
    float Square(float, float);
}

int main(){

    size_t choise;
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

            default:
                std::cout << "unknowned command" << std::endl;
        }
    }

    return 0;
}