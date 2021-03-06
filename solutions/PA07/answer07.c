#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

void sortIndeces(int* value, int* index, int length);
int indexCmp(const void* a, const void* b);


/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
	Node* p = head;
	while(p != NULL){
		fprintf(out, "%5d: %6d\n", p -> index, p -> value);
		p = p -> next;
	}
	printf("\n");
}

void List_dump(Node * head)
{
	Node* p = head;
	while(p != NULL){
		printf("[%p] %5d: %6d ==> %p\n", p, p -> index, p -> value, p -> next);
		p = p -> next;
	}
	printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
	while(head != NULL){
		Node* p = head->next;
		free(head);
		head = p;
	}
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
		Node* n = malloc(sizeof(Node));
		n->value =  value;
		n->index = index;
		n->next = NULL;
    return n;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
	int i;
	Node* n = NULL;
	sortIndeces(value, index, length);
	for(i = 0;i < length;i++){
		n = List_insert_ascend(n, value[i], index[i]);
	}

  return n;
}

void sortIndeces(int * value, int* index, int length){
	int* index_cpy = malloc(sizeof(int) * length);
	int* value_cpy = malloc(sizeof(int) * length);
	int i;

	for(i = 0;i < length;i++){
		index_cpy[i] = index[i];
	}
	qsort(index, length, sizeof(int), indexCmp);
	
	int key;
	for(i = 0;i < length;i++){
		key = index_cpy[i];
		int* match = (int*) bsearch(&key, index, length, sizeof(int), indexCmp);
		if(match == NULL){
			printf("\nNull match in binary seach\n");
		}
		int newILocation = match - index;
		value_cpy[newILocation] = value[i];
	}
	for(i = 0;i < length;i++){
		value[i] = value_cpy[i];
	}
 	
	free(index_cpy);
	free(value_cpy);
}

int indexCmp(const void* a, const void* b){
	int* pointa = (int*) a;
	int* pointb = (int*) b;
	int vala = *pointa;
	int valb = *pointb;

	if(vala < valb){
		return -1;
	}
	if(vala == valb){
		return 0;
	}
	return 1;
}

/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
	if(head == NULL){
		head = List_create(value, index);
		return head;
	}

	Node* p = head;
	while(p->next != NULL){
		p = p->next;
	}
	p->next = List_create(value, index);
	return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index)
{
	if(head == NULL){
		return head;
	}
	if(head->next == NULL){
		if(head->index == index){
			free(head);
			head = NULL;
		}
		return head;
	}
	if(head->next->index == index){
		printf("\nFound the index\n");
		Node* p = head->next->next;
		free(head->next);
		head->next = p;
		return head;
	}

	head = List_delete(head->next, index);
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head)
{
	Node* copy = NULL;
	Node* p = head;
	int length = 0;
	while(p != NULL){
		length++;
		p = p->next;
	}
	int* values = malloc(sizeof(int) * length);
	int* indeces = malloc(sizeof(int) * length);
	p = head;
	int i;
	for(i = 0;i < length;i++){
		values[i] = p->value;
		indeces[i] = p->index;
		p = p->next;
	}
	copy = List_build(values, indeces, length);
	free(values);
	free(indeces);
	return copy;
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_merge(Node * head1, Node * head2)
{
	Node* p = List_copy(head1);
	Node* a1 = head2;
	Node* a2 = p;
	while(a1 != NULL){
		if(a1->index == a2->index){
			al->value += a2->value;
		}
		else{
			List_insert_ascend(a1, a2->value, a2->index);
		}
		a1 = a1->next;
	}
	
	return p;
}

#ifdef MYTEST
//  gcc -g -Wall -Wshadow -DMYTEST -o answer07 answer07.c && ./answer07
void test_list_insert_ascend();

int main(int argc, char * * argv)
{
	test_list_insert_ascend();
	return 0;
}

void test_list_insert_ascend()
{
		printf("running tests on list-insert-ascend\n");
		
	  Node * head = List_create(100, 2);
		head -> next = List_create(100, 4);
		head -> next -> next = List_create(100, 6);
		head -> next -> next -> next = List_create(100, 8);
		head -> next -> next -> next -> next = List_create(100, 10);
		
		
		
	  //printf("Printing start-list\n");
	  //List_dump(head);
		List_print(stdout, head);
	  List_destroy(head);
}


#endif








