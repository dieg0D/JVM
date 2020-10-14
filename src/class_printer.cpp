#include "../include/class_printer.hpp"

#include <iostream>
#include <sstream>

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
string integerToHex(uint16_t integer) {
  stringstream aux;
  aux << hex << uppercase << integer;
  return aux.str();
}

string accessFlagsDecoder(uint16_t flag) {
  bool acc_public = false;
  bool acc_final = false;
  bool acc_super = false;
  bool acc_interface = false;
  bool acc_abstract = false;
  bool acc_synthetic = false;
  bool acc_annotation = false;
  bool acc_enum = false;

  string hexFlag = integerToHex(flag);
  int hexSize = hexFlag.length();
  string flagInHexString;
  string classFileAccessFlagString;

  // set flags e append 0s ao começo da string (precisa ser sem 4 numeros)
  flagInHexString = std::string(3, '0').append(hexFlag);
  switch (hexFlag[hexSize - 1]) {
    case '1':
      acc_public = true;
      break;
  }
  if (hexSize > 1) {
    flagInHexString = std::string(2, '0').append(hexFlag);
    switch (hexFlag[hexSize - 2]) {
      case '1':
        acc_final = true;
        break;
      case '2':
        acc_super = true;
        break;
      case '3':
        acc_final = true;
        acc_super = true;
        break;
    }
  }
  if (hexSize > 2) {
    flagInHexString = std::string(1, '0').append(hexFlag);
    switch (hexFlag[hexSize - 3]) {
      case '2':
        acc_interface = true;
        break;
      case '4':
        acc_abstract = true;
        break;
      case '6':
        acc_interface = true;
        acc_abstract = true;
        break;
    }
  }
  if (hexSize > 3) {
    flagInHexString = std::string(0, '0').append(hexFlag);
    switch (hexFlag[hexSize - 4]) {
      case '1':
        acc_synthetic = true;
        break;
      case '2':
        acc_annotation = true;
        break;
      case '4':
        acc_enum = true;
        break;
      case '3':
        acc_synthetic = true;
        acc_annotation = true;
        break;
      case '5':
        acc_synthetic = true;
        acc_enum = true;
        break;
      case '6':
        acc_annotation = true;
        acc_enum = true;
        break;
      case '7':
        acc_synthetic = true;
        acc_annotation = true;
        acc_enum = true;
        break;
    }
  }

  // flags validações
  if (acc_interface == true) {
    if (acc_abstract == false) {
      cout << "Interface precisa ser declarada como abstrata. \n";
    } else {
      if (acc_final == true || acc_super == true || acc_enum == true) {
        cout
            << "Interface não pode ser declarada como Final, Super ou Enum. \n";
      }
    }
  } else {
    if (acc_annotation == true) {
      cout << "Uma classe não pode ser declarada como Annotation. \n";
    }
    if (acc_final == true && acc_abstract == true) {
      cout << "Classes não podem ser declaradas como Final e Abstract ao mesmo "
              "tempo. \n";
    }
  }
  if (acc_annotation == true && acc_interface == false) {
    cout << "Annotations devem também ser declaradas como Interface. \n";
  }

  // construir string para exibir no General Info
  classFileAccessFlagString = "0x" + flagInHexString + " [";
  if (acc_public == true) {
    classFileAccessFlagString = classFileAccessFlagString + "public ";
  };
  if (acc_final == true) {
    classFileAccessFlagString = classFileAccessFlagString + "final ";
  };
  // if (acc_super == true) {
  //   classFileAccessFlagString = classFileAccessFlagString + "super ";
  // };
  if (acc_interface == true) {
    classFileAccessFlagString = classFileAccessFlagString + "interface ";
  };
  if (acc_abstract == true) {
    classFileAccessFlagString = classFileAccessFlagString + "abstract ";
  };
  if (acc_synthetic == true) {
    classFileAccessFlagString = classFileAccessFlagString + "synthetic ";
  };
  if (acc_annotation == true) {
    classFileAccessFlagString = classFileAccessFlagString + "annotation ";
  };
  if (acc_enum == true) {
    classFileAccessFlagString = classFileAccessFlagString + "enum ";
  };
  classFileAccessFlagString.pop_back();
  classFileAccessFlagString = classFileAccessFlagString + "]";

  return classFileAccessFlagString;
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
  cout << "Access flags: " << accessFlagsDecoder(classFile.accessFlags) << endl;
  cout << "This class: "
       << "referencia pra constant pool posicao: " << dec << uppercase
       << classFile.thisClass << endl;
  cout << "Super class: "
       << "valor 0 ou referencia pra constant pool posicao: " << dec << uppercase
       << classFile.superClass << endl;
  cout << "Interfaces count: " << dec << classFile.interfacesCount << endl;
  cout << "Fields count: " << dec << classFile.fieldsCount << endl;
  cout << "Methods count: " << dec << classFile.methodsCount << endl;
  cout << "Atributes count: " << dec << classFile.attributesCount << endl;
  cout << endl;
};

