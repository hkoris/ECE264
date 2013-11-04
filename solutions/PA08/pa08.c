/*
 * Do not modify this file
 */

#include <stdio.h>
#include <stdlib.h>
#include "pa08.h"

void printArray(SparseNode*);

int main ( int argc , char ** argv )
{
	int values[7] = {1, 10, 30, 5, 6, 2, 4};
	int indicies[7] = {2, 5, 4, 3, 7, 6, 8};
	int length = 7;

	SparseNode* array = SparseArray_build(indicies, values, length);
	printArray(array);
	printf("\n");

	SparseArray_remove(array, 5);
	printArray(array);
	printf("\n");
  return 1;
}

void printArray(SparseNode* array){
	if(array == NULL){
		return;
	}
	
	printArray(array->left);
	printf("\nIndex: %d, Value: %d", array->index, array->value);
	printArray(array->right);
}
