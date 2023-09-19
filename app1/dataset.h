/*Madeline Follosco
 * Due: 6/11/23
 * This file contains
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define maxAges 13
#define ageMin 18
#define ageMax 30
#define maxStud 3000
#define idMin 1
#define idMax 2000

typedef struct set SET;
typedef struct list LIST;
typedef struct node NODE;
unsigned hash (int k, int m);
SET *createDataSet(int maxppl);
void destroyDataSet(SET *sp);
int searchAge(SET *sp, int age);
void insert(SET *sp, int age, int id);
void deletion(SET *sp, int loc);
int maxAgeGap (SET *sp);
