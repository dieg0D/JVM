#ifndef __CLASSFILE_H_INCLUDED__
#define __CLASSFILE_H_INCLUDED__

#include <iostream>
#include <vector>

#include "./cp_info.hpp"
using namespace std;

typedef unsigned char BYTE;

typedef struct CPInfo {
  uint8_t tag;
  union {
    ConstantClassInfo CONSTANT_Class_info;
    ConstantFieldrefInfo CONSTANT_Fieldref_info;
    ConstantMethodrefInfo CONSTANT_Methodref_info;
    ConstantInterfaceMethodrefInfo CONSTANT_InterfaceMethodref_info;
    ConstantStringInfo CONSTANT_String_info;
    ConstantIntegerInfo CONSTANT_Integer_info;
    ConstantFloatInfo CONSTANT_Float_info;
    ConstantLongInfo CONSTANT_Long_info;
    ConstantDoubleInfo CONSTANT_Double_info;
    ConstantNameAndTypeInfo CONSTANT_NameAndType_info;
    ConstantUTF8Info CONSTANT_Utf8_info;
    ConstantMethodHandleInfo CONSTANT_MethodHandle_info;
    ConstantMethodTypeInfo CONSTANT_MethodType_info;
    ConstantInvokeDynamicInfo CONSTANT_InvokeDynamic_info;
  };
};

typedef struct InterfaceInfo {};

typedef struct FieldInfo {};

typedef struct MethodInfo {};

typedef struct AttributeInfo {};

typedef struct ClassFile {
  uint32_t magic;
  uint16_t minorVersion;
  uint16_t majorVersion;
  uint16_t constantPoolCount;
  vector<CPInfo> constantPool;
  uint16_t accessFlags;
  uint16_t thisClass;
  uint16_t superClass;
  uint16_t interfacesCount;
  vector<InterfaceInfo> interfaces;
  uint16_t fieldsCount;
  vector<FieldInfo> fields;
  uint16_t methodsCount;
  vector<MethodInfo> methods;
  uint16_t attributesCount;
  AttributeInfo attributes;
};

vector<BYTE> readFile(string filename);

void loadFile(string file);
#endif
