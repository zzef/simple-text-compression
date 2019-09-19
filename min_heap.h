#define MAX_HEAP 1024

struct node {
	char chr;
	int count;
	struct node* nodes[2];
};


void insert(struct node* data[], int* size, struct node* n);
void build_heap(struct node* data[], int len);
void display_heap(struct node* data[], int len);
struct node* extract_min(struct node* data[], int* len);
struct node* find_min(struct node* data[]);
