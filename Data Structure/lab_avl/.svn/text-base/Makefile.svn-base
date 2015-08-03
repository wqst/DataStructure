CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXENAME = testavl
OBJS = coloredout.o main.o

$(EXENAME) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

main.o: src/main.cpp $(wildcard include/*)
	$(CXX) $(CXXFLAGS) $<

coloredout.o: src/coloredout.cpp include/coloredout.h
	$(CXX) $(CXXFLAGS) $<

doc: lab_avl.doxygen $(wildcard include/*) $(wildcard src/*)
	doxygen $<

clean:
	-rm -f *.o $(EXENAME)

tidy:
	-rm -rf ./doc
