#include "../include/myCalls.hpp"
#include "../include/mFutex.hpp"
#include <string>
#define CHILD_NAME "./bin/child"
#define FILE_NAME "out.txt"
#define SHMNAME "shmFile2"

int main(){

    pid_t pid = getpid();
    std::cout << "This is process with pid: " << pid << std::endl;

    int mappedfile = mshm_open(SHMNAME);
    ftruncate(mappedfile, sizeof(float));

    int shmid = mshmget(4096);
    int* shared = (int*)mshmat(shmid);
    *shared = 0;

    std::string strSHMID(std::to_string(shmid));

    pid = createProcess();
    
    if(pid == 0){

        execute(CHILD_NAME, FILE_NAME, SHMNAME, strSHMID.c_str());

    }
    else{

        std::cout << "This is parent process with pid: " << getpid() << std::endl;
        float* number = (float*)mmapFD(sizeof(float), PROT_READ | PROT_WRITE, mappedfile);
        float num;
        while(std::cin >> num){
            *number = num;
            *shared = 5;
            futex_wake(shared);
            futex_wait(shared, 4);
        }
        *shared = 3;
        futex_wake(shared);
    }

    closeFD(mappedfile);
    return 0;
}