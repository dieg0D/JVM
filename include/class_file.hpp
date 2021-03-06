#ifndef __CLASSFILE_H_INCLUDED__
#define __CLASSFILE_H_INCLUDED__

#include <iostream>
#include <vector>

#include "./attribute_info.hpp"
#include "./cp_info.hpp"
using namespace std;

typedef unsigned char BYTE;

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

typedef struct {
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
    LargeNumeric CONSTANT_LargeNumeric_info;
  };
} CPInfo;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  vector<AttributeInfo> attributes;
  JavaType staticValue;
} FieldInfo;

typedef struct {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  vector<AttributeInfo> attributes;
} MethodInfo;

typedef struct {
  uint32_t magic;
  uint16_t minorVersion;
  uint16_t majorVersion;
  uint16_t constantPoolCount;
  vector<CPInfo> constantPool;
  uint16_t accessFlags;
  uint16_t thisClass;
  uint16_t superClass;
  uint16_t interfacesCount;
  vector<uint16_t> interfaces;
  uint16_t fieldsCount;
  vector<FieldInfo> fields;
  uint16_t methodsCount;
  vector<MethodInfo> methods;
  uint16_t attributesCount;
  vector<AttributeInfo> attributes;
} ClassFile;

vector<BYTE> readFile(string filename);

void loadFile(string file);
#endif
