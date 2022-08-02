#include <stdio.h>
#include <stdlib.h>
void randgen(FILE* f, int n){

    f = fopen("in.txt", "w");
    for (int i=0; i<n; i++){
        fprintf(f,"%d\n", rand());
    }
    fclose(f);
}

int main(){
FILE* rand;
randgen(rand, 4000);
}