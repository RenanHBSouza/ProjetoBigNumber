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

void passa_1(BigNumber num, int atual){
    if(num->digitos[atual] <10 || atual == num->tamanho-1){
        return;
    }
    num->digitos[atual] -=10;
    num->digitos[atual+1] += 1;
    passa_1(num,atual+1);
}

void Subtracao_bignumber(BigNumber num1, BigNumber num2);

void Soma_bignumber(BigNumber num1, BigNumber num2){
    int i,j,aux;
    if(num1->sinal==num2->sinal){       //Verifica se os sinais são iguais, pois nesse caso faz a soma normalmente
        if(num1->tamanho>num2->tamanho){       //Verifica qual numero tem maior tamanho, pois é ele quem é alterado
            for(i=0;i<num2->tamanho;i++){       //Enquanto ainda tiver digitos no numero menor vai somando os valores em aux
                aux=num1->digitos[i]+num2->digitos[i];
                if(aux>=10){        //Caso a soma ultprasse 9, subtrai 10 de aux e soma 1 no proximo valor
                    num1->digitos[i] = aux-10;
                    num1->digitos[i+1] += 1;
                }
                else{
                    num1->digitos[i] = aux;         //Passa aux para o digito atual
                }
            }
            if(num1->digitos[num2->tamanho]>=10 && num2->tamanho!= num1->tamanho-1){
                passa_1(num1,num2->tamanho);
            }
            Imprimir_bignumber(num1, num1->tamanho);        //Chama a função de impressão
        } 
        else if(num2->tamanho>num1->tamanho){     //Mesma logica para casa o outro numero seja maior
            for(j=0;j<num1->tamanho;j++){           
                aux=num2->digitos[j]+num1->digitos[j];
                if(aux>=10){
                    num2->digitos[j] = aux-10;
                    num2->digitos[j+1] += 1;
                }
                else{
                    num2->digitos[j] = aux;
                }
            }
            if(num2->digitos[num1->tamanho]>=10 && num1->tamanho!= num2->tamanho-1){
                passa_1(num2,num1->tamanho);
            }
            Imprimir_bignumber(num2, num2->tamanho);
        }
        else{       //Caso os tamanhos sejam iguais
            for(j=0;j<num2->tamanho;j++){           
                aux=num1->digitos[j]+num2->digitos[j];
                if(aux>=10){        //Se a soma for maior que 9, caso não seja o ultimo digitos dos vetores subtrai 10 do atual e soma 1 no proximo digito
                    if(j!=num2->tamanho-1){
                        num1->digitos[j] = aux-10;
                        num1->digitos[j+1] += 1;
                    }
                    else{       //Caso seja o ultimo digito dos vetores realoca mais 1 espaço para receber o novo valor
                        num1->tamanho+=1;
                        num1->digitos = realloc(num1->digitos, num1->tamanho*sizeof(int));
                        num1->digitos[j] = aux-10;
                        num1->digitos[j+1] = 1;
                    }
                }
                else{
                    num1->digitos[j] = aux;
                }
            }
            Imprimir_bignumber(num1, num1->tamanho);
            
        }
    }
    else if(num1->sinal=='+' && num2->sinal=='-'){      //se num1>0 e num2<0, num1 + -num2 --> num1 - num2
        num2->sinal = '+';      //Altera o sinal de num2 para enviar para a função de subtração
        Subtracao_bignumber(num1,num2);
    }
    else if(num1->sinal=='-' && num2->sinal=='+'){
        num1->sinal='+';
        Subtracao_bignumber(num2,num1);
    }
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
            Soma_bignumber(numero1,numero2);
        }
        else if(sinalCalc=='-'){
            Subtracao_bignumber(numero1,numero2);
        }
        Destruir_bignumber(numero1);
        Destruir_bignumber(numero2);
        i -= 1;
    }
    return 0;
}
