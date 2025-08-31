#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List insertPos(List L, int data, int position) {
    int i;
    if (L.count == MAX) return L;
    if (position < 0 || position > L.count) return L;
    for (i = L.count; i > position; i--) {
        L.elem[i] = L.elem[i - 1];
    }
    L.elem[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position) {
    int i;
    if (L.count == 0) return L;
    if (position < 0 || position >= L.count) return L;
    for (i = position; i < L.count - 1; i++) {
        L.elem[i] = L.elem[i + 1];
    }
    L.count--;
    return L;
}

int main() {
    List l;
    int i;
    l.elem[0] = 1;
    l.elem[1] = 3;
    l.elem[2] = 2;
    l.elem[3] = 5;
    l.count = 4;

    printf("Original List: ");
    for (i = 0; i < l.count; i++) {
        printf("%d ", l.elem[i]);
    }
    printf("\n");

    l = insertPos(l, 10, 2);

    printf("After Insert: ");
    for (i = 0; i < l.count; i++) {
        printf("%d ", l.elem[i]);
    }
    printf("\n");

    l = deletePos(l, 1);

    printf("After Delete: ");
    for (i = 0; i < l.count; i++) {
        printf("%d ", l.elem[i]);
    }
    printf("\n");

    return 0;
}
