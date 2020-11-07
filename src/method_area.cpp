#include "../include/method_area.hpp"

#include <iostream>

#include "../include/class_printer.hpp"
#include "../include/common.hpp"

using namespace std;

void insertClass() {
  string name = getCPInfoFirst(classFile.constantPool, classFile.thisClass - 1);

  methodArea.classes.insert(make_pair(name, classFile));
}

ClassFile getClassFile(string name) { return (methodArea.classes[name]); }

bool isClassInitialized(string name) {
  if (methodArea.clinitWasExecuted.count(name)) {
    return true;
  }
  return false;
}

void setClassAsInitialized(string name) {
  methodArea.clinitWasExecuted.insert(make_pair(name, true));
}
