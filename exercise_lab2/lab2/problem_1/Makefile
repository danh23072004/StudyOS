CC = gcc
TARGET = average_rating_movie

all:	$(TARGET)

$(TARGET):	average_rating_movie.o
	$(CC)	-o	$(TARGET)	average_rating_movie.o

average_rating_movie.o:	average_rating_movie.c
	$(CC)	-c	average_rating_movie.c

run:
	./$(TARGET)

clean:
	rm 	-f	*.o	$(TARGET)