#ifndef ATTRIBUTE_INFO_H_INCLUDED
#define ATTRIBUTE_INFO_H_INCLUDED

#include <cstdint>
#include <fstream>
#include <iostream>

using namespace std;

struct AttributeInfo;
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
  uint8_t* code;
  uint16_t exceptionTableLength;
  ExceptionHandler* exceptionTable;
  uint16_t attributesCount;
  AttributeInfo* attributes;
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
  ClassInfo* classes;
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
  LineNumber* lineNumberTable;
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
  LocalVariable* localVariableTable;
} LocalVariableTableAttribute;

struct AttributeInfo {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  union {
    ConstantValueAttribute constantValue;
    CodeAttribute code;
    ExceptionsAttribute exceptions;
    InnerClassesAttribute innerClasses;
    SourceFileAttribute sourceFile;
    LineNumberTableAttribute lineNumberTable;
    LocalVariableTableAttribute localVariableTable;
  };
  vector<uint8_t> info;
};

#endif
