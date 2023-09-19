/* Madeline Follosco
 * Due: 6/11/23
 * This file contains:This file contains: functions to create and maintain a hash chaining implementation. Doubly and circularly linked lists are used.
 *
 */

#include "dataset.h"


typedef struct list{
        int count;
        struct node *head;
}LIST;

typedef struct node{
        int age;
	int id;
        struct node *next;
        struct node *prev;
}NODE;


typedef struct set{

	LIST **lists;
	int min;
	int max;
        int length;
        int count;       

}SET;

//function: hash - the age and number of indexes in the array (number of ages in age range) are passed in to return a hash value that becomes the index of the array of structs where the data is located.
//time complexity: O(1)
unsigned hash (int k, int m) {
       	
	return k%m;
}

//function: createDataSet - creates/allocates memory for an array of structs of set as well as initiializes circularly doubly linked lists that will be pointed to by the SET pointer at a certain index of the array
//time complexity: O(n)
SET *createDataSet() {

	SET *sp = malloc(sizeof(SET));
	assert (sp != NULL);
	sp->length = maxAges;
	sp-> count = 0;
	sp->min = ageMax;
	sp->max = ageMin;

	int i;
	sp->lists = malloc(sizeof(LIST*)*sp->length);
        assert(sp->lists != NULL);
	for (i=0; i < sp->length; i++) {
        	struct list *lp;
		lp = malloc(sizeof(struct list));
		assert (lp != NULL);
		lp->count = 0;	
        	lp->head = malloc(sizeof(struct node));
        	assert(lp->head != NULL);
        	lp->head->next = lp->head;
        	lp->head->prev = lp->head;
		sp->lists[i] = lp;
	}
	
	return sp;

}

//function: destroyDataSet - frees all memory associated with each node of the linked list, each list pointer, and the set pointer
//time complexity: O(n) 
void destroyDataSet(SET *sp) {

        assert(sp != NULL);
	int i;
	for (i=0; i < sp->length; i++) {
		NODE *pDel, *pNext;
       		assert(sp != NULL);
        	pDel = sp->lists[i]->head;

        	do {
                	pNext = pDel->next;
                	free(pDel);
                	pDel = pNext;

        	} while(pDel != sp->lists[i]->head);

	}

	free(sp->lists);
	free (sp);
return;
}

//function: searchAge - a pointer to the set and the randomly generated age is passed in to be used in the hash function. Based on the simple search for the index, the student records found in under that age are printed while the index of that array of linked lists is returned
//time complexity: O(1)

int searchAge (SET *sp, int age) {

	assert(sp!=NULL);
	printf("Searching students of age: %d\n", age);
	int loc = hash(age, sp->length);

	LIST *lp = sp->lists[loc];
	if (lp->head->next == NULL) {
	//if no linked list in that index of the hash table / if no id's available for that age
		printf("Records not available for age: %d\n", age);
        	return;
	}	

	printf("Records found: \n");
	NODE *trav;
	trav = sp->lists[loc]->head->next;
	while (trav != sp->lists[loc]->head) {
		
		printf("%d \n" ,trav->id);	
		trav = trav->next;
	}
	return 0;
}
// function: searchID - a pointer to the set and the randomly generated ID is passed tobe searched. A node pointer is created to traverse the linked list and a list pointer gives it the start of every index. If the desired id is found its location/index of the array is returned.
// time comeplexity: O(n)
int searchID (SET *sp, int id) {
	assert(sp!=NULL);
        //searching entire hash table for ID passed in
        int i;
	NODE *trav;
	trav = malloc(sizeof(struct node));
	for (i=0; i < sp->length; i++) {
        	LIST *lp = sp->lists[i];
		
       		trav = lp->head->next;
        	while (trav != lp->head) {
		
 
			if(trav->id == id) {
                		printf("ID located\n");
				return i;
			}

               		trav = trav->next;
        	}
		
	}	
	return -1;	
		
}
//function: insert - a set pointer, random age and id are generated to be passed in. Depending on the hash value of the age the node is created and inserted at the right index. The new data is also checked to see if it contains the new max or min age of all the records.
//time complexity: O(1)
void insert (SET *sp, int age, int id) {
	
	assert(sp != NULL);
	int loc = hash(age,maxAges);
	LIST *lp = sp->lists[loc];
	NODE *new;
	new = malloc(sizeof(struct node));
	assert(new != NULL);
	new->age = age;
	new->id = id;
	
	new->next = lp->head;
        new->prev = lp->head->prev;
        lp->head->prev->next = new;
        lp->head->prev = new;
        lp->count++;

	//update min and max ages upon insertion
	
	if(new->age < sp->min){
		sp->min = new->age;

	}
	if(new->age > sp->max) {
		sp->max = new->age;
	}
	
return;
}

//function: deletion - a pointer to the set is passed in as well as the desired index of deletion. If no data exists for that age/index of the array, then that is communicated by a print statement. Otherwise a list pointer to a specific index of the set is created to traverse the linked list and delete the node with that specific ID
//time complexity: O(n)

void deletion(SET *sp, int loc) {
	assert(sp != NULL);

	if(loc == -1) {
		printf("ID not found\n");
		return;
	}

	LIST *lp = sp->lists[loc];
	
	if(lp != NULL) {
		NODE *trav;
		NODE *temp;
		trav = malloc(sizeof(struct node));
		trav = lp->head->prev;
        	while (lp->count != 0) {

        		trav->prev->next = lp->head;
                	lp->head->prev = trav->prev;
 			temp = trav;
                	lp->count --;
                	trav = trav->next;
			free(temp);
        	}

		free(lp);
		printf("Record successfully deleted\n");
	}
return;			
}

//function: maxAgeGap - returns the max age gap of all the student records
//time complexity: O(1)
int maxAgeGap (SET *sp) {

	int gap;
	gap = sp->max - sp->min;

return gap;
}
