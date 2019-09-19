#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"
#include <string.h>

void heapify(struct node* data[], int i, int len) {
	
	if (i>=len) {
		return;
	}
	int left = (i*2)+1;
	int right = (i*2)+2;
	int smallest = i;

	if (left<len && data[left]->count<data[smallest]->count) {
		smallest = left;
	}
	if (right<len && data[right]->count<data[smallest]->count) {
		smallest = right;
	}

	if (smallest!=i) {
		struct node* temp = data[i];
		data[i]=data[smallest];
		data[smallest]=temp;
		heapify(data,smallest,len);
	}

}


void sift_up(struct node* data[], int index) {
	int parent = (index-1)/2;
	while(data[parent]->count>data[index]->count) {
		struct node* temp = data[parent];
		data[parent]=data[index];
		data[index]=temp;
		index = parent;
		parent = (parent-1)/2;
	}	
}

void insert(struct node* data[], int* size, struct node* n) {
	data[*size]=n;
	sift_up(data, *size);
	*size=*size+1;
}

struct node* find_min(struct node* data[]) {
	return data[0];
}

void delete_min(struct node* data[], int* len) {
	data[0]=data[*len-1];
	heapify(data,0,*len-1);
	*len=*len-1;
}

struct node* extract_min(struct node* data[], int* len) {
	struct node* min = find_min(data);
	delete_min(data, len);
	return min;
}

void display_heap(struct node* data[], int len) {
	
	for (int i=0; i<len; i++) {
		printf("%i,",data[i]->count);
	}
	printf("\n");

}

void build_heap(struct node* data[], int len) {
	
	int mid = len/2;
	for (int i = mid; i>=0; i--) {
		heapify(data,i,len);
	}

}


