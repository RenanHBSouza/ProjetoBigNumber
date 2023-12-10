#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct n{
    int *digitos;
    int tamanho;
    char sinal;
}* BigNumber;

BigNumber Construcao_bignumber(BigNumber num, char* valor);
char* pegar_numero();

void Imprimir_bignumber(BigNumber numero, int tam);

void Soma_bignumber(BigNumber num1, BigNumber num2);
void Soma_interna(BigNumber num1, BigNumber num2);

void empresta(BigNumber num, int atual);
void passa_1(BigNumber num, int atual);
void pot10(BigNumber num, int k);

void Subtracao_bignumber(BigNumber num1, BigNumber num2);
void Subtracao_interna(BigNumber num1, BigNumber num2);

void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp);

void Destruir_bignumber(BigNumber num);

#endif