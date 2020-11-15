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

void printCode(CodeAttribute attribute) {
  cout << endl << "Bytecode-----------" << endl << endl;
  int length = attribute.codeLength;
  uint8_t *bytecode = attribute.code;
  for (int i = 0; i < length; i++) {
    uint8_t opcode = bytecode[i];

    cout << i << " " << get_mnemonic(opcode).first << " ";

    if (opcode == wide) {
      uint8_t modifiedOpcode = bytecode[++i];
      cout << get_mnemonic(modifiedOpcode).first << " ";

      if ((modifiedOpcode >= iload && modifiedOpcode <= aload) ||
          (modifiedOpcode >= istore && modifiedOpcode <= astore) ||
          (modifiedOpcode == ret)) {
        uint8_t indexbyte1 = bytecode[++i];
        uint8_t indexbyte2 = bytecode[++i];
        uint16_t index = (indexbyte1 << 8) | indexbyte2;

        cout << index << endl;
      } else if (modifiedOpcode == iinc) {
        uint8_t indexbyte1 = bytecode[++i];
        uint8_t indexbyte2 = bytecode[++i];
        uint16_t index = (indexbyte1 << 8) | indexbyte2;

        uint8_t constbyte1 = bytecode[++i];
        uint8_t constbyte2 = bytecode[++i];
        int16_t constImmediate = (constbyte1 << 8) | constbyte2;
        cout << index << " by " << constImmediate << endl;
      }
    } else if (opcode == tableswitch) {
      int baseAddress = i;
      i++;
      while (i % 4 != 0) {
        i++;
      }

      uint8_t defaultByte1 = bytecode[i++];
      uint8_t defaultByte2 = bytecode[i++];
      uint8_t defaultByte3 = bytecode[i++];
      uint8_t defaultByte4 = bytecode[i++];
      int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) |
                             (defaultByte3 << 8) | defaultByte4;

      uint8_t lowByte1 = bytecode[i++];
      uint8_t lowByte2 = bytecode[i++];
      uint8_t lowByte3 = bytecode[i++];
      uint8_t lowByte4 = bytecode[i++];
      int32_t low =
          (lowByte1 << 24) | (lowByte2 << 16) | (lowByte3 << 8) | lowByte4;

      uint8_t highByte1 = bytecode[i++];
      uint8_t highByte2 = bytecode[i++];
      uint8_t highByte3 = bytecode[i++];
      uint8_t highByte4 = bytecode[i++];
      int32_t high =
          (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

      cout << low << " to " << high << endl;

      for (int j = low; j <= high; j++) {
        uint8_t jumpByte1 = bytecode[i++];
        uint8_t jumpByte2 = bytecode[i++];
        uint8_t jumpByte3 = bytecode[i++];
        uint8_t jumpByte4 = bytecode[i++];
        int32_t jump = (jumpByte1 << 24) | (jumpByte2 << 16) |
                       (jumpByte3 << 8) | jumpByte4;

        string sign = jump > 0 ? "+" : "";
        printf("\t%d:    %d (%s%d)\n", j, baseAddress + jump, sign.c_str(),
               jump);
      }
      string sign = defaultValue > 0 ? "+" : "";
      printf("\tdefault:    %d (%s%d)\n", baseAddress + defaultValue,
             sign.c_str(), defaultValue);
      i--;
    } else if (opcode == lookupswitch) {
      int baseAddress = i;
      i++;
      while (i % 4 != 0) {
        i++;
      }

      uint8_t defaultByte1 = bytecode[i++];
      uint8_t defaultByte2 = bytecode[i++];
      uint8_t defaultByte3 = bytecode[i++];
      uint8_t defaultByte4 = bytecode[i++];
      int32_t defaultValue = (defaultByte1 << 24) | (defaultByte2 << 16) |
                             (defaultByte3 << 8) | defaultByte4;

      uint8_t npairs1 = bytecode[i++];
      uint8_t npairs2 = bytecode[i++];
      uint8_t npairs3 = bytecode[i++];
      uint8_t npairs4 = bytecode[i++];
      int32_t npairs =
          (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;
      cout << npairs << endl;

      for (int j = 0; j < npairs; j++) {
        uint8_t matchByte1 = bytecode[i++];
        uint8_t matchByte2 = bytecode[i++];
        uint8_t matchByte3 = bytecode[i++];
        uint8_t matchByte4 = bytecode[i++];
        int32_t match = (matchByte1 << 24) | (matchByte2 << 16) |
                        (matchByte3 << 8) | matchByte4;
        uint8_t offsetByte1 = bytecode[i++];
        uint8_t offsetByte2 = bytecode[i++];
        uint8_t offsetByte3 = bytecode[i++];
        uint8_t offsetByte4 = bytecode[i++];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) |
                         (offsetByte3 << 8) | offsetByte4;
        string sign = offset > 0 ? "+" : "";
        printf("\t%d:    %d (%s%d)\n", match, baseAddress + offset,
               sign.c_str(), offset);
      }
      string sign = defaultValue > 0 ? "+" : "";
      printf("\tdefault:    %d (%s%d)\n", baseAddress + defaultValue,
             sign.c_str(), defaultValue);
      i--;
    }
    // Operacoes que nao tem bytes adicionais
    else if (get_mnemonic(opcode).second == 0) {
      cout << endl;
    } else if (get_mnemonic(opcode).second == 1) {
      uint8_t byte = bytecode[++i];

      // Operacoes que exigem referencia a constant pool
      if (opcode == ldc) {
        uint8_t index = byte;
        cout << "#" << +index << " <"
             << getCPInfoFirst(classFile.constantPool, index - 1) << ">"
             << endl;
      } else if ((opcode == bipush)) {
        int32_t value = (int8_t)byte;
        cout << value << endl;
      } else if ((opcode >= iload && opcode <= aload) ||
                 (opcode >= istore && opcode <= astore) || (opcode == ret)) {
        uint8_t index = byte;
        cout << +index << endl;
      } else if (opcode == newarray) {
        int atype = byte;
        cout << atype << " ";
        switch (atype) {
          case T_BOOLEAN:
            cout << "(bool)";
            break;
          case T_CHAR:
            cout << "(char)";
            break;
          case T_FLOAT:
            cout << "(float)";
            break;
          case T_DOUBLE:
            cout << "(double)";
            break;
          case T_BYTE:
            cout << "(byte)";
            break;
          case T_SHORT:
            cout << "(short)";
            break;
          case T_INT:
            cout << "(int)";
            break;
          case T_LONG:
            cout << "(long)";
            break;
        }
        cout << endl;
      }
    } else if (get_mnemonic(opcode).second == 2) {
      uint8_t byte1 = bytecode[++i];
      uint8_t byte2 = bytecode[++i];
      if (opcode == sipush) {
        int16_t immediate = ((int16_t)byte1 << 8) | byte2;
        cout << immediate << endl;
      } else if (opcode == iinc) {
        uint8_t index = byte1;
        int8_t constImmediate = byte2;
        cout << +index << " by " << +constImmediate << endl;
      } else if ((opcode >= ifeq && opcode <= jsr) || (opcode == ifnull) ||
                 (opcode == ifnonnull)) {
        int16_t offset = ((int16_t)byte1 << 8) | byte2;
        int index = i - 2 + offset;
        string sign = offset > 0 ? "+" : "";

        cout << index << " (" << sign << offset << ")" << endl;
      } else if ((opcode >= getstatic && opcode <= invokestatic)) {
        uint16_t index = ((uint16_t)byte1 << 8) | byte2;
        string methodName = getCPInfoFirst(classFile.constantPool, index - 1);

        string descriptor =
            getCPInfoSecond(classFile.constantPool, index - 1).second;

        cout << "#" << index << " <" << methodName << "." << descriptor << ">"
             << endl;
      } else if ((opcode == ldc_w) || (opcode == ldc2_w) || (opcode == newOp) ||
                 (opcode == anewarray) || (opcode == checkcast) ||
                 (opcode == instanceof)) {
        uint16_t index = ((uint16_t)byte1 << 8) | byte2;
        string className = getCPInfoFirst(classFile.constantPool, index - 1);
        cout << "#" << index << " <" << className << ">" << endl;
      }
    } else if (get_mnemonic(opcode).second == 3) {
      uint8_t byte1 = bytecode[++i];
      uint8_t byte2 = bytecode[++i];
      uint8_t byte3 = bytecode[++i];
      if (opcode == multianewarray) {
        uint16_t index = ((uint16_t)byte1 << 8) | byte2;
        uint8_t dimensions = byte3;

        cout << "#" << index << " <"
             << getCPInfoFirst(classFile.constantPool, index - 1) << "> "
             << "dim " << +dimensions << endl;
      }
    } else if (get_mnemonic(opcode).second == 4) {
      uint8_t byte1 = bytecode[++i];
      uint8_t byte2 = bytecode[++i];
      uint8_t byte3 = bytecode[++i];
      uint8_t byte4 = bytecode[++i];

      if (opcode == goto_w || opcode == jsr_w) {
        int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
        int index = i - 2 + offset;
        string sign = offset > 0 ? "+" : "";

        cout << index << " (" << sign << offset << ")" << endl;
      } else if ((opcode == invokeinterface || opcode == invokedynamic)) {
        int16_t index = ((int16_t)byte1 << 8) | byte2;
        string methodName = getCPInfoFirst(classFile.constantPool, index - 1);

        string descriptor =
            getCPInfoSecond(classFile.constantPool, index - 1).second;
        cout << "#" << index << " <" << methodName << "." << descriptor << ">"
             << endl;
      }
    }
  }

  for (int j = 0; j < attribute.attributesCount; j++) {
    string name =
        getCPInfoFirst(classFile.constantPool,
                       attribute.attributes[j].attribute_name_index - 1);
    cout << endl << "\t [" << j << "] " << name << endl;
    cout << "\t\t Attribute name index: \tcp_info#"
         << attribute.attributes[j].attribute_name_index << " <" << name << ">"
         << endl;
    cout << "\t\t Attribute length:     \t" << dec
         << attribute.attributes[j].attribute_length << endl;
    cout << "Specific info --------------------------------------------" << endl
         << endl;
    printAttributes(name, attribute.attributes[j]);
  }
}

