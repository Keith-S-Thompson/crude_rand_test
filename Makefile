PROGRAM = crude_rand_test

all:	$(PROGRAM)

$(PROGRAM): *.c version.h
	$(CC) *.c -o $(PROGRAM)

version.h:
	./print-version > $@

clean:
	- rm -f *.o $(PROGRAM) version.h
