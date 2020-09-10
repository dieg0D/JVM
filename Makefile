OBJS = src/*.cpp

all : $(OBJS)
	@mkdir -p bin
	g++ $(OBJS) -std=c++11 -Wall -o bin/jvm
