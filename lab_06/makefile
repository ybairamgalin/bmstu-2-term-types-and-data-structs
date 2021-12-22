CC := gcc

OBJDIR := out
INCDIR := inc
UNITDIR := unit_tests

CFLAGS := -std=c99 -Wall -Werror -I$(INCDIR)
DEBUGFLAGS := -g -fno-inline -fno-omit-frame-pointer -O0 -fprofile-arcs -ftest-coverage -fPIC
RELEASEFLAGS := -DNDEBUG -g0
CHECK_FLAGS := -lcheck -g3 -fprofile-arcs

OUTDIR := $(shell mkdir -p out)
OBJS := $(OBJDIR)/main.o $(OBJDIR)/my_snprintf.o
UNITOBJS := $(OBJDIR)/check_my_snprintf.o $(OBJDIR)/check_main.o $(OBJDIR)/my_snprintf.o

.PHONY : clean func unit release debug tests

release : CFLAGS += $(RELEASEFLAGS)
release : release.last | app.exe

debug : CFLAGS += $(DEBUGFLAGS)
debug : debug.last | app.exe

tests : unit

unit : debug | unit_tests.exe
	./unit_tests.exe

debug.last:
	touch debug.last
	rm -rf app.exe $(OBJDIR)/*
	rm -rf release.last

release.last:
	touch release.last
	rm -rf app.exe $(OBJDIR)/*
	rm -rf debug.last

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

#unit_tests.exe : $(UNITOBJS)
#	$(CC) $(CHECK_FLAGS) -o $@  $^

$(OBJDIR)/main.o : src/main.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/my_snprintf.o : src/my_snprintf.c inc/my_snprintf.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/check_main.o : unit_tests/check_main.c inc/check_my_snprintf.h
	$(CC) $(CFLAGS) -o $@ -c $<

#$(OBJDIR)/check_my_snprintf.o : unit_tests/check_my_snprintf.c inc/check_my_snprintf.h inc/my_snprintf.h
#	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf *.exe
	rm -rf *.gcov
	rm -rf *.last
	rm -rf $(OBJDIR)/*.o
	rm -rf $(OBJDIR)/*.gcda
	rm -rf $(OBJDIR)/*.gcno
