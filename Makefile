CXX := g++
AR := ar
STRIP := strip

SRC_DIR := src
BIN_DIR := bin

LIB_NAME := liblog++
STAT_EXT := .a
DYN_EXT := .so

TUs = $(wildcard ${SRC_DIR}/*.cpp)
COMP_TUs = $(wildcard *.o)

CFLAGS=
LDFLAGS=

.PHONY: all static shared clean install debug strip

all: static shared
	@echo "Log++ has been built..."

static: ${COMP_TUs}
	@echo "Generating static library..."
	${AR} rvs ${LIB_NAME}${STAT_EXT} $^

shared: LDFLAGS += -shared
shared: ${COMP_TUs}
	@echo "Linking shared object..."
	${CXX} $^ ${LDFLAGS} -o ${LIB_NAME}${DYN_EXT}

debug: CFLAGS += -ggdb -O0
debug: all

strip: shared
	${STRIP} ${LIB_NAME}${DYN_EXT}

${COMP_TUs}: ${TUs}
	${CXX} $^ ${CFLAGS}
