CC = gcc

all: sum_serial sum_multi_thread

sum_serial: sum_serial.c
	$(CC) $(CFLAGS) -o sum_serial sum_serial.c

sum_multi_thread: sum_multi_thread.c
	$(CC) $(CFLAGS) -o sum_multi_thread sum_multi_thread.c

clean:
	rm -f sum_serial sum_multi_thread

run_serial:
	./sum_serial $(NUM)

run_multi_thread:
	./sum_multi_thread $(THREADS_NUM) $(NUM)