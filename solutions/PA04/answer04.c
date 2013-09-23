/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>

void partitionAll_helper(int*, int, int);
void partitionIncreasing_helper(int*, int, int);
void partitionDecreasing_helper(int*, int, int);
void partitionOdd_helper(int*, int, int);
void partitionEven_helper(int*, int, int);
void partitionOddAndEven_helper(int*, int, int);
void partitionPrime_helper(int*, int, int);
int isPrime(int);
void printPartition(int*, int);


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */


void partitionAll(int value)
{
	printf("partitionAll %d\n", value);
	int* arr = malloc(sizeof(int) * value);	
	partitionAll_helper(arr, 0, value);
}

void partitionAll_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		part[ind] = val;
		partitionAll_helper(part, ind+1, left-val);
	}
}

void printPartition(int* part, int length){
	int ind;
	for(ind = 0;ind < length-1;ind++){
		printf("%d + ", part[ind]);
	}
	printf("%d\n", part[length-1]);
}


/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionIncreasing(int value)
{
	printf("partitionIncreasing %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionIncreasing_helper(arr, 0, value);
}

void partitionIncreasing_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0){
			part[ind] = val;
			partitionIncreasing_helper(part, ind+1, left-val);
		}
		else{
			if(val > part[ind-1]){
				part[ind] = val;
				partitionIncreasing_helper(part, ind+1, left-val);
			}
		}
	}
}


/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
	printf("partitionDecreasing %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionDecreasing_helper(arr, 0, value);
}

void partitionDecreasing_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0){
			part[ind] = val;
			partitionDecreasing_helper(part, ind+1, left-val);
		}
		else{
			if(val < part[ind-1]){
				part[ind] = val; 
				partitionDecreasing_helper(part, ind+1, left-val);
			}
		}
	}
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionOdd_helper(arr, 0, value);
}

void partitionOdd_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0 && val % 2 > 0){
			part[ind] = val;
			partitionOdd_helper(part, ind+1, left-val);
		}
		else{
			if(val % 2 > 0){
				part[ind] = val; 
				partitionOdd_helper(part, ind+1, left-val);
			}
		}
	}
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionEven_helper(arr, 0, value);
}

void partitionEven_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0 && val % 2 == 0){
			part[ind] = val;
			partitionOdd_helper(part, ind+1, left-val);
		}
		else{
			if(val % 2 == 0){
				part[ind] = val; 
				partitionOdd_helper(part, ind+1, left-val);
			}
		}
	}
}


/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionOddAndEven_helper(arr, 0, value);
}

void partitionOddAndEven_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0 && val % 2 > 0){
			part[ind] = val;
			partitionOddAndEven_helper(part, ind+1, left-val);
		}
		else{
			if( (val % 2 == 0 && part[ind-1] % 2 > 0) || (val % 2 > 0 && part[ind-1] % 2 == 0) ){
				part[ind] = val; 
				partitionOddAndEven_helper(part, ind+1, left-val);
			}
		}
	}
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);
  int* arr = malloc(sizeof(int) * value);	
	partitionPrime_helper(arr, 0, value);
}

void partitionPrime_helper(int* part, int ind, int left){
	int val;
	if(left == 0){
		printPartition(part, ind);
		return;
	}
	for(val = 1;val <= left;val++){
		if(ind == 0 && isPrime(val)){
			part[ind] = val;
			partitionPrime_helper(part, ind+1, left-val);
		}
		else{
			if(isPrime(val)){
				part[ind] = val; 
				partitionPrime_helper(part, ind+1, left-val);
			}
		}
	}
}

int isPrime(int num){
	int j;	
	if(num == 1){
		return 0;
	}

	for(j = 2;j < num;j++){
		if(!(num % j)){
			return 0;
		}
	}

	return 1;
}



