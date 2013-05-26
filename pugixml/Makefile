CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

OUTPUT += pugixml.a

all: ${OUTPUT}

SRCS += pugixml.cpp pugixpath.cpp

OBJS += $(addsuffix .o,$(basename ${SRCS}))

${OUTPUT}: ${OBJS}
	${AR} $@ ${OBJS}
	${RANLIB} $@

clean:
	rm ${OBJS} ${OUTPUT} -rf

pugixml.o: pugixml.hpp pugiconfig.hpp
pugixpath.o: pugixml.hpp pugiconfig.hpp




