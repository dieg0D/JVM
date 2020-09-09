# JVM

Este repositório contém o Projeto final da Disciplina Software Básico de 2020/1. O trabalho consiste em implementar em C/C++ uma versão da Java Virtual Machine com um Leitor/Exibidor de bytecode.

Alunos: 
- Diego Antônio Barbosa Cardoso - 16/0005116
- Ivan Bastos Lancellotti       - 16/0009057
- João Marcos Schmaltz Duda     - 15/0132131
- Kevin da Silva Souto          - 16/0046688 
- Matheus Rodrigues Guimarães   - 15/0141661

## Para Compilar

Utilize o comando `make` na raiz do diretório. O `Makefile` irá utilizar o
comando de compilação `g++ src/*.cpp -std=c++11 -Wall -o bin/jvm` .

## Para Executar

Entre na pasta **bin** e rode o comando `./jvm <arquivo.class>`, substituindo o `<arquivo.class>` pelo arquivo que deseja testar. Exemplo: `.\bin\jvm.exe .\examples\HelloWorld.class` .




