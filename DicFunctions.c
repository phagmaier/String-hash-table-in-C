void free_node_contents(DicNode *node){
	free(node->key);
	node->val=0;
	node->key = NULL;
	node->has_child = 0;
	node->child = NULL;
}


void free_children(DicNode *node){
	DicNode *temp = NULL;
	while (node->has_child){
		temp = node->child;
		free_node_contents(node);
		free(node);
		node = temp;
	}
	free_node_contents(node);
	free(node);
}

void free_dic(DicNode *dic, int *arr, int size){
	for (int i=0; i<size; ++i){
		if (arr[i]){
			DicNode *node = &dic[i];
			if (node->has_child){
				free_children(node->child);
			}
			free_node_contents(node);
		}
	}
}

size_t get_hash(char *word, int size){
	size_t hash = 5381;
	int i= 0;
	while (word[i] != '\0'){
		hash = ((hash << 5) + hash) + word[i];
		++i;
	}
	return hash%size;
}


void add_no_coll(DicNode *node, char *str){
	char *new_word =(char*) malloc(sizeof(char) * (strlen(str) +1));
	memcpy(new_word, str, sizeof(char) * (strlen(str) +1));
	node->key = new_word;
	node->val = 1;
	node->has_child = 0;
	node->child = NULL;
}

void add_collision(DicNode *node, char *str){
	DicNode *new_node = (DicNode*) malloc(sizeof(DicNode));
	char *new_word =(char*) malloc(sizeof(char) * (strlen(str) +1));
	memcpy(new_word, str, sizeof(char) * (strlen(str) +1));
	new_node->key = new_word;
	new_node->val = 1;
	new_node->has_child = 0;
	node->has_child = 1;
	node->child = new_node;
}


void add_to_dic(DicNode *dic, char *str, int *arr, size_t hash){
	DicNode *node = &dic[hash];
	if (!arr[hash]){
		add_no_coll(node, str);
		arr[hash] = 1;
	}
	else if(strcmp(node->key, str)){
		while (strcmp(node->key, str) && node->has_child){
			node = node->child;
		}
		if (!strcmp(node->key, str)){
			node->val++;
			free(str);
		}
		else{
			add_collision(node, str);
		}
	}
}

void add_string_to_dic(DicNode *dic, char *file, int *arr, size_t start, int size){
	char *new_word = (char*) malloc(sizeof(char) *size);
	memcpy(new_word, file+start, size-1);
	add_to_dic(dic,new_word, arr, get_hash(new_word, size));
}


void print_children(DicNode *node){
	DicNode *temp = node;
	while (node->has_child){
		temp = node->child;
		printf("%s:%d\n", node->key, node->val);
		node = temp;
	}
	printf("%s:%d\n", node->key, node->val);

}
void print_dic(DicNode *dic, int *arr, int size){
	for (int i=0; i< size; ++i){
		if (arr[i]){
			DicNode *node = &dic[i];
			printf("%s:%d\n", node->key, node->val);
			if (node->has_child){
				print_children(node->child);
		}
		}
	}
}
