#include <stdio.h>
#include <stdlib.h>

void imprime(int*num,int tam){
    int i;
    for(i=0;i<tam;i++){
        printf("%d ", num[i]);
    }
    printf("\n");
    return;
}

void pot10(int* num, int tam, int k){
    num = realloc(num, (tam+k)*sizeof(int));
    int i;
    for(i=k;i>0;i--){
        num[(i+k)-1] = num[i-1];
        num[i-1] = 0;
    }
    return;
}

int main(){
    int* vet = malloc(2*sizeof(int));
    for(int i=0;i<2;i++){
        scanf("%d", &vet[i]);
    }
    pot10(vet,2,5);
    imprime(vet,7);
    return 0;
}