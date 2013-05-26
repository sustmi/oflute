OBJDIR   := obj
SRCDIR   := src
INCDIR   := include
DEPFILE  := obj/dependencias.d

CXX      := g++
CXXFLAGS += -I. -I$(INCDIR) -DSWIG_OMEGA
CXXFLAGS += -Igosu `gosu/bin/gosu-config --cxxflags`
CXXFLAGS += -Ipugixml -Ikissfft
CXXFLAGS += -O3#-g -Wall
CXXFLAGS += `pkg-config --cflags libpulse-simple`

#LDFLAGS  += `gosu/bin/gosu-config --libs --cxxflags` 
LDFLAGS  += `pkg-config --libs libpulse-simple`
LDFLAGS  += -lX11 -pthread -lpangoft2-1.0 -lpango-1.0 -lfreetype 
LDFLAGS  += -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt 
LDFLAGS  += -lglib-2.0 -lsndfile -lvorbisfile -lvorbis -logg -lm -lopenal -lpng -lstdc++ 
LDFLAGS  += -lGL -lSDL_ttf -lfreeimage

LDLIBS   += gosu/lib/libgosu.a
LDLIBS   += -lSDL_ttf
LDLIBS   += -lboost_filesystem
LDLIBS   += -lboost_regex
LDLIBS   += -lboost_thread
LDLIBS   += pugixml/pugixml.a
LDLIBS   += kissfft/kissfft.a

OUTPUT += oflute

SRCS := $(notdir $(shell ls -t $(SRCDIR)/*.cpp))

OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

all: $(OUTPUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..." $(notdir $<)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT):  $(OBJS)	
	@echo "Compiling pugixml..."
	@make -C pugixml
	@echo "Compiling kissfft..."
	@make -C kissfft
	@echo "Linking binary..."
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
	@echo "Done."

#depende: $(DEPFILE)

$(DEPFILE): $(shell ls -t $(INCDIR)/*.h)
	@echo "Generating dependency file..."
	@gcc -MM $(CXXFLAGS) $(shell ls -t $(SRCDIR)/*.cpp) | sed 's/^\([a-zA-Z]\+.o\)/$(OBJDIR)\/\1/g' > $(DEPFILE)

sinclude $(DEPFILE)

libgosu:
	cd gosu/linux ; make clean ; ./configure && make

regosu:
	make -C gosu/linux

clean:
	rm -rf $(OBJS) $(EXE) $(DEPFILE)
	make -C pugixml clean
	make -C kissfft clean


