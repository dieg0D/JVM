#include "../include/instructions.hpp"

#include <string.h>

#include <array>
#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/class_loader.hpp"
#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/frame.hpp"

using namespace std;

vector<JavaType>* buildMultiAnewArray(vector<int> dimensions, int index,
                                      char type) {
  vector<JavaType>* array = new vector<JavaType>(dimensions[index]);

  if (index == 0) {
    for (int i = 0; i < dimensions[index]; i++) {
      if (type == 'B' || type == 'C' || type == 'F' || type == 'I' ||
          type == 'S' || type == 'Z' || type == ';') {
        array->at(i).tag = CAT1;
        array->at(i).type_int = 0;
      } else if (type == 'D' || type == 'J') {
        array->at(i).tag = CAT1;
        array->at(i).type_int = 0;
      } else {
        cout << "Tipo desconhecido: " << type << endl;
        exit(0);
      }
    }
    return array;
  }

  for (int i = 0; i < dimensions[index]; i++) {
    array->at(i).tag = CAT1;
    array->at(i).type_reference =
        (uint64_t)buildMultiAnewArray(dimensions, index - 1, type);
  }

  return array;
}

map<string, JavaType>* initializeFields() {
  map<string, JavaType>* object = new map<string, JavaType>;
  ClassFile objectClass = classFile;

  do {
    for (uint16_t i = 0; i < classFile.fieldsCount; i++) {
      string fieldName = getCPInfoFirst(classFile.constantPool,
                                        classFile.fields[i].name_index - 1);

      string fieldDescriptor = getCPInfoFirst(
          classFile.constantPool, classFile.fields[i].descriptor_index - 1);
      JavaType fieldContent;

      if (fieldDescriptor.compare("C") == 0) {
        fieldContent.tag = CAT1;
        fieldContent.type_char = 0;
      } else if (fieldDescriptor.compare("I") == 0) {
        fieldContent.tag = CAT1;
        fieldContent.type_int = 0;
      } else if (fieldDescriptor.compare("F") == 0) {
        fieldContent.tag = CAT1;
        fieldContent.type_float = 0;
      } else if (fieldDescriptor.compare("D") == 0) {
        fieldContent.tag = CAT2;
        fieldContent.type_double = 0;
      } else if (fieldDescriptor.compare("J") == 0) {
        fieldContent.tag = CAT2;
        fieldContent.type_long = 0;
      } else if (fieldDescriptor.compare("Z") == 0) {
        fieldContent.tag = CAT1;
        fieldContent.type_boolean = 0;
      } else if (fieldDescriptor[0] == 'L') {
        fieldContent.tag = CAT1;
        fieldContent.type_reference = JAVA_NULL;
      } else if (fieldDescriptor[0] == '[') {
        fieldContent.tag = CAT1;
        fieldContent.type_reference = JAVA_NULL;
      } else {
        printf("Criacao de fields: tipo do descritor nao reconhecido: %s\n",
               fieldDescriptor.c_str());
        exit(0);
      }

      object->insert(make_pair(fieldName, fieldContent));
    }

    string superClassName =
        getCPInfoFirst(classFile.constantPool, classFile.superClass - 1);
    classFile = getClassFile(superClassName);
  } while (classFile.superClass != 0);

  // Warning!
  // cout << "Warning: os atributos de interfaces ainda nao estao sendo
  // buscados!" << endl;

  JavaType thisClass;
  string thisClassName =
      getCPInfoFirst(classFile.constantPool, classFile.thisClass - 1);
  thisClass.type_reference = (uint64_t) new string(thisClassName);
  object->insert(make_pair("<this_class>", thisClass));
  return object;
}

