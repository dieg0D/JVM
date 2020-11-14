# JVM

Este repositório contém o Projeto final da Disciplina Software Básico de 2020/1. O trabalho consiste em implementar em C/C++ uma versão da Java Virtual Machine com um Leitor/Exibidor de bytecode.

Alunos:

- Diego Antônio Barbosa Cardoso - 16/0005116
- Ivan Bastos Lancellotti - 16/0009057
- João Marcos Schmaltz Duda - 15/0132131
- Kevin da Silva Souto - 16/0046688
- Matheus Rodrigues Guimarães - 15/0141661

## Para Compilar

Utilize o comando `make` na raiz do diretório. O `Makefile` irá utilizar o
comando de compilação `g++ src/*.cpp -std=c++11 -Wall -o bin/jvm` .

## Para Executar

Entre na pasta **bin** e rode o comando `./jvm <arquivo.class>`, substituindo o `<arquivo.class>` pelo arquivo que deseja testar. Exemplo: `.\bin\jvm.exe .\examples\HelloWorld.class` .

## JVM - O que funciona?

- [x] arrays simples
- [x] arrays.length
- [x] arrays multidimensionais
- [x] arrays de referencia
- [x] doubles
- [x] floats
- [x] longs
- [x] inteiros
- [x] shorts
- [x] strings
- [x] desvios com cat 1
- [x] operacoes logicas com cat1
- [x] operacoes de deslocamento com cat 1
- [x] operacoes aritimeticas de cat 2
- [x] operacoes de deslocamento de longs
- [x] system.out.println (int, float, string e booleano)
- [x] conversao de e para cat 2
- [x] iteracao
- [x] switches
- [x] fields
- [ ] interfaces
- [x] recursao
- [x] metodos estaticos
- [x] metodos nao estaticos
- [ ] objetos
- [x] operacoes de retorno
- [ ] operacoes de manipulacao de pilha
- [x] consistencia
- [ ] exceptions
- [x] invokes
- [ ] polimorfismo e reescrita
