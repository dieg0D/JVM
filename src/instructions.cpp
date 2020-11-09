#include "../include/instructions.hpp"

#include <iostream>
#include <vector>

#include "../include/class_loader.hpp"
#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/frame.hpp"

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

uint32_t func_exec(Frame frame) {
  uint8_t* bytecode = frame.codeAttribute.code;
  uint8_t opcode = bytecode[frame.localPC];

  cout << hex << (unsigned int)(unsigned char)opcode << endl;
  switch (opcode) {
    // Constants
    case nop: {
      return get_mnemonic(opcode).second + 1;
    }
    case aconst_null: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_m1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_4: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_5: {
      return get_mnemonic(opcode).second + 1;
    }
    case lconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case bipush: {
      return get_mnemonic(opcode).second + 1;
    }
    case sipush: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc_w: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc2_w: {
      return get_mnemonic(opcode).second + 1;
    }

    // Loads
    case iload: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iaload: {
      return get_mnemonic(opcode).second + 1;
    }
    case laload: {
      return get_mnemonic(opcode).second + 1;
    }
    case faload: {
      return get_mnemonic(opcode).second + 1;
    }
    case daload: {
      return get_mnemonic(opcode).second + 1;
    }
    case aaload: {
      return get_mnemonic(opcode).second + 1;
    }
    case baload: {
      return get_mnemonic(opcode).second + 1;
    }
    case caload: {
      return get_mnemonic(opcode).second + 1;
    }
    case saload: {
      return get_mnemonic(opcode).second + 1;
    }

    // Stores
    case istore: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case lastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case fastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case dastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case aastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case bastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case castore: {
      return get_mnemonic(opcode).second + 1;
    }
    case sastore: {
      return get_mnemonic(opcode).second + 1;
    }

    // Stack
    case pop: {
      return get_mnemonic(opcode).second + 1;
    }
    case pop2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup_x1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup_x2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2_x1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2_x2: {
      return get_mnemonic(opcode).second + 1;
    }
    case swapOp: {
      return get_mnemonic(opcode).second + 1;
    }

    // Math
    case iadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case ladd: {
      return get_mnemonic(opcode).second + 1;
    }
    case fadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case dadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case isub: {
      return get_mnemonic(opcode).second + 1;
    }
    case lsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case fsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case dsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case imul: {
      return get_mnemonic(opcode).second + 1;
    }
    case lmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case fmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case dmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case idiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldivOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case fdiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case ddiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case irem: {
      return get_mnemonic(opcode).second + 1;
    }
    case lrem: {
      return get_mnemonic(opcode).second + 1;
    }
    case frem: {
      return get_mnemonic(opcode).second + 1;
    }
    case drem: {
      return get_mnemonic(opcode).second + 1;
    }
    case ineg: {
      return get_mnemonic(opcode).second + 1;
    }
    case lneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case fneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case dneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case ishl: {
      return get_mnemonic(opcode).second + 1;
    }
    case lshl: {
      return get_mnemonic(opcode).second + 1;
    }
    case ishr: {
      return get_mnemonic(opcode).second + 1;
    }
    case lshr: {
      return get_mnemonic(opcode).second + 1;
    }
    case iushr: {
      return get_mnemonic(opcode).second + 1;
    }
    case lushr: {
      return get_mnemonic(opcode).second + 1;
    }
    case iand: {
      return get_mnemonic(opcode).second + 1;
    }
    case land: {
      return get_mnemonic(opcode).second + 1;
    }
    case ior: {
      return get_mnemonic(opcode).second + 1;
    }
    case lor: {
      return get_mnemonic(opcode).second + 1;
    }
    case ixor: {
      return get_mnemonic(opcode).second + 1;
    }
    case lxor: {
      return get_mnemonic(opcode).second + 1;
    }
    case iinc: {
      return get_mnemonic(opcode).second + 1;
    }

    // Conversions
    case i2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2b: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2c: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2s: {
      return get_mnemonic(opcode).second + 1;
    }

    // Comparisons
    case lcmp: {
      return get_mnemonic(opcode).second + 1;
    }
    case fcmpl: {
      return get_mnemonic(opcode).second + 1;
    }
    case fcmpg: {
      return get_mnemonic(opcode).second + 1;
    }
    case dcmpl: {
      return get_mnemonic(opcode).second + 1;
    }
    case dcmpg: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifne: {
      return get_mnemonic(opcode).second + 1;
    }
    case iflt: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifge: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifgt: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifle: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpne: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmplt: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpge: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpgt: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmple: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_acmpeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_acmpne: {
      return get_mnemonic(opcode).second + 1;
    }

    // Control
    case gotoOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case jsr: {
      return get_mnemonic(opcode).second + 1;
    }
    case ret: {
      return get_mnemonic(opcode).second + 1;
    }
    case tableswitch: {
      return get_mnemonic(opcode).second + 1;
    }
    case lookupswitch: {
      return get_mnemonic(opcode).second + 1;
    }
    case ireturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case lreturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case freturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case dreturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case areturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case returnOp: {
      return get_mnemonic(opcode).second + 1;
    }

    // References
    case getstatic: {
      uint8_t byte1 = bytecode[frame.localPC + 1];
      uint8_t byte2 = bytecode[frame.localPC + 2];

      uint16_t index = ((uint16_t)byte1 << 8) | byte2;
      string className = getCPInfoFirst(frame.constantPool, index - 1);
      cout << className << endl;

      string nameAndType =
          getCPInfoSecond(frame.constantPool, index - 1).second;
      cout << nameAndType << endl;

      // int j = 0;

      // while (j < nameAndType.size() && nameAndType[j + 1] != ':') {
      //   j++;
      // }
      // string fieldName = nameAndType.substr(0, j);
      // string fieldDescriptor = nameAndType.substr(j + 3, nameAndType.size());

      if (className.compare("java/lang/System") == 0) {
        return get_mnemonic(opcode).second + 1;  // incrementa jvthread.pc em 1
      } else {
        // if (!isClassInitialized(className)) {
        //   setClassAsInitialized(className);

        //   loadClassFile(className + ".class");
        //   loadSuperClasses();
        //   ClassFile* classFile =
        //   classLoader->getClassFromMethodArea(className); vector<CPInfo*>
        //   constantPool = classFile->getConstantPool(); vector<MethodInfo*>
        //   methods = classFile->getMethods(); MethodInfo* method;

        //   bool foundClinit = false;
        //   for (int i = 0; i < classFile->getMethodsCount() && !foundClinit;
        //        i++) {
        //     method = methods[i];
        //     uint16_t nameIndex = method->getNameIndex();
        //     uint16_t descriptorIndex = method->getDescriptorIndex();
        //     string name =
        //         constantPool[nameIndex - 1]->getInfo(constantPool).first;
        //     string classDescriptor =
        //         constantPool[descriptorIndex -
        //         1]->getInfo(constantPool).first;
        //     if (name.compare("<clinit>") == 0 &&
        //         classDescriptor.compare("()V") == 0) {
        //       foundClinit = true;
        //     }
        //   }

        //   if (foundClinit) {
        //     Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
        //     frame->jvmStack->push(clinitMethodFrame);
        //     frame->localPC -= 2;
        //     return clinitMethodFrame.localPC;
        //   }
      }

      //   ClassFile* classFile = methodArea->getClassFile(className);
      //   vector<CPInfo*> constantPool = classFile->getConstantPool();
      //   vector<FieldInfo*> fields = classFile->getFields();
      //   FieldInfo* field;
      //   bool foundField = false;

      //   for (int i = 0; i < classFile->getFieldsCount() && !foundField; i++)
      //   {
      //     field = fields[i];
      //     uint16_t nameIndex = field->getNameIndex();
      //     uint16_t descriptorIndex = field->getDescriptorIndex();
      //     string name =
      //         constantPool[nameIndex - 1]->getInfo(constantPool).first;
      //     string descriptor =
      //         constantPool[descriptorIndex - 1]->getInfo(constantPool).first;
      //     if (name.compare(fieldName) == 0 &&
      //         descriptor.compare(fieldDescriptor) == 0) {
      //       foundField = true;
      //     }
      //   }

      //   if (!foundField) {
      //     printf(
      //         "getstatic: o field especificado nao pode ser resolvido! Deve "
      //         "estar em uma superclasse ou superinterface! Falta "
      //         "implementar!\n");
      //     exit(0);
      //   }

      //   if (fieldDescriptor.compare("C") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor.compare("I") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor.compare("F") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor.compare("D") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor.compare("J") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor.compare("Z") == 0) {
      //     frame->operandStack.push(field->staticValue);
      //   } else if (fieldDescriptor[0] == '[') {
      //     frame->operandStack.push(field->staticValue);
      //   } else {
      //     printf("getstatic: tipo do descritor nao reconhecido: %s\n",
      //            fieldDescriptor.c_str());
      //     exit(0);
      //   }
      // }

      return get_mnemonic(opcode).second + 1;
    }
    case putstatic: {
      return get_mnemonic(opcode).second + 1;
    }
    case getfield: {
      return get_mnemonic(opcode).second + 1;
    }
    case putfield: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokevirtual: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokespecial: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokestatic: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokeinterface: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokedynamic: {
      return get_mnemonic(opcode).second + 1;
    }
    case newOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case newarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case anewarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case arraylength: {
      return get_mnemonic(opcode).second + 1;
    }
    case athrow: {
      return get_mnemonic(opcode).second + 1;
    }
    case checkcast: {
      return get_mnemonic(opcode).second + 1;
    }
    case instanceof: {
      return get_mnemonic(opcode).second + 1;
    }
    case monitorenter: {
      return get_mnemonic(opcode).second + 1;
    }
    case monitorexit: {
      return get_mnemonic(opcode).second + 1;
    }

    // Extended
    case wide: {
      return get_mnemonic(opcode).second + 1;
    }
    case multianewarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifnull: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifnonnull: {
      return get_mnemonic(opcode).second + 1;
    }
    case goto_w: {
      return get_mnemonic(opcode).second + 1;
    }
    case jsr_w: {
      return get_mnemonic(opcode).second + 1;
    }
    default:
      return 0;
  }
}
