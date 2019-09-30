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

void set_bit(ssize_t pos, char* buffer, char chr) {
	printf("%i",chr);
	if (chr==0) {
		char b = ~(1 << (7-pos));
		*buffer = *buffer & b;
	}
	if (chr==1) {
		char b = 1 << (7-pos);
		*buffer = *buffer | b;
	}
}

void write_bit(char compressed[], ssize_t size, char chr, ssize_t* bit_seek) {

	//if gets too big reallocate
	
	ssize_t	offset = *bit_seek/8;
	char buffer;

	if ((*bit_seek%8)==0) {
		printf("|");
		buffer = 0;
		set_bit(0,&buffer,chr);
	}
	else {
		buffer = compressed[offset];
		set_bit(*bit_seek-(offset*8),&buffer,chr);
	}
	compressed[offset]=buffer;
	*bit_seek=*bit_seek+1;
}

void write_byte(char compressed[], ssize_t size, char chr, ssize_t* bit_seek) {
	//printf("|%c",chr);
	for (int i = 0; i<8; i++) {
		write_bit(compressed, size, ((1 << 7-i) & chr) != 0, bit_seek);
	}
	//printf("|");

}

struct node* build_codebook(struct node* tree, char compressed[], ssize_t size, ssize_t* bit_seek) {
	
	char chr = tree->chr;

	if (chr!=-56) {
		write_bit(compressed,size,1,bit_seek);
		write_byte(compressed,size,chr,bit_seek);
	}
	else {
		write_bit(compressed,0,size,bit_seek);
		build_codebook((tree->nodes)[0],compressed,size,bit_seek);
		build_codebook((tree->nodes)[1],compressed,size,bit_seek);
	}
}

int main(int argc, char** argv) {


	/*FILE *test;

	test=fopen("tests/test3.txt","w");

	for (int i =0; i<128;i++) {
		fseek(test,i,SEEK_SET);
		fputc(i,test);
	}*/

	FILE *text;
	int length=0;
	int freq_table[CHARS];
	struct node* nodes[CHARS];
	char* codes[CHARS];
	struct node* tree;
	char code[CHARS];
	char compressed[1024];
	memset(compressed,0,1024);
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


	/*if (!(compressed=fopen("compressed.txt","wrb"))) {
		printf("Failed to create a new file");
		return 0;
	}*/

	ssize_t bit_seek = 0;
	build_codebook(tree,compressed,1024,&bit_seek);

	printf("\ncompressed tree: ");
	for (int i = 0; i < (bit_seek/8)+1; i++) {
		printf("%i,",compressed[i]);
	}
	printf("\nsize: %i\n",bit_seek);

	for (int i = 0;i<CHARS;i++) {
		free(codes[i]);
		codes[i]=NULL;
	}

}


