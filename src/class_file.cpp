#include "../include/class_file.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
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

    position =
        position + nextPosition(bitset<8>(fileData[position]).to_ulong(),
                                fileData, position);

    // cout << i << " " << position << endl;
  }

  // classFile.accessFlags = getDatafromArray(
  //     fileData, position + 10, position + 12, classFile.accessFlags);
  // cout << hex << uppercase << classFile.accessFlags;
};
