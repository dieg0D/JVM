#include "../include/class_printer.hpp"

#include <iostream>

#include "../include/common.hpp"

using namespace std;

string getMajorVersion(unsigned int major) {
  switch (major) {
    case 46:
      return "1.2";

    case 47:
      return "1.3";

    case 48:
      return "1.4";

    case 49:
      return "1.5";

    case 50:
      return "1.6";

    case 51:
      return "1.7";

    case 52:
      return "1.8";

    case 53:
      return "1.9";

    case 54:
      return "1.10";

    case 55:
      return "1.11";

    case 56:
      return "1.12";

    case 57:
      return "1.13";
  }
}

void printGeneralInformation() {
  cout << "_________________General Information_________________" << endl
       << endl;
  cout << "Magic Number: "
       << "0x" << hex << uppercase << classFile.magic << endl;
  cout << "Minor version: " << dec << classFile.minorVersion << endl;
  cout << "Major version: " << dec << classFile.majorVersion << '['
       << getMajorVersion(classFile.majorVersion) << ']' << endl;
  cout << "Constant pool count: " << dec << classFile.constantPoolCount << endl;
  cout << "Access flags: " << endl;
  cout << "This class: " << endl;
  cout << "Super class: " << endl;
  cout << "Interfaces count: " << endl;
  cout << "Fields count: " << endl;
  cout << "Methods count: " << endl;
  cout << "Atributes count: " << endl;
  cout << endl;
};

void printConstantPool() {
  cout << "____________________Constant Pool____________________" << endl
       << endl;

  cout << endl;
};

void printInterfaces() {
  cout << "______________________Interfaces_____________________" << endl
       << endl;

  cout << endl;
};

void printFields() {
  cout << "_______________________Fields________________________" << endl
       << endl;

  cout << endl;
};

void printMethods() {
  cout << "_______________________Methods_______________________" << endl
       << endl;

  cout << endl;
};

void printAttributes() {
  cout << "_____________________Attributes______________________" << endl
       << endl;

  cout << endl;
};

void printClassFile() {
  printGeneralInformation();
  printConstantPool();
  printInterfaces();
  printFields();
  printMethods();
  printAttributes();
};
