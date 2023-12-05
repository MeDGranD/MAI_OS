#include "../include/myCalls.hpp"

void closeFD(int fd){
    if(close(fd) == -1){
        std::cerr << "Error: failed closing fd - " << fd << std::endl;
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
    int file = open(str, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(file == -1){
        std::cerr << "Error: failed openin file with name - " << str << std::endl;
        exit(-1);
    }
    return file;
}

void execute(const char* str1, const char* str2, const char* str3, const char* str4){
    if(execl(str1, str1, str2, str3, str4, NULL) == -1){
            std::cerr << "Error: failed execute child programm" << std::endl;
            exit(-1);
    }
}

void* mmapFD(int len, int prot, int fd){
    void* temp = mmap(NULL, len, prot, MAP_SHARED, fd, 0);
    if(temp == MAP_FAILED){
        std::cerr << "Error: failed to map file - " << fd << " " << errno << std::endl;
        exit(-1);
    }
    return temp;
}

int mshmget(int size){
    int res = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
    if(res == -1){
        std::cerr << "shmget error : " << errno << std::endl;
        exit(-1);
    }
    return res;
}

void* mshmat(int shmid){
    void* res = shmat(shmid, NULL, 0);
    if(res == ((void*)-1)){
        std::cerr << "shmat error : " << errno << std::endl;
        exit(-1);
    }
    return res;
}

int mshm_open(const char* name){
    int res = shm_open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if(res < 0){
        std::cerr << "shm_open error : " << errno << std::endl;
    }
    return res;
}