void printAttributes(string attributeName, AttributeInfo attr_info) {
  if (attributeName == "Code") {
    cout << "Misc----------------" << endl << endl;
    cout << "Max Stack:               " << attr_info.code.maxStack << endl;
    cout << "Maximum local variables: " << attr_info.code.maxLocals << endl;
    cout << "Code Length:             " << attr_info.code.codeLength << endl;
    printCode(attr_info.code);
  } else if (attributeName == "ConstantValue") {
    cout << "Constante value Index: cp info #"
         << attr_info.constantValue.constantValueIndex << " "
         << getCPInfoFirst(classFile.constantPool,
                           attr_info.constantValue.constantValueIndex - 1)
         << endl;
  } else if (attributeName == "Exceptions") {
    ExceptionsAttribute exceptionTable = attr_info.exceptions;

    printf("Nr.\tException\tVerbose\n");

    for (int i = 0; i < attr_info.exceptions.numberOfExceptions; i++) {
      uint16_t exceptionIndex = exceptionTable.execeptionIndexTable;
      string verbose =
          getCPInfoFirst(classFile.constantPool, exceptionIndex - 1);

      printf("%d\tcp_info #%d\t%s\n", i, exceptionIndex, verbose.c_str());
    }
  } else if (attributeName == "InnerClasses") {
    ClassInfo *classes = attr_info.innerClasses.classes;

    printf("Nr.\tInner Class\t\tOuter Class\tInner Name\tAccess Flags\n");

    for (int i = 0; i < attr_info.innerClasses.numberOfClasses; i++) {
      uint16_t innerClassInfoIndex = classes[i].innerClassInfoIndex;
      uint16_t outerClassInfoIndex = classes[i].outerClassInfoIndex;
      uint16_t innerNameIndex = classes[i].innerNameIndex;
      uint16_t innerClassAccessFlags = classes[i].innerClassAccessFlags;
      string innerClassName =
          getCPInfoFirst(classFile.constantPool, innerClassInfoIndex - 1);
      string outerClassName =
          getCPInfoFirst(classFile.constantPool, outerClassInfoIndex - 1);
      string innerName =
          getCPInfoFirst(classFile.constantPool, innerNameIndex - 1);
      string flags = accessFlagsDecoder(innerClassAccessFlags, 0);

      printf("%d\tcp_info #%d\t\tcp_info #%d\tcp_info#%d\t0x%04x ", i,
             innerClassInfoIndex, outerClassInfoIndex, innerNameIndex,
             innerClassAccessFlags);
      cout << flags << endl;
      printf("\t%s\t%s\t%s\n", innerClassName.c_str(), outerClassName.c_str(),
             innerName.c_str());
    }
  } else if (attributeName == "SourceFile") {
    cout << "Source File name index:     cp_info# "
         << attr_info.sourceFile.sourcefileIndex << " <"
         << getCPInfoFirst(classFile.constantPool,
                           attr_info.sourceFile.sourcefileIndex - 1)
         << ">" << endl;
    ;
  } else if (attributeName == "LineNumberTable") {
    uint16_t lineNumberTableLength =
        attr_info.lineNumberTable.lineNumberTableLength;
    LineNumber *lineNumberTable = attr_info.lineNumberTable.lineNumberTable;

    printf("Nr.\tStart PC\tLineNumber\n");
    for (int i = 0; i < lineNumberTableLength; i++) {
      printf("%d\t%d\t\t%d\n", i, lineNumberTable[i].startPC,
             lineNumberTable[i].lineNumber);
    }
  } else if (attributeName == "LocalVariableTable") {
    uint16_t localVariableTableLength =
        attr_info.localVariableTable.localVariableTableLength;
    LocalVariable *localVariableTable =
        attr_info.localVariableTable.localVariableTable;

    printf("Nr.\tStart PC\tLength\tIndex\tName\t\t\tDescriptor\n");
    for (int i = 0; i < localVariableTableLength; i++) {
      uint16_t startPC = localVariableTable[i].startPC;
      uint16_t length = localVariableTable[i].length;
      uint16_t index = localVariableTable[i].index;
      uint16_t nameIndex = localVariableTable[i].nameIndex;
      uint16_t descriptorIndex = localVariableTable[i].descriptorIndex;
      string name = getCPInfoFirst(classFile.constantPool, nameIndex - 1);
      string descriptor =
          getCPInfoFirst(classFile.constantPool, descriptorIndex - 1);

      printf("%d\t%d\t\t%d\t%d\tcp_info #%d\t\tcp_info #%d\n", i, startPC,
             length, index, nameIndex, descriptorIndex);
      printf("\t\t\t\t\t\t\t\t%s\r\t\t\t\t\t%s\n", descriptor.c_str(),
             name.c_str());
    }
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
      cout << "Specific info --------------------------------------------"
           << endl
           << endl;
      printAttributes(name, classFile.methods[i].attributes[j]);
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
      cout << "Specific info --------------------------------------------"
           << endl
           << endl;
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
