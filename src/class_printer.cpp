#include "../include/class_printer.hpp"

#include <string.h>

#include <bitset>
#include <iostream>
#include <sstream>

#include "../include/common.hpp"
#include "../include/instructions.hpp"
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
    default:
      return "0";
  }
}
string integerToHex(uint16_t integer) {
  stringstream aux;
  aux << hex << uppercase << integer;
  return aux.str();
}

// essa função cuida de todas as access flags de classFile, Fields e Methods,
// variando qual processar de acordo com flag_type
string accessFlagsDecoder(uint16_t flag, int flag_type) {
  bool acc_public = false;
  bool acc_private = false;
  bool acc_protected = false;
  bool acc_static = false;
  bool acc_final = false;
  bool acc_volatile = false;
  bool acc_transient = false;
  bool acc_synchronized = false;
  bool acc_bridge = false;
  bool acc_super = false;
  bool acc_varargs = false;
  bool acc_native = false;
  bool acc_interface = false;
  bool acc_abstract = false;
  bool acc_strict = false;
  bool acc_synthetic = false;
  bool acc_annotation = false;
  bool acc_enum = false;

  string hexFlag = integerToHex(flag);
  int hexSize = hexFlag.length();
  string flagInHexString;
  string classFileAccessFlagString;

  // append 0s ao começo da string (precisa ser sem 4 numeros)
  flagInHexString = std::string(3, '0').append(hexFlag);
  if (hexSize > 1) {
    flagInHexString = std::string(2, '0').append(hexFlag);
  }
  if (hexSize > 2) {
    flagInHexString = std::string(1, '0').append(hexFlag);
  }
  if (hexSize > 3) {
    flagInHexString = std::string(0, '0').append(hexFlag);
  }

  // se flag_type for 0, roda accessflag de class, 1 roda de fields, 2 roda de
  // methods
  if (flag_type == 0) {
    // set flags
    switch (hexFlag[hexSize - 1]) {
      case '1':
        acc_public = true;
        break;
    }
    if (hexSize > 1) {
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
          cout << "Interface não pode ser declarada como Final, Super ou Enum. "
                  "\n";
        }
      }
    } else {
      if (acc_annotation == true) {
        cout << "Uma classe não pode ser declarada como Annotation. \n";
      }
      if (acc_final == true && acc_abstract == true) {
        cout << "Classes não podem ser declaradas como Final e Abstract ao "
                "mesmo "
                "tempo. \n";
      }
    }
    if (acc_annotation == true && acc_interface == false) {
      cout << "Annotations devem também ser declaradas como Interface. \n";
    }

    // construir string para exibir no General Info
    classFileAccessFlagString = "0x" + flagInHexString + " [ ";
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
  } else {
    if (flag_type == 1) {
      // set flags
      switch (hexFlag[hexSize - 1]) {
        case '1':
          acc_public = true;
          break;
        case '2':
          acc_private = true;
          break;
        case '4':
          acc_protected = true;
          break;
        case '8':
          acc_static = true;
          break;
        case '9':
          acc_public = true;
          acc_static = true;
          break;
        case 'A':
          acc_private = true;
          acc_static = true;
          break;
        case 'C':
          acc_protected = true;
          acc_static = true;
          break;
      }
      if (hexSize > 1) {
        switch (hexFlag[hexSize - 2]) {
          case '1':
            acc_final = true;
            break;
          case '4':
            acc_volatile = true;
            break;
          case '8':
            acc_transient = true;
            break;
          case '5':
            acc_final = true;
            acc_volatile = true;
            break;
          case '9':
            acc_final = true;
            acc_transient = true;
            break;
          case 'C':
            acc_volatile = true;
            acc_transient = true;
            break;
          case 'D':
            acc_final = true;
            acc_volatile = true;
            acc_transient = true;
            break;
        }
      }
      if (hexSize > 3) {
        switch (hexFlag[hexSize - 4]) {
          case '1':
            acc_synthetic = true;
            break;
          case '4':
            acc_enum = true;
            break;
          case '5':
            acc_synthetic = true;
            acc_enum = true;
            break;
        }
      }

      // flags validações

      /*TODO*/
      // vei desculpa, mas nao vai rolar. Sem tempo irmão

      // construir string para exibir no Fields
      classFileAccessFlagString = "0x" + flagInHexString + " [ ";
      if (acc_public == true) {
        classFileAccessFlagString = classFileAccessFlagString + "public ";
      };
      if (acc_private == true) {
        classFileAccessFlagString = classFileAccessFlagString + "private ";
      };
      if (acc_protected == true) {
        classFileAccessFlagString = classFileAccessFlagString + "protected ";
      };
      if (acc_static == true) {
        classFileAccessFlagString = classFileAccessFlagString + "static ";
      };
      if (acc_final == true) {
        classFileAccessFlagString = classFileAccessFlagString + "final ";
      };
      if (acc_volatile == true) {
        classFileAccessFlagString = classFileAccessFlagString + "volatile ";
      };
      if (acc_transient == true) {
        classFileAccessFlagString = classFileAccessFlagString + "transient ";
      };
      if (acc_synthetic == true) {
        classFileAccessFlagString = classFileAccessFlagString + "synthetic ";
      };
      if (acc_enum == true) {
        classFileAccessFlagString = classFileAccessFlagString + "enum ";
      };
      classFileAccessFlagString.pop_back();
      classFileAccessFlagString = classFileAccessFlagString + "]";

      return classFileAccessFlagString;
    } else {
      if (flag_type == 2) {
        // set flags
        switch (hexFlag[hexSize - 1]) {
          case '1':
            acc_public = true;
            break;
          case '2':
            acc_private = true;
            break;
          case '4':
            acc_protected = true;
            break;
          case '8':
            acc_static = true;
            break;
          case '9':
            acc_public = true;
            acc_static = true;
            break;
          case 'A':
            acc_private = true;
            acc_static = true;
            break;
          case 'C':
            acc_protected = true;
            acc_static = true;
            break;
        }
        if (hexSize > 1) {
          switch (hexFlag[hexSize - 2]) {
            case '1':
              acc_final = true;
              break;
            case '2':
              acc_synchronized = true;
              break;
            case '4':
              acc_bridge = true;
              break;
            case '8':
              acc_varargs = true;
              break;
            case '3':
              acc_final = true;
              acc_synchronized = true;
              break;
            case '5':
              acc_final = true;
              acc_bridge = true;
              break;
            case '9':
              acc_final = true;
              acc_varargs = true;
              break;
            case '6':
              acc_synchronized = true;
              acc_bridge = true;
              break;
            case 'A':
              acc_synchronized = true;
              acc_varargs = true;
              break;
            case 'C':
              acc_bridge = true;
              acc_varargs = true;
              break;
            case '7':
              acc_final = true;
              acc_synchronized = true;
              acc_bridge = true;
              break;
            case 'B':
              acc_final = true;
              acc_synchronized = true;
              acc_varargs = true;
              break;
            case 'E':
              acc_bridge = true;
              acc_synchronized = true;
              acc_varargs = true;
              break;
            case 'F':
              acc_final = true;
              acc_bridge = true;
              acc_synchronized = true;
              acc_varargs = true;
              break;
          }
        }
        if (hexSize > 2) {
          switch (hexFlag[hexSize - 2]) {
            case '1':
              acc_native = true;
              break;
            case '4':
              acc_abstract = true;
              break;
            case '8':
              acc_strict = true;
              break;
            case '5':
              acc_native = true;
              acc_abstract = true;
              break;
            case '9':
              acc_native = true;
              acc_strict = true;
              break;
            case 'C':
              acc_abstract = true;
              acc_strict = true;
              break;
            case 'D':
              acc_native = true;
              acc_abstract = true;
              acc_strict = true;
              break;
          }
        }
        if (hexSize > 3) {
          switch (hexFlag[hexSize - 4]) {
            case '1':
              acc_synthetic = true;
              break;
          }
        }

        // flags validações

        /*TODO*/
        // vei desculpa, mas nao vai rolar. Sem tempo irmão

        // construir string para exibir no Fields
        classFileAccessFlagString = "0x" + flagInHexString + " [ ";
        if (acc_public == true) {
          classFileAccessFlagString = classFileAccessFlagString + "public ";
        };
        if (acc_private == true) {
          classFileAccessFlagString = classFileAccessFlagString + "private ";
        };
        if (acc_protected == true) {
          classFileAccessFlagString = classFileAccessFlagString + "protected ";
        };
        if (acc_static == true) {
          classFileAccessFlagString = classFileAccessFlagString + "static ";
        };
        if (acc_final == true) {
          classFileAccessFlagString = classFileAccessFlagString + "final ";
        };
        if (acc_synchronized == true) {
          classFileAccessFlagString =
              classFileAccessFlagString + "synchronized ";
        };
        if (acc_bridge == true) {
          classFileAccessFlagString = classFileAccessFlagString + "bridge ";
        };
        if (acc_varargs == true) {
          classFileAccessFlagString = classFileAccessFlagString + "varargs ";
        };
        if (acc_native == true) {
          classFileAccessFlagString = classFileAccessFlagString + "native ";
        };
        if (acc_abstract == true) {
          classFileAccessFlagString = classFileAccessFlagString + "abstract ";
        };
        if (acc_strict == true) {
          classFileAccessFlagString = classFileAccessFlagString + "strict ";
        };
        if (acc_synthetic == true) {
          classFileAccessFlagString = classFileAccessFlagString + "synthetic ";
        };
        classFileAccessFlagString.pop_back();
        classFileAccessFlagString = classFileAccessFlagString + "]";

        return classFileAccessFlagString;
      } else {
        return "Access Flag mal definida.";
      }
    }
  }
}

