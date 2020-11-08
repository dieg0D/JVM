#include "../include/execution_engine.hpp"

#include <iostream>

#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/instructions.hpp"
#include "../include/method_area.hpp"

using namespace std;

void findMainMethod() {
  string mainClassFileName =
      getCPInfoFirst(classFile.constantPool, classFile.thisClass - 1);
  ClassFile mainClassFile = getClassFile(mainClassFileName);

  int i;
  bool foundMain = false;

  for (i = 0; i < mainClassFile.methodsCount && !foundMain; i++) {
    MethodInfo method = mainClassFile.methods[i];
    uint16_t nameIndex = method.name_index;
    uint16_t descriptorIndex = method.descriptor_index;
    string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);
    ;
    string descriptor =
        getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

    if (name.compare("main") == 0 &&
        descriptor.compare("([Ljava/lang/String;)V") == 0) {
      foundMain = true;
      executionEngine.mainClassFileName = mainClassFileName;
      executionEngine.mainMethod = method;
    }
  }

  if (!foundMain) {
    printf("A main nao foi encontrada no arquivo especificado!\n");
    exit(0);
  }
}

void execute() {
  Frame mainFrame =
      createFrame(classFile.constantPool, executionEngine.mainMethod);

  pushToJVMStack(mainFrame);

  // Frame currentFrame = getCurrentFrame();
  // uint8_t* bytecode = currentFrame.codeAttribute.code;
  // uint32_t bytecodeLength = currentFrame.codeAttribute.codeLength;

  // for (unsigned int i = 0; i < bytecodeLength; i++) {
  //   uint8_t opcode = bytecode[i];

  //   cout << "OPCODE " << hex << (unsigned int)(unsigned char)opcode << " "
  //        << get_mnemonic(opcode).first << endl;
  //   // cout << i << " : " << get_mnemonic(opcode).first << " ";

  //   i = i + get_mnemonic(opcode).second;
  // }

  do {
    Frame currentFrame = getCurrentFrame();
    uint8_t* bytecode = currentFrame.codeAttribute.code;
    uint32_t bytecodeLength = currentFrame.codeAttribute.codeLength;

    for (unsigned int i = 0; i < bytecodeLength; i++) {
      uint8_t opcode = bytecode[i];
      cout << i << ": " << get_mnemonic(opcode).first << " ";
      i = i + get_mnemonic(opcode).second;
    }

    uint8_t opcode = bytecode[jvmThread.pc];
    Instruction instruction = instructions[opcode];

    cout << bytecode << endl;

    // Para debug
    cout << "Executando: " << jvmThread.pc << " " << get_mnemonic(opcode).first
         << endl;

    jvmThread.pc = instruction.func(currentFrame);
    jvmThread.pc = get_mnemonic(opcode).second;

    if (get_mnemonic(opcode).first.compare("return") == 0) {
      popFromJVMStack();
      if (!isJVMStackEmpty()) {
        jvmThread.pc = getCurrentFrame().localPC;
      }
    }
  } while (!isJVMStackEmpty());
}
