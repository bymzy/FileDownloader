XX=g++
CXXFLAGS=-g
TARGET=FileGet
LIB=curl
SOURCEDIR=src
OBJDIR=objs
BINDIR=bin
MARCOS=-D_LARGEFILE64_SOURCE -D _LARGEFILE_SOURCE -D_LARGE_FILES -D _FILE_OFFSET_BITS=64
SOURCES=${wildcard ${SOURCEDIR}/*.cpp}
OBJS=${patsubst ${SOURCEDIR}/%.cpp, ${OBJDIR}/%.o, ${SOURCES}}

${BINDIR}/${TARGET}:${OBJS}
	${XX} -l${LIB} -o ${BINDIR}/${TARGET} ${OBJS}

${OBJS}:${SOURCES}
	@for src in `echo ${SOURCES}`; do\
		obj=`echo $$src | sed "s/src/objs/" | sed "s/\.cpp/\.o/"`;\
		${XX} -c $$src -o $$obj ${MARCOS} ${CXXFLAGS};\
	done\

help:
	@echo "... clean (rm objs and bin)"
.PHONY : help

info:
	@echo "sources are all in src dir, objs are all in objs dirs"
	@echo "binary file is in bind dir"
.PHONY : info

clean:
	@rm -rf ${OBJS} ${BINDIR}/${TARGET}
.PHONY : clean
