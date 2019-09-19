#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"
#include <string.h>
#include <math.h>
#include <inttypes.h>

int gen_codes(struct node* htree, uint64_t codes[], uint64_t code) {

	if ((htree->nodes)[0]->chr!=-56) {
		codes[(htree->nodes)[0]->chr]=(code*10)+1;
	}
	else {
		gen_codes((htree->nodes)[0],codes,(code*10)+1);
	}

	if ((htree->nodes)[1]->chr!=-56) {
		codes[(htree->nodes)[1]->chr]=(code*10)+2;
	}
	else {
		gen_codes((htree->nodes)[1],codes,(code*10)+2);
	}
}

void count_freqs(FILE* text, int table[]) {
	int c;
	while ((c=fgetc(text)) != EOF) {	
		table[c]++;
	}
}

void init_heap(int freq_table[], struct node* nodes[], int* length) {
	for(int i=0; i<128; i++) {
		if (freq_table[i]>0) {
			struct node* n = malloc(sizeof(struct node));
			n->chr=i;
			n->count=freq_table[i];
			n->nodes[0]=NULL;
			n->nodes[1]=NULL;
			nodes[*length]=n;
			*length=*length+1;
		}
	}
}


struct node* gen_huffman(struct node* nodes[], int* length) {
	while (*length>1) {
		struct node* first = extract_min(nodes,length);
		struct node* second = extract_min(nodes,length);
		struct node* new = malloc(sizeof(struct node));
		new->chr=200;
		new->count=second->count+first->count;
		new->nodes[0]=first;
		new->nodes[1]=second;
		insert(nodes,length,new);
	}	
	return extract_min(nodes,length);
}

int main(int argc, char** argv) {

	FILE *text;
	int length=0;
	int freq_table[128];
	struct node* nodes[128];
	memset(freq_table,0,128*sizeof(int));
	uint64_t codes[128];
	struct node* tree;

	if (!(text=fopen(argv[1],"r"))) {
		printf("Failed to open file");
		return 0;
	}

	count_freqs(text,freq_table);
	init_heap(freq_table,nodes,&length);

	for(int i=0; i<length; i++) {
		printf("count: %c - %i",nodes[i]->chr,nodes[i]->count);
		printf("\n");
	}
		
	build_heap(nodes,length);
	tree = gen_huffman(nodes,&length);

	memset(codes,0,128*sizeof(uint64_t));
	printf("generating codes\n");
	gen_codes(tree,codes,0);
}


