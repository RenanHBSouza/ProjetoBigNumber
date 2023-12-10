#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n {
    int *digitos;
    size_t tamanho;
    char sinal;
} *BigNumber;

void Soma_interna(BigNumber num1, BigNumber num2);

BigNumber Construcao_bignumber(BigNumber num, char *valor) {
int i;
    num = malloc(sizeof(struct n));     //Aloca memória para a estrutura
    if(num == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    num->tamanho = strlen(valor);       //Pega o tamanho da string valor para definir o tamanho de digitos
    if(valor[0] == '-'){        //Se o 1º valor for '-' armazena esse sinal na estrutura 
        num->sinal = '-';
        num->tamanho -= 1;      //Remove 1 do tamanho que será utilizado para os digitos (digito do -)
        num->digitos = malloc(num->tamanho*sizeof(int));    //Aloca memória para o vetor de inteiros que receberá cada digito
        if(num->digitos == NULL){
            printf("Nao ha memoria suficiente!\n");
            exit(1);
        }
        for(i=0;i<num->tamanho;i++){    //Converte cada caractere para int e insere em digitos
            num->digitos[i] = (int)valor[(num->tamanho)-i]-48;      //-48 para converter da tabela ASCII
        }
    }
    else{
        num->sinal = '+';       //Mantem os digitos e adiciona '+' quando não recebe '-'
        num->digitos = malloc(num->tamanho*sizeof(int));
        if(num->digitos == NULL){
            printf("Nao ha memoria suficiente!\n");
            exit(1);
        }
        for(i=0;i<num->tamanho;i++){        //Adiciona os valores da string para os digitos
            num->digitos[i] = (int)valor[(num->tamanho-1)-i]-48;
        }
    }
    while(num->digitos[num->tamanho-1]==0 && num->tamanho!=1){        //Tira os 0's quando eles estão depois do fim do numero
        if(num->digitos[num->tamanho-1]==0){
            num->tamanho -= 1;
        }
        num->digitos = realloc(num->digitos, num->tamanho*sizeof(int));     //Realoca com o tamanho novo
        if(num->digitos == NULL){
            printf("Nao ha memoria suficiente!\n");
            exit(1);
        }
    }
    //free(valor);        //Libera a memoria da string valor para garantir mais memoria
    return num;
}

void Imprimir_bignumber(BigNumber numero, int tam) {
   if(tam==numero->tamanho){     //Caso esteja no inicio da execução printa '-' se tiver       
        if(numero->sinal=='-'){
            printf("%c",'-');
        }
    }
    while(numero->digitos[numero->tamanho-1]==0 && numero->tamanho>1){      //Caso o primeiro digito do valor (final do vetor) tenha sido zerado, remove pois é digito inutil
        numero->tamanho-=1;
        tam-=1;
        numero->digitos = realloc(numero->digitos, numero->tamanho*sizeof(int));
        if(numero->digitos == NULL){
            printf("Nao ha memoria suficiente!\n");
            exit(1);
    }
    }
    if(tam==0){         //Quando a variavel de tamanho chegar em 0 termina a recursão
        printf("\n");
        return;
    }       

    printf("%d", numero->digitos[tam-1]);   
    Imprimir_bignumber(numero,tam-1);     //Chama a função novamente para ir printando de modo invertido
}

void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp) {
    size_t m;

    if (num1->tamanho == 1 && num1->digitos[0] == 0) {
        resp->tamanho = 1;
        resp->sinal = '+';
        resp->digitos = realloc(resp->digitos, sizeof(int));
        if (resp->digitos == NULL) {
            printf("Nao ha memoria suficiente!\n");
            exit(1);
        }
        resp->digitos[0] = 0;
        return;
    }

    if (num2->tamanho == 1 && num2->digitos[0] == 0) {
        resp->tamanho = 1;
        resp->sinal = '+';
        resp->digitos = realloc(resp->digitos, sizeof(int));
        if (resp->digitos == NULL) {
            printf("Nao ha memoria suficiente!\n");
            exit(1);
        }
        resp->digitos[0] = 0;
        return;
    }

    // Determina a metade do BigN
    if (num1->tamanho > num2->tamanho) {
        m = num1->tamanho / 2;
    } else {
        m = num2->tamanho / 2;
    }

    // Cria os BigNumbers a, b, c, e d
    BigNumber a = malloc(sizeof(struct n));
    a->tamanho = m;
    a->digitos = calloc(a->tamanho, sizeof(int));
    a->sinal = num1->sinal;

    BigNumber b = malloc(sizeof(struct n));
    b->tamanho = m;
    b->digitos = calloc(b->tamanho, sizeof(int));
    b->sinal = num1->sinal;

    BigNumber c = malloc(sizeof(struct n));
    c->tamanho = m;
    c->digitos = calloc(c->tamanho, sizeof(int));
    c->sinal = num2->sinal;

    BigNumber d = malloc(sizeof(struct n));
    d->tamanho = m;
    d->digitos = calloc(d->tamanho, sizeof(int));
    d->sinal = num2->sinal;

    // Preenche os valores de a, b, c, e d
    for (size_t i = 0; i < m; i++) {
        if (i < num1->tamanho) {
            a->digitos[i] = num1->digitos[i + m];
            b->digitos[i] = num1->digitos[i];
        }

        if (i < num2->tamanho) {
            c->digitos[i] = num2->digitos[i + m];
            d->digitos[i] = num2->digitos[i];
        }
    }

    // Calcula os produtos recursivamente usando algoritmo de Karatsuba
    BigNumber ac = malloc(sizeof(struct n));
    ac->tamanho = a->tamanho + c->tamanho;
    ac->sinal = '+';
    ac->digitos = calloc(ac->tamanho, sizeof(int));
    Karatsuba_bignumber(a, c, ac);

    BigNumber bd = malloc(sizeof(struct n));
    bd->tamanho = b->tamanho + d->tamanho;
    bd->sinal = '+';
    bd->digitos = calloc(bd->tamanho, sizeof(int));
    Karatsuba_bignumber(b, d, bd);

    // (a+b)*(c+d)
    BigNumber abcd = malloc(sizeof(struct n));
    abcd->tamanho = (a->tamanho + b->tamanho) * 2;
    abcd->sinal = '+';
    abcd->digitos = calloc(abcd->tamanho, sizeof(int));
    Soma_interna(a, b);
    Soma_interna(c, d);
    Karatsuba_bignumber(a, c, abcd);

    // Resultado final
    Soma_interna(ac, bd);
    BigNumber acbd = malloc(sizeof(struct n));
    acbd->tamanho = ac->tamanho + bd->tamanho;
    acbd->sinal = '+';
    acbd->digitos = calloc(acbd->tamanho, sizeof(int));
    Karatsuba_bignumber(ac, bd, acbd);
    Soma_interna(acbd, abcd);

    // Copia o resultado para o número de resposta
    resp->tamanho = acbd->tamanho;
    resp->sinal = acbd->sinal;
    resp->digitos = realloc(resp->digitos, resp->tamanho * sizeof(int));
    memcpy(resp->digitos, acbd->digitos, resp->tamanho * sizeof(int));

    // Libera memória alocada para os números intermediários
    free(a->digitos);
    free(b->digitos);
    free(c->digitos);
    free(d->digitos);
    free(ac->digitos);
    free(bd->digitos);
    free(abcd->digitos);
    free(acbd->digitos);

    free(a);
    free(b);
    free(c);
    free(d);
    free(ac);
    free(bd);
    free(abcd);
    free(acbd);
}

