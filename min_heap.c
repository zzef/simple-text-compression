#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

void heapify(int* data, int i, int len) {
	
	if (i>=len) {
		return;
	}
	int left = (i*2)+1;
	int right = (i*2)+2;
	int smallest = i;

	if (left<len && data[left]<data[smallest]) {
		smallest = left;
	}
	if (right<len && data[right]<data[smallest]) {
		smallest = right;
	}

	if (smallest!=i) {
		int temp = data[i];
		data[i]=data[smallest];
		data[smallest]=temp;
		heapify(data,smallest,len);
	}

}


void sift_up(int* data, int index) {
	int parent = (index-1)/2;
	while(data[parent]>data[index]) {
		int temp = data[parent];
		data[parent]=data[index];
		data[index]=temp;
		index = parent;
		parent = (parent-1)/2;
	}	
}

void insert(int* data, int* size, int value) {
	data[*size]=value;
	sift_up(data, *size);
	*size=*size+1;
}

int find_min(int* data) {
	return data[0];
}

void delete_min(int* data, int* len) {
	data[0]=data[*len-1];
	heapify(data,0,*len);
	*len=*len-1;
}

int extract_min(int* data, int* len) {
	int min = find_min(data);
	delete_min(data, len);
	return min;
}

void display_heap(int* data, int len) {
	
	for (int i=0; i<len; i++) {
		printf("%i,",data[i]);
	}
	printf("\n");

}

void create_heap(int* data, int len) {
	
	int mid = len/2;
	for (int i = mid; i>=0; i--) {
		heapify(data,i,len);
	}

}


