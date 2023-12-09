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
    //free(valor);        //Libera a memoria da string valor para garantir mais memoria
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
    if(tam==numero->tamanho){     //Caso esteja no inicio da execução printa '-' se tiver       
        if(numero->sinal=='-'){
            printf("%c",'-');
        }
    }
    while(numero->digitos[numero->tamanho-1]==0 && numero->tamanho>1){      //Caso o primeiro digito do valor (final do vetor) tenha sido zerado, remove pois é digito inutil
        numero->tamanho-=1;
        tam-=1;
        numero->digitos = realloc(numero->digitos, numero->tamanho*sizeof(int));
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
    else if(num1->sinal=='-' && num2->sinal=='-'){
        num2->sinal='+';
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
                aux = num2->digitos[i]-num1->digitos[i];
                if(aux<0 && num2->digitos[i+1]!=0){
                    num2->digitos[i+1]-=1;
                    num2->digitos[i]+=10;
                }
                else if(aux<0 && num2->digitos[i+1]==0){
                    empresta(num2,i+1);
                }
                aux = num2->digitos[i]-num1->digitos[i];
                num2->digitos[i] = aux;
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
    }
    else if(num2->tamanho>num1->tamanho){       //Caso num2 seja maior faz a mesma logica, porém altera o sinal devido a esse resultado ser negativo
        for(i=0;i<num1->tamanho;i++){
            aux = num2->digitos[i]-num1->digitos[i];
            if(aux<0 && num2->digitos[i+1]!=0){
                num2->digitos[i+1]-=1;
                num2->digitos[i]+=10;
            }
            else if(aux<0 && num2->digitos[i+1]==0){
                empresta(num2,i+1);
            }
            aux = num2->digitos[i]-num1->digitos[i];
            num2->digitos[i] = aux;
            num2->sinal='-';
        }
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
            }
            else if(i==0){
                i = -1;
                num1->digitos[0] = 0;
            }
            else{
                i-=1;
            }
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
    int i;
    for(i=num->tamanho-1;i>=0;i--){
        num->digitos[(i+k)] = num->digitos[i];
        printf("indice: %d, num: %d\n",(i+k),num->digitos[i+k]);
        num->digitos[i] = 0;
        printf("indice: %d, num: %d\n",i,num->digitos[i]);
    }
    num->tamanho += k;
    return;
}

