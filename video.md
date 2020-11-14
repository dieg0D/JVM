## Para Compilar

Utilize o comando `make` na raiz do diretório. O `Makefile` irá utilizar o
comando de compilação `g++ src/*.cpp -std=c++11 -Wall -o bin/jvm` .

## Para Executar

### Exibidor

Entre na pasta **bin** e rode o comando `./jvm <arquivo.class>`, substituindo o `<arquivo.class>` pelo arquivo que deseja testar. Exemplo: `.\bin\jvm.exe -e .\examples\HelloWorld.class` .

### Interpretador

Entre na pasta **bin** e rode o comando `./jvm <arquivo.class>`, substituindo o `<arquivo.class>` pelo arquivo que deseja testar. Exemplo: `.\bin\jvm.exe -i .\examples\HelloWorld.class` .

## JVM testes:

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
- [ ] conversao de e para cat 2
- [x] iteracao
- [ ] switches
- [ ] fields
- [ ] interfaces
- [x] recursao
- [ ] metodos estaticos
- [ ] metodos nao estaticos
- [ ] objetos
- [x] operacoes de retorno
- [ ] operacoes de manipulacao de pilha
- [x] consistencia
- [ ] exceptions
- [x] invokes
- [ ] polimorfismo e reescrita

A gente tem operações aritiméticas e lógicas com todos os tipos elementares, tem prints, valida consistencia (nome arquivo), tem switch case menos pro caso default, tem comparação, tem invokes, tem deslocamento.

A gente não tem arrays, não tem iterações, não tem recursividade, não tem operações com retorno, não tem objetos, não tem métodos não estáticos, não tem polimorfismo.