string utf8Converter(uint8_t value){
  stringstream stream;
  stream << (unsigned int)(unsigned char)(value);
  string convertedStr = stream.str();
  return convertedStr;
}

string getCPInfoFirst (vector<CPInfo> cp_info, int indice){
  stringstream stream;
  stream << (unsigned int)(unsigned char)(cp_info[indice].tag);
  string tag_info = stream.str();
  int tag = stoi(tag_info);
  
  if(tag == 1){
    return (char*)(cp_info[indice].CONSTANT_Utf8_info.bytes);
  }

  cout << "1-TAG: " << tag << endl;
  switch (tag)
  {
  case 7:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_Class_info.name_index-1);
  case 9:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_Fieldref_info.class_index-1);
  case 10:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_Methodref_info.class_index-1);
  case 11:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_InterfaceMethodref_info.class_index-1);
  case 8:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_String_info.string_index-1);
  case 12:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_NameAndType_info.name_index-1);
  default:
    return "";
  }
}

string getCPInfoSecond (vector<CPInfo> cp_info, int indice){
  stringstream stream;
  stream << (unsigned int)(unsigned char)(cp_info[indice].tag);
  string tag_info = stream.str();
  int tag = stoi(tag_info);
  
  if(tag == 1){
    return (char*)(cp_info[indice].CONSTANT_Utf8_info.bytes);
  }
  cout << "2-TAG: " << tag << endl;
  switch (tag)
  {
  case 7:
    return getCPInfoFirst(cp_info, cp_info[indice].CONSTANT_Class_info.name_index-1);
  case 9:
    return getCPInfoSecond(cp_info, cp_info[indice].CONSTANT_Fieldref_info.name_and_type_index-1);
  case 10:
    return getCPInfoSecond(cp_info, cp_info[indice].CONSTANT_Methodref_info.name_and_type_index-1);
  case 11:
    return getCPInfoSecond(cp_info, cp_info[indice].CONSTANT_InterfaceMethodref_info.name_and_type_index-1);
  case 12:
    return getCPInfoSecond(cp_info, cp_info[indice].CONSTANT_NameAndType_info.descriptor_index-1);
  default:
    return "";
  }
}


