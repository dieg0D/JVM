#include "../include/frame.hpp"

#include <iostream>

#include "../include/class_printer.hpp"
#include "../include/common.hpp"
#include "../include/method_area.hpp"

using namespace std;

Frame createFrame(vector<CPInfo> constantPool, MethodInfo method) {
  Frame frame;

  uint16_t attributesCount = method.attributes_count;
  vector<AttributeInfo> attributes = method.attributes;
  int i;

  bool foundCode = false;
  for (i = 0; i < attributesCount && !foundCode; i++) {
    AttributeInfo attribute = attributes[i];
    uint16_t nameIndex = attribute.attribute_name_index;
    string attributeName =
        getCPInfoFirst(classFile.constantPool, nameIndex - 1);

    if (attributeName.compare("Code") == 0) {
      foundCode = true;
      i--;
    }
  }

  if (foundCode) {
    uint16_t maxLocals = attributes[i].code.maxLocals;
    frame.codeAttribute = attributes[i].code;
    frame.localVariables = vector<JavaType>(maxLocals);
    frame.localPC = 0;
    frame.constantPool = constantPool;
    frame.method = method;
  } else {
    printf("Atributo Code nao encontrado no metodo [%d]\n", method.name_index);
    exit(0);
  }

  return frame;
}
