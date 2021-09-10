gcc errors.c -Wall -std=c99 -c
gcc big_int.c -Wall -std=c99 -c
gcc main.c -Wall -std=c99 -c
gcc main.o big_int.o errors.o -o main.exe