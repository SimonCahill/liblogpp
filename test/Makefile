CROSS=
CXX := ${CROSS}g++

CFLAGS := -std=gnu++14 -I../ -I../include -Iinclude

.PHONY: all clean prepare test

prepare:
	@-mkdir build ||:
	@echo "Build was prepared!"

build/test: ../build/liblogpp.a src/TestMain.cpp
	@${CXX} ${CFLAGS} $^ -o $@

test: build/test

all: prepare test
	@echo "Built test!"

clean:
	@rm -Rfv build/*