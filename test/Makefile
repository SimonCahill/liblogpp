CROSS=
CXX := ${CROSS}g++

CFLAGS := -L../build -std=gnu++14 -I../ -I../include -Iinclude -llogpp

.PHONY: all clean prepare test

build/test: src/TestMain.cpp
	@-mkdir build 2>&1||:
	@echo "Build was prepared!"
	@echo "Compiling..."
	@${CXX} ${CFLAGS} $^ -o $@

test: build/test

all: test
	@echo "Built test!"

clean:
	@rm -Rfv build/*