string utf8Converter(uint8_t value) {
  stringstream stream;
  stream << (unsigned int)(unsigned char)(value);
  string convertedStr = stream.str();
  return convertedStr;
}

string getCPInfoFirst(vector<CPInfo> cp_info, int indice) {
  stringstream stream;
  stream << (unsigned int)(unsigned char)(cp_info[indice].tag);
  string tag_info = stream.str();
  int tag = stoi(tag_info);

  if (tag == 1) {
    return (char *)(cp_info[indice].CONSTANT_Utf8_info.bytes);
  }

  switch (tag) {
    case 7:
      return getCPInfoFirst(cp_info,
                            cp_info[indice].CONSTANT_Class_info.name_index - 1);
    case 9:
      return getCPInfoFirst(
          cp_info, cp_info[indice].CONSTANT_Fieldref_info.class_index - 1);
    case 10:
      return getCPInfoFirst(
          cp_info, cp_info[indice].CONSTANT_Methodref_info.class_index - 1);
    case 11:
      return getCPInfoFirst(
          cp_info,
          cp_info[indice].CONSTANT_InterfaceMethodref_info.class_index - 1);
    case 8:
      return getCPInfoFirst(
          cp_info, cp_info[indice].CONSTANT_String_info.string_index - 1);
    case 12:
      return getCPInfoFirst(
          cp_info, cp_info[indice].CONSTANT_NameAndType_info.name_index - 1);
    default:
      return "";
  }
}

