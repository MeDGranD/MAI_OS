#include "../include/myCalls.hpp"
#define CHILD_NAME "./bin/child"
#define FILE_NAME "out.txt"

int main(){

    pid_t pid = getpid();
    std::cout << "This is process with pid: " << pid << std::endl;

    int fd1[2];
    int fd2[2];
    pipeFD(fd1);
    pipeFD(fd2);

    int write1 = fd1[1]; int write2 = fd2[1];
    int read1 = fd1[0]; int read2 = fd2[0];

    pid = createProcess();

    if(pid == 0){
        closeFD(write1);
        closeFD(read2);
        dup2FD(read1, STDIN_FILENO);
        closeFD(read1);
        closeFD(write2);

        execute(CHILD_NAME, FILE_NAME);

    }
    else{
        closeFD(read1);
        closeFD(write2);

        std::cout << "This is parent process with pid: " << getpid() << std::endl;

        float number;
        while(std::cin >> number){
            dprintf(write1, "%f ", number);
        }

        closeFD(read2);
        closeFD(write1);
    }


    return 0;
}