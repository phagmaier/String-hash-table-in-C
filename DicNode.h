typedef struct DicNode{
	char *key;
	int val;
	int has_child;
	struct DicNode *child;
}DicNode;