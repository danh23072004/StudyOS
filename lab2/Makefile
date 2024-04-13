# create a makefile for average_rating_movie.c program

# define the compiler
CC = gcc

# define the compiler flags
CFLAGS = -Wall -g

# define the target
TARGET = average_rating_movie

# define the source files
SRC = average_rating_movie.c

# define the object files
OBJ = $(SRC:.c=.o)

# define the header files
HDR =

# define the libraries
LIBS =

# define the include paths
INCLUDES =

# define the build target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

# define the object files
$(OBJ): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDES)

# define the clean target
clean:
	$(RM) $(TARGET) $(OBJ)

# define the run target
run:
	./$(TARGET)

# define the test target
test:
	./$(TARGET) < test.txt

# define the valgrind target
valgrind:
	valgrind ./$(TARGET)

# define the valgrind test target
valgrind-test:
	valgrind ./$(TARGET) < test.txt

# define the help target
help:
	@echo "make: compile the program"
	@echo "make run: run the program"
	@echo "make test: run the program with test.txt"
	@echo "make valgrind: run the program with valgrind"
	@echo "make valgrind-test: run the program with test.txt and valgrind"
	@echo "make clean: remove the program and object files"
	@echo "make help: display this help message"

# define the phony targets
.PHONY: clean run test valgrind valgrind-test help

# end of Makefile
