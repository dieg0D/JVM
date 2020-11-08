#include "../include/class_loader.hpp"

#include <iostream>

#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/method_area.hpp"

using namespace std;

void loadClassFile(string className, string projectPath) {
  string path = "";

  if (className.compare("java/lang/Object") == 0) {
    path = "java/lang/Object.class";
  } else {
    path = (projectPath + className);
  }

  if (path != "") {
    loadFile(path);

    insertClass();

    // if (className.compare(getCPInfoFirst(classFile.constantPool,
    //                                      classFile.thisClass - 1)) != 0) {
    //   printf(
    //       "O nome do .class nao bate com o nome da classe encontrato no "
    //       "constant pool!\n");
    //   exit(-1);
    // }

    return;
  }
  cout << "Nao foi possivel abrir o arquivo! Programa terminado!" << projectPath
       << " " << className << endl;
  exit(0);
}

void loadSuperClasses(string projectPath) {
  if (classFile.superClass == 0) {
    return;
  }

  string superClassPath =
      getCPInfoFirst(classFile.constantPool, classFile.superClass - 1);

  // if (superClassPath.compare("java/lang/string") == 0 ||
  //     superClassPath.compare("java/lang/System.out") == 0 ||
  //     superClassPath.compare("java/lang/System.in") == 0) {
  //     return;
  // }

  // cout << superClassPath << endl;

  if (superClassPath.compare("java/lang/Object") == 0) {
    loadClassFile("java/lang/Object", projectPath);
  } else {
    loadClassFile(superClassPath + ".class", projectPath);
    loadSuperClasses(projectPath);
  }
  return;
}
