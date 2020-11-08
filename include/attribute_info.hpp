#ifndef ATTRIBUTE_INFO_H_INCLUDED
#define ATTRIBUTE_INFO_H_INCLUDED

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "./class_file.hpp"

using namespace std;

typedef struct {
  uint16_t constantValueIndex;
} ConstantValueAttribute;

typedef struct {
  uint16_t startPC;
  uint16_t endPC;
  uint16_t handlerPC;
  uint16_t catchType;
} ExceptionHandler;

typedef struct {
  uint16_t maxStack;
  uint16_t maxLocals;
  uint32_t codeLength;
  vector<uint8_t> code;
  uint16_t exceptionTableLength;
  ExceptionHandler exceptionTable;
  uint16_t attributesCount;
  AttributeInfo attributes;
} CodeAttribute;

typedef struct {
  uint16_t numberOfExceptions;
  uint16_t execeptionIndexTable;
} ExceptionsAttribute;

typedef struct {
  uint16_t innerClassInfoIndex;
  uint16_t outerClassInfoIndex;
  uint16_t innerNameIndex;
  uint16_t innerClassAccessFlags;
} ClassInfo;

typedef struct {
  uint16_t numberOfClasses;
  vector<ClassInfo> classes;
} InnerClassesAttribute;

typedef struct {
  uint16_t sourcefileIndex;
} SourceFileAttribute;

typedef struct {
  uint16_t startPC;
  uint16_t lineNumber;
} LineNumber;

typedef struct {
  uint16_t lineNumberTableLength;
  vector<LineNumber> lineNumberTable;
} LineNumberTableAttribute;

typedef struct {
  uint16_t startPC;
  uint16_t length;
  uint16_t nameIndex;
  uint16_t descriptorIndex;
  uint16_t index;
} LocalVariable;

typedef struct {
  uint16_t localVariableTableLength;
  vector<LocalVariable> localVariableTable;
} LocalVariableTableAttribute;

#endif
