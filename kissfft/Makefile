CC     := g++
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CFLAGS  := -W -Wall -Waggregate-return 
CFLAGS  += -Wcast-align -Wcast-qual -Wshadow 
CFLAGS  += -Wwrite-strings -O3
CFLAGS  += -I. -Itools


LDFLAGS   := -Wall
LIBS      :=

DATATYPE  := float

OUTPUTLIB += kissfft.a

all: $(OUTPUTLIB)

SRCS += kiss_fft.c tools/kiss_fftr.c

OBJS += $(addsuffix .o,$(basename $(SRCS)))

$(OUTPUTLIB): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

clean:
	rm $(OBJS) $(OUTPUTLIB) *~ -rf

