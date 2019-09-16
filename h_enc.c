#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

int main() {

	int data[MAX_HEAP] = {2334,55,54,3,1,1,3,3,44,23,11,45,22,4,88,964,23,453,89,2327,5,22,4,67};
	int heap_size = 24;
	create_heap(data,heap_size);
	display_heap(data,heap_size);
	insert(data,&heap_size,0);
	insert(data,&heap_size,-1);
	display_heap(data,heap_size);
	int min = extract_min(data,&heap_size);
	printf("result: %i\n, size: %i\n",min,heap_size);
	display_heap(data,heap_size);
}


