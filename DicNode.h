typedef struct DicNode{ 
	char *key;
	size_t val;
	int has_children;
	struct DicNode *child;
}DicNode;