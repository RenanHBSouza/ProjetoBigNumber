#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

int main() {
    BigNumber numero1, numero2, resp;
        char sinalCalc;
        char* entrada;
        char x[2] = {'0','\0'};

    while(1){
        entrada = pegar_numero();
        numero1 = Construcao_bignumber(numero1, entrada);
        entrada = pegar_numero();
        numero2 = Construcao_bignumber(numero2, entrada);
        resp = Construcao_bignumber(resp, x);
        scanf("%c", &sinalCalc);
        if(sinalCalc=='+'){
            Soma_bignumber(numero1,numero2);
            Imprimir_bignumber(numero1, numero1->tamanho);      //  Chamada da impressao do resultado
        }
        else if(sinalCalc=='-'){
            Subtracao_bignumber(numero1,numero2);
            Imprimir_bignumber(numero1, numero1->tamanho);      //Chamada da impressao do resultado
        }
        else if(sinalCalc=='*'){
            Karatsuba_bignumber(numero1,numero2,resp);
            Imprimir_bignumber(resp, resp->tamanho);      //Chamada da impressao do resultado
        }
        else{
            printf("Valor inválido!");
        }
        Destruir_bignumber(numero1);
        Destruir_bignumber(numero2);
    }
    return 0;
}
