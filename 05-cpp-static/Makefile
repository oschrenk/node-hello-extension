LIB = libTestNode.a

OBJS = TestNode.o

TARTGET = waf

all: waf

waf: $(LIB)
	node-waf configure build

$(LIB): $(OBJS)
	ar -cr $(LIB) $(OBJS)
	ranlib $(LIB)

TestNode.o: TestNode.cpp TestNode.hpp
	g++ -fPIC -c TestNode.cpp -o TestNode.o

clean:
	node-waf clean
	rm -rf build *.o libTestNode.a

