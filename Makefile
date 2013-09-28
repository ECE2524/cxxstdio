CXX ?= g++
CXXFLAGS ?= -Wall -std=c++11 -g
PROGNAME := myprog
SRCS := main.cpp # add more c source files here, separate by spaces

prefix ?= /usr/local

OBJS := $(SRCS:.cpp=.o)

pedantic: CFLAGS += -Wextra -pedantic -D_XOPEN_SOURCE=700

all: $(PROGNAME)
pedantic: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

-include $(OBJS:.o=.P)

# compilation and auto-dependancy generation 
# in one step. Works with gcc and clang
# See http://mad-scientist.net/make/autodep.html
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MD -c -o $@ $<
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $*.d >>$*.P; \
	rm -f $*.d

.PHONY: clean
clean:
	rm -f *.o *.P $(PROGNAME)

install:
	cp $(PROGNAME) $(prefix)/bin
