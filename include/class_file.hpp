#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char BYTE;

typedef struct CPInfo {};

typedef struct InterfaceInfo {};

typedef struct FieldInfo {};

typedef struct MethodInfo {};

typedef struct AttributeInfo {};

typedef struct ClassFile {
  uint32_t magic;
  uint16_t minorVersion;
  uint16_t majorVersion;
  uint16_t constantPoolCount;
  vector<CPInfo> constantPool;
  uint16_t accessFlags;
  uint16_t thisClass;
  uint16_t superClass;
  uint16_t interfacesCount;
  vector<InterfaceInfo> interfaces;
  uint16_t fieldsCount;
  vector<FieldInfo> fields;
  uint16_t methodsCount;
  vector<MethodInfo> methods;
  uint16_t attributesCount;
  AttributeInfo attributes;
};

vector<BYTE> readFile(string filename);

void printFile(string file);
