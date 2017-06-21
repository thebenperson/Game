#Game Development Build
#https://github.com/TheBenPerson/Game

#Copyright (C) 2016-2017 Ben Stockett <thebenstockett@gmail.com>

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

#flags
CF := -Isrc/client -Isrc/server -Isrc/common -Wall -Wextra -Wno-conversion-null -Wno-write-strings
LF := -fsanitize=leak -g

#build directories
BIN := bin
OBJ := $(BIN)/obj

#default target
all: $(BIN)/game

.PHONY: release
release: LF := -Ofast
release: $(BIN)/game
	strip --strip-unneeded $(addprefix $(BIN)/, libclient.so libcommon.so)

$(BIN)/game: $(OBJ)/main.o $(addprefix $(BIN)/, libclient.so libcommon.so)
	gcc $(OBJ)/main.o $(BIN)/libcommon.so -ldl -lstdc++ -pthread $(LF) -o $@

$(OBJ)/main.o: src/main/main.cpp
	gcc $(CF) -c $^ $(LF) -o $@

$(BIN)/libclient.so: $(shell find src/client -name "*.cpp")
	gcc $(CF) -Isrc/client -shared -fpic -lGL -lpng -lX11 -lX11-xcb -lxcb $^ $(LF) -o $@

$(BIN)/libserver.so: $(shell find src/server -name "*.cpp")
	gcc $(CF) -Isrc/server -shared -fpic $^ -o $(LF) $@

$(BIN)/libcommon.so: $(shell find src/common -name "*.cpp")
	gcc $(CF) -Isrc/util -shared -fpic $^ $(LF) -o $@

.PHONY: clean
clean:
	-rm $(OBJ)/* $(BIN)/* 2> /dev/null
