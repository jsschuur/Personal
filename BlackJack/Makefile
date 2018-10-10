src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

output: $(src)
	g++  *.cpp -w -g -lSDL2 -lSDL2_image -I/usr/include/SDL2 -o $@

.PHONY: run
run:
	./output

.PHONY: clean
clean:
	rm output
