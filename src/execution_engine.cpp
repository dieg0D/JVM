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
  ClassFile* mainClassFile = getClassFile(mainClassFileName);

  // cout << "mainClassFileName: " << mainClassFileName << endl;
  // cout << "classFile.thisClass - 1: " << classFile.thisClass - 1 << endl;

  int i;
  bool foundMain = false;

  for (i = 0; i < mainClassFile->methodsCount && !foundMain; i++) {
    MethodInfo method = mainClassFile->methods[i];
    uint16_t nameIndex = method.name_index;
    uint16_t descriptorIndex = method.descriptor_index;
    string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);

    string descriptor =
        getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

    // cout << "Descriptor: " << descriptor << "\nName: " << name << endl;

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
  stack<Frame> jvmStack = getJVMStack();
  Frame mainFrame = createFrame(classFile.constantPool,
                                &executionEngine.mainMethod, &jvmStack);

  pushToJVMStack(mainFrame);
  // int contador = 0;
  do {
    Frame* currentFrame = getCurrentFrame();
    uint8_t* bytecode = currentFrame->codeAttribute.code;

    uint8_t opcode = bytecode[currentFrame->localPC];

    // cout << "Executando: " << jvmThread.pc << " " <<
    // get_mnemonic(opcode).first
    //      << " " << endl;
    jvmThread.pc = func_exec(currentFrame);
    if (get_mnemonic(opcode).first.compare("returnOp") == 0) {
      popFromJVMStack();
      if (!isJVMStackEmpty()) {
        jvmThread.pc = currentFrame->localPC;
      }
    }
    // contador++;

    // if (contador >= 20) {
    //   break;
    // }

  } while (!isJVMStackEmpty());
}
