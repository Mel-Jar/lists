//
// Created by Mason Landis on 1/28/22.
//
#include <stdlib.h>
#include "lists.mlandis1.h"
int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName){
    if(theList != NULL && findPart(*theList, partNumber) == NULL) {
        PartRecord *curr = *theList;
        PartRecord *prev = NULL;
        PartRecord *newRecord = malloc(sizeof(PartRecord));
        strcpy(newRecord->partName, partName);
        newRecord->partNumber = partNumber;
        newRecord->quantity = quantity;
        newRecord->next = NULL;
        if (curr == NULL) {
            *theList = newRecord;
        } else {
            while (curr != NULL && partNumber > curr->partNumber) {
                prev = curr;
                curr = curr->next;
            }
            newRecord->next = curr;
            if (prev != NULL)
                prev->next = newRecord;
            else
                *theList = newRecord;
        }
        return 0;
    }else{
        return 1;
    }
}

int deletePart(PartRecord **theList, int partNumber){
    PartRecord *curr = *theList;
    PartRecord *prev = NULL;
    while(curr != NULL && curr->partNumber != partNumber){
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        return 1;
    }else{
        if(prev != NULL)
            prev->next = curr->next;
        else
            *theList = curr->next;
        free(curr);
        return 0;
    }

}

PartRecord *findPart(PartRecord *theList, int partNumber){
    PartRecord *curr = theList;
    int found = 0;
    while ( curr != NULL && !found ) {
        if ( curr->partNumber == partNumber)
            found = 1;
        else
            curr = curr->next;
    }
    if (found)
        return curr;
    else
        return NULL;
}

void printParts(PartRecord *theList){
    PartRecord *curr = theList;
    if(curr == NULL)
        printf("(list is empty)");
    else{
        while(curr != NULL){
            printf("\nnumber = %d, quantity = %d, name = |%s| \n", curr->partNumber, curr->quantity, curr->partName);
            curr = curr->next;
        }
    }
}

int mergePartLists(PartRecord *theListOne, PartRecord *theListTwo, PartRecord **theMergedList){
    PartRecord *currOne = theListOne;
    PartRecord *currTwo = theListTwo;
    PartRecord *conflict = malloc(sizeof(PartRecord));
    int problem;
    int found= 0;
    while ( currOne != NULL) {
        while ( currTwo != NULL && currOne->partNumber >= currTwo->partNumber) {
            if ( currOne->partNumber == currTwo->partNumber){
                problem = strcmp(currOne->partName, currTwo->partName);
                //printf("%d",problem);
                if (problem != 0) {
                    found = 1;
                    strcpy(conflict->partName, currOne->partName);
                    conflict->partNumber = currOne->partNumber;
                    conflict->quantity = currOne->quantity;
                    conflict->next = NULL;
                    printParts(conflict);
                    strcpy(conflict->partName, currTwo->partName);
                    conflict->partNumber = currTwo->partNumber;
                    conflict->quantity = currTwo->quantity;
                    conflict->next = NULL;
                    printParts(conflict);
                }
            }
            currTwo = currTwo->next;
        }
        currOne = currOne->next;
    }
    if (found==1)
        return 1;
    else{
        currOne = theListOne;
        currTwo = theListTwo;
        while ( currOne != NULL) {
            while ( currTwo != NULL && currOne->partNumber >= currTwo->partNumber) {
                if ( currOne->partNumber == currTwo->partNumber){
                    insertPart(theMergedList, currOne->partNumber, currOne->quantity+currTwo->quantity, currOne->partName);
                }
                currTwo = currTwo->next;
            }
            currOne = currOne->next;
        }
        currOne = theListOne;
        currTwo = theListTwo;
        while ( currOne != NULL) {
            insertPart(theMergedList, currOne->partNumber, currOne->quantity, currOne->partName);
            currOne = currOne->next;
        }
        while ( currTwo != NULL) {
            insertPart(theMergedList, currTwo->partNumber, currTwo->quantity, currTwo->partName);
            currTwo = currTwo->next;
        }
        return 0;
    }
}