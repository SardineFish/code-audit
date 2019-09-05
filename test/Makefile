.DEFAULT_GOAL := all
CC=g++
CPPFLAGS+= -I../core/include
CPPFLAGS+= --std=c++11
CPPFLAGS+= -g
BUILD_DIR=build
BIN_DIR=bin


define win_mkdir
	if not exist "$(abspath $(1))" mkdir "$(abspath $(1))"
endef

define mkdir
	$(if $(filter $(OS), Windows_NT), $(call win_mkdir,$(1)), mkdir -p $(1))
endef

define rm
	$(if $(filter $(OS), Windows_NT), rd /S /Q $(1), rm -rf $(1))
endef

clean:
	find -name "*.o" -type f -delete
	$(call rm, $(BUILD_DIR))
	$(call rm, $(BIN_DIR))
	
config: 
	$(if $(filter $(OS), Windows_NT), cmake . -B$(BUILD_DIR) -G "MinGW Makefiles", cmake . -B$(BUILD_DIR))

all: test-lexer test-diff
	cd ./build && make

../core/src/lexer/lex.yy.c: ../core/src/lexer/c.l
	cd ../core/src/lexer && flex c.l

test-lexer: src/lexer/test_lexer.o ../core/src/lexer/lex.yy.o
	g++ -o ./bin/test-lexer $^

src/test_diff.o: src/test_diff.cpp ../core/include/code_audit/diff.h
	$(CC) -c $(CPPFLAGS) -o src/test_diff.o src/test_diff.cpp

test-diff: src/test_diff.o
	g++ -o ./bin/test-diff $^ 