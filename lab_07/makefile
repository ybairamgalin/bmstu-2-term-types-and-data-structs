CC := gcc
CFLAGS := -Wall -Werror -Wpedantic -Iinc

OBJS := out/main.o out/graph.o out/matrix.o

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

out/%.o : src/%.c inc/*.h
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY : clean
clean :
	rm -rf out/* app.exe