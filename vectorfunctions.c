void free_vec(Vec *vec){
	for (int i=0; i<vec->index; ++i){
		free(vec->arr[i]);
	}
	free(vec->arr);
	vec->index=0;
	vec->cap =0;
	vec->arr = NULL;
}


void add_to_vector(Vec *vec, char *file, size_t start, int size){
	if (vec->cap == vec->index){
		vec->arr = realloc(vec->arr, sizeof(char*) * vec->cap *2);
		vec->cap *=2;
	}
	char *new_word = (char*) malloc(sizeof(char) *size);
	memcpy(new_word, file+start, size-1);
	new_word[size-1] = '\0';
	vec->arr[vec->index] = new_word;
	vec->index++;
	//printf("%s", new_word);
}