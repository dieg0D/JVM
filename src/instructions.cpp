#include "../include/instructions.hpp"

#include <iostream>
#include <vector>

#include "../include/common.hpp"

using namespace std;

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

  instruction.mnemonic = "drem";
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
  //   cout << "GET MNEMONIC" << endl;
  //   cout << (unsigned int)(unsigned char)opcode << endl;
  string mnemonic = "";
  int length = -1;
  for (auto i : instructions) {
    if (i.opcode == opcode) {
      mnemonic = i.mnemonic;
      length = i.length;
      break;
    }
  }
  return make_pair(mnemonic, length);
}