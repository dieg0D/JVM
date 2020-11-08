#ifndef JAVA_VIRTUAL_MACHINE_THREAD_H_INCLUDED
#define JAVA_VIRTUAL_MACHINE_THREAD_H_INCLUDED

#include <stack>

#include "./frame.hpp"

using namespace std;

typedef struct {
  stack<Frame> javaVirtualMachineStack;
  uint32_t pc = 0;
} JavaVirtualMachineThread;

void pushToJVMStack(Frame frame);

void popFromJVMStack();

void incrementPcBy(uint32_t increment);

Frame getCurrentFrame();

bool isJVMStackEmpty();

stack<Frame> getJVMStack();

#endif