void printConstantPool() {
  cout << "____________________Constant Pool____________________" << endl;
  vector<CPInfo> constant_pool = classFile.constantPool;
  for(int i = 0; i < classFile.constantPoolCount - 1; i++){
    cout << "[" << i+1 << "] ";
    int tag = stoi(utf8Converter(constant_pool[i].tag));
    switch (tag) {
    case 7: {
      cout << "CONSTANT_Class_info" << endl;
      string class_name = getCPInfoFirst(constant_pool, i);
      cout << "Class name: cp_info#" << constant_pool[i].CONSTANT_Class_info.name_index << " <" << class_name << "> " << endl;
    }
      break;
    case 9: {
      cout << "CONSTANT_Fieldref_info" << endl;
      string class_name = getCPInfoFirst(constant_pool, i);
      string name_and_type = getCPInfoSecond(constant_pool, i);
      cout << "Class name:    cp_info#" << constant_pool[i].CONSTANT_Fieldref_info.class_index << " <" << class_name << "> " << endl;
      cout << "Name and type: cp_info#" << constant_pool[i].CONSTANT_Fieldref_info.name_and_type_index << " <" << name_and_type << "> " << endl;
    }
      break;
    case 10:{
      cout << "CONSTANT_Methodref_info" << endl;
      string class_name = getCPInfoFirst(constant_pool, i);
      string name_and_type = getCPInfoSecond(constant_pool, i);
      cout << "Class name:    cp_info#" << constant_pool[i].CONSTANT_Methodref_info.class_index << " <" << class_name << "> " << endl;
      cout << "Name and type: cp_info#" << constant_pool[i].CONSTANT_Methodref_info.name_and_type_index << " <" << name_and_type << "> " << endl;
    }
      break;
    case 11:{
      cout << "CONSTANT_InterfaceMethodref_info" << endl;
      string class_name = getCPInfoFirst(constant_pool, i);
      string name_and_type = getCPInfoSecond(constant_pool, i);
      cout << "Class name:    cp_info #" << constant_pool[i].CONSTANT_InterfaceMethodref_info.class_index << " <" << class_name << ">" << endl;
      cout << "Name and type: cp_info #" << constant_pool[i].CONSTANT_InterfaceMethodref_info.name_and_type_index << " <" << name_and_type << ">";
    }
      break;
    case 8:{
      cout << "CONSTANT_String_info" << endl;
      string value = getCPInfoFirst(constant_pool, i);
      cout << "String: cp_info#" << constant_pool[i].CONSTANT_String_info.string_index << " <" << value << "> " << endl;
    }
      break;
    case 3:{
      cout << "CONSTANT_Integer" << endl;
      cout << "Bytes: " << constant_pool[i].CONSTANT_Integer_info.bytes << endl;
    }
      break;
    case 4:{
      cout << "CONSTANT_Float_info" << endl;
      cout << "Bytes: " << constant_pool[i].CONSTANT_Float_info.bytes << endl;
    }
      break;
    case 5:{
      cout << "CONSTANT_Long_info" << endl;
      cout << "High Bytes: " << endl;
      cout << "Low Bytes:  " << endl;
      cout << "Long:       " << endl;
    }
      break;
    case 6:{
      cout << "CONSTANT_Double_info" << endl;
      cout << "High Bytes: " << endl;
      cout << "Low Bytes:  " << endl;
      cout << "Long:       " << endl;
    }
      break;
    case 12:{
      cout << "CONSTANT_NameAndType_info" << endl;
      string name = getCPInfoFirst(constant_pool, i);
      string descriptor = getCPInfoSecond(constant_pool, i);
      cout << "Name:       cp_info #" << constant_pool[i].CONSTANT_NameAndType_info.name_index << " <" << name << ">" << endl;
      cout << "Descriptor: cp_info #" << constant_pool[i].CONSTANT_NameAndType_info.descriptor_index << " <" << descriptor << ">" << endl;
    }
      break;
    case 1: {
      cout << "CONSTANT_Utf8_info" << endl;
      string name = getCPInfoFirst(constant_pool, i);
      string descriptor = getCPInfoSecond(constant_pool, i);
      cout << "Length of byte array: " << constant_pool[i].CONSTANT_Utf8_info.length << endl;
      cout << "Length of string:     " << constant_pool[i].CONSTANT_Utf8_info.length << endl;
      cout << "String:               " << constant_pool[i].CONSTANT_Utf8_info.bytes  << endl;
    }
      break;
    case 15:{
      cout << "CONSTANT_MethodHandle_info" << endl;
    }
      break;
    case 16:{
      cout << "CONSTANT_MethodType_info" << endl;
    }
      break;
    case 18:{
      cout << "CONSTANT_InvokeDynamic_info" << endl;
    }
      break;
    }
  }
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
