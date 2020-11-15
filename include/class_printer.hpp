#ifndef __CLASSPRINTER_H_INCLUDED__
#define __CLASSPRINTER_H_INCLUDED__

#include <iomanip>
#include <iostream>

#include "./class_file.hpp"

using namespace std;

void printGeneralInformation();

void printConstantPool();

void printInterfaces();

void printFields();

void printMethods();

void printClassFile();

string getCPInfoFirst(vector<CPInfo> cp_info, int indice);
pair<string, string> getCPInfoSecond(vector<CPInfo> cp_info, int indice);
void printAttributes(string attributeName, AttributeInfo attr_info);

#endif
