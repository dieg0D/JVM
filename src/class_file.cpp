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

CPInfo setConstantInfo(unsigned int tag, vector<BYTE> fileData, int position) {
  CPInfo constant;

  // constant.tag = tag;

  // constant.CONSTANT_Methodref_info.class_index =
  //     getDatafromArray(fileData, position + 1, position + 3,
  //                      constant.CONSTANT_Methodref_info.class_index);

  // constant.CONSTANT_Methodref_info.name_and_type_index =
  //     getDatafromArray(fileData, position + 3, position + 5,
  //                      constant.CONSTANT_Methodref_info.name_and_type_index);

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

string intToHex(uint16_t integer) {
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

  string hexFlag = intToHex(flag);
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

  // atribuindo o hex ao Class File e retornando string completa.
  classFile.accessFlags = std::stoi(flagInHexString, 0, 16);

  return classFileAccessFlagString;
}

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
    // CPInfo aux = setConstantInfo(bitset<8>(fileData[10 + i]).to_ulong(),
    //                              fileData, 10 + i + position);
    position = position + nextPosition(bitset<8>(fileData[position]).to_ulong(),
                                       fileData, position);
    // cout << i << " " << position << endl;
  }

  accessFlagsDecoder(getDatafromArray(fileData, position, position + 2,
                                      classFile.accessFlags));
};
