.DEFAULT_GOAL:=all
CC=g++
CPPFLAGS+= -I../core/include
CPPFLAGS+= --std=c++11
CPPFLAGS+= -g
BUILD_DIR=build
BIN_DIR=bin

clean:
	rm -r $(BUILD_DIR)
	rm -r $(BIN_DIR)

config: 
	$(if $(filter $(OS), Windows_NT), cmake . -B$(BUILD_DIR) -G "MinGW Makefiles", cmake . -B$(BUILD_DIR))

all: build/Makefile
	cd build && make

build/Makefile: src/lexer/lex.yy.cpp src/parser/parser.yy.cpp
	make config


src/lexer/lex.yy.cpp: src/lexer/c.l
	flex -o $@ $^

src/parser/parser.yy.cpp: src/parser/c.y
	bison -o $@ $^