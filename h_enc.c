#include <stdio.h>
#include <stdlib.h>
#include "h_enc.h"

int heapify(int *data, int i, int len) {
	
	printf("sd\n");
	
	if (i==len-1) {
		return 0;
	}
	int left = (i*2)+1;
	int right = (i*2)+2;
	
	int largest = data[i];
	int node;

	if (left<=len && data[left]>largest) {
		largest = data[left];
		node=left;
	}
	if (right<=len && data[right]>largest) {
		largest = data[right];
		node=right;
	}

	if (largest!=data[i]) {
		printf("larg");
		int temp = data[i];
		data[i]=largest;
		data[node]=temp;
		heapify(data,node,len);
	}

}

int main() {

	int data[] = {9,3,3,44,23,11,45,22,4,88,964,23,453,89,2327,5,22,4,67};
	int len = sizeof(data)/sizeof(int);
	int mid = len/2;

	for (int i = mid; i>=0; i--) {
		heapify(data,i,len);
	}

	for (int i=0; i<len; i++) {
		printf("%i,",data[i]);
	}
	printf("\n");
}
