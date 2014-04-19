PROGRAM = crude_rand_test

all:	$(PROGRAM)

$(PROGRAM): *.c
	$(CC) *.c -o $(PROGRAM)

clean:
	- rm -f *.o $(PROGRAM)
