#ifndef __COMMON_H_INCLUDED__
#define __COMMON_H_INCLUDED__

#include "./Jvm_thread.hpp"
#include "./class_file.hpp"
#include "./execution_engine.hpp"
#include "./instructions.hpp"
#include "./method_area.hpp"

extern vector<Instruction> instructions;
extern ClassFile classFile;
extern MethodArea methodArea;
extern ExecutionEngine executionEngine;
extern JavaVirtualMachineThread jvmThread;
extern string projectPath;

#endif
