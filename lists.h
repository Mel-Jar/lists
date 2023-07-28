//
// Created by Mason Landis on 1/28/22.
//

#ifndef LISTS_LISTS_MLANDIS1_H
#define LISTS_LISTS_MLANDIS1_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PARTNAME_LEN 32

typedef struct PartRecordStruct {
    int partNumber;
    int quantity;
    char partName[PARTNAME_LEN];
    struct PartRecordStruct *next;
} PartRecord;

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName);

int deletePart(PartRecord **theList, int partNumber);

PartRecord *findPart(PartRecord *theList, int partNumber);

void printParts(PartRecord *theList);
int mergePartLists(PartRecord *listOne, PartRecord *listTwo, PartRecord **mergedList);

#endif //LISTS_LISTS_MLANDIS1_H
