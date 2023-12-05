#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <iostream>

int futex(int*, int, int, const struct timespec*,
          int*, int);
void futex_wait(int*, int);
void futex_wake(int*);