void initialize_instruction() {
  Instruction instruction;
  // Constantes
  instruction.mnemonic = "nop";
  instruction.opcode = 0x00;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aconst_null";
  instruction.opcode = 0x01;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_m1";
  instruction.opcode = 0x02;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_0";
  instruction.opcode = 0x03;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_1";
  instruction.opcode = 0x04;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_2";
  instruction.opcode = 0x05;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_3";
  instruction.opcode = 0x06;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_4";
  instruction.opcode = 0x07;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iconst_5";
  instruction.opcode = 0x08;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lconst_0";
  instruction.opcode = 0x09;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lconst_1";
  instruction.opcode = 0x0a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fconst_0";
  instruction.opcode = 0x0b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fconst_1";
  instruction.opcode = 0x0c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fconst_2";
  instruction.opcode = 0x0d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dconst_0";
  instruction.opcode = 0x0e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dconst_1";
  instruction.opcode = 0x0f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "bipush";
  instruction.opcode = 0x10;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "sipush";
  instruction.opcode = 0x11;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ldc";
  instruction.opcode = 0x12;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "ldc_w";
  instruction.opcode = 0x13;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ldc2_w";
  instruction.opcode = 0x14;
  instruction.length = 2;
  instructions.push_back(instruction);

  // Loads
  instruction.mnemonic = "iload";
  instruction.opcode = 0x15;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "lload";
  instruction.opcode = 0x16;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "fload";
  instruction.opcode = 0x17;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "dload";
  instruction.opcode = 0x18;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "aload";
  instruction.opcode = 0x19;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "iload_0";
  instruction.opcode = 0x1a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iload_1";
  instruction.opcode = 0x1b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iload_2";
  instruction.opcode = 0x1c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iload_3";
  instruction.opcode = 0x1d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lload_0";
  instruction.opcode = 0x1e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lload_1";
  instruction.opcode = 0x1f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lload_2";
  instruction.opcode = 0x20;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lload_3";
  instruction.opcode = 0x21;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fload_0";
  instruction.opcode = 0x22;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fload_1";
  instruction.opcode = 0x23;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fload_2";
  instruction.opcode = 0x24;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fload_3";
  instruction.opcode = 0x25;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dload_0";
  instruction.opcode = 0x26;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dload_1";
  instruction.opcode = 0x27;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dload_2";
  instruction.opcode = 0x28;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dload_3";
  instruction.opcode = 0x29;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aload_0";
  instruction.opcode = 0x2a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aload_1";
  instruction.opcode = 0x2b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aload_2";
  instruction.opcode = 0x2c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aload_3";
  instruction.opcode = 0x2d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iaload";
  instruction.opcode = 0x2e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "laload";
  instruction.opcode = 0x2f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "faload";
  instruction.opcode = 0x30;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "daload";
  instruction.opcode = 0x31;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aaload";
  instruction.opcode = 0x32;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "baload";
  instruction.opcode = 0x33;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "caload";
  instruction.opcode = 0x34;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "saload";
  instruction.opcode = 0x35;
  instruction.length = 0;
  instructions.push_back(instruction);

  // Stores
  instruction.mnemonic = "istore";
  instruction.opcode = 0x36;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "lstore";
  instruction.opcode = 0x37;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "fstore";
  instruction.opcode = 0x38;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "dstore";
  instruction.opcode = 0x39;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "astore";
  instruction.opcode = 0x3a;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "istore_0";
  instruction.opcode = 0x3b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "istore_1";
  instruction.opcode = 0x3c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "istore_2";
  instruction.opcode = 0x3d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "istore_3";
  instruction.opcode = 0x3e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lstore_0";
  instruction.opcode = 0x3f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lstore_1";
  instruction.opcode = 0x40;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lstore_2";
  instruction.opcode = 0x41;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lstore_3";
  instruction.opcode = 0x42;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fstore_0";
  instruction.opcode = 0x43;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fstore_1";
  instruction.opcode = 0x44;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fstore_2";
  instruction.opcode = 0x45;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fstore_3";
  instruction.opcode = 0x46;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dstore_0";
  instruction.opcode = 0x47;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dstore_1";
  instruction.opcode = 0x48;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dstore_2";
  instruction.opcode = 0x49;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dstore_3";
  instruction.opcode = 0x4a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "astore_0";
  instruction.opcode = 0x4b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "astore_1";
  instruction.opcode = 0x4c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "astore_2";
  instruction.opcode = 0x4d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "astore_3";
  instruction.opcode = 0x4e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iastore";
  instruction.opcode = 0x4f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lastore";
  instruction.opcode = 0x50;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fastore";
  instruction.opcode = 0x51;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dastore";
  instruction.opcode = 0x52;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "aastore";
  instruction.opcode = 0x53;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "bastore";
  instruction.opcode = 0x54;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "castore";
  instruction.opcode = 0x55;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "sastore";
  instruction.opcode = 0x56;
  instruction.length = 0;
  instructions.push_back(instruction);

  // Stack
  instruction.mnemonic = "pop";
  instruction.opcode = 0x57;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "pop2";
  instruction.opcode = 0x58;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup";
  instruction.opcode = 0x59;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup_x1";
  instruction.opcode = 0x5a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup_x2";
  instruction.opcode = 0x5b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup2";
  instruction.opcode = 0x5c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup2_x1";
  instruction.opcode = 0x5d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dup2_x2";
  instruction.opcode = 0x5e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "swap";
  instruction.opcode = 0x5f;
  instruction.length = 0;
  instructions.push_back(instruction);

  // Math
  instruction.mnemonic = "iadd";
  instruction.opcode = 0x60;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ladd";
  instruction.opcode = 0x61;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fadd";
  instruction.opcode = 0x62;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dadd";
  instruction.opcode = 0x63;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "isub";
  instruction.opcode = 0x64;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lsub";
  instruction.opcode = 0x65;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fsub";
  instruction.opcode = 0x66;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dsub";
  instruction.opcode = 0x67;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "imul";
  instruction.opcode = 0x68;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lmul";
  instruction.opcode = 0x69;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fmul";
  instruction.opcode = 0x6a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dmul";
  instruction.opcode = 0x6b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "idiv";
  instruction.opcode = 0x6c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ldivOp";
  instruction.opcode = 0x6d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fdiv";
  instruction.opcode = 0x6e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ddiv";
  instruction.opcode = 0x6f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "irem";
  instruction.opcode = 0x70;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lrem";
  instruction.opcode = 0x71;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "frem";
  instruction.opcode = 0x72;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dremOp";
  instruction.opcode = 0x73;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ineg";
  instruction.opcode = 0x74;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lneg";
  instruction.opcode = 0x75;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fneg";
  instruction.opcode = 0x76;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dneg";
  instruction.opcode = 0x77;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ishl";
  instruction.opcode = 0x78;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lshl";
  instruction.opcode = 0x79;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ishr";
  instruction.opcode = 0x7a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lshr";
  instruction.opcode = 0x7b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iushr";
  instruction.opcode = 0x7c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lushr";
  instruction.opcode = 0x7d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iand";
  instruction.opcode = 0x7e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "land";
  instruction.opcode = 0x7f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ior";
  instruction.opcode = 0x80;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lor";
  instruction.opcode = 0x81;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ixor";
  instruction.opcode = 0x82;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lxor";
  instruction.opcode = 0x83;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "iinc";
  instruction.opcode = 0x84;
  instruction.length = 2;
  instructions.push_back(instruction);

  // Conversions
  instruction.mnemonic = "i2l";
  instruction.opcode = 0x85;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "i2f";
  instruction.opcode = 0x86;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "i2d";
  instruction.opcode = 0x87;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "l2i";
  instruction.opcode = 0x88;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "l2f";
  instruction.opcode = 0x89;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "l2d";
  instruction.opcode = 0x8a;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "f2i";
  instruction.opcode = 0x8b;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "f2l";
  instruction.opcode = 0x8c;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "f2d";
  instruction.opcode = 0x8d;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "d2i";
  instruction.opcode = 0x8e;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "d2l";
  instruction.opcode = 0x8f;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "d2f";
  instruction.opcode = 0x90;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "i2b";
  instruction.opcode = 0x91;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "i2c";
  instruction.opcode = 0x92;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "i2s";
  instruction.opcode = 0x93;
  instruction.length = 0;
  instructions.push_back(instruction);

  // Comparisons
  instruction.mnemonic = "lcmp";
  instruction.opcode = 0x94;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fcmpl";
  instruction.opcode = 0x95;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "fcmpg";
  instruction.opcode = 0x96;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dcmpl";
  instruction.opcode = 0x97;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dcmpg";
  instruction.opcode = 0x98;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifeq";
  instruction.opcode = 0x99;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifne";
  instruction.opcode = 0x9a;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "iflt";
  instruction.opcode = 0x9b;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifge";
  instruction.opcode = 0x9c;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifgt";
  instruction.opcode = 0x9d;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifle";
  instruction.opcode = 0x9e;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmpeq";
  instruction.opcode = 0x9f;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmpne";
  instruction.opcode = 0xa0;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmplt";
  instruction.opcode = 0xa1;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmpge";
  instruction.opcode = 0xa2;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmpgt";
  instruction.opcode = 0xa3;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_icmple";
  instruction.opcode = 0xa4;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_acmpeq";
  instruction.opcode = 0xa5;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "if_acmpne";
  instruction.opcode = 0xa6;
  instruction.length = 2;
  instructions.push_back(instruction);

  // Control
  instruction.mnemonic = "gotoOp";
  instruction.opcode = 0xa7;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "jsr";
  instruction.opcode = 0xa8;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ret";
  instruction.opcode = 0xa9;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "tableswitch";
  instruction.opcode = 0xaa;
  instruction.length = 16;
  instructions.push_back(instruction);

  instruction.mnemonic = "lookupswitch";
  instruction.opcode = 0xab;
  instruction.length = 8;
  instructions.push_back(instruction);

  instruction.mnemonic = "ireturn";
  instruction.opcode = 0xac;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "lreturn";
  instruction.opcode = 0xad;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "freturn";
  instruction.opcode = 0xae;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "dreturn";
  instruction.opcode = 0xaf;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "areturn ";
  instruction.opcode = 0xb0;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "returnOp";
  instruction.opcode = 0xb1;
  instruction.length = 0;
  instructions.push_back(instruction);

  // References
  instruction.mnemonic = "getstatic";
  instruction.opcode = 0xb2;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "putstatic";
  instruction.opcode = 0xb3;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "getfield";
  instruction.opcode = 0xb4;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "putfield";
  instruction.opcode = 0xb5;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "invokevirtual";
  instruction.opcode = 0xb6;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "invokespecial";
  instruction.opcode = 0xb7;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "invokestatic";
  instruction.opcode = 0xb8;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "invokeinterface";
  instruction.opcode = 0xb9;
  instruction.length = 4;
  instructions.push_back(instruction);

  instruction.mnemonic = "invokedynamic";
  instruction.opcode = 0xba;
  instruction.length = 4;
  instructions.push_back(instruction);

  instruction.mnemonic = "newOp";
  instruction.opcode = 0xbb;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "newarray";
  instruction.opcode = 0xbc;
  instruction.length = 1;
  instructions.push_back(instruction);

  instruction.mnemonic = "anewarray";
  instruction.opcode = 0xbd;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "arraylength";
  instruction.opcode = 0xbe;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "athrow";
  instruction.opcode = 0xbf;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "checkcast";
  instruction.opcode = 0xc0;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "instanceof";
  instruction.opcode = 0xc1;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "monitorenter";
  instruction.opcode = 0xc2;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "monitorexit";
  instruction.opcode = 0xc3;
  instruction.length = 0;
  instructions.push_back(instruction);

  // Extended
  instruction.mnemonic = "wide";
  instruction.opcode = 0xc4;
  instruction.length = 5;
  instructions.push_back(instruction);

  instruction.mnemonic = "multianewarray";
  instruction.opcode = 0xc5;
  instruction.length = 3;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifnull";
  instruction.opcode = 0xc6;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "ifnonnull";
  instruction.opcode = 0xc7;
  instruction.length = 2;
  instructions.push_back(instruction);

  instruction.mnemonic = "goto_w";
  instruction.opcode = 0xc8;
  instruction.length = 4;
  instructions.push_back(instruction);

  instruction.mnemonic = "jsr_w";
  instruction.opcode = 0xc9;
  instruction.length = 4;
  instructions.push_back(instruction);

  // newarray type codes
  instruction.mnemonic = "T_BOOLEAN";
  instruction.opcode = 4;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_CHAR";
  instruction.opcode = 5;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_FLOAT";
  instruction.opcode = 6;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_DOUBLE";
  instruction.opcode = 7;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_BYTE";
  instruction.opcode = 8;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_SHORT";
  instruction.opcode = 9;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_INT";
  instruction.opcode = 10;
  instruction.length = 0;
  instructions.push_back(instruction);

  instruction.mnemonic = "T_LONG";
  instruction.opcode = 11;
  instruction.length = 0;
  instructions.push_back(instruction);

  return;
}

pair<string, int> get_mnemonic(uint8_t opcode) {
  string mnemonic = "";
  int length = -1;
  for (auto i : instructions) {
    if (i.opcode == opcode) {
      mnemonic = i.mnemonic;
      length = i.length;
      break;
    } else {
    }
  }
  return make_pair(mnemonic, length);
};

