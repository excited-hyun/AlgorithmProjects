mss20171653 : mss20171653.o
	gcc -o mss20171653 mss20171653.o

mss20171653.o : mss20171653.c
	gcc -c -o mss20171653.o mss20171653.c

clean:
	rm -rf *.o
