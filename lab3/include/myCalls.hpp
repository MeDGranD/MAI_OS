#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

void closeFD(int);
pid_t createProcess();
int openFile(const char*);
void execute(const char*, const char*, const char*, const char*);
void* mmapFD(int, int, int);
void* mshmat(int);
int mshmget(int);
int mshm_open(const char*);