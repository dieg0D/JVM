#ifndef __CLASSLOADER_H_INCLUDED__
#define __CLASSLOADER_H_INCLUDED__

#include "./class_file.hpp"
#include "./method_area.hpp"

void loadClassFile(string className);
void loadSuperClasses();
#endif
