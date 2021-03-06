#include <bitset>
#include <fstream>
#include <iostream>

#include "../include/class_file.hpp"
#include "../include/class_loader.hpp"
#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/method_area.hpp"

using namespace std;

ClassFile classFile;
MethodArea methodArea;
ExecutionEngine executionEngine;
JavaVirtualMachineThread jvmThread;
vector<Instruction> instructions;
string projectPath;

string getProjectPath(string commandLinePath) {
  int i = commandLinePath.size() - 1;

#if defined(_WIN32)
  while (i >= 0 && commandLinePath[i] != '\\') {
    i--;
  }
#else
  while (i >= 0 && commandLinePath[i] != '/') {
    i--;
  }
#endif

  return commandLinePath.substr(0, i + 1);
}

string getClassName(string commandLinePath) {
  int i = commandLinePath.size() - 1;

#if defined(_WIN32)
  while (i >= 0 && commandLinePath[i] != '\\') {
    i--;
  }
#else
  while (i >= 0 && commandLinePath[i] != '/') {
    i--;
  }
#endif

  return commandLinePath.substr(i + 1, commandLinePath.size());
}

int main(int argc, char* argv[]) {
  // Verifica se os argumentos foram passados
  if (argc == 3) {
    string option = argv[1];
    projectPath = getProjectPath(argv[2]);
    string className = getClassName(argv[2]);
    initialize_instruction();

    loadClassFile(className);
    if (className.compare(
            getCPInfoFirst(classFile.constantPool, classFile.thisClass - 1) +
            ".class") != 0) {
      printf(
          "O nome do .class nao bate com o nome da classe encontrato no "
          "constant pool!\n");
      exit(-1);
    }

    if (option.compare("-e") == 0) {
      printClassFile();
    } else if (option.compare("-i") == 0) {
      loadSuperClasses();
      classFile = *getClassFile(
          className.replace(className.end() - 6, className.end(), ""));
      findMainMethod();
      execute();

    } else {
      cout << "O segundo argumento deve ser -e para exibidor ou -i para "
              "interpretador."
           << endl;
    }

  } else {
    cout << endl
         << "Numero incorreto de argumentos especificado!!!" << endl
         << endl;
    cout << "- O segundo argumento deve ser -e para exibidor ou -i para "
            "interpretador."
         << endl;
    cout << "- O terceiro argumento deve ser um arquivo.class para funcionar"
         << endl
         << endl;
    return -1;
  }
  return 0;
}
