#ifndef METHOD_AREA_H_INCLUDED
#define METHOD_AREA_H_INCLUDED

#include <map>
#include <vector>

#include "./class_file.hpp"

using namespace std;

typedef struct {
  map<string, ClassFile> classes;
  map<string, bool> clinitWasExecuted;
} MethodArea;

void insertClass();
ClassFile* getClassFile(string name);
bool isClassInitialized(string name);
void setClassAsInitialized(string name);

#endif
