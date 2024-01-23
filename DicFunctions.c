
void add_new_no_coll(DicNode *dic, char *word, int *arr, size_t index){
		dic[index].val = 1;
		char *new_word = (char*) malloc(sizeof(word) * sizeof(char));
		strcpy(new_word, word);
		dic[index].has_children = 0;
		dic[index].child = NULL;
		dic[index].key = new_word;
		arr[index] = 1;
}

void add_new_coll(DicNode *node, char *word){
	node->has_children =1;
	DicNode *new_node = (DicNode*) malloc(sizeof(DicNode));
	char *new_word = (char*) malloc(sizeof(word) * sizeof(char));
	strcpy(new_word, word);
	new_node->has_children = 0;
	new_node->key = new_word;
	new_node->val = 1;
	new_node->child = NULL;
	node->child = new_node;
}

void add_string(DicNode *dic, char *word, int *arr, size_t index){
	DicNode *node = &dic[index];
	if (!arr[index]){
		add_new_no_coll(dic, word, arr, index);
	}

	else if (!strcmp(word, node->key)){
		node->val++;
	}
	else if (node->has_children){
		node = node->child;
		while (strcmp(node->key, word) && node->has_children){
			node = node->child;
		}
		//had children but we found the match there was a collision
		if (!strcmp(node->key, word)){
			node->val++;
		}
		//there was a collision but there was no match
		else{
			add_new_coll(node, word);
		}

	}
	//didn't have children and there was no match
	else{
		add_new_coll(node, word);	
	}
	
}

//jsut returns the value for that particular string will need to run a hash function
//returns 0 if doesn't exist
size_t  get_value(char *word, DicNode **dic, int *arr, size_t hash){
	DicNode *node =  dic[hash];
	while (node->has_children){
		if (!strcmp(node->key,word)){
		return node->val;
	}
	}
	if (!strcmp(node->key, word)){
		return node->val;
	}
	return 0;
}

void free_children(DicNode *node){
	DicNode *parent = node;
	while (node->has_children){
		node = node->child;
		free(parent->key);
		free(parent);
		parent->val = 0;
		parent->child = NULL;
		parent->has_children = 0;
		parent->key = NULL;
	}
	if (node){
		free(node->key);
		node->val = 0;
		node->child = NULL;
		node->has_children = 0;
		node->key = NULL;
		free(node);
	}
}

void free_dic_vals(DicNode *dic, int *arr, size_t size){
	for (int i=0; i<size; ++i){
		if (arr[i]){
			DicNode *node = &dic[i];
			if (node->has_children){
				free_children(node->child);

			}
			arr[i] = 0;
			free(node->key);
			node->val=0;
			node->key=NULL;
			node->has_children=0;
			node->child = NULL;
		}
	}
}

size_t get_hash(char *word, size_t size){
	unsigned long hash = 5381;
	int c;
	int i=0;
	while (word[i]){
		hash = ((hash << 5) + hash) + (int)word[i];
		i++;
	}
	return hash % size;
}

void print_node(DicNode *dic){
	printf("%s:%zu\n", dic->key, dic->val);

}

void print_dic(DicNode *dic, int *arr, size_t size){
	for (int i=0; i<size; ++i){
		if (arr[i]){
			DicNode *node = &dic[i];
			if(node->has_children){
				print_node(node);
				node = node->child;
			}
			print_node(node);
		}
	}
}