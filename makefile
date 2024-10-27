LIBDIR=lib/

C3=c3c
C3FLAGS=--libdir ${LIBDIR} --lib raylib5

TARGET=gcrisp

SRCS = $(shell find $(SRC_DIR) -name '*.c3')

all: ${TARGET}

${TARGET}: ${SRCS}
	${C3} ${C3FLAGS} -o $@ compile ${SRCS}
	

clean:
	rm ${TARGET}