void Soma_interna(BigNumber num1, BigNumber num2) {
    // Adaptei a função de soma para receber dois números BigNumbers e realizar a soma in-place
    size_t tam = (num1->tamanho > num2->tamanho) ? num1->tamanho : num2->tamanho;
    int carry = 0;

    for (size_t i = 0; i < tam || carry; i++) {
        if (i == num1->tamanho) {
            num1->digitos = realloc(num1->digitos, (i + 1) * sizeof(int));
            if (num1->digitos == NULL) {
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            num1->digitos[i] = 0;
        }

        int soma = num1->digitos[i] + carry + ((i < num2->tamanho) ? num2->digitos[i] : 0);
        carry = soma / 10;
        num1->digitos[i] = soma % 10;
    }
}

int main() {
    // Teste da multiplicação de Karatsuba
    BigNumber num1 = malloc(sizeof(struct n));
    BigNumber num2 = malloc(sizeof(struct n));
    BigNumber resp = malloc(sizeof(struct n));

    num1 = Construcao_bignumber(num1, "1234");
    num2 = Construcao_bignumber(num2, "5678");
    resp->tamanho = 0;
    resp->sinal = '+';
    resp->digitos = NULL;

    Karatsuba_bignumber(num1, num2, resp);

    Imprimir_bignumber(resp, resp->tamanho);
    
    // Libera a memória alocada
    free(num1->digitos);
    free(num1);
    free(num2->digitos);
    free(num2);
    free(resp->digitos);
    free(resp);

    return 0;
}