XX=g++
CXXFLAGS=-g
TARGET=FileGet
LIB=-lcurl -pthread
SOURCEDIR=src
OBJDIR=objs
BINDIR=bin
MARCOS=-D_LARGEFILE64_SOURCE -D _LARGEFILE_SOURCE -D_LARGE_FILES -D _FILE_OFFSET_BITS=64
SOURCES=${wildcard ${SOURCEDIR}/*.cpp}
OBJS=${patsubst ${SOURCEDIR}/%.cpp, ${OBJDIR}/%.o, ${SOURCES}}

${BINDIR}/${TARGET}:${OBJS}
	${XX} ${LIB} -o ${BINDIR}/${TARGET} ${OBJS}

${OBJDIR}/%.o:${SOURCEDIR}/%.cpp
	${XX} -c $< -o $@ ${MARCOS} ${CXXFLAGS}
	
#${OBJS}:${SOURCES}
#	@for src in `echo ${SOURCES}`; do\
#		obj=`echo $$src | sed "s/src/objs/" | sed "s/\.cpp/\.o/"`;\
#		${XX} -c $$src -o $$obj ${MARCOS} ${CXXFLAGS};\
#	done\

help:
	@echo "... clean (rm objs and bin)"
	@echo "... info (show info of this program)"
.PHONY : help

info:
	@echo "program writed by mzy. Using libcurl to download file from Internet"
	@echo "sources are all in src dir, objs are all in objs dirs"
	@echo "binary file is in bin dir"
.PHONY : info

clean:
	@rm -rf ${OBJS} ${BINDIR}/${TARGET}
.PHONY : clean
