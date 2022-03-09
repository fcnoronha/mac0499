CFLAGS=-std=c++17
WFLAGS=-Wall -Wextra -Wshadow -pedantic
# WFLAGS=-Wall -Wextra -Wshadow -pedantic -fsanitize=address -fsanitize=undefined -fno-sanitize-recover 

%.o: %.cpp
	g++ -c -o $@ $< -Wall

linkCutTreeTest: linkCutTreeTest.o linkCutTree.o splayTree.o
	g++ $(CFLAGS) $(WFLAGS) -o $@ $^

retroactiveUnionFindTest: retroactiveUnionFindTest.o retroactiveUnionFind.o linkCutTree.o splayTree.o
	g++ $(CFLAGS) $(WFLAGS) -o $@ $^

clean:
	rm -f *.o
