# variables
PROGNAME = numeral
OBJECTS = main.o
INCLUDE = .
LIB = .

# compiler options
BASE_CFLAGS = -Wall
CFLAGS = -O3
LD_FLAGS =


# targets
all: $(PROGNAME)

$(PROGNAME): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) -L$(LIB) $(LD_FLAGS)

strip: all
	strip -sv $(PROGNAME)

clean:
	-rm -f *.o
	-rm -f $(PROGNAME)
	-rm -f core
	-rm -f a.out


# dependancies
main.o: main.cpp
	$(CXX) -I$(INCLUDE) $(CFLAGS) -c $<
