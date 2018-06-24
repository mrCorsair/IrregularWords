flags = -Wall -Werror -std=c11

prog:bin build bin/prog
test:bin build bin/test

bin/prog: build/main.o build/settings.o build/exercise.o build/print_functions.o build/datawork.o
	gcc $(flags) build/main.o build/settings.o build/exercise.o build/print_functions.o build/datawork.o -o bin/prog -lncursesw

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o -lncursesw
	
build/settings.o: src/settings.c
	gcc $(flags) -c src/settings.c -o build/settings.o 
	
build/print_functions.o: src/print_functions.c
	gcc $(flags) -c src/print_functions.c -o build/print_functions.o 
	
build/exercise.o: src/exercise.c
	gcc $(flags) -c src/exercise.c -o build/exercise.o 
	
build/datawork.o: src/datawork.c
	gcc $(flags) -c src/datawork.c -o build/datawork.o

bin/test: build/datawork.o build/test.o build/in.o
	gcc $(flags) build/datawork.o build/test.o build/in.o -o bin/test

build/test.o: test/test.c
	gcc -Wall -c test/test.c -o build/test.o -Ithirdparty -Isrc
	
build/in.o: test/in.c
	gcc -Wall -c test/in.c -o build/in.o -Ithirdparty

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin
