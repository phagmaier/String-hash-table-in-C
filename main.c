//NOW YOU JUST HAVE TO DO PARSING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vector.h"
#include "vectorfunctions.c"
#include "DicNode.h"
#include "DicFunctions.c"

#define SIZE (1000)

int inUse[SIZE];

int main(){

    //simple example of how it works.
    //will have the moby dick parser and dic example runnint tomorow
	char str1[] = "Parker";
	char str2[] = "Ava";
	char str3[] = "Parker";
	char str4[] = "steve";
	DicNode dic[SIZE];
	add_string(dic, str1, inUse, get_hash(str1, SIZE));
	add_string(dic, str2, inUse, get_hash(str2, SIZE));
	add_string(dic, str3, inUse, get_hash(str3, SIZE));
	add_string(dic, str4, inUse, 754);
	print_dic(dic, inUse,SIZE);
	free_dic_vals(dic, inUse, SIZE);
	return 0;
}
