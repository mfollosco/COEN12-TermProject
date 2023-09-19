/*Maddie Follosco
 * Due: 6/11/23
 * This file contains:
 */

#include "dataset.h"

int main (void) {
	
	SET* sp = createDataSet();
	//create 1000 student records
	int prevID = 0;
	int i, recordAge, idGen, recordID,newID;
	srand(time(0));
	for (i=0; i < 1000; i++) {
		recordAge = (rand() % (ageMax-ageMin +1)) + ageMin;
		idGen = (rand() % (2 - 1 + 1)) + 1;
		recordID = prevID + idGen;
		prevID = recordID;
		//printf("age: %d id: %d \n", recordAge, recordID);
		insert(sp,recordAge,recordID);

	}

	//generating: a random, unique ID to search and delete from the records
	
	int randAge,randID,gap1;
	randAge = (rand() % (ageMax - ageMin + 1)) + ageMin;
	int target = searchAge(sp, randAge);
	randID = (rand() % (idMax - idMin + 1)) + idMin;
	printf("ID to be searched and deleted is %d \n", randID);
	searchID(sp, randID);
	deletion(sp, target);
	gap1 = maxAgeGap(sp);
	printf("The max age gap is %d years \n", gap1);
	destroyDataSet(sp);

return 0;
}
