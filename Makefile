h_enc: min_heap.o h_enc.c
	gcc -g -o h_enc h_enc.c min_heap.o
min_heap.o: min_heap.c min_heap.h
	gcc -c -g min_heap.c

