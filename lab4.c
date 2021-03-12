//
// Created by Kataee on 10/03/2021.
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <time.h>
#include "lab4.h"

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void printElements(Set set) {
    if (set.size == 0) {
        printf("Nincs a halmaznak eleme\n");
    }
    for (int i=0; i < set.size; ++i) {
        printf("%i ", set.elements[i]);
    }
    printf("   size: %i\n", set.size);
}

Set* createSet(Set* set) {
    (*set).elements = (int*)malloc(0 * sizeof(int));
    (*set).size = 0;
    if ( !(set)) {
        return NULL;
    }
    //see above, line 20
    //pset->size = 0;
    return set;
}

int size(Set set) {
    return set.size;
}

bool isEmpty(Set set) {
    if (set.size == 0) {
        return true;
    }
    return false;
}

void insert(Set* set, int element) {
    for (int i=0; i < (*set).size; ++i) {
        if (element == (*set).elements[i] ) {
            //printf("Ez a szam mar eleme a halmaznak\n");
            return;
        }
    }
    (*set).size++;
    (*set).elements = (int*)realloc((*set).elements, (*set).size * sizeof(int));

    if ((*set).size) {
        (*set).elements[(*set).size-1] = element;
    } else { return; }

        qsort((*set).elements, (*set).size, sizeof(int), cmpfunc);
}

void erase(Set* set, int element) {
    bool isElement = false;
    int index;
    for (int i=0; i < (*set).size; ++i) {
        if (element == (*set).elements[i]) {
            isElement = true;
            index = i; //keep the index of the element
            break;
        }
    }

    if (isElement) {
        int temp;
        temp = (*set).elements[(*set).size-1];
        (*set).elements[index] = (*set).elements[(*set).size-1];
        (*set).size--;
        (*set).elements = (int*)realloc((*set).elements, (*set).size * sizeof(int));
        qsort((*set).elements, (*set).size, sizeof(int), cmpfunc);
    } else {
        printf("Ez az elem nem letezik a halmazban.\n");
        return;
    }
}

void erasePos(Set* set, int position) {
    if (position < 0 || position > (*set).size-1) {
        printf("Ez a pozicio nem letezik\n");
        return;
    }
    (*set).elements[position] = (*set).elements[(*set).size-1];
    (*set).size--;
    (*set).elements = (int*)realloc((*set).elements, (*set).size * sizeof(int));
    qsort((*set).elements, (*set).size, sizeof(int), cmpfunc);
}

void clear(Set* set) {
    (*set).elements = (int*)realloc((*set).elements, 0);
}

int find(Set set, int element) {
    int position;
    for (int i=0; i < set.size; ++i ) {
        if (element == set.elements[i]) {
            printf("A keresett elem pozicioja: %i\n", i);
            return i;
        }
    }
    printf("Nem talaltuk meg a keresett elemet.\n");
    return -1;
}

int lowerBound(Set set, int element) {
    int lowerBound, index=0;

    do {
        lowerBound = set.elements[index];
        index++;
    } while (element >= set.elements[index]);
    printf("A lowerBound: %i\n", lowerBound);
    return lowerBound;
}

int upperBound(Set set, int element) {
    int upperBound, index=0;

    do {
        upperBound = set.elements[index];
        if (element < set.elements[0]) {
            printf("Az upperBound: %i\n", upperBound);
            return upperBound;
        }
        if (element == set.elements[index]) {
            printf("Az upperBound: %i\n", upperBound);
            return upperBound;
        }
        index++;
        if (index == set.size-1) {
            printf("Az upperBound: %i\n", set.elements[index]);
            return set.elements[index];
        }
    } while (index < set.size);

}

void fillSet(Set* set, int size) {
    srand(time(NULL));
    int element;

    for (int i=0; i < size; ++i) {
        //element = 5 + rand() % 1000;
        //element = random_number(0,50);
        element = (int)(random_uint(50) + 1);
        insert(set, element);
        //insert(set, i+size);
    }
    //printElements(*set);
}

void unite(Set* set1, Set* set2, Set* unitedSet) {
    fillSet(set1, 6);
    fillSet(set2, 13);
    printElements(*set1);
    printElements(*set2);

    printf("size: %i   size: %i\n", (*set1).size, (*set2).size);

    for (int i=0; i< (*set1).size; ++i) {
        insert(unitedSet, (*set1).elements[i]);
    }
    for (int i=0; i< (*set2).size; ++i) {
        insert(unitedSet, (*set2).elements[i]);
    }
    printf("united: \n");
    printElements(*unitedSet);

        //nem tudom miért generálódnak ugyan azok a számok mindkét halmazban

}


/* Random integer in [0, limit) */
unsigned int random_uint(unsigned int limit) {
    union {
        unsigned int i;
        unsigned char c[sizeof(unsigned int)];
    } u;

    do {
        if (!RAND_bytes(u.c, sizeof(u.c))) {
            fprintf(stderr, "Can't get random bytes!\n");
            exit(1);
        }
    } while (u.i < (-limit % limit)); /* u.i < (2**size % limit) */
    return u.i % limit;
}