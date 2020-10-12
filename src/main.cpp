#include <bitset>
#include <fstream>
#include <iostream>

#include "../include/class_file.hpp"
#include "../include/class_printer.hpp"
#include "../include/common.hpp"
using namespace std;

ClassFile classFile;

int main(int argc, char* argv[]) {
  // Verifica se os argumentos foram passados
  if (argc == 2) {
    cout << "[main] "
         << "Arquivo recebido, tentado abrir..." << endl
         << endl;
    loadFile(argv[1]);
    // printClassFile();
  } else {
    cout << "[main] "
         << "O programa precisa de um arquivo.class para funcionar. Por favor "
            "insira um arquivo =D"
         << endl;
    return -1;
  }
  return 0;
}
