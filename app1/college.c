/*Maddie Follosco
 * Due: 6/11/23
 * This file contains:
 */

#include "dataset.h"

int main (void) {
	
	SET* sp = createDataSet(maxStud);
	//create 1000 student records
	int prevID = 0;
	int i, recordAge, idGen, recordID,newID;
	srand(time(NULL));
	for (i=0; i < 1000; i++) {
		recordAge = (rand() % (ageMax-ageMin +1)) + ageMin;
		idGen = (rand() % (2 - 1 + 1)) + 1;
		recordID = prevID + idGen;
		prevID = recordID;
		insert(sp,recordAge,recordID);

	}

	//generating: random age to search and delete from the range of 18 to 30
	
	int randAge,gap1;
	randAge = (rand() % (ageMax - ageMin + 1)) + ageMin;
	int target = searchAge(sp, randAge);
	deletion(sp, target);
	gap1 = maxAgeGap(sp);
	printf("The max age gap is %d years \n", gap1);
	destroyDataSet(sp);
	
return 0;
}
