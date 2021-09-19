CFLAGS := -std=c99 -Wall -Werror -pedantic

main.exe : main.o errors.o big_int.o big_float.o
	gcc -o main.exe main.o errors.o big_int.o big_float.o

main.o : main.c errors.h big_float.h
	gcc $(CFLAGS) -c main.c

errors.o : errors.c errors.h
	gcc $(CFLAGS) -c errors.c

big_int.o : big_int.c big_int.h
	gcc $(CFLAGS) -c big_int.c

big_float.o : big_float.c big_float.h
	gcc $(CFLAGS) -c big_float.c

clean :
	rm *.o *.exe
