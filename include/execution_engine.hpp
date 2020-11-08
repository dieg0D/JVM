#ifndef EXECUTION_ENGINE_H_INCLUDED
#define EXECUTION_ENGINE_H_INCLUDED

#include <string>

#include "./class_file.hpp"
#include "./method_area.hpp"

typedef struct {
  string mainClassFileName;
  MethodInfo mainMethod;
} ExecutionEngine;

void findMainMethod();
void execute();

#endif
