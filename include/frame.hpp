#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <cstdint>
#include <stack>
#include <vector>

#include "./attribute_info.hpp"
#include "./class_file.hpp"
#include "./cp_info.hpp"

const uint64_t JAVA_NULL = 0;
const uint8_t CAT_NULL = 0;
const uint8_t CAT1 = 1;
const uint8_t CAT2 = 2;

struct Frame;
typedef struct {
  uint8_t tag;
  union {
    uint32_t type_empty;
    uint32_t type_boolean;
    uint32_t type_byte;
    uint32_t type_char;
    uint32_t type_short;
    uint32_t type_int;
    uint32_t type_float;
    uint64_t type_reference;
    uint32_t type_returnAddress;
    uint64_t type_long;
    uint64_t type_double;
  };
} JavaType;

struct Frame {
  MethodInfo method;
  vector<CPInfo> constantPool;
  CodeAttribute codeAttribute;
  stack<JavaType> operandStack;
  vector<JavaType> localVariables;
  stack<Frame>* jvmStack;
  uint32_t localPC = 0;
};

Frame createFrame(vector<CPInfo> constantPool, MethodInfo method);
#endif
