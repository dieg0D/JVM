#include "../include/Jvm_thread.hpp"

#include "../include/common.hpp"

using namespace std;

void pushToJVMStack(Frame frame) {
  jvmThread.javaVirtualMachineStack.push(frame);
}

void popFromJVMStack() { jvmThread.javaVirtualMachineStack.pop(); }

void incrementPcBy(uint32_t increment) { jvmThread.pc += increment; }

Frame* getCurrentFrame() { return (&jvmThread.javaVirtualMachineStack.top()); }

bool isJVMStackEmpty() { return jvmThread.javaVirtualMachineStack.empty(); }

stack<Frame> getJVMStack() { return jvmThread.javaVirtualMachineStack; }
