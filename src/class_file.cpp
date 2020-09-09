#include "../include/class_file.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>
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
}

void printFile(string file) {
  vector<BYTE> fileData = readFile(file);
  for (auto i : fileData) {
    cout << bitset<8>(i);
  }
}