uint32_t func_exec(Frame* frame) {
  uint8_t* bytecode = frame->codeAttribute.code;
  uint8_t opcode = bytecode[frame->localPC];

  cout << frame->localPC << " " << get_mnemonic(opcode).first << endl;
  switch (opcode) {
    // Constants
    case nop: {
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aconst_null: {
      JavaType null;
      null.tag = CAT_NULL;
      null.type_reference = JAVA_NULL;
      frame->operandStack.push(null);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_m1: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)(-1);
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_0: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)0;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_1: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)1;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_2: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)2;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_3: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)3;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_4: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)4;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iconst_5: {
      JavaType constant;
      constant.tag = CAT1;
      constant.type_int = (int32_t)5;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lconst_0: {
      JavaType constant;
      constant.tag = CAT2;
      constant.type_long = (int64_t)0;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lconst_1: {
      JavaType constant;
      constant.tag = CAT2;
      constant.type_long = (int64_t)1;
      frame->operandStack.push(constant);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fconst_0: {
      JavaType value;
      float fconst = 0.0f;

      memcpy(&value.type_float, &fconst, sizeof(uint32_t));
      value.tag = CAT1;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fconst_1: {
      JavaType value;
      float fconst = 1.0f;

      memcpy(&value.type_float, &fconst, sizeof(uint32_t));
      value.tag = CAT1;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fconst_2: {
      JavaType value;
      float fconst = 2.0f;

      memcpy(&value.type_float, &fconst, sizeof(uint32_t));
      value.tag = CAT1;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dconst_0: {
      JavaType value;
      double dconst = 0.0;

      memcpy(&value.type_double, &dconst, sizeof(uint64_t));
      value.tag = CAT2;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dconst_1: {
      JavaType value;
      double dconst = 1.0;

      memcpy(&value.type_double, &dconst, sizeof(uint64_t));
      value.tag = CAT2;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case bipush: {
      uint8_t byte = bytecode[frame->localPC + 1];
      JavaType value;

      value.type_int = (int32_t)((int8_t)byte);
      value.tag = CAT1;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case sipush: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      JavaType value;

      value.type_short = (int32_t)((((int16_t)(int8_t)byte1 << 8)) | byte2);
      value.tag = CAT1;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ldc: {
      uint8_t byte = bytecode[frame->localPC + 1];
      uint8_t index = byte;
      JavaType value;
      stringstream stream;

      CPInfo cpInfo = frame->constantPool[index - 1];
      stream << (unsigned int)(unsigned char)(cpInfo.tag);
      string tag_info = stream.str();
      int tag = stoi(tag_info);

      switch (tag) {
        case 8:
          value.type_reference = (uint64_t) new string(
              getCPInfoFirst(frame->constantPool,
                             cpInfo.CONSTANT_String_info.string_index - 1));
          value.tag = CAT1;
          frame->operandStack.push(value);
          break;
        case 3:
          value.type_int = cpInfo.CONSTANT_Integer_info.bytes;
          value.tag = CAT1;
          frame->operandStack.push(value);
          break;
        case 4:
          value.type_float = cpInfo.CONSTANT_Float_info.bytes;
          value.tag = CAT1;
          frame->operandStack.push(value);
          break;
        default:
          cout << "A funcao ldc encontrou um tipo indefinido: %d" << cpInfo.tag
               << endl;
          exit(0);
          break;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ldc_w: {
      printf("Instrucao ldc_wFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ldc2_w: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      uint16_t index = ((uint16_t)byte1 << 8) | byte2;

      JavaType value;
      stringstream stream;

      CPInfo cpInfo = frame->constantPool[index - 1];
      stream << (unsigned int)(unsigned char)(cpInfo.tag);
      string tag_info = stream.str();
      int tag = stoi(tag_info);

      switch (tag) {
        case 5:
          value.type_long =
              ((uint64_t)cpInfo.CONSTANT_Long_info.high_bytes << 32) |
              cpInfo.CONSTANT_Long_info.low_bytes;
          value.tag = CAT2;
          frame->operandStack.push(value);
          break;
        case 6:
          value.type_double =
              ((uint64_t)cpInfo.CONSTANT_Double_info.high_bytes << 32) |
              cpInfo.CONSTANT_Double_info.low_bytes;
          value.tag = CAT2;
          frame->operandStack.push(value);
          break;
        default:
          printf("A funcao ldc2_w encontrou um tipo indefinido: %d\n",
                 cpInfo.tag);
          exit(0);
          break;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Loads
    case iload: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value = frame->localVariables[index];
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lload: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value = frame->localVariables[index];
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fload: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value = frame->localVariables[index];
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dload: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value = frame->localVariables[index];
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aload: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value = frame->localVariables[index];
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iload_0: {
      JavaType value;
      value.type_int = frame->localVariables[0].type_int;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iload_1: {
      JavaType value;
      value.type_int = frame->localVariables[1].type_int;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iload_2: {
      JavaType value;
      value.type_int = frame->localVariables[2].type_int;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iload_3: {
      JavaType value;
      value.type_int = frame->localVariables[3].type_int;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lload_0: {
      JavaType value;
      value.type_long = frame->localVariables[0].type_long;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lload_1: {
      JavaType value;
      value.type_long = frame->localVariables[1].type_long;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lload_2: {
      JavaType value;
      value.type_long = frame->localVariables[2].type_long;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lload_3: {
      JavaType value;
      value.type_long = frame->localVariables[3].type_long;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fload_0: {
      JavaType value;
      value.type_float = frame->localVariables[0].type_float;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fload_1: {
      JavaType value;
      value.type_float = frame->localVariables[1].type_float;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fload_2: {
      JavaType value;
      value.type_float = frame->localVariables[2].type_float;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fload_3: {
      JavaType value;
      value.type_float = frame->localVariables[3].type_float;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dload_0: {
      JavaType value;
      value.type_double = frame->localVariables[0].type_double;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dload_1: {
      JavaType value;
      value.type_double = frame->localVariables[1].type_double;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dload_2: {
      JavaType value;
      value.type_double = frame->localVariables[2].type_double;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dload_3: {
      JavaType value;
      value.type_double = frame->localVariables[3].type_double;
      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aload_0: {
      JavaType objectref;

      objectref.type_reference = frame->localVariables[0].type_reference;
      frame->operandStack.push(objectref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aload_1: {
      JavaType objectref;

      objectref.type_reference = frame->localVariables[1].type_reference;
      frame->operandStack.push(objectref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aload_2: {
      JavaType objectref;

      objectref.type_reference = frame->localVariables[2].type_reference;
      frame->operandStack.push(objectref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aload_3: {
      JavaType objectref;

      objectref.type_reference = frame->localVariables[3].type_reference;
      frame->operandStack.push(objectref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iaload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case laload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case faload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case daload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aaload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case baload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case caload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case saload: {
      JavaType index;
      JavaType arrayref;

      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      JavaType value = array->at((int32_t)index.type_int);

      frame->operandStack.push(value);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Stores
    case istore: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value.tag = CAT1;
      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      frame->localVariables[index] = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    case lstore: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value.tag = CAT2;
      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      frame->localVariables[index] = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fstore: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value.tag = CAT1;
      value.type_float = frame->operandStack.top().type_float;
      frame->operandStack.pop();
      frame->localVariables[index] = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dstore: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value.tag = CAT2;
      value.type_double = frame->operandStack.top().type_double;
      frame->operandStack.pop();
      frame->localVariables[index] = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case astore: {
      uint8_t index = bytecode[frame->localPC + 1];
      JavaType value;

      value.tag = CAT1;
      value.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->localVariables[index] = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case istore_0: {
      frame->localVariables[0] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case istore_1: {
      frame->localVariables[1] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case istore_2: {
      frame->localVariables[2] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case istore_3: {
      frame->localVariables[3] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lstore_0: {
      frame->localVariables[0] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lstore_1: {
      frame->localVariables[1] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lstore_2: {
      frame->localVariables[2] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lstore_3: {
      frame->localVariables[3] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fstore_0: {
      frame->localVariables[0] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fstore_1: {
      frame->localVariables[1] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fstore_2: {
      frame->localVariables[2] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fstore_3: {
      frame->localVariables[3] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dstore_0: {
      frame->localVariables[0] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dstore_1: {
      frame->localVariables[1] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dstore_2: {
      frame->localVariables[2] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dstore_3: {
      frame->localVariables[3] = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case astore_0: {
      JavaType objectref;

      objectref.tag = CAT1;
      objectref.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->localVariables[0] = objectref;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case astore_1: {
      JavaType objectref;

      objectref.tag = CAT1;
      objectref.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->localVariables[1] = objectref;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case astore_2: {
      JavaType objectref;

      objectref.tag = CAT1;
      objectref.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->localVariables[2] = objectref;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case astore_3: {
      JavaType objectref;

      objectref.tag = CAT1;
      objectref.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->localVariables[3] = objectref;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iastore: {
      JavaType value;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      cout << "to aqui ?" << value.type_int << " " << index.type_int << endl;
      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = value;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lastore: {
      JavaType value;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fastore: {
      JavaType value;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dastore: {
      JavaType value;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case aastore: {
      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType index = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = value;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case bastore: {
      JavaType value;
      JavaType byteValue;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      byteValue.tag = CAT1;
      byteValue.type_byte = (int8_t)value.type_int;

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = byteValue;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case castore: {
      JavaType value;
      JavaType charValue;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      charValue.tag = CAT1;
      charValue.type_byte = (int8_t)value.type_int;

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = charValue;

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case sastore: {
      JavaType value;
      JavaType shortValue;
      JavaType index;
      JavaType arrayref;

      value = frame->operandStack.top();
      frame->operandStack.pop();
      index = frame->operandStack.top();
      frame->operandStack.pop();
      arrayref = frame->operandStack.top();
      frame->operandStack.pop();

      shortValue.tag = CAT1;
      shortValue.type_byte = (int16_t)value.type_int;

      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;
      array->at((int32_t)index.type_int) = shortValue;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Stack
    case pop: {
      frame->operandStack.pop();
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case pop2: {
      printf("Instrucao pop2Function nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup: {
      JavaType duplicated = frame->operandStack.top();
      frame->operandStack.pop();
      frame->operandStack.push(duplicated);
      frame->operandStack.push(duplicated);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup_x1: {
      printf("Instrucao dup_x1Function nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup_x2: {
      printf("Instrucao dup_x2Function nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup2: {
      if (frame->operandStack.top().tag == CAT1) {
        JavaType value1 = frame->operandStack.top();
        frame->operandStack.pop();
        JavaType value2 = frame->operandStack.top();
        frame->operandStack.pop();

        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
      } else if (frame->operandStack.top().tag == CAT2) {
        JavaType value = frame->operandStack.top();
        frame->operandStack.pop();
        frame->operandStack.push(value);
        frame->operandStack.push(value);
      } else {
        cout << "Erro no dup2: categoria indefinida!: "
             << frame->operandStack.top().tag << endl;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup2_x1: {
      printf("Instrucao dup2_x1Function nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dup2_x2: {
      printf("Instrucao dup2_x2Function nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case swapOp: {
      printf("Instrucao swapFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Math
    case iadd: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_int = (int32_t)value1.type_int + (int32_t)value2.type_int;

      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ladd: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long + (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fadd: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;
      float fresult;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      fresult = fvalue1 + fvalue2;

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dadd: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;
      double dresult;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      dresult = dvalue1 + dvalue2;

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case isub: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int =
          (int32_t)((int32_t)value1.type_int - (int32_t)value2.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lsub: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long - (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fsub: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;
      float fresult;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      fresult = fvalue1 - fvalue2;

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dsub: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;
      double dresult;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      dresult = dvalue1 - dvalue2;

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case imul: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int =
          (int32_t)((int32_t)value1.type_int * (int32_t)value2.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lmul: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long * (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fmul: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;
      float fresult;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      fresult = fvalue1 * fvalue2;

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dmul: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;
      double dresult;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      dresult = dvalue1 * dvalue2;

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case idiv: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int =
          (int32_t)((int32_t)value1.type_int / (int32_t)value2.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ldivOp: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long / (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fdiv: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;
      float fresult;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      fresult = fvalue1 / fvalue2;

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ddiv: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;
      double dresult;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      dresult = dvalue1 / dvalue2;

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case irem: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int = (int32_t)(
          (int32_t)value1.type_int -
          (int32_t)((int32_t)value1.type_int / (int32_t)value2.type_int) *
              (int32_t)value2.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lrem: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      result.type_long = (int64_t)(
          (int64_t)value1.type_long -
          (int64_t)((int64_t)value1.type_long / (int64_t)value2.type_long) *
              (int64_t)value2.type_long);
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case frem: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;
      float fresult;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      fresult = fmod(fvalue1, fvalue2);

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dremOp: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;
      double dresult;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      dresult = fmod(dvalue1, dvalue2);

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ineg: {
      JavaType value;
      JavaType result;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int = (int32_t)(-(int32_t)value.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lneg: {
      JavaType value;
      JavaType result;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      result.type_long = (int64_t)(-(int64_t)value.type_long);
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fneg: {
      JavaType value;
      JavaType result;
      float fvalue;
      float fresult;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      memcpy(&fvalue, &value.type_int, sizeof(float));

      fresult = -fvalue;

      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dneg: {
      JavaType value;
      JavaType result;
      double dvalue;
      double dresult;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      memcpy(&dvalue, &value.type_long, sizeof(double));

      dresult = -dvalue;

      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ishl: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int = (int32_t)((int32_t)value1.type_int
                                  << ((int32_t)value2.type_int & 0x0000001F));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lshl: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      result.type_long = (int64_t)((int64_t)value1.type_long
                                   << ((int32_t)value2.type_int & 0x0000003F));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ishr: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int = (int32_t)((int32_t)value1.type_int >>
                                  ((int32_t)value2.type_int & 0x0000001F));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lshr: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      result.type_long = (int64_t)((int64_t)value1.type_long >>
                                   ((int32_t)value2.type_int & 0x0000003F));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iushr: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      result.type_int = (uint32_t)((uint32_t)value1.type_int >>
                                   ((int32_t)value2.type_int & 0x0000001F));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lushr: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      result.type_long = (uint64_t)((uint64_t)value1.type_long >>
                                    ((int32_t)value2.type_int & 0x0000003F));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iand: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_int = (int32_t)value1.type_int & (int32_t)value2.type_int;
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case land: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long & (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ior: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_int = (int32_t)value1.type_int | (int32_t)value2.type_int;
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lor: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long | (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ixor: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_int = (int32_t)value1.type_int ^ (int32_t)value2.type_int;
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lxor: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_long = (int64_t)value1.type_long ^ (int64_t)value2.type_long;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iinc: {
      uint8_t* bytecode = frame->codeAttribute.code;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];

      uint16_t index = byte1;
      int32_t constValue = (int32_t)((int8_t)byte2);
      frame->localVariables[index].type_int =
          (int32_t)frame->localVariables[index].type_int + constValue;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Conversions
    case i2l: {
      JavaType value;
      JavaType result;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_long = (int64_t)((int32_t)value.type_int);
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case i2f: {
      JavaType value;
      JavaType result;
      float fresult;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      fresult = (float)((int32_t)value.type_int);
      memcpy(&(result.type_float), &fresult, sizeof(float));

      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case i2d: {
      JavaType value;
      JavaType result;
      double dresult;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      dresult = (double)((int32_t)value.type_int);
      memcpy(&(result.type_float), &dresult, sizeof(double));

      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case l2i: {
      JavaType value;
      JavaType result;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      result.type_int = int32_t((int64_t)value.type_long);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case l2f: {
      JavaType value;
      JavaType result;
      float fresult;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      fresult = (float)((int64_t)value.type_long);
      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case l2d: {
      JavaType value;
      JavaType result;
      double dresult;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      dresult = (double)((int64_t)value.type_long);
      memcpy(&(result.type_float), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case f2i: {
      JavaType value;
      JavaType result;
      float fvalue;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue, &(value.type_int), sizeof(float));
      result.type_int = (int32_t)fvalue;
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case f2l: {
      JavaType value;
      JavaType result;
      float fvalue;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue, &(value.type_int), sizeof(float));
      result.type_long = (int64_t)fvalue;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case f2d: {
      JavaType value;
      JavaType result;
      float fvalue;
      double dresult;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue, &(value.type_int), sizeof(float));
      dresult = (double)fvalue;
      memcpy(&(result.type_double), &dresult, sizeof(double));
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case d2i: {
      JavaType value;
      JavaType result;
      double dvalue;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue, &(value.type_long), sizeof(double));
      result.type_int = (int32_t)dvalue;
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case d2l: {
      JavaType value;
      JavaType result;
      double dvalue;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue, &(value.type_long), sizeof(double));
      result.type_long = (int64_t)dvalue;
      result.tag = CAT2;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case d2f: {
      JavaType value;
      JavaType result;
      double dvalue;
      float fresult;

      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue, &(value.type_long), sizeof(double));
      fresult = (float)dvalue;
      memcpy(&(result.type_float), &fresult, sizeof(float));
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case i2b: {
      JavaType value;
      JavaType result;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_byte = (int8_t)((int32_t)value.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case i2c: {
      JavaType value;
      JavaType result;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_char = (uint8_t)((int32_t)value.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case i2s: {
      JavaType value;
      JavaType result;

      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      result.type_short = (int16_t)((int32_t)value.type_int);
      result.tag = CAT1;
      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Comparisons
    case lcmp: {
      JavaType value1;
      JavaType value2;
      JavaType result;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      if (value1.type_long > value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      } else if (value1.type_long == value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
      } else if (value1.type_long < value2.type_long) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      }

      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fcmpl: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      if (fvalue1 > fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      } else if (fvalue1 == fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
      } else if (fvalue1 < fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      } else {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      }

      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case fcmpg: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      float fvalue1;
      float fvalue2;

      value2.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      value1.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();

      memcpy(&fvalue1, &value1.type_int, sizeof(float));
      memcpy(&fvalue2, &value2.type_int, sizeof(float));

      if (fvalue1 > fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      } else if (fvalue1 == fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
      } else if (fvalue1 < fvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      } else {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      }

      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dcmpl: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      if (dvalue1 > dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      } else if (dvalue1 == dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
      } else if (dvalue1 < dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      } else {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      }

      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dcmpg: {
      JavaType value1;
      JavaType value2;
      JavaType result;
      double dvalue1;
      double dvalue2;

      value2.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      value1.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();

      memcpy(&dvalue1, &value1.type_long, sizeof(double));
      memcpy(&dvalue2, &value2.type_long, sizeof(double));

      if (dvalue1 > dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      } else if (dvalue1 == dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)0;
      } else if (dvalue1 < dvalue2) {
        result.tag = CAT1;
        result.type_int = (int32_t)-1;
      } else {
        result.tag = CAT1;
        result.type_int = (int32_t)1;
      }

      frame->operandStack.push(result);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifeq: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int == 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifne: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int != 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case iflt: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int < 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifge: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int >= 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifgt: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int > 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifle: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value.type_int <= 0) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmpeq: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int == (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmpne: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int != (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmplt: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int < (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmpge: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int >= (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmpgt: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int > (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_icmple: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[++frame->localPC];
      uint8_t byte2 = bytecode[++frame->localPC];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value2 = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType value1 = frame->operandStack.top();
      frame->operandStack.pop();

      if ((int32_t)value1.type_int <= (int32_t)value2.type_int) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_acmpeq: {
      printf("Instrucao if_acmpeqFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case if_acmpne: {
      printf("Instrucao if_acmpneFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Control
    case gotoOp: {
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      frame->localPC = baseAddress + branchOffset;
      // frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case jsr: {
      printf("Instrucao jsrFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ret: {
      printf("Instrucao retFunction nao implementada ainda!\n");
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case tableswitch: {
      uint32_t baseAddress = frame->localPC;
      JavaType key = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC = frame->localPC + 1;
      while ((frame->localPC) % 4 != 0) {
        frame->localPC = frame->localPC + 1;
      }

      uint8_t defaultByte1 = bytecode[frame->localPC + 1];
      uint8_t defaultByte2 = bytecode[frame->localPC + 2];
      uint8_t defaultByte3 = bytecode[frame->localPC + 3];
      uint8_t defaultByte4 = bytecode[frame->localPC + 4];
      int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) |
                             (defaultByte3 << 8) | defaultByte4;

      uint8_t lowByte1 = bytecode[frame->localPC + 5];
      uint8_t lowByte2 = bytecode[frame->localPC + 6];
      uint8_t lowByte3 = bytecode[frame->localPC + 7];
      uint8_t lowByte4 = bytecode[frame->localPC + 8];
      int32_t low =
          (lowByte1 << 24) | (lowByte2 << 16) | (lowByte3 << 8) | lowByte4;

      uint8_t highByte1 = bytecode[frame->localPC + 9];
      uint8_t highByte2 = bytecode[frame->localPC + 10];
      uint8_t highByte3 = bytecode[frame->localPC + 11];
      uint8_t highByte4 = bytecode[frame->localPC + 12];
      int32_t high =
          (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

      for (int match = low; match <= high; match++) {
        uint8_t offsetByte1 = bytecode[frame->localPC + 13];
        uint8_t offsetByte2 = bytecode[frame->localPC + 14];
        uint8_t offsetByte3 = bytecode[frame->localPC + 15];
        uint8_t offsetByte4 = bytecode[frame->localPC + 16];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) |
                         (offsetByte3 << 8) | offsetByte4;

        if ((int32_t)key.type_int == match) {
          frame->localPC = baseAddress + offset;
          return frame->localPC;
        }
      }
      frame->localPC = baseAddress + defaultValue;
      return frame->localPC;
    }
    case lookupswitch: {
      uint32_t baseAddress = frame->localPC;
      JavaType key = frame->operandStack.top();
      frame->operandStack.pop();

      frame->localPC++;
      while ((frame->localPC) % 4 != 0) {
        frame->localPC++;
      }

      uint8_t defaultByte1 = bytecode[frame->localPC + 1];
      uint8_t defaultByte2 = bytecode[frame->localPC + 2];
      uint8_t defaultByte3 = bytecode[frame->localPC + 3];
      uint8_t defaultByte4 = bytecode[frame->localPC + 4];
      int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) |
                             (defaultByte3 << 8) | defaultByte4;

      uint8_t npairs1 = bytecode[frame->localPC + 5];
      uint8_t npairs2 = bytecode[frame->localPC + 6];
      uint8_t npairs3 = bytecode[frame->localPC + 7];
      uint8_t npairs4 = bytecode[frame->localPC + 8];
      int32_t npairs =
          (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

      for (int i = 0; i < npairs; i++) {
        uint8_t matchByte1 = bytecode[frame->localPC + 9];
        uint8_t matchByte2 = bytecode[frame->localPC + 10];
        uint8_t matchByte3 = bytecode[frame->localPC + 11];
        uint8_t matchByte4 = bytecode[frame->localPC + 12];
        int32_t match = (matchByte1 << 24) | (matchByte2 << 16) |
                        (matchByte3 << 8) | matchByte4;

        uint8_t offsetByte1 = bytecode[frame->localPC + 13];
        uint8_t offsetByte2 = bytecode[frame->localPC + 14];
        uint8_t offsetByte3 = bytecode[frame->localPC + 15];
        uint8_t offsetByte4 = bytecode[frame->localPC + 16];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) |
                         (offsetByte3 << 8) | offsetByte4;

        if ((int32_t)key.type_int == match) {
          frame->localPC = baseAddress + offset;
          return frame->localPC;
        }
      }
      frame->localPC = baseAddress + defaultValue;
      return frame->localPC;
    }
    case ireturn: {
      JavaType value;

      value.tag = CAT1;
      value.type_int = frame->operandStack.top().type_int;
      frame->operandStack.pop();
      frame->jvmStack->pop();

      Frame* invoker = &(frame->jvmStack->top());
      invoker->operandStack.push(value);
      return invoker->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case lreturn: {
      JavaType value;

      value.tag = CAT2;
      value.type_long = frame->operandStack.top().type_long;
      frame->operandStack.pop();
      frame->jvmStack->pop();

      Frame* invoker = &(frame->jvmStack->top());
      invoker->operandStack.push(value);
      return invoker->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case freturn: {
      JavaType value;

      value.tag = CAT1;
      value.type_float = frame->operandStack.top().type_float;
      frame->operandStack.pop();
      frame->jvmStack->pop();

      Frame* invoker = &(frame->jvmStack->top());
      invoker->operandStack.push(value);
      return invoker->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case dreturn: {
      JavaType value;

      value.tag = CAT2;
      value.type_double = frame->operandStack.top().type_double;
      frame->operandStack.pop();
      frame->jvmStack->pop();

      Frame* invoker = &(frame->jvmStack->top());
      invoker->operandStack.push(value);
      return invoker->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case areturn: {
      JavaType value;

      value.tag = CAT1;
      value.type_reference = frame->operandStack.top().type_reference;
      frame->operandStack.pop();
      frame->jvmStack->pop();

      Frame* invoker = &(frame->jvmStack->top());
      invoker->operandStack.push(value);
      return invoker->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case returnOp: {
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // References
    case getstatic: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];

      uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      string className = getCPInfoFirst(frame->constantPool, index - 1);

      string fieldName = getCPInfoSecond(frame->constantPool, index - 1).second;

      string fieldDescriptor =
          getCPInfoSecond(frame->constantPool, index - 1).first;

      if (className.compare("java/lang/System") == 0) {
        frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
        return frame->localPC;  // incrementa jvthread.pc em 1
      } else {
        if (!isClassInitialized(className)) {
          setClassAsInitialized(className);

          loadClassFile(className + ".class");
          loadSuperClasses();
          ClassFile classFile = getClassFile(className);
          MethodInfo method;

          bool foundClinit = false;
          for (int i = 0; i < classFile.methodsCount && !foundClinit; i++) {
            method = classFile.methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);

            string classDescriptor =
                getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

            if (name.compare("<clinit>") == 0 &&
                classDescriptor.compare("()V") == 0) {
              foundClinit = true;
            }
          }

          if (foundClinit) {
            Frame clinitMethodFrame =
                createFrame(classFile.constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            return clinitMethodFrame.localPC;
          }
        }

        ClassFile classFile = getClassFile(className);
        FieldInfo field;
        bool foundField = false;

        for (int i = 0; i < classFile.fieldsCount && !foundField; i++) {
          field = classFile.fields[i];
          uint16_t nameIndex = field.name_index;
          uint16_t descriptorIndex = field.descriptor_index;
          string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);

          string descriptor =
              getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

          if (name.compare(fieldName) == 0 &&
              descriptor.compare(fieldDescriptor) == 0) {
            foundField = true;
          }
        }

        if (!foundField) {
          printf("getstatic: o field especificado nao pode ser resolvido!");
          exit(0);
        }

        if (fieldDescriptor.compare("C") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor.compare("I") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor.compare("F") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor.compare("D") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor.compare("J") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor.compare("Z") == 0) {
          frame->operandStack.push(field.staticValue);
        } else if (fieldDescriptor[0] == '[') {
          frame->operandStack.push(field.staticValue);
        } else {
          printf("getstatic: tipo do descritor nao reconhecido: %s\n",
                 fieldDescriptor.c_str());
          exit(0);
        }
      }

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case putstatic: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];

      uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      string className = getCPInfoFirst(frame->constantPool, index - 1);

      string fieldName = getCPInfoSecond(frame->constantPool, index - 1).second;

      string fieldDescriptor =
          getCPInfoSecond(frame->constantPool, index - 1).first;

      if (!isClassInitialized(className)) {
        setClassAsInitialized(className);

        loadClassFile(className + ".class");
        loadSuperClasses();

        ClassFile classFile = getClassFile(className);

        MethodInfo method;

        bool foundClinit = false;
        for (int i = 0; i < classFile.methodsCount && !foundClinit; i++) {
          method = classFile.methods[i];
          uint16_t nameIndex = method.name_index;
          uint16_t descriptorIndex = method.descriptor_index;
          string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);
          string classDescriptor =
              getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);
          if (name.compare("<clinit>") == 0 &&
              classDescriptor.compare("()V") == 0) {
            foundClinit = true;
          }
        }

        if (foundClinit) {
          Frame clinitMethodFrame =
              createFrame(classFile.constantPool, method, frame->jvmStack);
          frame->jvmStack->push(clinitMethodFrame);
          return clinitMethodFrame.localPC;
        }
      }

      ClassFile classFile = getClassFile(className);

      FieldInfo field;
      bool foundField = false;

      for (int i = 0; i < classFile.fieldsCount && !foundField; i++) {
        field = classFile.fields[i];
        uint16_t nameIndex = field.name_index;
        uint16_t descriptorIndex = field.descriptor_index;
        string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);
        string descriptor =
            getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);
        if (name.compare(fieldName) == 0 &&
            descriptor.compare(fieldDescriptor) == 0) {
          foundField = true;
        }
      }

      if (!foundField) {
        printf(
            "putstatic: o field especificado nao pode ser resolvido! Deve "
            "estar em "
            "uma superclasse ou superinterface! Falta implementar!\n");
        exit(0);
      }

      cout << "to no roleeeee " << endl;

      if (fieldDescriptor.compare("C") == 0) {
        field.staticValue.tag = CAT1;
        field.staticValue.type_char = frame->operandStack.top().type_char;
        frame->operandStack.pop();
      } else if (fieldDescriptor.compare("I") == 0) {
        field.staticValue.tag = CAT1;
        field.staticValue.type_int = frame->operandStack.top().type_int;
        frame->operandStack.pop();
      } else if (fieldDescriptor.compare("F") == 0) {
        field.staticValue.tag = CAT1;
        field.staticValue.type_float = frame->operandStack.top().type_float;
        frame->operandStack.pop();
      } else if (fieldDescriptor.compare("D") == 0) {
        field.staticValue.tag = CAT2;
        field.staticValue.type_double = frame->operandStack.top().type_double;
        frame->operandStack.pop();
      } else if (fieldDescriptor.compare("J") == 0) {
        field.staticValue.tag = CAT2;
        field.staticValue.type_long = frame->operandStack.top().type_long;
        frame->operandStack.pop();
      } else if (fieldDescriptor.compare("Z") == 0) {
        field.staticValue.tag = CAT1;
        field.staticValue.type_boolean = frame->operandStack.top().type_boolean;
        frame->operandStack.pop();
      } else if (fieldDescriptor[0] == '[') {
        field.staticValue.tag = CAT1;
        field.staticValue.type_reference =
            frame->operandStack.top().type_reference;
        frame->operandStack.pop();
      } else {
        printf("putstatic: tipo do descritor nao reconhecido: %s\n",
               fieldDescriptor.c_str());
        exit(0);
      }

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case getfield: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      uint16_t index = ((uint16_t)byte1 << 8) | byte2;

      string className = getCPInfoFirst(frame->constantPool, index - 1);

      string fieldName = getCPInfoSecond(frame->constantPool, index - 1).second;

      string fieldDescriptor =
          getCPInfoSecond(frame->constantPool, index - 1).first;

      JavaType objectref = frame->operandStack.top();
      frame->operandStack.pop();

      map<string, JavaType>* object =
          (map<string, JavaType>*)objectref.type_reference;
      JavaType value = object->at(fieldName);
      frame->operandStack.push(value);

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case putfield: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      uint16_t index = ((uint16_t)byte1 << 8) | byte2;

      string className = getCPInfoFirst(frame->constantPool, index - 1);

      string fieldName = getCPInfoSecond(frame->constantPool, index - 1).second;

      string fieldDescriptor =
          getCPInfoSecond(frame->constantPool, index - 1).first;
      // Falta resolver o field!

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();
      JavaType objectref = frame->operandStack.top();
      frame->operandStack.pop();

      map<string, JavaType>* object =
          (map<string, JavaType>*)objectref.type_reference;
      object->at(fieldName) = value;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case invokevirtual: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];

      uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      string className = getCPInfoFirst(frame->constantPool, index - 1);

      string methodName =
          getCPInfoSecond(frame->constantPool, index - 1).second;

      string descriptor = getCPInfoSecond(frame->constantPool, index - 1).first;

      // Para debug
      // cout << className << " " << methodName << " " << descriptor << endl;

      if (className.compare("java/io/PrintStream") == 0) {
        if (methodName.compare("println") == 0) {
          if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
            string* stringReference =
                (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            cout << *stringReference << endl;
          } else if (descriptor.compare("(C)V") == 0) {
            uint8_t character = frame->operandStack.top().type_char;
            frame->operandStack.pop();
            cout << character << endl;
          } else if (descriptor.compare("(I)V") == 0) {
            int32_t integer = (int32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();
            cout << integer << endl;
          } else if (descriptor.compare("(F)V") == 0) {
            float floatNumber;
            memcpy(&floatNumber, &(frame->operandStack.top().type_float),
                   sizeof(float));
            frame->operandStack.pop();
            cout << floatNumber << endl;
          } else if (descriptor.compare("(D)V") == 0) {
            double doubleNumber;
            memcpy(&doubleNumber, &(frame->operandStack.top().type_double),
                   sizeof(double));
            frame->operandStack.pop();
            cout << doubleNumber << endl;
          } else if (descriptor.compare("(J)V") == 0) {
            int64_t longNumber = (int64_t)frame->operandStack.top().type_long;
            frame->operandStack.pop();
            cout << longNumber << endl;
          } else if (descriptor.compare("(Z)V") == 0) {
            uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();

            if (integer == 1) {
              cout << "true" << endl;
            } else if (integer == 0) {
              cout << "false" << endl;
            } else {
              cout << "Erro no tipo booleano!\\n" << endl;
              exit(0);
            }
          } else if (descriptor.compare("()V") == 0) {
            cout << endl;
          } else {
            cout << "invokevirtualFunction: tipo do descritor nao "
                    "reconhecido : "
                 << descriptor.c_str() << endl;
            exit(0);
          }
        } else if (methodName.compare("print") == 0) {
          if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
            string* stringReference =
                (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            cout << *stringReference;
          } else if (descriptor.compare("(I)V") == 0) {
            int32_t integer = (int32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();
            cout << integer;
          } else if (descriptor.compare("(F)V") == 0) {
            float floatNumber;
            memcpy(&floatNumber, &(frame->operandStack.top().type_float),
                   sizeof(float));
            frame->operandStack.pop();
            cout << floatNumber;
          } else if (descriptor.compare("(D)V") == 0) {
            double doubleNumber;
            memcpy(&doubleNumber, &(frame->operandStack.top().type_double),
                   sizeof(double));
            frame->operandStack.pop();
            cout << doubleNumber;
          } else if (descriptor.compare("(J)V") == 0) {
            int64_t longNumber = (int64_t)frame->operandStack.top().type_long;
            frame->operandStack.pop();
            cout << longNumber;
          } else if (descriptor.compare("(Z)V") == 0) {
            uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();

            if (integer == 1) {
              cout << "true";
            } else if (integer == 0) {
              cout << "false";
            } else {
              cout << "Erro no tipo booleano!";
              exit(0);
            }
          } else if (descriptor.compare("()V") == 0) {
            // Nao faz nada
          } else {
            cout << "invokevirtualFunction: tipo do descritor nao "
                    "reconhecido : "
                 << descriptor.c_str() << endl;
            exit(0);
          }
        } else {
          printf("invokevirtualFunction: falta implementar\n");
          exit(0);
        }
      } else if (className.compare("java/lang/StringBuilder") == 0) {
        if (methodName.compare("append") == 0) {
          if (descriptor.compare(
                  "(Ljava/lang/String;)Ljava/lang/StringBuilder;") == 0) {
            string* str1 = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            string* str2 = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            JavaType objectref;
            objectref.type_reference = (uint64_t) new string(*str2 + *str1);
            objectref.tag = CAT1;
            frame->operandStack.push(objectref);
          } else if (descriptor.compare("(I)Ljava/lang/StringBuilder;") == 0) {
            int32_t integer = (int32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();
            string* str = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            JavaType objectref;
            objectref.type_reference =
                (uint64_t) new string(*str + to_string(integer));
            objectref.tag = CAT1;
            frame->operandStack.push(objectref);
          } else if (descriptor.compare("(J)Ljava/lang/StringBuilder;") == 0) {
            int64_t longNumber = (int64_t)(frame->operandStack.top().type_long);
            frame->operandStack.pop();
            string* str = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            JavaType objectref;
            objectref.type_reference =
                (uint64_t) new string(*str + to_string(longNumber));
            objectref.tag = CAT1;
            frame->operandStack.push(objectref);
          } else if (descriptor.compare("(F)Ljava/lang/StringBuilder;") == 0) {
            uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();
            string* str = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            float floatNumber;
            memcpy(&floatNumber, &integer, sizeof(float));

            JavaType objectref;
            objectref.type_reference =
                (uint64_t) new string(*str + to_string(floatNumber));
            objectref.tag = CAT1;
            frame->operandStack.push(objectref);
          } else if (descriptor.compare("(D)Ljava/lang/StringBuilder;") == 0) {
            uint64_t longNumber =
                (uint64_t)(frame->operandStack.top().type_double);
            frame->operandStack.pop();
            string* str = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            double doubleNumber;
            memcpy(&doubleNumber, &longNumber, sizeof(double));

            JavaType objectref;
            objectref.type_reference =
                (uint64_t) new string(*str + to_string(doubleNumber));
            objectref.tag = CAT1;
            frame->operandStack.push(objectref);
          } else if (descriptor.compare("(Z)Ljava/lang/StringBuilder;") == 0) {
            uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
            frame->operandStack.pop();
            string* str = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();

            JavaType objectref;
            if (integer == 1) {
              objectref.type_reference = (uint64_t) new string(*str + "true");
            } else if (integer == 0) {
              objectref.type_reference = (uint64_t) new string(*str + "false");
            } else {
              cout << "Erro no tipo booleano durante a concatenacao!";
              exit(0);
            }
            frame->operandStack.push(objectref);
            objectref.tag = CAT1;
          } else {
            printf(
                "invokevirtual: StringBuilder: descritor nao reconhecido: "
                "%s\n",
                descriptor.c_str());
            exit(0);
          }
        } else if (methodName.compare("toString") == 0) {
          // Fingindo que estou convertendo em string
        } else {
          printf(
              "invokevirtualFunction: Metodo do StringBuilder nao "
              "reconhecido "
              "%s\n",
              methodName.c_str());
          exit(0);
        }
      } else {
        stack<JavaType> auxstack;
        for (int i = 1; descriptor[i] != ')'; i++) {
          if (descriptor[i] == 'I' || descriptor[i] == 'F') {
          } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
          } else if (descriptor[i] == 'L') {
            while (descriptor[i] != ';') {
              i++;
            }
          } else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
              i++;
            }
            if (descriptor[i] == 'L') {
              while (descriptor[i] != ';') {
                i++;
              }
            }
          } else {
            cout << "Tipo de descritor nao reconhecido na contagem: "
                 << descriptor[i] << endl;
            exit(0);
          }
          auxstack.push(frame->operandStack.top());
          frame->operandStack.pop();
        }

        // ORIENTACAO OBJETOS NAO IMPLEMENTADA AINDA
        bool foundMethod = false;
        MethodInfo method;

        JavaType objectref = frame->operandStack.top();
        frame->operandStack.pop();
        map<string, JavaType>* object =
            (map<string, JavaType>*)objectref.type_reference;

        string* objectClassName =
            (string*)object->at("<this_class>").type_reference;

        ClassFile objectClassFile = getClassFile(*objectClassName);

        for (int i = 0; i < objectClassFile.methodsCount && !foundMethod; i++) {
          method = objectClassFile.methods[i];
          uint16_t nameIndex = method.name_index;
          uint16_t descriptorIndex = method.descriptor_index;
          string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);

          string methodDescriptor =
              getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);
          if (name.compare(methodName) == 0 &&
              methodDescriptor.compare(descriptor) == 0) {
            foundMethod = true;
          }
        }

        // // Caso nao encontre checa as superclasses
        if (!foundMethod) {
          do {
            ClassFile classFile = getClassFile(className);

            for (int i = 0; i < classFile.methodsCount && !foundMethod; i++) {
              method = classFile.methods[i];
              uint16_t nameIndex = method.name_index;
              uint16_t descriptorIndex = method.descriptor_index;
              string name =
                  getCPInfoFirst(classFile.constantPool, nameIndex - 1);

              string methodDescriptor =
                  getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

              if (name.compare(methodName) == 0 &&
                  methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
              }
            }

            if (!foundMethod) {
              if (classFile.superClass == 0) {
                printf(
                    "invokevirutal:  metodo nao foi encontrado em nenhuma "
                    "superclasse!");
                exit(0);
              }

              className = getCPInfoFirst(classFile.constantPool,
                                         classFile.superClass - 1);
            }
          } while (!foundMethod);
        }

        Frame staticMethodFrame =
            createFrame(classFile.constantPool, method, frame->jvmStack);

        int argCnt = 1;
        for (int i = 1; descriptor[i] != ')'; i++) {
          if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
          } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt += 2;
          } else if (descriptor[i] == 'L') {
            while (descriptor[i] != ';') {
              i++;
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
          } else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
              i++;
            }
            if (descriptor[i] == 'L') {
              while (descriptor[i] != ';') {
                i++;
              }
            }
            JavaType arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
          } else {
            cout << "Tipo de descritor nao reconhecido: " << descriptor[i]
                 << endl;
            exit(0);
          }
        }
        staticMethodFrame.localVariables[0] = objectref;

        frame->jvmStack->push(staticMethodFrame);
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case invokespecial: {
      //     MethodArea* methodArea = classLoader->getMethodArea();
      // uint8_t* bytecode = frame->getCode();
      // uint8_t byte1 = bytecode[++frame->localPC];
      // uint8_t byte2 = bytecode[++frame->localPC];

      // uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      // string className =
      //     frame->constantPool[index - 1]->getInfo(frame->constantPool).first;
      // string nameAndType =
      //     frame->constantPool[index -
      //     1]->getInfo(frame->constantPool).second;
      // int j = 0;

      // while (j < nameAndType.size() && nameAndType[j + 1] != ':') {
      //   j++;
      // }
      // string methodName = nameAndType.substr(0, j);
      // string descriptor = nameAndType.substr(j + 3, nameAndType.size());

      // if (className.compare("java/lang/String") == 0) {
      //   if (methodName.compare("<init>") == 0) {
      //     string* stringReference =
      //         (string*)(frame->operandStack.top().type_reference);
      //     frame->operandStack.pop();
      //     string* initStringReference =
      //         (string*)(frame->operandStack.top().type_reference);
      //     frame->operandStack.pop();
      //     *initStringReference = *stringReference;
      //   } else {
      //     printf("invokespecial: metodo da classe string desconhecido: %s\n",
      //            methodName.c_str());
      //     exit(0);
      //   }
      //   return ++frame->localPC;
      // }
      // if (className.compare("java/lang/StringBuilder") == 0) {
      //   if (methodName.compare("<init>") == 0) {
      //     frame->operandStack.pop();
      //   }
      //   return ++frame->localPC;
      // }

      // bool foundMethod = false;
      // vector<CPInfo*> constantPool;
      // MethodInfo* method;
      // do {
      //   ClassFile* classFile = methodArea->getClassFile(className);
      //   constantPool = classFile->getConstantPool();
      //   vector<MethodInfo*> methods = classFile->getMethods();

      //   for (int i = 0; i < classFile->getMethodsCount() && !foundMethod;
      //   i++) {
      //     method = methods[i];
      //     uint16_t nameIndex = method->getNameIndex();
      //     uint16_t descriptorIndex = method->getDescriptorIndex();
      //     string name = constantPool[nameIndex -
      //     1]->getInfo(constantPool).first; string methodDescriptor =
      //         constantPool[descriptorIndex - 1]->getInfo(constantPool).first;
      //     if (name.compare(methodName) == 0 &&
      //         methodDescriptor.compare(descriptor) == 0) {
      //       foundMethod = true;
      //     }
      //   }

      //   if (!foundMethod) {
      //     if (classFile->getSuperClass() == 0) {
      //       printf(
      //           "invokespecial:  metodo nao foi encontrado em nenhuma
      //           superclasse! " "Talvez esteja em uma interface, falta
      //           Implementar!\n");
      //     }
      //     string className = constantPool[classFile->getSuperClass() - 1]
      //                            ->getInfo(constantPool)
      //                            .first;
      //   }
      // } while (!foundMethod);

      // Frame staticMethodFrame(constantPool, method, frame->jvmStack);

      // stack<JavaType> auxstack;

      // for (int i = 1; descriptor[i] != ')'; i++) {
      //   if (descriptor[i] == 'I' || descriptor[i] == 'F') {
      //   } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
      //   } else if (descriptor[i] == 'L') {
      //     while (descriptor[i] != ';') {
      //       i++;
      //     }
      //   } else if (descriptor[i] == '[') {
      //     while (descriptor[i] == '[') {
      //       i++;
      //     }
      //     if (descriptor[i] == 'L') {
      //       while (descriptor[i] != ';') {
      //         i++;
      //       }
      //     }
      //   } else {
      //     cout << "Tipo de descritor nao reconhecido na contagem: " <<
      //     descriptor[i]
      //          << endl;
      //     exit(0);
      //   }
      //   auxstack.push(frame->operandStack.top());
      //   frame->operandStack.pop();
      // }
      // int argCnt = 1;
      // for (int i = 1; descriptor[i] != ')'; i++) {
      //   if (descriptor[i] == 'I' || descriptor[i] == 'F') {
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt += 2;
      //   } else if (descriptor[i] == 'L') {
      //     int j = i;
      //     while (descriptor[i] != ';') {
      //       i++;
      //     }
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else if (descriptor[i] == '[') {
      //     while (descriptor[i] == '[') {
      //       i++;
      //     }
      //     if (descriptor[i] == 'L') {
      //       while (descriptor[i] != ';') {
      //         i++;
      //       }
      //     }
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else {
      //     cout << "Tipo de descritor nao reconhecido: " << descriptor[i] <<
      //     endl; exit(0);
      //   }
      // }
      // JavaType objectref = frame->operandStack.top();
      // frame->operandStack.pop();
      // staticMethodFrame->localVariables[0] = objectref;

      // frame->jvmStack->push(staticMethodFrame);
      // frame->localPC++;
      // return staticMethodFrame->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case invokestatic: {
      //     uint8_t* bytecode = frame->getCode();
      // uint8_t byte1 = bytecode[++frame->localPC];
      // uint8_t byte2 = bytecode[++frame->localPC];
      // uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      // MethodArea* methodArea = classLoader->getMethodArea();

      // string className =
      //     frame->constantPool[index - 1]->getInfo(frame->constantPool).first;
      // string nameAndType =
      //     frame->constantPool[index -
      //     1]->getInfo(frame->constantPool).second;
      // int j = 0;

      // while (j < nameAndType.size() && nameAndType[j + 1] != ':') {
      //   j++;
      // }
      // string methodName = nameAndType.substr(0, j);
      // string descriptor = nameAndType.substr(j + 3, nameAndType.size());

      // if (!methodArea->isClassInitialized(className)) {
      //   methodArea->setClassAsInitialized(className);

      //   ClassFile aux = classLoader->loadClassFile(className + ".class");
      //   classLoader->loadSuperClasses(&aux);
      //   ClassFile* classFile =
      //   classLoader->getClassFromMethodArea(className); vector<CPInfo*>
      //   constantPool = classFile->getConstantPool(); vector<MethodInfo*>
      //   methods = classFile->getMethods(); MethodInfo* method;

      //   bool foundClinit = false;
      //   for (int i = 0; i < classFile->getMethodsCount() && !foundClinit;
      //   i++) {
      //     method = methods[i];
      //     uint16_t nameIndex = method->getNameIndex();
      //     uint16_t descriptorIndex = method->getDescriptorIndex();
      //     string name = constantPool[nameIndex -
      //     1]->getInfo(constantPool).first; string classDescriptor =
      //         constantPool[descriptorIndex - 1]->getInfo(constantPool).first;
      //     if (name.compare("<clinit>") == 0 &&
      //         classDescriptor.compare("()V") == 0) {
      //       foundClinit = true;
      //     }
      //   }

      //   if (foundClinit) {
      //     Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
      //     frame->jvmStack->push(clinitMethodFrame);
      //     frame->localPC -= 2;
      //     return clinitMethodFrame->localPC;
      //   }
      // }

      // ClassFile* classFile = methodArea->getClassFile(className);
      // vector<CPInfo*> constantPool = classFile->getConstantPool();
      // vector<MethodInfo*> methods = classFile->getMethods();
      // MethodInfo* method;
      // bool foundMethod = false;

      // for (int i = 0; i < classFile->getMethodsCount() && !foundMethod; i++)
      // {
      //   method = methods[i];
      //   uint16_t nameIndex = method->getNameIndex();
      //   uint16_t descriptorIndex = method->getDescriptorIndex();
      //   string name = constantPool[nameIndex -
      //   1]->getInfo(constantPool).first; string classDescriptor =
      //       constantPool[descriptorIndex - 1]->getInfo(constantPool).first;
      //   if (name.compare(methodName) == 0 &&
      //       classDescriptor.compare(descriptor) == 0) {
      //     foundMethod = true;
      //   }
      // }

      // if (!foundMethod) {
      //   printf("Invokestatic: o método especificado nao foi encontrado!\n");
      //   exit(0);
      // }

      // Frame staticMethodFrame(constantPool, method, frame->jvmStack);

      // stack<JavaType> auxstack;

      // for (int i = 1; descriptor[i] != ')'; i++) {
      //   if (descriptor[i] == 'I' || descriptor[i] == 'F') {
      //   } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
      //   } else if (descriptor[i] == 'L') {
      //     while (descriptor[i] != ';') {
      //       i++;
      //     }
      //   } else if (descriptor[i] == '[') {
      //     while (descriptor[i] == '[') {
      //       i++;
      //     }
      //     if (descriptor[i] == 'L') {
      //       while (descriptor[i] != ';') {
      //         i++;
      //       }
      //     }
      //   } else {
      //     cout << "Tipo de descritor nao reconhecido na contagem: " <<
      //     descriptor[i]
      //          << endl;
      //     exit(0);
      //   }
      //   auxstack.push(frame->operandStack.top());
      //   frame->operandStack.pop();
      // }
      // int argCnt = 0;
      // for (int i = 1; descriptor[i] != ')'; i++) {
      //   if (descriptor[i] == 'I' || descriptor[i] == 'F') {
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt += 2;
      //   } else if (descriptor[i] == 'L') {
      //     int j = i;
      //     while (descriptor[i] != ';') {
      //       i++;
      //     }
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else if (descriptor[i] == '[') {
      //     while (descriptor[i] == '[') {
      //       i++;
      //     }
      //     if (descriptor[i] == 'L') {
      //       while (descriptor[i] != ';') {
      //         i++;
      //       }
      //     }
      //     JavaType arg = auxstack.top();
      //     auxstack.pop();
      //     staticMethodFrame->localVariables[argCnt] = arg;
      //     argCnt++;
      //   } else {
      //     cout << "Tipo de descritor nao reconhecido: " << descriptor[i] <<
      //     endl; exit(0);
      //   }
      // }

      // frame->jvmStack->push(staticMethodFrame);
      // frame->localPC++;
      // return staticMethodFrame->localPC;
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case invokeinterface: {
      cout << "Instrucao invokeinterface nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case invokedynamic: {
      cout << "Instrucao invokedynamic nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case newOp: {
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      uint16_t index = ((uint16_t)byte1 << 8) | byte2;

      string className = getCPInfoFirst(frame->constantPool, index - 1);

      if (className.compare("java/lang/String") == 0) {
        JavaType objectref;
        objectref.type_reference = (uint64_t) new string("");
        objectref.tag = CAT1;
        frame->operandStack.push(objectref);
      } else if (className.compare("java/lang/StringBuilder") == 0) {
        JavaType objectref;
        objectref.type_reference = (uint64_t) new string("");
        objectref.tag = CAT1;
        frame->operandStack.push(objectref);
      } else {
        if (!isClassInitialized(className)) {
          setClassAsInitialized(className);

          loadClassFile(className + ".class");
          loadSuperClasses();
          MethodInfo method;

          bool foundClinit = false;
          for (int i = 0; i < classFile.methodsCount && !foundClinit; i++) {
            method = classFile.methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);

            string classDescriptor =
                getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

            if (name.compare("<clinit>") == 0 &&
                classDescriptor.compare("()V") == 0) {
              foundClinit = true;
            }
          }

          if (foundClinit) {
            Frame clinitMethodFrame =
                createFrame(classFile.constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            frame->localPC -= 2;
            return clinitMethodFrame.localPC;
          }
        }

        classFile = getClassFile(className);
        JavaType objectref;
        objectref.tag = CAT1;
        objectref.type_reference = (uint64_t)initializeFields();
        frame->operandStack.push(objectref);
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case newarray: {
      uint8_t atype = bytecode[frame->localPC + 1];

      JavaType count;
      count.type_int = (int32_t)frame->operandStack.top().type_int;
      frame->operandStack.pop();

      vector<JavaType>* array = new vector<JavaType>(count.type_int);

      if (atype == T_BOOLEAN) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_boolean = (int8_t)0;
        }
      } else if (atype == T_CHAR) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_char = (int16_t)0;
        }
      } else if (atype == T_FLOAT) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_float = (uint32_t)0;
        }
      } else if (atype == T_DOUBLE) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT2;
          array->at(i).type_double = (uint64_t)0;
        }
      } else if (atype == T_BYTE) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_byte = (int8_t)0;
        }
      } else if (atype == T_SHORT) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_short = (int16_t)0;
        }
      } else if (atype == T_INT) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT1;
          array->at(i).type_int = (int32_t)0;
        }
      } else if (atype == T_LONG) {
        for (uint32_t i = 0; i < count.type_int; i++) {
          array->at(i).tag = CAT2;
          array->at(i).type_long = (int64_t)0;
        }
      } else {
        printf("newarray: tipo de array indefinido: %u\n", atype);
      }

      JavaType arrayref;
      arrayref.tag = CAT1;
      arrayref.type_reference = (uint64_t)array;
      frame->operandStack.push(arrayref);

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case anewarray: {
      int32_t count = (int32_t)frame->operandStack.top().type_int;
      frame->operandStack.pop();

      vector<JavaType>* array = new vector<JavaType>(count);

      for (int i = 0; i < count; i++) {
        array->at(i).tag = CAT1;
        array->at(i).type_reference = JAVA_NULL;
      }

      JavaType arrayref;
      arrayref.tag = CAT1;
      arrayref.type_reference = (uint64_t)array;
      frame->operandStack.push(arrayref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case arraylength: {
      JavaType arrayref = frame->operandStack.top();
      frame->operandStack.pop();
      vector<JavaType>* array = (vector<JavaType>*)arrayref.type_reference;

      JavaType length;
      length.tag = CAT1;
      length.type_int = (uint32_t)array->size();
      frame->operandStack.push(length);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case athrow: {
      cout << "Instrucao athrow nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case checkcast: {
      cout << "Instrucao checkcast nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case instanceof: {
      cout << "Instrucao instanceof nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case monitorenter: {
      cout << "Instrucao monitorenter nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case monitorexit: {
      cout << "Instrucao monitorexit nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }

    // Extended
    case wide: {
      cout << "Instrucao wide nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case multianewarray: {
      uint8_t* bytecode = frame->codeAttribute.code;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      uint8_t byte3 = bytecode[frame->localPC + 3];
      uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      uint32_t dimensions = byte3;
      vector<int> dimensionsArray;

      for (uint32_t i = 0; i < dimensions; i++) {
        uint32_t dimension = frame->operandStack.top().type_int;
        frame->operandStack.pop();
        if (dimension == 0) {
          break;
        }
        dimensionsArray.push_back(dimension);
      }

      string className = getCPInfoFirst(frame->constantPool, index - 1);
      vector<JavaType>* array = buildMultiAnewArray(
          dimensionsArray, dimensions - 1, className[className.size() - 1]);

      JavaType arrayref;
      arrayref.tag = CAT1;
      arrayref.type_reference = (uint64_t)array;
      frame->operandStack.push(arrayref);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifnull: {
      uint8_t* bytecode = frame->codeAttribute.code;
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if (value.type_reference == JAVA_NULL) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case ifnonnull: {
      uint8_t* bytecode = frame->codeAttribute.code;
      uint32_t baseAddress = frame->localPC;
      uint8_t byte1 = bytecode[frame->localPC + 1];
      uint8_t byte2 = bytecode[frame->localPC + 2];
      int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

      JavaType value = frame->operandStack.top();
      frame->operandStack.pop();

      if (value.type_reference != JAVA_NULL) {
        frame->localPC = baseAddress + branchOffset;
        return frame->localPC;
      }

      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case goto_w: {
      cout << "Instrucao goto_w nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    case jsr_w: {
      cout << "Instrucao jsr_w nao implementada ainda!" << endl;
      exit(0);
      frame->localPC = frame->localPC + get_mnemonic(opcode).second + 1;
      return frame->localPC;
    }
    default:
      return 0;
  }
}
