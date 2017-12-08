XX=g++
TARGET=FileGet
LIB=curl
SOURCES=${wildcard src/*.cpp}
OBJS=${patsubst %.cpp, %.o,${SOURCES}}

${TARGET}:${OBJS}
	${XX} -l${LIB} -o ${TARGET} ${OBJS}

%.o:%.cpp
	${XX} -c $<

output:
	echo ${SOURCES}
	echo ${OBJS}

clean:
	rm -rf ${OBJS} ${TARGET}

