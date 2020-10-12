#include "../include/class_file.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

#include "../include/common.hpp"
#include "../include/cp_info.hpp"
using namespace std;

int lastPosition = 0;

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

  lastPosition = end;

  return bitset<sizeof(size) * 8>(data).to_ulong();
};

CPInfo setConstantInfo(unsigned int tag, vector<BYTE> fileData, int position) {
  CPInfo constant;

  constant.tag = tag;

  constant.CONSTANT_Methodref_info.class_index =
      getDatafromArray(fileData, position + 1, position + 3,
                       constant.CONSTANT_Methodref_info.class_index);

  constant.CONSTANT_Methodref_info.name_and_type_index =
      getDatafromArray(fileData, position + 3, position + 5,
                       constant.CONSTANT_Methodref_info.name_and_type_index);

  cout << constant.tag;

  return constant;
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
  int i = 0;
  while (i < classFile.constantPoolCount - 1) {
    CPInfo aux = setConstantInfo(bitset<8>(fileData[10 + i]).to_ulong(),
                                 fileData, 10 + i);

    break;
  }

  // classFile.accessFlags = getDatafromArray(
  //     fileData, 11 + ((classFile.constantPoolCount - 1)),
  //     13 + ((classFile.constantPoolCount - 1)), classFile.accessFlags);
  // cout << hex << uppercase << classFile.accessFlags;
};
