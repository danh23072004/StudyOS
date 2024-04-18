CC = gcc
TARGET = calc

all:	$(TARGET)

$(TARGET):	calc.o
	$(CC)	-o	$(TARGET)	calc.o

calc.o:	calc.c
	$(CC)	-c	calc.c

clean:
	rm 	-f	*.o	$(TARGET)