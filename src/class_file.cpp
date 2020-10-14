#include "../include/class_file.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../include/common.hpp"
#include "../include/cp_info.hpp"
using namespace std;

vector<BYTE> readFile(string filename) {
  // open the file:
  streampos fileSize;
  ifstream file(filename, ios::binary);

  // get its size:
  file.seekg(0, ios::end);
  fileSize = file.tellg();
  file.seekg(0, ios::beg);

  // read the data:
  vector<BYTE> fileData(fileSize);
  file.read((char*)&fileData[0], fileSize);
  return fileData;
};

// begin é a posição que eu quero e end é aposição depois da que eu quero
unsigned int getDatafromArray(vector<BYTE> fileData, int begin, int end,
                              unsigned int size) {
  vector<BYTE> newVec;

  newVec.insert(newVec.begin(), fileData.begin() + begin,
                fileData.begin() + end);
  string data = "";

  for (auto i : newVec) {
    data = (data + bitset<8>(i).to_string());
  }

  return bitset<sizeof(size) * 8>(data).to_ulong();
};

CPInfo setConstantInfo(int tag, vector<BYTE> fileData, int position) {
  CPInfo constant;

  switch (tag) {
    case 7: {
      constant.tag = tag;
      constant.CONSTANT_Class_info.name_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_Class_info.name_index);
    } break;
    case 9: {
      constant.tag = tag;
      constant.CONSTANT_Fieldref_info.class_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_Fieldref_info.class_index);
      constant.CONSTANT_Fieldref_info.name_and_type_index =
          getDatafromArray(fileData, position + 3, position + 5,
                           constant.CONSTANT_Fieldref_info.name_and_type_index);
    } break;
    case 10: {
      constant.tag = tag;
      constant.CONSTANT_Methodref_info.class_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_Methodref_info.class_index);
      constant.CONSTANT_Methodref_info.name_and_type_index = getDatafromArray(
          fileData, position + 3, position + 5,
          constant.CONSTANT_Methodref_info.name_and_type_index);
    } break;
    case 11: {
      constant.tag = tag;
      constant.CONSTANT_InterfaceMethodref_info.class_index = getDatafromArray(
          fileData, position + 1, position + 3,
          constant.CONSTANT_InterfaceMethodref_info.class_index);
      constant.CONSTANT_InterfaceMethodref_info.name_and_type_index =
          getDatafromArray(
              fileData, position + 3, position + 5,
              constant.CONSTANT_InterfaceMethodref_info.name_and_type_index);
    } break;
    case 8: {
      constant.tag = tag;
      constant.CONSTANT_String_info.string_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_String_info.string_index);
    } break;
    case 3: {
      constant.tag = tag;
      constant.CONSTANT_Integer_info.bytes =
          getDatafromArray(fileData, position + 1, position + 5,
                           constant.CONSTANT_Integer_info.bytes);
    } break;
    case 4: {
      constant.tag = tag;
      constant.CONSTANT_Float_info.bytes =
          getDatafromArray(fileData, position + 1, position + 5,
                           constant.CONSTANT_Float_info.bytes);
    } break;
    case 5: {
      constant.tag = tag;
      constant.CONSTANT_Long_info.high_bytes =
          getDatafromArray(fileData, position + 1, position + 5,
                           constant.CONSTANT_Long_info.high_bytes);
      constant.CONSTANT_Long_info.low_bytes =
          getDatafromArray(fileData, position + 5, position + 9,
                           constant.CONSTANT_Long_info.low_bytes);
    } break;
    case 6: {
      constant.tag = tag;
      constant.CONSTANT_Double_info.high_bytes =
          getDatafromArray(fileData, position + 1, position + 5,
                           constant.CONSTANT_Double_info.high_bytes);
      constant.CONSTANT_Double_info.low_bytes =
          getDatafromArray(fileData, position + 5, position + 9,
                           constant.CONSTANT_Double_info.low_bytes);
    } break;
    case 12: {
      constant.tag = tag;
      constant.CONSTANT_NameAndType_info.name_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_NameAndType_info.name_index);
      constant.CONSTANT_NameAndType_info.descriptor_index =
          getDatafromArray(fileData, position + 3, position + 5,
                           constant.CONSTANT_NameAndType_info.descriptor_index);
    } break;
    case 1: {
      constant.tag = tag;
      constant.CONSTANT_Utf8_info.length =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_Utf8_info.length);
    } break;
    case 15: {
      constant.tag = tag;
      constant.CONSTANT_MethodHandle_info.reference_kind =
          getDatafromArray(fileData, position + 1, position + 2,
                           constant.CONSTANT_MethodHandle_info.reference_kind);
      constant.CONSTANT_MethodHandle_info.reference_index =
          getDatafromArray(fileData, position + 2, position + 4,
                           constant.CONSTANT_MethodHandle_info.reference_index);
    } break;
    case 16: {
      constant.tag = tag;
      constant.CONSTANT_MethodType_info.descriptor_index =
          getDatafromArray(fileData, position + 1, position + 3,
                           constant.CONSTANT_MethodType_info.descriptor_index);
    } break;
    case 18: {
      constant.tag = tag;
      constant.CONSTANT_InvokeDynamic_info.bootstrap_method_attr_index =
          getDatafromArray(
              fileData, position + 1, position + 3,
              constant.CONSTANT_InvokeDynamic_info.bootstrap_method_attr_index);
      constant.CONSTANT_InvokeDynamic_info.name_and_type_index =
          getDatafromArray(
              fileData, position + 3, position + 5,
              constant.CONSTANT_InvokeDynamic_info.name_and_type_index);
    } break;
  }
  return constant;
}

