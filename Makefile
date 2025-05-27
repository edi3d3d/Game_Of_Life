SRC = Game_Of_Life.c
SRC1 = graph.c

INPUT_FILES = $(wildcard InputData/data*.in)

all: build

build:
	gcc -O2 -Wall $(SRC) $(SRC1) -o a.out

run: 
	./a.out $(INPUT_FILES)

clean:
	rm -f a.out
