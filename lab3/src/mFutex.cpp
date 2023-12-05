#include "../include/mFutex.hpp"

int futex(int* uaddr, int futex_op, int val, const struct timespec* timeout,
          int* uaddr2, int val3)
{
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}

void futex_wait(int* futex_addr, int val){
    while(1){
        int fut_res = futex(futex_addr, FUTEX_WAIT, val, NULL, NULL, 0);
        if(fut_res == 0){
            if(*futex_addr == val) return;
        }
        else if (fut_res == -1) {
            if (errno != EAGAIN) {
                std::cerr << "Futex wait error : " << errno << std::endl;
                exit(-1);
            }
        }
        else{
            std::cerr << "Futex wait error : " << errno << std::endl;
            exit(-1);
        }
    }
}

void futex_wake(int* futex_addr){
    while(1){
        int fut_res = futex(futex_addr, FUTEX_WAKE, 1, NULL, NULL, 0);
        if(fut_res < 0){
            std::cerr << "Futex wake error : " << errno << std::endl;
            exit(-1);
        }
        else if(fut_res > 0) return;
    }
}