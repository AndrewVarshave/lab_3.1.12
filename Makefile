CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o stack.o args.o sort.o io.o
EXEC = main.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

   main.o: main.c publication.h stack.h args.h sort.h io.h
	$(CC) $(CFLAGS) -c main.c

   stack.o: stack.c stack.h publication.h
	$(CC) $(CFLAGS) -c stack.c

   args.o: args.c args.h
	$(CC) $(CFLAGS) -c args.c

   sort.o: sort.c sort.h stack.h publication.h
	$(CC) $(CFLAGS) -c sort.c

   io.o: io.c io.h stack.h publication.h
	 $(CC) $(CFLAGS) -c io.c

   clean:
	del -f $(OBJS) $(EXEC)