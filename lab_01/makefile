CFLAGS := -std=c99 -Wall -Werror -pedantic

main.exe : main.o big_float.o
	gcc -o main.exe main.o big_float.o

main.o : main.c big_float.h
	gcc $(CFLAGS) -c main.c

big_float.o : big_float.c big_float.h
	gcc $(CFLAGS) -c big_float.c

clean :
	rm *.o *.exe
