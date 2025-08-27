#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct 
{
    int elem[MAX];
    int count;

} List;

List L;

List insertPos(List L, int data, int position){

int i;
for (int i = 0; i < position; i--){
    L.elem[i] = L.elem[i-1];
}

L.elem[i] = data;

return L;

}

List deletePos(List L, int position){

}

int main(){
    List l;
    int i;

    l.elem[0] = 1;
    l.elem[1] = 3;
    l.elem[2] = 2;
    l.elem[3] = 5;
    l.count = 4;

    for (i = 0; i < l.count; i++){
        printf("%d", l.elem[i]);
    }

}


