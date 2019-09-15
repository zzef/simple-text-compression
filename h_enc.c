#include <stdio.h>
#include <stdlib.h>
#include "h_enc.h"

#define MAX_HEAP 1024

int sift_up(int* data, int index) {
	int parent = (index-1)/2;
	while(data[parent]>data[index]) {
		int temp = data[parent];
		data[parent]=data[index];
		data[index]=temp;
		index = parent;
		parent = (parent-1)/2;
	}	
}

int insert(int* data, int size, int value) {
	data[size]=value;
	sift_up(data, size);
	return size+1;
}

int find_max() {

}

int delete_min() {

}

int extract_min() {

}

int heapify(int *data, int i, int len) {
	
	printf("sd\n");
	
	if (i>=len) {
		return 0;
	}
	int left = (i*2)+1;
	int right = (i*2)+2;
	
	int smallest = data[i];
	int node;

	if (left<len && data[left]<smallest) {
		smallest = data[left];
		node=left;
	}
	if (right<len && data[right]<smallest) {
		smallest = data[right];
		node=right;
	}

	if (smallest!=data[i]) {
		printf("larg");
		int temp = data[i];
		data[i]=smallest;
		data[node]=temp;
		heapify(data,node,len);
	}

}

void display_heap(int* data, int len) {
	
	for (int i=0; i<len; i++) {
		printf("%i,",data[i]);
	}
	printf("\n");

}

void create_heap(int* data, int len) {
	int mid = len/2;
	printf("sds: %i\n",len);
	for (int i = mid; i>=0; i--) {
		heapify(data,i,len);
	}

}

int main() {

	int data[MAX_HEAP] = {2334,55,54,3,1,1,3,3,44,23,11,45,22,4,88,964,23,453,89,2327,5,22,4,67};
	int heap_size = 24;
	create_heap(data,heap_size);
	display_heap(data,heap_size);
	heap_size = insert(data,heap_size,0);
	display_heap(data,heap_size);
}


