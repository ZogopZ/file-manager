#############################################################################
# Makefile for: Syspro: Project 2 					    #
#############################################################################


CC            = gcc
CFLAGS        = -g -Wall -W
DEL_FILE      = rm -f

OBJECTS       = main.o \
		cli.o \
		command_line_utils.o \
		doc_utils.o \
		workers.o \
		map.o \
		retrie.o \
		posting_list.o

default: jobExecutor

jobExecutor: main.o map.o cli.o retrie.o doc_utils.o command_line_utils.o posting_list.o workers.o
	$(CC) $(CFLAGS) -o jobExecutor main.o map.o cli.o retrie.o doc_utils.o command_line_utils.o posting_list.o workers.o

main.o: main.c cli.h \
		main.h \
		map.h \
		workers.h \
		retrie.h \
		command_line_utils.h \
		doc_utils.h
	$(CC) -c $(CFLAGS) -o main.o main.c

cli.o: cli.c cli.h \
		main.h \
		map.h \
		workers.h \
		retrie.h \
		command_line_utils.h \
		doc_utils.h \
		posting_list.h
	$(CC) -c $(CFLAGS) -o cli.o cli.c

command_line_utils.o: command_line_utils.c command_line_utils.h
	$(CC) -c $(CFLAGS) -o command_line_utils.o command_line_utils.c

doc_utils.o: doc_utils.c command_line_utils.h \
		doc_utils.h \
		main.h \
		workers.h \
		retrie.h \
		map.h
	$(CC) -c $(CFLAGS) -o doc_utils.o doc_utils.c

workers.o: workers.c command_line_utils.h \
		doc_utils.h \
		main.h \
		map.h \
		posting_list.h \
		workers.h \
		retrie.h
	$(CC) -c $(CFLAGS) -o workers.o workers.c

map.o: map.c cli.h \
		main.h \
		map.h \
		workers.h \
		retrie.h \
		command_line_utils.h \
		doc_utils.h
	$(CC) -c $(CFLAGS) -o map.o map.c

retrie.o: retrie.c retrie.h \
		map.h \
		workers.h \
		main.h \
		posting_list.h
	$(CC) -c $(CFLAGS) -o retrie.o retrie.c

posting_list.o: posting_list.c map.h \
		posting_list.h
	$(CC) -c $(CFLAGS) -o posting_list.o posting_list.c


clean:
	-$(DEL_FILE)  jobExecutor
	-$(DEL_FILE)  $(OBJECTS)