void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp) {
    size_t m;
    // Se um dos numeros for zero, o resultado é zero
   /*
    if (num1->tamanho == 1 && num1->digitos[0] == 0) {
        resp->tamanho = 1;
        resp->sinal = '+';
        resp->digitos = realloc(resp->digitos, sizeof(int));
        resp->digitos[0] = 0;
        return;
    }
    if (num2->tamanho == 1 && num2->digitos[0] == 0) {
        resp->tamanho = 1;
        resp->sinal = '+';
        resp->digitos = realloc(resp->digitos, sizeof(int));
        resp->digitos[0] = 0;
        return;
    }*/
    if(max(num1->tamanho,num2->tamanho)==1){
        resp->digitos[0] = (num1->digitos[0]*num2->digitos[0])%10;
        resp->digitos[1] = (num1->digitos[0]*num2->digitos[0])/10;
        return;
    }

    // Verifica sinal dos numeros
    //Imprimir_bignumber(num1,num1->tamanho);
    //Imprimir_bignumber(num2,num2->tamanho);
    resp->sinal = (num1->sinal == num2->sinal) ? '+' : '-';  

    // Determina a metade do BigN e coloca 0 para deixar numeros pares de mesmo tamanho
    if (num1->tamanho > num2->tamanho){
        if(num1->tamanho%2!=0){
            num1->tamanho +=1;
            num1->digitos = realloc(num1->digitos, num1->tamanho*sizeof(int));
            num1->digitos[num1->tamanho-1] = 0;
            num2->digitos = realloc(num2->digitos, num1->tamanho*sizeof(int));
            for(int i=num2->tamanho;i<num1->tamanho;i++){
                num2->digitos[i] = 0;
            }
        }                       // |2|  |2|0| i=1
        else{
            num2->digitos = realloc(num2->digitos, num1->tamanho*sizeof(int));
            for(int i=num2->tamanho;i<num1->tamanho;i++){
                num2->digitos[i] = 0;
            }           
        }
        num2->tamanho = num1->tamanho;
        m = num1->tamanho/2;
    }
    else{
        if(num2->tamanho%2!=0){
            num2->tamanho +=1;
            num2->digitos = realloc(num2->digitos, num2->tamanho*sizeof(int));
            num2->digitos[num2->tamanho-1] = 0;
            num1->digitos = realloc(num1->digitos, num2->tamanho*sizeof(int));
            for(int i=num1->tamanho;i<num2->tamanho;i++){
                num1->digitos[i] = 0;
            }
        }
        else{
            num1->digitos = realloc(num1->digitos, num2->tamanho*sizeof(int));
            for(int i=num1->tamanho;i<num2->tamanho;i++){
                num1->digitos[i] = 0;
            }           
        }
        num1->tamanho = num2->tamanho;
        m = num2->tamanho/2;
    }
    for(int i=0;i<num1->tamanho;i++){
        printf("%d ",num1->digitos[i]);
    }
    printf("\n");
    for(int i=0;i<num2->tamanho;i++){
        printf("%d ",num2->digitos[i]);
    }
    printf("\n");
    // Quebra os BigN em duas partes cada
    BigNumber a = malloc(sizeof(struct n));
    a->tamanho = m;
    a->digitos = calloc(a->tamanho, sizeof(int));
    for(int i=0;i<m;i++){
        a->digitos[i] = num1->digitos[m+i];
    }
    a->sinal = num1->sinal;

    BigNumber b = malloc(sizeof(struct n));
    b->tamanho = m;
    b->digitos = calloc(b->tamanho, sizeof(int));
    for(int i=0;i<m;i++){
        b->digitos[i] = num1->digitos[i];
    }
    b->sinal = num1->sinal;

    BigNumber c = malloc(sizeof(struct n));
    c->tamanho = m;
    c->digitos = calloc(c->tamanho, sizeof(int));
    for(int i=0;i<m;i++){
        c->digitos[i] = num2->digitos[m+i];
    }
    c->sinal = num2->sinal;

    BigNumber d = malloc(sizeof(struct n));
    d->tamanho = m;
    d->digitos = calloc(d->tamanho, sizeof(int));
    for(int i=0;i<m;i++){
        d->digitos[i] = num2->digitos[i];
    }
    d->sinal = num2->sinal;

    // Calcula os produtos recursivamente
    BigNumber ac = malloc(sizeof(struct n));
    ac->tamanho = a->tamanho+c->tamanho;
    ac->sinal = '+';
    ac->digitos = calloc(ac->tamanho, sizeof(int));
    Karatsuba_bignumber(a, c, ac);

    BigNumber bd = malloc(sizeof(struct n));
    bd->tamanho = b->tamanho+d->tamanho;
    bd->sinal = '+';
    bd->digitos = calloc(bd->tamanho, sizeof(int));
    Karatsuba_bignumber(b, d, bd);

    // Calcula a + b e c + d
    Soma_interna(a, b);

    Soma_interna(c, d);

    // Calcula (a + b) * (c + d)
    BigNumber abcd = malloc(sizeof(struct n));
    abcd->tamanho = a->tamanho+c->tamanho;
    abcd->sinal = '+';
    abcd->digitos = calloc(abcd->tamanho,sizeof(int));
    Karatsuba_bignumber(a, c, abcd);


    // Calcula ac + bd - (a + b) * (c + d)
    //Subtracao_bignumber(ac, bd);
    //Subtracao_bignumber(ac, abcd);
    //Soma_bignumber(ac, bd);

    // Salva os resultados para o objeto 'resp'
    resp->tamanho = num1->tamanho+num2->tamanho;
    resp->digitos = realloc(resp->digitos, resp->tamanho * sizeof(int));
    for(int i=0;i<abcd->tamanho;i++){
        printf("%d ",abcd->digitos[i]);
    }
    printf("\n");
    for(int i=0;i<ac->tamanho;i++){
        printf("%d ",ac->digitos[i]);
    }
    printf("\n");
    Subtracao_interna(abcd,ac);
    for(int i=0;i<abcd->tamanho;i++){
        printf("%d ",abcd->digitos[i]);
    }
    printf("\n");
    Subtracao_interna(abcd,bd);
    for(int i=0;i<abcd->tamanho;i++){
        printf("%d ",abcd->digitos[i]);
    }
    printf("\n");
    pot10(abcd,m);
    for(int i=0;i<abcd->tamanho;i++){
        printf("%d ",abcd->digitos[i]);
    }
    printf("\n");
    pot10(ac,2*m);
    for(int i=0;i<ac->tamanho;i++){
        printf("%d ",ac->digitos[i]);
    }
    printf("\n");
    Soma_interna(ac,abcd);
    for(int i=0;i<ac->tamanho;i++){
        printf("%d ",ac->digitos[i]);
    }
    printf("\n");
    Soma_interna(ac,bd);
    for(int i=0;i<ac->tamanho;i++){
        printf("%d ",ac->digitos[i]);
    }
    printf("\n");

    // Copia o resultado para o num1
    //num1->tamanho = resp->tamanho;
    //num1->sinal = resp->sinal;
    //num1->digitos = realloc(num1->digitos, num1->tamanho * sizeof(int));
    memcpy(resp->digitos, ac->digitos, resp->tamanho * sizeof(int));
    Imprimir_bignumber(resp, resp->tamanho);

    // Libera a memoria
    Destruir_bignumber(a);
    Destruir_bignumber(b);
    Destruir_bignumber(c);
    Destruir_bignumber(d);
    Destruir_bignumber(ac);
    Destruir_bignumber(bd);
    Destruir_bignumber(abcd);
}

int main() {
    BigNumber numero1, numero2, resp;
    int i=30;
    char sinalCalc;
    char* entrada;
    char x[1] = {'0'};
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
        }
        else{
            printf("Valor inválido!");
        }
        Destruir_bignumber(numero1);
        Destruir_bignumber(numero2);
        i -= 1;
    }
    return 0;
}
