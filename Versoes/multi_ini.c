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

char* pegar_numero(){       //Função para receber string do usuário
    char* temp = malloc(10000*sizeof(char));        //Aloca com um tamanho padrão
    if(temp == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    if(scanf("%s", temp)==EOF){     //Termina o codigo quando não tem mais entrada da instancia
        exit(1);
    }          
    getchar();      
    temp = realloc(temp, strlen(temp)+1);       //Realoca a partir do tamanho realmente necessário
    if(temp == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    return temp;
}

void Imprimir_bignumber(BigNumber numero, int tam){     //Função para imprimir o big number
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
                        if(num1->digitos == NULL){
                            printf("Nao ha memoria suficiente!\n");
                            exit(1);
                        }
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

void Soma_interna(BigNumber num1, BigNumber num2){
    int i,j,aux;
    if(num2->tamanho>num1->tamanho){        //Passos para completar de 0's o numero de menor tamanho
        num1->digitos = realloc(num1->digitos,num2->tamanho*sizeof(int));
        for(i=num1->tamanho;i<num2->tamanho;i++){
            num1->digitos[i]=0;
        }
        num1->tamanho = num2->tamanho;
    }
    else{
        num2->digitos = realloc(num2->digitos,num1->tamanho*sizeof(int));
        for(i=num2->tamanho;i<num1->tamanho;i++){
            num2->digitos[i]=0;
        }
        num2->tamanho = num1->tamanho;    
    }
    for(j=0;j<num2->tamanho;j++){        //Loop para percorrer o numero
        aux=num1->digitos[j]+num2->digitos[j]; // Soma os digitos correspondentes de num1 e num2 alem do valor acumulado do resto, se houver
           if(aux>=10){        //Se a soma for maior que 9, caso não seja o ultimo digitos dos vetores subtrai 10 do atual e soma 1 no proximo digito
               if(j!=num1->tamanho-1){
                   num1->digitos[j] = aux-10; //Atualiza o digito atual num1
                   num1->digitos[j+1] += 1;
                }
                else{       //Caso seja o ultimo digito dos vetores realoca mais 1 espaço para receber o novo valor
                   num1->tamanho+=1;
                   num1->digitos = realloc(num1->digitos, num1->tamanho*sizeof(int));
                   if(num1->digitos == NULL){
                        printf("Nao ha memoria suficiente!\n");
                        exit(1);
                    }
                    num1->digitos[j] = aux-10;
                    num1->digitos[j+1] = 1;
                }
            }
            else{       //Caso aux não passe de 10 adiciona no indice atual
                num1->digitos[j] = aux;
            }
    }          
}


void empresta(BigNumber num, int atual){        //Função para emprestar valor em contas de subtração
    int aux=atual, valor=9;     //Auxiliar recebe o valor inicial de atual que será alterado
    while(num->digitos[atual]==0 && atual!=num->tamanho-1){     //Vai somando em atual enquanto o digito é 0 ee o numero não terminou
        atual += 1;     
    }
    num->digitos[atual]-=1;     //Ao terminar, subtrai 1 de onde parou
    while(atual!=aux){      //Vai adicionando 9 no lugar dos 0's enquanto volta para a posição inicial que precisou emprestar
        atual-=1;
        num->digitos[atual]=9;
    }
    num->digitos[aux-1]+=10;        //Soma 10 no valor que solicitou emprestimo
    return;
}

void Subtracao_bignumber(BigNumber num1, BigNumber num2){
    int i, aux;
    if(num1->sinal=='+' && num2->sinal=='-'){       //Se num1>0 e num2<0, num1 - -num2 --> num1 + num2
        num2->sinal = '+';      //Altera o sinal de num2 e envia para soma
        Soma_bignumber(num1, num2);
    }
    else if(num1->sinal=='-' && num2->sinal=='+'){      //Se num1<0 e num2>0, -num1 - num2 --> -num1 + -num2 
        num2->sinal='-';        //Altera o sinal de num2 e envia para soma
        Soma_bignumber(num1,num2);
    }
    else if(num1->sinal=='-' && num2->sinal=='-'){      //Se num1<0 e num2<0, -num1 - -num2 --> -num1 + num2
        num2->sinal='+';                               //Altera o sinal de num2 e envia para soma
        Soma_bignumber(num1,num2);
    }
    else if(num1->sinal=='+' && num2->sinal=='+'){       //caso num1>0 e num2>0, faz o calculo de subtração comum
        if(num1->tamanho>num2->tamanho){        //Verifica se num1>num2 para utilizar num1 como vetor a ser alterado
            for(i=0;i<num2->tamanho;i++){       //Faz as subtrações digito a digito enquanto num2 tem caractere
                aux = num1->digitos[i]-num2->digitos[i];
                if(aux<0 && num1->digitos[i+1]!=0){     //Se o digito deu negativo e o proximo digito é diferente que 0 segue um emprestimo unico
                    num1->digitos[i+1]-=1;
                    num1->digitos[i]+=10;
                }
                else if(aux<0 && num1->digitos[i+1]==0){       //Caso o digito seja negativo e o proximo igual a 0, chama a função empresta
                    empresta(num1,i+1);
                }
                aux = num1->digitos[i]-num2->digitos[i];        
                num1->digitos[i] = aux;       //Após os adendos passa o valor de aux para o digito que esta sendo calculado
            }
            Imprimir_bignumber(num1,num1->tamanho);         //Chama a função de impressão
        }
        else if(num2->tamanho>num1->tamanho){       //Caso num2 seja maior faz a mesma logica, porém altera o sinal devido a esse resultado ser negativo
            for(i=0;i<num1->tamanho;i++){
                aux = num2->digitos[i]-num1->digitos[i];        //aux recebe a subtracao de num2 e num1
                if(aux<0 && num2->digitos[i+1]!=0){         //Verifica se ele eh menor que zero e o digito a direita eh diferente de 0
                    num2->digitos[i+1]-=1;              //Subtrai 1 do digito vizinho
                    num2->digitos[i]+=10;               //Soma 10 no digito atual
                }
                else if(aux<0 && num2->digitos[i+1]==0){        //Verifica se o aux eh negativo e o digito seguinte eh zero
                    empresta(num2,i+1);                     //Chamada da funcao empresta
                }
                aux = num2->digitos[i]-num1->digitos[i];        //aux eh recalculado
                num2->digitos[i] = aux;                     //num2 assume o valor do aux na posicao i
                num2->sinal='-';
            }
            Imprimir_bignumber(num2,num2->tamanho);
        }
        else{                  
            i = num1->tamanho-1;
            while(i>=0){
                if(num1->digitos[i]>num2->digitos[i]){
                    i = -1;
                    for(int j=0;j<num2->tamanho;j++){       //Faz as subtrações digito a digito enquanto num2 tem caractere
                        aux = num1->digitos[j]-num2->digitos[j];
                        if(aux<0 && num1->digitos[j+1]!=0){     //Se o digito deu negativo e o proximo digito é diferente que 0 segue um emprestimo unico
                            num1->digitos[j+1]-=1;
                            num1->digitos[j]+=10;
                        }
                        else if(aux<0 && num1->digitos[j+1]==0){       //Caso o digito seja negativo e o proximo igual a 0, chama a função empresta
                            empresta(num1,j+1);
                        }
                        aux = num1->digitos[j]-num2->digitos[j];        
                        num1->digitos[j] = aux;       //Após os adendos passa o valor de aux para o digito que esta sendo calculado
                    }
                Imprimir_bignumber(num1,num1->tamanho);         //Chama a função de impressão
                }
                else if(num2->digitos[i]>num1->digitos[i]){
                    i=-1;
                    for(int j=0;j<num1->tamanho;j++){
                        aux = num2->digitos[j]-num1->digitos[j];
                        if(aux<0 && num2->digitos[j+1]!=0){
                            num2->digitos[j+1]-=1;
                            num2->digitos[j]+=10;
                        }
                        else if(aux<0 && num2->digitos[j+1]==0){
                            empresta(num2,j+1);
                        }
                        aux = num2->digitos[j]-num1->digitos[j];
                        num1->digitos[j] = aux;
                        num1->sinal='-';
                    }
                    Imprimir_bignumber(num1,num1->tamanho);
                }
                else if(i==0){
                    i = -1;
                    num1->tamanho=1;
                    num1->digitos = realloc(num1->digitos, sizeof(int));
                    if(num1->digitos == NULL){
                        printf("Nao ha memoria suficiente!\n");
                        exit(1);
                    }
                    num1->digitos[0] = 0;
                    printf("%d\n",num1->digitos[0]);
                }
                else{
                    i-=1;
                }
            }
        }
    }
}


void Subtracao_interna(BigNumber num1, BigNumber num2){
    int i, aux;
    if(num2->tamanho>num1->tamanho){        //Passos para completar de 0's o numero de menor tamanho
        num1->digitos = realloc(num1->digitos,num2->tamanho*sizeof(int));
        for(i=num1->tamanho;i<num2->tamanho;i++){
            num1->digitos[i]=0;
        }
        num1->tamanho = num2->tamanho;
    }
    else{
        num2->digitos = realloc(num2->digitos,num1->tamanho*sizeof(int));
        for(i=num2->tamanho;i<num1->tamanho;i++){
            num2->digitos[i]=0;
        }
        num2->tamanho = num1->tamanho;    
    }

    i = num1->tamanho-1;        //variavel utilizada para percorrer os digitos de tras para frente

    while(i>=0){
        if(num1->digitos[i]>num2->digitos[i]){      //Procura qual dos dois numeros é maior
            i = -1;
            for(int j=0;j<num2->tamanho;j++){       //Faz as subtrações digito a digito enquanto num2 tem caractere
                aux = num1->digitos[j]-num2->digitos[j];
                if(aux<0 && num1->digitos[j+1]!=0){     //Se o digito deu negativo e o proximo digito é diferente que 0 segue um emprestimo unico
                    num1->digitos[j+1]-=1;
                    num1->digitos[j]+=10;
                }
                else if(aux<0 && num1->digitos[j+1]==0){       //Caso o digito seja negativo e o proximo igual a 0, chama a função empresta
                    empresta(num1,j+1);
                }
                aux = num1->digitos[j]-num2->digitos[j];        
                num1->digitos[j] = aux;       //Após os adendos passa o valor de aux para o digito que esta sendo calculado
            }
        }
        else if(num2->digitos[i]>num1->digitos[i]){      //Verifica se o segundo digito for maior que o primeiro
            i=-1;
            for(int j=0;j<num1->tamanho;j++){
                aux = num2->digitos[j]-num1->digitos[j];        //O aux realiza a subtracao
                if(aux<0 && num2->digitos[j+1]!=0){         //Verifica se o aux eh negativo e se nao estamos no primeiro digito do num2
                    num2->digitos[j+1]-=1;                  //Em caso positivo, subtrai 1 do algorismo seguinte e acrescenta 10 no atual
                    num2->digitos[j]+=10;
                }
                else if(aux<0 && num2->digitos[j+1]==0){        //Se aux der negativo e a posicao atual for a inicial, chama-se a funcao empresta
                    empresta(num2,j+1);
                }
                aux = num2->digitos[j]-num1->digitos[j];        //Recalcula o aux apos mudancas
                num1->digitos[j] = aux;                     //Com aux>0, ele é inserido no num1
                num1->sinal='-';                           //num1 assume sinal negativo
            }
        }
        if(i==0){
            i = -1;
            for(int j=0;j<num1->tamanho;j++){
            num1->digitos[j] = 0;       // //Se nenhum dos numeros for diferente, sera atribuido ao seu unico digito um zero
            }
        }
        else{
            i-=1;
        }
    }
}


void Destruir_bignumber(BigNumber num){     //Função que libera os digitos e em seguida a estrutura
    free(num->digitos);
    free(num);
    return;
}

void pot10(BigNumber num, int k){
    num->digitos = realloc(num->digitos, (num->tamanho+k)*sizeof(int));
    if(num->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    int i;
    for(i=num->tamanho-1;i>=0;i--){             //Loop para deslocar os elementos do vetor para a direita
        num->digitos[(i+k)] = num->digitos[i];
        num->digitos[i] = 0;                                        //Adiciona zero nos digitos iniciais que sobrarem
    }
    num->tamanho += k;  
    return;
}

void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp) {
    int cont;
    size_t m;

    if(num1->sinal!=num2->sinal){       //Verifica o sinal da resposta
        resp->sinal='-';
    }
    else{
        resp->sinal='+';
    } 

    if(max(num1->tamanho,num2->tamanho)==1){                      //Verifica se ambos os numeros estao com no max 1 digito
        if(resp->tamanho==1){
            resp->tamanho+=1;
            resp->digitos = realloc(resp->digitos,resp->tamanho*sizeof(int));
        }
        resp->digitos[0] = (num1->digitos[0]*num2->digitos[0])%10;      //Calcula a multiplicação deixando apenas o digito menos sig.
        resp->digitos[1] = (num1->digitos[0]*num2->digitos[0])/10;      //Coloca o digito mais sig. se o tiver
        return;
    }

    // Determina a metade do BigN e coloca 0 para deixar numeros pares de mesmo tamanho
    if (num1->tamanho > num2->tamanho){
        if(num1->tamanho%2!=0){              // Se o tamanho de num1 for ímpar, incrementa o tamanho e realoca a memória para num1 e num2
            num1->tamanho +=1;
            num1->digitos = realloc(num1->digitos, num1->tamanho*sizeof(int));
            if(num1->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            num1->digitos[num1->tamanho-1] = 0;
            num2->digitos = realloc(num2->digitos, num1->tamanho*sizeof(int));
            if(num2->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            for(int i=num2->tamanho;i<num1->tamanho;i++){       //Preenche os digitos adicionados com zero
                num2->digitos[i] = 0;
            }
        }
        else{           // Se o tamanho de num1 for par, apenas realoca a memória para num2 e preenche os dígitos adicionados com zero
            num2->digitos = realloc(num2->digitos, num1->tamanho*sizeof(int));
            if(num2->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            for(int i=num2->tamanho;i<num1->tamanho;i++){
                num2->digitos[i] = 0;
            }           
        }
        num2->tamanho = num1->tamanho;          //Iguala o tamanho de num2 ao tamanho de num1
        m = num1->tamanho/2;                //Assume m como sendo um inteiro que representa metade do tamanho ne num1
    }
    else{
        if(num2->tamanho%2!=0){         //Verifica se num2 é impar
            num2->tamanho +=1;                              //Acrescenta um ao tamanho original para que o tamanho seja par
            num2->digitos = realloc(num2->digitos, num2->tamanho*sizeof(int));
             if(num2->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            num2->digitos[num2->tamanho-1] = 0;     //Acrescenta o valor 0 na ultima posicao
            num1->digitos = realloc(num1->digitos, num2->tamanho*sizeof(int));
            if(num1->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            for(int i=num1->tamanho;i<num2->tamanho;i++){       
                num1->digitos[i] = 0;                           //Preenche od digitos adicionados com 0
            }
        }
        else{
            num1->digitos = realloc(num1->digitos, num2->tamanho*sizeof(int));
            if(num1->digitos == NULL){
                printf("Nao ha memoria suficiente!\n");
                exit(1);
            }
            for(int i=num1->tamanho;i<num2->tamanho;i++){
                num1->digitos[i] = 0;                       //Adiciona 0 nos digitos adicionado em num1
            }           
        }
        num1->tamanho = num2->tamanho;      //Iguala o tamanho de num1 e num2
        m = num2->tamanho/2;                    //Assume m como inteiro com valor de metade do tamanho de num2
    }
                                                 
    BigNumber a = malloc(sizeof(struct n)); //inicializa os BigNumber a       
    if(a == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    a->tamanho = m;                                 //a recebe o tamanho de metade do num1 inicial
    a->digitos = calloc(a->tamanho, sizeof(int));
    if(a->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){                       //Loop para a receber os valores da metade inicial de num1
        a->digitos[i] = num1->digitos[m+i];
    }
    a->sinal = num1->sinal;             //a recebe o sinal de num1

    BigNumber b = malloc(sizeof(struct n));      //Inicializa o BigNumber b
    if(b == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    b->tamanho = m;                                 //b recebe o tamanho de metade do num1 inicial  
    b->digitos = calloc(b->tamanho, sizeof(int));
    if(b->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){                    //Loop para b receber os valores da metade final de num1
        b->digitos[i] = num1->digitos[i];
    }
    b->sinal = num1->sinal;         //b recebe o sinal de num1

    BigNumber c = malloc(sizeof(struct n));         //Inicializa o BigNumber c
    if(c == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    c->tamanho = m;                                 //c recebe o tamanho de metade do num2 inicial
    c->digitos = calloc(c->tamanho, sizeof(int));
    if(c->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    for(int i=0;i<m;i++){                       //Loop para c receber os valores da metade inicial de num2
        c->digitos[i] = num2->digitos[m+i];
    }
    c->sinal = num2->sinal;     //c recebe o sinal de num2

    BigNumber d = malloc(sizeof(struct n));     //Inicializa o BigNumber d
    if(d == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    d->tamanho = m;                                 //d recebe o tamanho de metade do num2 inicial
    d->digitos = calloc(d->tamanho, sizeof(int));
    if(d->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }

    for(int i=0;i<m;i++){                   //Loop para d receber os valores da metade final de num2
        d->digitos[i] = num2->digitos[i];
    }
    d->sinal = num2->sinal;         //d recebe o sinal de num2
                                                                                        
    BigNumber ac = malloc(sizeof(struct n));    // Calcula o produto ac recursivamente usando algoritmo de Karatsuba
    if(ac == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    ac->tamanho = a->tamanho+c->tamanho;        //ac recebe o tamanho maximo da multiplicacao de a e c
    ac->sinal = '+';                            //ac recebe sinal positivo
    ac->digitos = calloc(ac->tamanho, sizeof(int));
    if(ac->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    Karatsuba_bignumber(a, c, ac);      //Chamada da funcao Karatsuba

    BigNumber bd = malloc(sizeof(struct n));     // Calcula o produto bd recursivamente usando algoritmo de Karatsuba
    if(bd == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    bd->tamanho = b->tamanho+d->tamanho;        //bd recebe o tamanho maximo da multiplicacao de b e d
    bd->sinal = '+';                            //bd rece sinal positivo
    bd->digitos = calloc(bd->tamanho, sizeof(int));
    if(bd == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    Karatsuba_bignumber(b, d, bd);      //Chamada da funcao Karatsuba

    Soma_interna(a, b);     //Calcula-se a+b

    Soma_interna(c, d);     //Calcula-se c+d

    BigNumber abcd = malloc(sizeof(struct n));      //Inicializa o BigNumber abcd
    if(abcd == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    abcd->tamanho = a->tamanho+c->tamanho;          //abcd recebe o tamanho maximo da multiplicacao de(a+b) e (c+d)
    abcd->sinal = '+';                              //abcd recebe sinal positivo
    abcd->digitos = calloc(abcd->tamanho,sizeof(int));
    if(abcd->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    Karatsuba_bignumber(a, c, abcd);      //Chamada da funcao Karatsuba que calcula (a + b) * (c + d)


    resp->tamanho = num1->tamanho+num2->tamanho;        //O BigNumber resp recebe o tamanho do num1
    resp->digitos = realloc(resp->digitos, resp->tamanho * sizeof(int));
    if(resp->digitos == NULL){
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }
    //Calculo de ac*10^(2*m)+(abcd-ac-bd)*10^m+bd
    Subtracao_interna(abcd,ac);         //Chamada funcao de subtracao entre abcd e ac
    Subtracao_interna(abcd,bd);           //Chamada da funcao de subtracao entre abcd e bd
    pot10(abcd,m);                          //Chamada da funcao potencia com 10 elevado a m para abcd
    pot10(ac,2*m);                      //Chamada da funcao potencia com 10 elevado a 2*m para ac
    Soma_interna(ac,abcd);         //Chamada da funcao soma para ac e abcd
    Soma_interna(ac,bd);            //Chamada da funcao soma para ac e bd

    memcpy(resp->digitos, ac->digitos, resp->tamanho * sizeof(int));        //Chamada funcao que copia os dados de ac em resp
    cont=0;
    for(int i=0;i<resp->tamanho;i++){       //for para percorrer o numero e verificar se ele é 0
        if(resp->digitos[i]==0){
            cont+=1;
        }
    }
    if(cont==resp->tamanho){    //Caso seja garante o sinal positivo
        resp->sinal='+';
    }

    Destruir_bignumber(a);          // Libera a memoria de a, b, c, d, ac, bd e abcd
    Destruir_bignumber(b);
    Destruir_bignumber(c);
    Destruir_bignumber(d);
    Destruir_bignumber(ac);
    Destruir_bignumber(bd);
    Destruir_bignumber(abcd);
}

int main() {
    BigNumber numero1, numero2, resp;
    char sinalCalc;
    char* entrada;
    char x[2] = {'0','\0'};;

    while(1){
        entrada = pegar_numero();
        numero1 = Construcao_bignumber(numero1, entrada);
        entrada = pegar_numero();
        numero2 = Construcao_bignumber(numero2, entrada);
        resp = Construcao_bignumber(resp, x);
        scanf("%c", &sinalCalc);
        if(sinalCalc=='+'){
            Soma_bignumber(numero1,numero2);
        }
        else if(sinalCalc=='-'){
            Subtracao_bignumber(numero1,numero2);
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