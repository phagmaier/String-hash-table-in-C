#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DicNode.h"
#include "DicFunctions.c"
#include "vector.h"
#include "vectorfunctions.c"
#include "parsefunctions.c"
#define SIZE (1000)

int inUse[SIZE];


int main(){
	FILE *file = fopen("mobydick.txt", "rb");

	if (!file){
		perror("Error opening the fil\n");
		return 1;
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file,0,SEEK_SET);
	char *contents = (char *) malloc(size);
	if (!contents){
		perror("Error allocating memory\n");
		return 1;
	}
	fread(contents, 1, size, file);

	fclose(file);
	//printf("%s\n", contents);
	Vec vec = {.index=0, .cap = SIZE, .arr = (char**) malloc(sizeof(char*) * size)};
	parser(&vec, contents);
	free(contents);
	DicNode dic[SIZE];
	for (int i=0; i<vec.index; ++i){
		size_t hash = get_hash(vec.arr[i], SIZE);
		//size_t hash = 69;
		add_to_dic(dic, vec.arr[i], inUse, hash);
	}

	free_vec(&vec);
	print_dic(dic, inUse, SIZE);
	free_dic(dic, inUse, SIZE);
	return 0;
}