pair<string, string> getCPInfoSecond(vector<CPInfo> cp_info, int indice) {
  stringstream stream;
  stream << (unsigned int)(unsigned char)(cp_info[indice].tag);
  string tag_info = stream.str();
  int tag = stoi(tag_info);

  if (tag == 1) {
    return make_pair((char *)(cp_info[indice].CONSTANT_Utf8_info.bytes), "");
  }
  switch (tag) {
    case 7:
      return getCPInfoSecond(
          cp_info, cp_info[indice].CONSTANT_Class_info.name_index - 1);
    case 9: {
      string second = getCPInfoFirst(
          cp_info,
          cp_info[indice].CONSTANT_Fieldref_info.name_and_type_index - 1);
      string first =
          getCPInfoSecond(
              cp_info,
              cp_info[indice].CONSTANT_Fieldref_info.name_and_type_index - 1)
              .first;
      return make_pair(first, second);
    }
    case 10: {
      string second = getCPInfoFirst(
          cp_info,
          cp_info[indice].CONSTANT_Methodref_info.name_and_type_index - 1);
      string first =
          getCPInfoSecond(
              cp_info,
              cp_info[indice].CONSTANT_Methodref_info.name_and_type_index - 1)
              .first;
      return make_pair(first, second);
    }
    case 11: {
      string second = getCPInfoFirst(
          cp_info,
          cp_info[indice].CONSTANT_InterfaceMethodref_info.name_and_type_index -
              1);
      string first =
          getCPInfoSecond(
              cp_info,
              cp_info[indice]
                      .CONSTANT_InterfaceMethodref_info.name_and_type_index -
                  1)
              .first;
      return make_pair(first, second);
    };
    case 8:
      return getCPInfoSecond(
          cp_info, cp_info[indice].CONSTANT_String_info.string_index - 1);
    case 12: {
      string second = getCPInfoFirst(
          cp_info,
          cp_info[indice].CONSTANT_NameAndType_info.descriptor_index - 1);
      string first =
          getCPInfoSecond(
              cp_info,
              cp_info[indice].CONSTANT_NameAndType_info.descriptor_index - 1)
              .first;
      return make_pair(first, second);
      return getCPInfoSecond(
          cp_info,
          cp_info[indice].CONSTANT_NameAndType_info.descriptor_index - 1);
    };
    default:
      return make_pair("", "");
  }
}

