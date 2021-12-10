CC := gcc

CFLAGS := -Wall -Werror -std=c99 -Iinc -Wpedantic

.PHONY : clean

app.exe : out/main.o out/queue.o out/service_simulation.o out/arr_queue.o
	$(CC) $(CFLAGS) -o $@ $^

out/main.o: src/main.c
	$(CC) $(CFLAGS) -o $@ -c $<

out/queue.o : src/queue.c inc/queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/arr_queue.o : src/arr_queue.c inc/arr_queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/service_simulation.o : src/service_simulation.c inc/service_simulation.h inc/queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf out/*

