void initialize_Dic(Dic *dic, size_t size){
	dic->size = size;
	dic->arr = malloc(sizeof(DicNode) * size);
	dic->inUse = malloc(sizeof(int) * size);
	memset(dic->inUse, 0, size * sizeof(int));
}


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

void free_dic(Dic *dic){
	for (int i=0; i<dic->size; ++i){
		if (dic->inUse[i]){
			DicNode *node = &dic->arr[i];
			if (node->has_child){
				free_children(node->child);
			}
			free_node_contents(node);
		}
	}
	free(dic->arr);
	free(dic->inUse);
}

size_t get_hash(char *word, int size){
	size_t hash = 5381;
	int i= 0;
	while (word[i] != '\0'){
		hash = ((hash << 5) + hash) + word[i];
		++i;
	}
	//printf("%zu\n", hash%size);
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


void add_to_dic(Dic *dic, char *str, size_t hash){
	DicNode *node = &dic->arr[hash];
	if (!dic->inUse[hash]){
		add_no_coll(node, str);
		dic->inUse[hash] = 1;
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

void add_string_to_dic(Dic *dic, char *file, size_t start, int size){
	char *new_word = (char*) malloc(sizeof(char) *size);
	memcpy(new_word, file+start, size-1);
	new_word[size-1] = '\0';
	add_to_dic(dic,new_word, get_hash(new_word, dic->size));
}


void print_children(DicNode *node){
	//DicNode *temp = node;
	printf("%s:%d\n", node->key, node->val);	
	while (node->has_child){
		node = node->child;
		printf("%s:%d\n", node->key, node->val);
	}

}
void print_dic(Dic *dic){
	for (int i=0; i< dic->size; ++i){
		if (dic->inUse[i]){
			DicNode *node = &dic->arr[i];
			printf("%s:%d\n", node->key, node->val);
			if (node->has_child){
				print_children(node->child);
		}
		}
	}
}

//Would probably be more convenient if the dic Node came with it's own
//array and was initiliazed to zero it would also make things easier
//so a dicNode would be the node and a Dic would actually just be a list 
//That was iniitialied to 0 (probably dynamically)

int get_element_val(Dic *dic, char *str){
	size_t i = get_hash(str,dic->size);
	//printf("Looking up:%s which should be at: %zu\n", str, i);

	if (dic->inUse[i]){
		//printf("are we even here?\n");
		DicNode *node = &dic->arr[i];
		while (strcmp(node->key, str) && node->has_child){
			node = node->child;
		}
		if (!strcmp(node->key,str)){
			return node->val;
		}
	}
	return -1;
}

DicNode *get_node(Dic *dic, char *str){
	size_t i = get_hash(str,dic->size);
	//printf("Looking up:%s which should be at: %zu\n", str, i);

	if (dic->inUse[i]){
		//printf("are we even here?\n");
		DicNode *node = &dic->arr[i];
		while (strcmp(node->key, str) && node->has_child){
			node = node->child;
		}
		if (!strcmp(node->key,str)){
			return node;
		}
	}
	return NULL;
}


