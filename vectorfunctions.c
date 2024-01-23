void append_vec(char *word, Vector *vec){
	if (vec->index == vec->cap){
		vec->arr = realloc(vec->arr, sizeof(char*) * vec->cap*2);
		vec->cap *=2;
	}
	char *new_word = (char*)malloc(sizeof(char) * sizeof(word));
	strcpy(new_word, word);
	vec->arr[vec->index] = new_word;
	vec->index++;
}

void free_vec_elements(Vector *vec){
	for (int i=0; i<vec->index; ++i){
		free(vec->arr[i]);
	}
}

void init_vec(Vector *vec, size_t size){
	vec->index = 0;
	vec->cap = size;
	vec->arr = (char**) malloc(sizeof(char*) * vec->cap);
}