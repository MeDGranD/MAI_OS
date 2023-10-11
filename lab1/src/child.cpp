#include "../include/myCalls.hpp"

int main(int argc, char *argv[])
{
    
    std::cout << "This is child process with pid: " << getpid() << std::endl;

    int file = openFile(argv[1]);
    dup2FD(file, STDOUT_FILENO);
    closeFD(file);

    float sum = 0;
    float number;
    while(std::cin >> number){
        sum += number;
    }

    std::cout << sum;

    return 0;
}