int nextPosition(int tag, vector<BYTE> fileData, int position) {
  switch (tag) {
    case 7:
      return 3;
      break;
    case 9:
      return 5;
      break;
    case 10:
      return 5;
      break;
    case 11:
      return 5;
      break;
    case 8:
      return 3;
      break;
    case 3:
      return 5;
      break;
    case 4:
      return 5;
      break;
    case 5:
      return 9;
      break;
    case 6:
      return 9;
      break;
    case 12:
      return 5;
      break;
    case 1: {
      uint16_t length;
      uint16_t result =
          getDatafromArray(fileData, position + 1, position + 3, length);

      return 3 + result;
    } break;
    case 15:
      return 4;
      break;
    case 16:
      return 3;
      break;
    case 18:
      return 5;
      break;
  }
}

int fieldPositionIncrement(int attr_counts) { int increment = 8; }

void loadFile(string file) {
  vector<BYTE> fileData = readFile(file);

  classFile.magic = getDatafromArray(fileData, 0, 4, classFile.magic);

  classFile.minorVersion =
      getDatafromArray(fileData, 4, 6, classFile.minorVersion);

  classFile.majorVersion =
      getDatafromArray(fileData, 6, 8, classFile.majorVersion);

  classFile.constantPoolCount =
      getDatafromArray(fileData, 8, 10, classFile.constantPoolCount);

  int position = 10;  // inicializado em 10 pois a CP começa no 10o byte.

  for (int i = 0; i < classFile.constantPoolCount - 1; i++) {
    classFile.constantPool.push_back(setConstantInfo(
        bitset<8>(fileData[position]).to_ulong(), fileData, position));

    // cout << hex << classFile.constantPool[i].tag << endl;
    if((unsigned int)(unsigned char)(classFile.constantPool[i].tag) == 10){
      cout << "Class index " << (unsigned int)(unsigned char)(classFile.constantPool[i].CONSTANT_Methodref_info.class_index) << endl;
      cout << "Name index " << (unsigned int)(unsigned char)(classFile.constantPool[i].CONSTANT_Methodref_info.name_and_type_index) << endl;
    }

    position = position + nextPosition(bitset<8>(fileData[position]).to_ulong(),
                                       fileData, position);
  }

  classFile.accessFlags =
      getDatafromArray(fileData, position, position + 2, classFile.accessFlags);
  position = position + 2;

  classFile.thisClass =
      getDatafromArray(fileData, position, position + 2, classFile.thisClass);
  position = position + 2;

  classFile.superClass =
      getDatafromArray(fileData, position, position + 2, classFile.superClass);
  position = position + 2;

  classFile.interfacesCount = getDatafromArray(fileData, position, position + 2,
                                               classFile.interfacesCount);
  position = position + 2;

  for (int i = 0; i < classFile.interfacesCount; i++) {
    /*TODO*/
    // array de referencias de interfaces. Atualmente só incrementa a posição
    // (sempre u2) para continuar a leitura
    position = position + 2;
  }

  classFile.fieldsCount =
      getDatafromArray(fileData, position, position + 2, classFile.fieldsCount);
  position = position + 2;

  for (int i = 0; i < classFile.fieldsCount; i++) {
    /*TODO*/
    int attr_counts = 0;

    /*
      empaquei, não sei pegar o tamanho dos fields pq nao sei como acessar o
      numero de atributos dele para poder pegar o tamanho do attributes_info.
      muita coisa dentro de outra.
      inception de tamanhos. rip.
    */

    position = position + fieldPositionIncrement(attr_counts);
  }
};