// begin é a posição que eu quero e end é aposição depois da que eu quero
unsigned int getData(vector<uint8_t> fileData, int begin, int end,
                     unsigned int size) {
  vector<uint8_t> newVec;

  newVec.insert(newVec.begin(), fileData.begin() + begin,
                fileData.begin() + end);
  string data = "";

  for (auto i : newVec) {
    data = (data + bitset<8>(i).to_string());
  }

  return bitset<sizeof(size) * 8>(data).to_ulong();
};

void func_exec(Frame currentFrame) {
  uint8_t* bytecode = currentFrame.codeAttribute.code;
  uint8_t opcode = bytecode[jvmThread.pc];
  uint32_t pc;

  switch (opcode) {
    // Constants
    case nop: {
      return get_mnemonic(opcode).second + 1;
    }
    case aconst_null: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_m1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_4: {
      return get_mnemonic(opcode).second + 1;
    }
    case iconst_5: {
      return get_mnemonic(opcode).second + 1;
    }
    case lconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fconst_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dconst_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dconst_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case bipush: {
      return get_mnemonic(opcode).second + 1;
    }
    case sipush: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc_w: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldc2_w: {
      return get_mnemonic(opcode).second + 1;
    }

    // Loads
    case iload: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case iload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case lload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case fload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case aload_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iaload: {
      return get_mnemonic(opcode).second + 1;
    }
    case laload: {
      return get_mnemonic(opcode).second + 1;
    }
    case faload: {
      return get_mnemonic(opcode).second + 1;
    }
    case daload: {
      return get_mnemonic(opcode).second + 1;
    }
    case aaload: {
      return get_mnemonic(opcode).second + 1;
    }
    case baload: {
      return get_mnemonic(opcode).second + 1;
    }
    case caload: {
      return get_mnemonic(opcode).second + 1;
    }
    case saload: {
      return get_mnemonic(opcode).second + 1;
    }

    // Stores
    case istore: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case istore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case lstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case fstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dstore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_0: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_1: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_2: {
      return get_mnemonic(opcode).second + 1;
    }
    case astore_3: {
      return get_mnemonic(opcode).second + 1;
    }
    case iastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case lastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case fastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case dastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case aastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case bastore: {
      return get_mnemonic(opcode).second + 1;
    }
    case castore: {
      return get_mnemonic(opcode).second + 1;
    }
    case sastore: {
      return get_mnemonic(opcode).second + 1;
    }

    // Stack
    case pop: {
      return get_mnemonic(opcode).second + 1;
    }
    case pop2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup_x1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup_x2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2_x1: {
      return get_mnemonic(opcode).second + 1;
    }
    case dup2_x2: {
      return get_mnemonic(opcode).second + 1;
    }
    case swapOp: {
      return get_mnemonic(opcode).second + 1;
    }

    // Math
    case iadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case ladd: {
      return get_mnemonic(opcode).second + 1;
    }
    case fadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case dadd: {
      return get_mnemonic(opcode).second + 1;
    }
    case isub: {
      return get_mnemonic(opcode).second + 1;
    }
    case lsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case fsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case dsub: {
      return get_mnemonic(opcode).second + 1;
    }
    case imul: {
      return get_mnemonic(opcode).second + 1;
    }
    case lmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case fmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case dmul: {
      return get_mnemonic(opcode).second + 1;
    }
    case idiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case ldivOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case fdiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case ddiv: {
      return get_mnemonic(opcode).second + 1;
    }
    case irem: {
      return get_mnemonic(opcode).second + 1;
    }
    case lrem: {
      return get_mnemonic(opcode).second + 1;
    }
    case frem: {
      return get_mnemonic(opcode).second + 1;
    }
    case dremOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case ineg: {
      return get_mnemonic(opcode).second + 1;
    }
    case lneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case fneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case dneg: {
      return get_mnemonic(opcode).second + 1;
    }
    case ishl: {
      return get_mnemonic(opcode).second + 1;
    }
    case lshl: {
      return get_mnemonic(opcode).second + 1;
    }
    case ishr: {
      return get_mnemonic(opcode).second + 1;
    }
    case lshr: {
      return get_mnemonic(opcode).second + 1;
    }
    case iushr: {
      return get_mnemonic(opcode).second + 1;
    }
    case lushr: {
      return get_mnemonic(opcode).second + 1;
    }
    case iand: {
      return get_mnemonic(opcode).second + 1;
    }
    case land: {
      return get_mnemonic(opcode).second + 1;
    }
    case ior: {
      return get_mnemonic(opcode).second + 1;
    }
    case lor: {
      return get_mnemonic(opcode).second + 1;
    }
    case ixor: {
      return get_mnemonic(opcode).second + 1;
    }
    case lxor: {
      return get_mnemonic(opcode).second + 1;
    }
    case iinc: {
      return get_mnemonic(opcode).second + 1;
    }

    // Conversions
    case i2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case l2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case f2d: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2i: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2l: {
      return get_mnemonic(opcode).second + 1;
    }
    case d2f: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2b: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2c: {
      return get_mnemonic(opcode).second + 1;
    }
    case i2s: {
      return get_mnemonic(opcode).second + 1;
    }

    // Comparisons
    case lcmp: {
      return get_mnemonic(opcode).second + 1;
    }
    case fcmpl: {
      return get_mnemonic(opcode).second + 1;
    }
    case fcmpg: {
      return get_mnemonic(opcode).second + 1;
    }
    case dcmpl: {
      return get_mnemonic(opcode).second + 1;
    }
    case dcmpg: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifne: {
      return get_mnemonic(opcode).second + 1;
    }
    case iflt: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifge: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifgt: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifle: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpne: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmplt: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpge: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmpgt: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_icmple: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_acmpeq: {
      return get_mnemonic(opcode).second + 1;
    }
    case if_acmpne: {
      return get_mnemonic(opcode).second + 1;
    }

    // Control
    case gotoOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case jsr: {
      return get_mnemonic(opcode).second + 1;
    }
    case ret: {
      return get_mnemonic(opcode).second + 1;
    }
    case tableswitch: {
      return get_mnemonic(opcode).second + 1;
    }
    case lookupswitch: {
      return get_mnemonic(opcode).second + 1;
    }
    case ireturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case lreturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case freturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case dreturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case areturn: {
      return get_mnemonic(opcode).second + 1;
    }
    case returnOp: {
      return get_mnemonic(opcode).second + 1;
    }

    // References
    case getstatic: {
      return get_mnemonic(opcode).second + 1;
    }
    case putstatic: {
      return get_mnemonic(opcode).second + 1;
    }
    case getfield: {
      return get_mnemonic(opcode).second + 1;
    }
    case putfield: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokevirtual: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokespecial: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokestatic: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokeinterface: {
      return get_mnemonic(opcode).second + 1;
    }
    case invokedynamic: {
      return get_mnemonic(opcode).second + 1;
    }
    case newOp: {
      return get_mnemonic(opcode).second + 1;
    }
    case newarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case anewarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case arraylength: {
      return get_mnemonic(opcode).second + 1;
    }
    case athrow: {
      return get_mnemonic(opcode).second + 1;
    }
    case checkcast: {
      return get_mnemonic(opcode).second + 1;
    }
    case instanceof: {
      return get_mnemonic(opcode).second + 1;
    }
    case monitorenter: {
      return get_mnemonic(opcode).second + 1;
    }
    case monitorexit: {
      return get_mnemonic(opcode).second + 1;
    }

    // Extended
    case wide: {
      return get_mnemonic(opcode).second + 1;
    }
    case multianewarray: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifnull: {
      return get_mnemonic(opcode).second + 1;
    }
    case ifnonnull: {
      return get_mnemonic(opcode).second + 1;
    }
    case goto_w: {
      return get_mnemonic(opcode).second + 1;
    }
    case jsr_w: {
      return get_mnemonic(opcode).second + 1;
    }
    default:
      return 0;
  }
}

