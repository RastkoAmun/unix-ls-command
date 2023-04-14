all:
	gcc -g -o UnixLs main.c unixLs.c 

clean:
	rm -f ./main.o