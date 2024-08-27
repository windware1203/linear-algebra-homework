
CC = g++

BIN_PATH = bin
SRC_PATH = src
INCLIUDE_PATH = ./include
ARGS = -std=c++11 -Wall -I ${INCLIUDE_PATH}
VPATH += ${SRC_PATH} ${INCLIUDE_PATH} ${BIN_PATH}

# add file here

_OBJS = number.o formula.o
main = ${SRC_PATH}/main.cpp
EXE_FILE = main
TEST_FILE = test.txt

OBJS = ${patsubst %.o, ${BIN_PATH}/%.o, ${_OBJS}}

.PHONY:all compile run

all:compile run

compile: ${OBJS}
	${CC} ${ARGS} -o ${EXE_FILE} ${OBJS} ${main}

run:
	${EXE_FILE}

test:compile
	${EXE_FILE} < ${TEST_FILE}

${BIN_PATH}/%.o: %.h %.cpp
	-@mkdir "${BIN_PATH}"
	${CC} ${ARGS} -c -o ${BIN_PATH}/$*.o ${SRC_PATH}/$*.cpp



number.o: number.cpp number.h
formula.o: formula.cpp formula.h