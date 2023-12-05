#include "../include/myCalls.hpp"
#include "../include/mFutex.hpp"

int* shared;
float sum = 0;

void* threadfunc(void* args){
  futex_wait(shared, 3);
  std::cout << sum;
  exit(1);
}

int main(int argc, char *argv[])
{

    std::cout << "This is child process with pid: " << getpid() << std::endl;

    int file = openFile(argv[1]);
    dup2(file, STDOUT_FILENO);
    closeFD(file);

    int mappedfile = mshm_open(argv[2]);
    ftruncate(mappedfile, sizeof(float));

    shared = (int*)mshmat(std::stoi(argv[3]));

    pthread_t exit_thread;
    pthread_create(&exit_thread, NULL, threadfunc, NULL);

    float* number = (float*)mmapFD(sizeof(float), PROT_READ | PROT_WRITE, mappedfile);

    while(1){
      futex_wait(shared, 5);
      sum += *number;
      *shared = 4;
      futex_wake(shared);
    }

    return 0;
}