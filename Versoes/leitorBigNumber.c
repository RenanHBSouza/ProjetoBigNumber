#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>



// Ponteiro de estrutura para representar um big number
typedef struct n{
    int *digitos;
    size_t tamanho;
    char sinal;
}* BigNumber;

BigNumber Construcao_bignumber(BigNumber num, char* valor) {    //Função que retorna um big number construído
    int i;
    num = malloc(sizeof(struct n));     //Aloca memória para a estrutura
    num->tamanho = strlen(valor);       //Pega o tamanho da string valor para definir o tamanho de digitos
    if(valor[0] == '-'){        //Se o 1º valor for '-' armazena esse sinal na estrutura 
        num->sinal = '-';
        num->tamanho -= 1;      //Remove 1 do tamanho que será utilizado para os digitos (digito do -)
        num->digitos = malloc(num->tamanho*sizeof(int));    //Aloca memória para o vetor de inteiros que receberá cada digito
        for(i=0;i<num->tamanho;i++){    //Converte cada caractere para int e insere em digitos
            num->digitos[i] = (int)valor[(num->tamanho)-i]-48;      //-48 para converter da tabela ASCII
        }
    }
    else{
        num->sinal = '+';       //Mantem os digitos e adiciona '+' quando não recebe '-'
        num->digitos = malloc(num->tamanho*sizeof(int));
        for(i=0;i<num->tamanho;i++){        //Adiciona os valores da string para os digitos
            num->digitos[i] = (int)valor[(num->tamanho-1)-i]-48;
        }
    }
    while(num->digitos[num->tamanho-1]==0 && num->tamanho!=1){        //Tira os 0's quando eles estão depois do fim do numero
        if(num->digitos[num->tamanho-1]==0){
            num->tamanho -= 1;
        }
        num->digitos = realloc(num->digitos, num->tamanho*sizeof(int));     //Realoca com o tamanho novo
    }
    free(valor);        //Libera a memoria da string valor para garantir mais memoria
    return num;
}

char* pegar_numero(){       //Função para receber string do usuário
    char* temp = malloc(10000*sizeof(char));        //Aloca com um tamanho padrão
    if(scanf("%s", temp)==EOF){     //Termina o codigo quando não tem mais entrada da instancia
        exit(1);
    }          
    getchar();      
    temp = realloc(temp, strlen(temp)+1);       //Realoca a partir do tamanho realmente necessário
    return temp;
}

void Imprimir_bignumber(BigNumber numero, int tam){     //Função para imprimir o big number
    if(tam==0){         //Quando a variavel de tamanho chegar em 0 termina a recursão
        printf("\n");
        return;
    }       
    if(tam==numero->tamanho){     //Caso esteja no inicio da execução printa '-' se tiver       
        if(numero->sinal=='-'){
            printf("%c",'-');
        }
    }
    printf("%d", numero->digitos[tam-1]);   
    tam -= 1;
    Imprimir_bignumber(numero,tam);     //Chama a função novamente para ir printando de modo invertido
}

void Destruir_bignumber(BigNumber num){     //Função que libera os digitos e em seguida a estrutura
    free(num->digitos);
    free(num);
    return;
}

int main() {
    BigNumber numero1, numero2;
    int i=30;
    char sinalCalc;
    char* entrada;
    while(1){
        entrada = pegar_numero();
        numero1 = Construcao_bignumber(numero1, entrada);
        entrada = pegar_numero();
        numero2 = Construcao_bignumber(numero2, entrada);
        scanf("%c", &sinalCalc);
        if(sinalCalc=='+'){
            //Função soma
        }
        else if(sinalCalc=='-'){
            //Função subtração
        }
        Destruir_bignumber(numero1);
        Destruir_bignumber(numero2);
        i -= 1;
    }
    return 0;
}
