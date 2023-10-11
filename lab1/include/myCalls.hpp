#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>

void closeFD(int);
void dup2FD(int, int);
void pipeFD(int*);
pid_t createProcess();
int openFile(const char*);
void execute(const char*, const char*);