all:
	gcc -g -o main.o main.c unixLs.c 

clean:
	rm -f ./main.o