#ifndef __CPINFO_H_INCLUDED__
#define __CPINFO_H_INCLUDED__
#include <vector>

#include "../include/class_file.hpp"

typedef struct {
  uint16_t name_index;
} ConstantClassInfo;

typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} ConstantFieldrefInfo;

typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} ConstantMethodrefInfo;

typedef struct {
  uint16_t class_index;
  uint16_t name_and_type_index;
} ConstantInterfaceMethodrefInfo;

typedef struct {
  uint16_t string_index;
} ConstantStringInfo;

typedef struct {
  uint32_t bytes;
} ConstantIntegerInfo;

typedef struct {
  uint32_t bytes;
} ConstantFloatInfo;

typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} ConstantLongInfo;

typedef struct {
  uint32_t high_bytes;
  uint32_t low_bytes;
} ConstantDoubleInfo;

typedef struct {
  uint16_t name_index;
  uint16_t descriptor_index;
} ConstantNameAndTypeInfo;

typedef struct {
  uint16_t length;
  uint8_t *bytes;
} ConstantUTF8Info;

typedef struct {
  uint8_t reference_kind;
  uint16_t reference_index;
} ConstantMethodHandleInfo;

typedef struct {
  uint16_t descriptor_index;
} ConstantMethodTypeInfo;

typedef struct {
  uint16_t bootstrap_method_attr_index;
  uint16_t name_and_type_index;
} ConstantInvokeDynamicInfo;

typedef struct {
} LargeNumeric;
#endif
