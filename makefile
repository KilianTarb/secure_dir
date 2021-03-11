CC = g++

INCLUDEFLAGS = -Iinclude
OUTFLAGS = -o build/
FLAGS = -std=c++17
SSLFLAGS = -lssl -lcrypto 

all: 
	${CC} -c lib/indexfile.cpp ${INCLUDEFLAGS} ${FLAGS} ${OUTFLAGS}indexfile.o
	${CC} -c lib/AesEnc.cpp ${INCLUDEFLAGS} ${FLAGS} ${OUTFLAGS}AesEnc.o
	${CC} -c main.cpp ${INCLUDEFLAGS} ${FLAGS} ${OUTFLAGS}main.o
	${CC} build/*  ${SSLFLAGS} ${FLAGS} ${OUTFLAGS}securedir

clean:
	rm build/*