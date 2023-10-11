#include "../include/myCalls.hpp"

void closeFD(int fd){
    if(close(fd) == -1){
        std::cerr << "Error: failed closing fd - " << fd << std::endl;
        exit(-1);
    }
}

void dup2FD(int oldfd, int newfd){
    if(dup2(oldfd, newfd) == -1){
        std::cerr << "Error: failed dup2 to this fds - " 
                  << oldfd << '\t' << newfd << std::endl;
        exit(-1);
    }
}

void pipeFD(int* fd){
    if(pipe(fd) == -1){
        std::cerr << "Error: failed creating pipe" << std::endl;
        exit(-1);
    }
}

pid_t createProcess(){
    pid_t pid = fork();
    if(pid == -1){
        std::cerr << "Error: failed creating child process" << std::endl;
        exit(-1);
    }
    return pid;
}

int openFile(const char* str){
    int file = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(file == -1){
        std::cerr << "Error: failed openin file with name - " << str << std::endl;
        exit(-1);
    }
    return file;
}

void execute(const char* str1, const char* str2){
    if(execl(str1, str1, str2, NULL) == -1){
            std::cerr << "Error: failed execute child programm" << std::endl;
            exit(-1);
    }
}