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
    //FILE *file = fopen("aa.txt", "rb");


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
	DicNode dic[SIZE];
	parse_file_add_to_dic(dic, contents, inUse, SIZE);
	free(contents);
	print_dic(dic, inUse, SIZE);

	//int val = get_element_val(dic, inUse,"name", SIZE);
	//printf("%d\n", val);

	free_dic(dic, inUse, SIZE);

	return 0;
}
