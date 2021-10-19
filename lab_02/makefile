CC := gcc

OBJDIR := out
INCDIR := inc

CFLAGS := -std=c99 -Wall -Werror
DEBUGFLAGS := -g3
RELEASEFLAGS := -DNDEBUG -g0
CHECK_FLAGS := -lcheck

OUTDIR := $(shell mkdir -p out)
OBJS := $(OBJDIR)/main.o $(OBJDIR)/address.o $(OBJDIR)/subscriber.o $(OBJDIR)/subscriber_info.o $(OBJDIR)/common.o

.PHONY : clean func_tests unit release debug

release : CFLAGS += $(RELEASEFLAGS)
release : lastrelease | app.exe

debug : CFLAGS += $(DEBUGFLAGS)
debug : lastdebug | app.exe

lastdebug:
	touch lastdebug
	rm -rf app.exe $(OBJDIR)/*
	rm -rf lastrelease

lastrelease:
	touch lastrelease
	rm -rf app.exe $(OBJDIR)/*
	rm -rf lastdebug

app.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/address.o : src/address.c inc/address.h inc/common.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/common.o : src/common.c inc/common.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/subscriber.o : src/subscriber.c inc/subscriber.h inc/subscriber_info.h inc/address.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/subscriber_info.o : src/subscriber_info.c inc/subscriber_info.h inc/address.h inc/common.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/main.o : src/main.c inc/subscriber.h inc/common.h
	$(CC) $(CFLAGS) -o $@ -c $<

