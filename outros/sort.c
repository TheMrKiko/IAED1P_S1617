#include <stdio.h>

void imprime(char M[], int H[]){
    int i;
    for (i = 0; i <= 7; i++){
        printf("%c\n", M[H[i]]);
    };
};

int main() {
    char M[] = {'f', 'h', 'b', 'j', 'w', 'g', 'a', 'q'};
    int H[] = {0,1,2,3,4,5,6,7};
    int i, j;
    for (i = 1; i <= 7; i++) {
        int v = H[i];
        j = i-1;
        while (j >= 0 && M[v] < M[ H[j] ]) {
            H[j+1] = H[j];
            j--;
        };
        H[j+1] = v;
    };
    imprime(M, H);
    return 0;
};
