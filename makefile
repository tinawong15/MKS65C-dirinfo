all: dir.o main.o
	gcc main.o dir.o

main.o: main.c
	gcc -c main.c
	
dir.o: dir.c dir.h
	gcc -c dir.c

run:
	./a.out

clean:
	rm -rf *.o a.out
