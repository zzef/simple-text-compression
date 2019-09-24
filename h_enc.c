#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"
#include <string.h>
#include <math.h>
#include <inttypes.h>

#define CHARS 128

int gen_codes(struct node* htree, char* codes[], char* code, int top) {

	int chr = htree->chr;
	
	if (chr!=-56) {
		printf("reached %c\n",chr);
		codes[chr]=malloc(sizeof(char)*top);
		memcpy(codes[chr],code,sizeof(char)*top);
	}
	else {
		printf("going right\n");
		code[top]='1';
		gen_codes((htree->nodes)[1],codes,code,top+1);
		printf("going left\n");
		code[top]='0';
		gen_codes((htree->nodes)[0],codes,code,top+1);

	}
}

void count_freqs(FILE* text, int table[]) {
	int c;
	while ((c=fgetc(text)) != EOF) {	
		table[c]++;
	}
}

void init_heap(int freq_table[], struct node* nodes[], int* length) {
	for(int i=0; i<CHARS; i++) {
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

void print_codes(char* codes[], int length) {
	for (int i = 0; i<length; i++) {
		if (codes[i]) {
			printf("chr: %c -> %s\n",i,codes[i]);
		}
	}
}

int main(int argc, char** argv) {

	FILE *text;
	int length=0;
	int freq_table[CHARS];
	struct node* nodes[CHARS];
	char* codes[CHARS];
	struct node* tree;
	char code[CHARS];
	memset(code,0,CHARS*sizeof(char));
	memset(freq_table,0,CHARS*sizeof(int));
	memset(codes,0,CHARS*sizeof(char*));

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
	printf("result: %i\nsize: %i\nchar: %c\n",tree->count, length, tree->chr);	

	printf("generating codes\n");
	gen_codes(tree,codes,code,0);
	printf("done\n");
	print_codes(codes,CHARS);

	for (int i = 0;i<CHARS;i++) {
		free(codes[i]);
		codes[i]=NULL;
	}	


}


