
VERSION = 1.0
NAME = automata

FA_VER = 1.0
FA_LIB = libFA-$(FA_VER).a

LIB_NAME = $(NAME)-$(VERSION)
LIB_FILE = lib$(LIB_NAME).a


INCLUDE = -I . -I include
OBJS = $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp))

AD = AutomataDefs
FA = FiniteAutomata

all: $(LIB_FILE) tests

$(LIB_FILE): $(OBJS)
	ar rcs $@ $^

$(FA_LIB): bin/$(FA).o bin/$(AD).o
	ar rcs $@ $^

bin/%.o: bin

bin/$(AD).o: src/$(AD).cpp include/$(AD).h
	g++ -c -Wall $(INCLUDE) -o $@ $<

bin/$(FA).o: src/$(FA).cpp include/$(FA).h
	g++ -c -Wall $(INCLUDE) -o $@ $<

bin:
	mkdir bin

tests: $(patsubst %.cpp,%,$(wildcard tests/*))

tests/%: tests/%.cpp $(LIB_FILE)
	g++ $(INCLUDE) -o $@ $^

clean: 
	rm -f bin/* *.a $(filter-out tests/%.cpp,$(wildcard tests/*))
