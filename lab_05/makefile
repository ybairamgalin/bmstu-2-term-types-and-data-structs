CC := gcc

CFLAGS := -Wall -Werror -std=c99 -Iinc

.PHONY : clean

app.exe : out/main.o
	$(CC) $(CFLAGS) -o $@ $^

out/main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	rm -rf out/*

