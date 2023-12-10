PROJETO BIG NUMBER PARA AULA DE PROGRAMACAO ESTRUTURADA

Autores: - Fernanda Simone Silva            RA: 11202130276
         - Renan Henrique Barreiro Souza    RA: 11202130682
         - Renan Santana Ferreira           RA: 11202131332

REPRESENTACAO BIGNUMBER: A representacao de  um BigNumber utilizando um ponteiro de struct eh uma abordagem eficiente para lidar com numeros inteiros de magnitude extraordinariamente alta. Nessa representacao, utilizamos uma estrutura de dados que contem tres elementos principais: o sinal do numero, seu tamanho e um vetor de inteiros.

O sinal eh um indicador que especifica se o numero eh positivo ou negativo. Ja o tamanho representa o numero total de digitos no BigNumber. Esses dois elementos sao armazenados diretamente na struct.

O vetor de inteiros eh a parte crucial da representacao. Ele eh alocado dinamicamente na memoria e contem os digitos individuais do numero inserido. Cada elemento, representa um digito do BigNumber, permitindo a flexibilidade necessaria para lidar com numeros de tamanhos variaveis. Vale ressaltar que a alocacao dinamica de memoria eh empregada para criar um BigNumber, garantindo que os recursos necessarios sejam alocados conforme a necessidade. Essa abordagem oferece vantagens na manipulacao eficiente de numeros grandes, sem a restricao de um tamanho fixo.


INTERFACE PUBLICA: 

- BigNumber Construcao_bignumber(BigNumber num, char* valor)
- char* pegar_numero()
- void Imprimir_bignumber(BigNumber numero, int tam)
- void Soma_bignumber(BigNumber num1, BigNumber num2)
- void Subtracao_bignumber(BigNumber num1, BigNumber num2)
- void Destruir_bignumber(BigNumber num)
- void pot10(BigNumber num, int k)
- void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp)

Essas funções são declaradas no arquivo de cabeçalho 'BigNumber.h' e sao as partes do codigo que podem ser acessadas externamente.

MELHORA DE EXECUCAO: 

Para otimizar o tempo de execucao do codigo, empregamos o uso de ponteiros nas operacoes com a estrutura BigNumber. A abordagem consiste em passar apenas os endereços dos numeros envolvidos, evitando a criacao de copias desnecessarias. Alem disso, realizamos modificacoes diretas em um dos números, eliminando a necessidade de criar uma nova instância de BigNumber. Essa prática foi aplicada em operações como soma e multiplicacao, melhorando significativamente a eficiência do codigo ao evitar alocacoes desnecessarias de memoria e reduzir o tempo de execucao.

DIVISAO DE TRABALHO:

No desenvolvimento deste projeto, a divisao de trabalhos ficou definida da seguinte forma:

Fernanda:
Ficou encarregada de implementar as operações de soma e subtracao, desempenhou um papel na fundamentação matematica do codigo. Alem disso, contribuiu para ajustes na logica da multiplicacao. Foi responsavel, tambem, pela elaboracao do arquivo README.

Renan H. B. Souza:
Responsavel, também, pelas operacoes de soma e subtracao, realizou os ajustes iniciais na estrutura do bignumber. Sua contribuicao na fase inicial do projeto foi fundamental para estabelecer bases solidas e garantir a consistencia das operacoes fundamentais.

Renan S. Ferreira:
Foi responsavel pela tarefa de ajustar o bignumber para acomodar os valores maximos da maquina. Além disso, ele desenvolveu o codigo inicial para a operacao de multiplicacao.




