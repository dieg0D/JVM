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
  file.read((char *)&fileData[0], fileSize);
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

      stringstream stream;
      stream
          << (unsigned int)(unsigned char)(constant.CONSTANT_Utf8_info.length);
      string tam = stream.str();
      int tamanho = stoi(tam);

      int pos = position + 3;
      constant.CONSTANT_Utf8_info.bytes =
          (uint8_t *)calloc(tamanho, sizeof(uint8_t));
      for (int i = 0; i < tamanho; i++) {
        constant.CONSTANT_Utf8_info.bytes[i] = getDatafromArray(
            fileData, pos, pos + 1, sizeof(constant.CONSTANT_Utf8_info.bytes));
        pos++;
      }
      constant.CONSTANT_Utf8_info.bytes[tamanho] = '\0';

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
      uint16_t length = 0;
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
    default:
      return 0;
      break;
  }
}

void loadFile(string file) {
  vector<BYTE> fileData = readFile(file);
  int position = 0;

  classFile.magic =
      getDatafromArray(fileData, position, position + 4, classFile.magic);
  position = position + 4;

  if (classFile.magic != 3405691582) {
    cout << "O magic number nao e 0xCAFEBABE! Programa encerrado!" << endl;
    exit(0);
  }

  classFile.minorVersion = getDatafromArray(fileData, position, position + 2,
                                            classFile.minorVersion);
  position = position + 2;

  classFile.majorVersion = getDatafromArray(fileData, position, position + 2,
                                            classFile.majorVersion);
  position = position + 2;

  classFile.constantPoolCount = getDatafromArray(
      fileData, position, position + 2, classFile.constantPoolCount);
  position = position + 2;

  for (int i = 0; i < classFile.constantPoolCount - 1; i++) {
    classFile.constantPool.push_back(setConstantInfo(
        bitset<8>(fileData[position]).to_ulong(), fileData, position));

    stringstream stream;
    stream << (unsigned int)(unsigned char)(classFile.constantPool[i].tag);
    string tag_info = stream.str();
    int tag = stoi(tag_info);
    if (tag == 5 || tag == 6) {
      CPInfo cp_info;
      cp_info.tag = 99;
      classFile.constantPool.push_back(cp_info);
      i++;
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
    uint16_t inter_info;
    inter_info = getDatafromArray(fileData, position, position + 2, inter_info);
    position = position + 2;

    classFile.interfaces.push_back(inter_info);
  }

  classFile.fieldsCount =
      getDatafromArray(fileData, position, position + 2, classFile.fieldsCount);
  position = position + 2;

  for (int i = 0; i < classFile.fieldsCount; i++) {
    FieldInfo fields;
    fields.access_flags =
        getDatafromArray(fileData, position, position + 2, fields.access_flags);
    position = position + 2;

    fields.name_index =
        getDatafromArray(fileData, position, position + 2, fields.name_index);
    position = position + 2;

    fields.descriptor_index = getDatafromArray(fileData, position, position + 2,
                                               fields.descriptor_index);
    position = position + 2;

    fields.attributes_count = getDatafromArray(fileData, position, position + 2,
                                               fields.attributes_count);
    position = position + 2;

    for (int j = 0; j < fields.attributes_count; j++) {
      AttributeInfo attr_info;
      attr_info.attribute_name_index = getDatafromArray(
          fileData, position, position + 2, attr_info.attribute_name_index);
      position = position + 2;

      attr_info.attribute_length = getDatafromArray(
          fileData, position, position + 4, attr_info.attribute_length);
      position = position + 4;

      int attr_lenght = (int)attr_info.attribute_length;
      for (int k = 0; k < attr_lenght; k++) {
        uint8_t info;
        info = getDatafromArray(fileData, position, position + 1, info);
        position = position + 1;

        attr_info.info.push_back(info);
      }

      fields.attributes.push_back(attr_info);
    }
    classFile.fields.push_back(fields);
  }

  classFile.methodsCount = getDatafromArray(fileData, position, position + 2,
                                            classFile.methodsCount);
  position = position + 2;
  for (int i = 0; i < classFile.methodsCount; i++) {
    MethodInfo methods;
    methods.access_flags = getDatafromArray(fileData, position, position + 2,
                                            methods.access_flags);
    position = position + 2;

    methods.name_index =
        getDatafromArray(fileData, position, position + 2, methods.name_index);
    position = position + 2;

    methods.descriptor_index = getDatafromArray(
        fileData, position, position + 2, methods.descriptor_index);
    position = position + 2;

    methods.attributes_count = getDatafromArray(
        fileData, position, position + 2, methods.attributes_count);
    position = position + 2;

    for (int j = 0; j < methods.attributes_count; j++) {
      AttributeInfo attr_info;
      attr_info.attribute_name_index = getDatafromArray(
          fileData, position, position + 2, attr_info.attribute_name_index);
      position = position + 2;

      attr_info.attribute_length = getDatafromArray(
          fileData, position, position + 4, attr_info.attribute_length);
      position = position + 4;

      int attr_lenght = (int)attr_info.attribute_length;
      for (int k = 0; k < attr_lenght; k++) {
        uint8_t info;
        info = getDatafromArray(fileData, position, position + 1, info);
        position = position + 1;
        attr_info.info.push_back(info);
      }
      methods.attributes.push_back(attr_info);
    }
    classFile.methods.push_back(methods);
  }

  classFile.attributesCount = getDatafromArray(fileData, position, position + 2,
                                               classFile.attributesCount);
  position = position + 2;

  for (int j = 0; j < classFile.attributesCount; j++) {
    AttributeInfo attr_info;
    attr_info.attribute_name_index = getDatafromArray(
        fileData, position, position + 2, attr_info.attribute_name_index);
    position = position + 2;

    attr_info.attribute_length = getDatafromArray(
        fileData, position, position + 4, attr_info.attribute_length);
    position = position + 4;

    int attr_lenght = (int)attr_info.attribute_length;
    for (int k = 0; k < attr_lenght; k++) {
      uint8_t info;
      info = getDatafromArray(fileData, position, position + 1, info);
      position = position + 1;
      attr_info.info.push_back(info);
    }
    classFile.attributes.push_back(attr_info);
  }
};