void printAttributes(string attributeName, AttributeInfo attr_info) {
  if (attributeName == "Code") {
    cout << "Misc----------------" << endl << endl;
    cout << "Max Stack:               " << attr_info.code.maxStack << endl;
    cout << "Maximum local variables: " << attr_info.code.maxLocals << endl;
    cout << "Code Length:             " << attr_info.code.codeLength << endl;
  } else if (attributeName == "ConstantValue") {
  } else if (attributeName == "Exceptions") {
  } else if (attributeName == "InnerClasses") {
  } else if (attributeName == "SourceFile") {
    cout << "Source File name index:     cp_info# "
         << attr_info.sourceFile.sourcefileIndex << " <"
         << getCPInfoFirst(classFile.constantPool,
                           attr_info.sourceFile.sourcefileIndex - 1)
         << ">" << endl;
    ;

  } else if (attributeName == "LineNumberTable") {
  } else if (attributeName == "LocalVariableTable") {
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

  cout << "Access flags: " << accessFlagsDecoder(classFile.accessFlags, 0)
       << endl;

  string this_class =
      getCPInfoFirst(classFile.constantPool, classFile.thisClass - 1);
  cout << "This class: cp_info#" << classFile.thisClass << " <" << this_class
       << ">" << endl;
  if (classFile.superClass == 0) {
    cout << "Super class:  cp_info#" << classFile.superClass
         << " <invalid constant pool reference>" << endl;
  } else {
    string super_class =
        getCPInfoFirst(classFile.constantPool, classFile.superClass - 1);
    cout << "Super class:    cp_info#" << classFile.superClass << " <"
         << super_class << ">" << endl;
  }
  cout << "Interfaces count: " << dec << classFile.interfacesCount << endl;
  cout << "Fields count: " << dec << classFile.fieldsCount << endl;
  cout << "Methods count: " << dec << classFile.methodsCount << endl;
  cout << "Atributes count: " << dec << classFile.attributesCount << endl;
  cout << endl;
};

void printConstantPool() {
  cout << "____________________Constant Pool____________________" << endl
       << endl;
  vector<CPInfo> constant_pool = classFile.constantPool;
  for (int i = 0; i < classFile.constantPoolCount - 1; i++) {
    cout << endl << "[" << dec << i + 1 << "] ";
    int tag = stoi(utf8Converter(constant_pool[i].tag));
    switch (tag) {
      case 7: {
        cout << "CONSTANT_Class_info" << endl;
        string class_name = getCPInfoFirst(constant_pool, i);
        cout << "Class name: cp_info#"
             << constant_pool[i].CONSTANT_Class_info.name_index << " <"
             << class_name << "> " << endl;
      } break;
      case 9: {
        cout << "CONSTANT_Fieldref_info" << endl;
        string class_name = getCPInfoFirst(constant_pool, i);
        string name = getCPInfoSecond(constant_pool, i).first;
        string type = getCPInfoSecond(constant_pool, i).second;

        cout << "Class name:    cp_info#"
             << constant_pool[i].CONSTANT_Fieldref_info.class_index << " <"
             << class_name << "> " << endl;
        cout << "Name and type: cp_info#"
             << constant_pool[i].CONSTANT_Fieldref_info.name_and_type_index
             << " <" << type << " : " << name << "> " << endl;

      } break;
      case 10: {
        cout << "CONSTANT_Methodref_info" << endl;
        string class_name = getCPInfoFirst(constant_pool, i);
        string name = getCPInfoSecond(constant_pool, i).first;
        string type = getCPInfoSecond(constant_pool, i).second;

        cout << "Class name:    cp_info#"
             << constant_pool[i].CONSTANT_Methodref_info.class_index << " <"
             << class_name << "> " << endl;
        cout << "Name and type: cp_info#"
             << constant_pool[i].CONSTANT_Methodref_info.name_and_type_index
             << " <" << type << " : " << name << "> " << endl;

      } break;
      case 11: {
        cout << "CONSTANT_InterfaceMethodref_info" << endl;
        string class_name = getCPInfoFirst(constant_pool, i);
        string name = getCPInfoSecond(constant_pool, i).first;
        string type = getCPInfoSecond(constant_pool, i).second;

        cout << "Class name:    cp_info #"
             << constant_pool[i].CONSTANT_InterfaceMethodref_info.class_index
             << " <" << class_name << ">" << endl;
        cout << "Name and type: cp_info #"
             << constant_pool[i]
                    .CONSTANT_InterfaceMethodref_info.name_and_type_index
             << " <" << type << " : " << name << "> " << endl;

      } break;
      case 8: {
        cout << "CONSTANT_String_info" << endl;
        string value = getCPInfoFirst(constant_pool, i);
        cout << "String: cp_info#"
             << constant_pool[i].CONSTANT_String_info.string_index << " <"
             << value << "> " << endl;
      } break;
      case 3: {
        cout << "CONSTANT_Integer" << endl;
        cout << "Bytes: 0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Integer_info.bytes << endl;
        cout << "Integer: " << dec
             << constant_pool[i].CONSTANT_Integer_info.bytes << endl;

      } break;
      case 4: {
        cout << "CONSTANT_Float_info" << endl;
        cout << "Bytes: 0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Float_info.bytes << endl;
        float float_num;
        memcpy(&float_num, &constant_pool[i].CONSTANT_Float_info.bytes,
               sizeof(float));
        cout << "Float: " << float_num;
      } break;
      case 5: {
        cout << "CONSTANT_Long_info" << endl;
        cout << "High Bytes: 0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Long_info.high_bytes << endl;
        cout << "Low Bytes:  0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Long_info.low_bytes << endl;
        uint64_t long_value =
            ((uint64_t)constant_pool[i].CONSTANT_Long_info.high_bytes << 32) |
            constant_pool[i].CONSTANT_Long_info.low_bytes;
        cout << "Long:       " << dec << long_value << endl;

      } break;
      case 6: {
        cout << "CONSTANT_Double_info" << endl;
        cout << "High Bytes: 0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Double_info.high_bytes << endl;
        cout << "Low Bytes:  0x" << setfill('0') << setw(8) << hex
             << constant_pool[i].CONSTANT_Double_info.low_bytes << endl;
        uint64_t double_value =
            ((uint64_t)constant_pool[i].CONSTANT_Double_info.high_bytes << 32) |
            constant_pool[i].CONSTANT_Double_info.low_bytes;
        double double_num;
        memcpy(&double_num, &double_value, sizeof(double));
        cout << "Double:       " << dec << double_num << endl;

      } break;
      case 12: {
        cout << "CONSTANT_NameAndType_info" << endl;
        string name = getCPInfoFirst(constant_pool, i);
        string descriptor = getCPInfoSecond(constant_pool, i).first;

        cout << "Name:       cp_info #"
             << constant_pool[i].CONSTANT_NameAndType_info.name_index << " <"
             << name << ">" << endl;
        cout << "Descriptor: cp_info #"
             << constant_pool[i].CONSTANT_NameAndType_info.descriptor_index
             << " <" << descriptor << ">" << endl;
      } break;
      case 1: {
        cout << "CONSTANT_Utf8_info" << endl;
        string name = getCPInfoFirst(constant_pool, i);

        string descriptor = getCPInfoSecond(constant_pool, i).first;

        cout << "Length of byte array: "
             << constant_pool[i].CONSTANT_Utf8_info.length << endl;
        cout << "Length of string:     "
             << constant_pool[i].CONSTANT_Utf8_info.length << endl;
        cout << "String:               "
             << constant_pool[i].CONSTANT_Utf8_info.bytes << endl;
      } break;
      case 15: {
        cout << "CONSTANT_MethodHandle_info" << endl;
      } break;
      case 16: {
        cout << "CONSTANT_MethodType_info" << endl;
      } break;
      case 18: {
        cout << "CONSTANT_InvokeDynamic_info" << endl;
      } break;

      case 99: {
        cout << "(large numeric continued)" << endl;
      }
    }
  }
  cout << endl;
};

void printInterfaces() {
  cout << "______________________Interfaces_____________________" << endl
       << endl;

  for (int i = 0; i < classFile.interfacesCount; i++) {
    cout << endl << "[" << dec << i << "] ";

    string inter_name =
        getCPInfoFirst(classFile.constantPool, classFile.interfaces[i] - 1);

    cout << "Interface: cp_info #" << classFile.interfaces[i] << " <"
         << inter_name << " >" << endl
         << endl;
  }

  cout << endl;
};

void printFields() {
  cout << "_______________________Fields________________________" << endl
       << endl;
  for (int i = 0; i < classFile.fieldsCount; i++) {
    string name = getCPInfoFirst(classFile.constantPool,
                                 classFile.fields[i].name_index - 1);
    string descriptor = getCPInfoFirst(
        classFile.constantPool, classFile.fields[i].descriptor_index - 1);
    string access_flags =
        accessFlagsDecoder(classFile.fields[i].access_flags, 1);

    cout << endl << "[" << i << "] " << name << endl;
    cout << "\t Name:      \tcp_info#" << classFile.fields[i].name_index << " <"
         << name << ">" << endl;
    cout << "\t Description:\tcp_info#" << classFile.fields[i].descriptor_index
         << " <" << descriptor << ">" << endl;
    cout << "\t Access flags:\t" << access_flags << endl;

    for (int j = 0; j < classFile.fields[i].attributes_count; j++) {
      string name = getCPInfoFirst(
          classFile.constantPool,
          classFile.fields[i].attributes[j].attribute_name_index - 1);

      cout << "\t [" << j << "] " << name << endl;
      cout << "\t\t Attribute name index: \tcp_info#"
           << classFile.fields[i].attributes[j].attribute_name_index << " <"
           << name << ">" << endl;
      cout << "\t\t Attribute length:     \t" << dec
           << classFile.fields[i].attributes[j].attribute_length << endl;
    }

    cout << endl;
  }
  cout << endl;
};

void printMethods() {
  cout << "_______________________Methods_______________________" << endl
       << endl;
  for (int i = 0; i < classFile.methodsCount; i++) {
    string name = getCPInfoFirst(classFile.constantPool,
                                 classFile.methods[i].name_index - 1);
    string descriptor = getCPInfoFirst(
        classFile.constantPool, classFile.methods[i].descriptor_index - 1);
    string access_flags =
        accessFlagsDecoder(classFile.methods[i].access_flags, 2);

    cout << endl << "[" << i << "] " << name << endl;
    cout << "\t Name:      \tcp_info#" << classFile.methods[i].name_index
         << " <" << name << ">" << endl;
    cout << "\t Description:\tcp_info#" << classFile.methods[i].descriptor_index
         << " <" << descriptor << ">" << endl;
    cout << "\t Access flags:\t" << access_flags << endl;

    for (int j = 0; j < classFile.methods[i].attributes_count; j++) {
      string name = getCPInfoFirst(
          classFile.constantPool,
          classFile.methods[i].attributes[j].attribute_name_index - 1);

      cout << "\t [" << j << "] " << name << endl;
      cout << "\t\t Attribute name index: \tcp_info#"
           << classFile.methods[i].attributes[j].attribute_name_index << " <"
           << name << ">" << endl;
      cout << "\t\t Attribute length:     \t" << dec
           << classFile.methods[i].attributes[j].attribute_length << endl;

      printAttributes(name, classFile.methods[i].attributes[j]);
    }

    cout << endl;
  }
  cout << endl;
};

void printAttributes() {
  cout << "_____________________Attributes______________________" << endl
       << endl;
  for (int i = 0; i < classFile.attributesCount; i++) {
    string attr_name =
        getCPInfoFirst(classFile.constantPool,
                       classFile.attributes[i].attribute_name_index - 1);

    cout << endl << "[" << dec << i + 1 << "] " << attr_name << endl;
    cout << "Generic info ---------------------------------------------"
         << endl;
    cout << "Attribute name index: cp_info #"
         << classFile.attributes[i].attribute_name_index << " <" << attr_name
         << ">" << endl;
    cout << "Attribute length:     " << classFile.attributes[i].attribute_length
         << endl
         << endl;
    cout << "Specific info --------------------------------------------" << endl
         << endl;
    printAttributes(attr_name, classFile.attributes[i]);
  }

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
