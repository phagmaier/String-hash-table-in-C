size_t move_past_whitespace(char *file, size_t i){
	while (file[i] == ' ' || file[i] == '\n'){
		++i;
	}
	return i;
}

size_t remove_puncuation(char *file, size_t i){
	int offset =0;
	while(!isalnum(file[i-offset])){
		offset++;
	}
	return offset;
}

void parser(Vec *vec, char *file){
	size_t i = move_past_whitespace(file, 0);
	int offset;
	int size;
	size_t start = i;
	while (file[i] != '\0'){
		if (file[i] == ' ' || file[i] == '\n'){
			offset = remove_puncuation(file, i-1);
			size = i - (start + offset);
			if (size > 0){
				add_to_vector(vec, file, start, size+1);	
			}
			i = move_past_whitespace(file, i);
			size = 0;
			start = i;
		}
		++i;
	}
	offset = remove_puncuation(file, i-1);
			size = i - (start + offset);
			if (size > 0){
				add_to_vector(vec, file, start, size+1);	
			}
}