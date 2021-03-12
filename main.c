#include <stdio.h>
#include "lab4.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
int main() {
    Set set, set1, set2, unitedSet;
    createSet(&set);
    /*
    printf("Size: %i\n", size(set));
    isEmpty(set) ? printf("isEmpty: true\n") : printf("isEmpty: false\n");

    for (int i=15; i>10; --i) {
        insert(&set, i);
        printElements(set);
    }
    erase(&set, 14);
    printElements(set);

    erasePos(&set, 2);
    printElements(set);

    find(set, 16);
    lowerBound(set, 13);
    upperBound(set, 12);
     */

    /////////////EGYESÍTÉS
    createSet(&set1);
    createSet(&set2);
    createSet(&unitedSet);
    unite(&set1, &set2, &unitedSet);

    return 0;
}
