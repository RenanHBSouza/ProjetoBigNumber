PROJETO BIG NUMBER PARA AULA DE PROGRAMAÇÃO ESTRUTURADA


Autores: - Fernanda Simone Silva            RA: 11202130276
         - Renan Henrique Barreiro Souza    RA: 11202130682
         - Renan Santana Ferreira           RA: 11202131332


REPRESENTAÇÃO BIGNUMBER: 
A representação de  um BigNumber utilizando um ponteiro de struct é uma abordagem eficiente para lidar com números inteiros de magnitude extraordinariamente alta. Nessa representação, utilizamos uma estrutura de dados que contém três elementos principais: o sinal do número, seu tamanho e um vetor de inteiros.
O sinal é um indicador que especifica se o número é positivo ou negativo. Já o tamanho representa o número total de dígitos no BigNumber. Esses dois elementos são armazenados diretamente na struct.
O vetor de inteiros é a parte crucial da representação. Ele é alocado dinamicamente na memória e contém os dígitos individuais do número inserido. Cada elemento representa um dígito do BigNumber, permitindo a flexibilidade necessária para lidar com números de tamanhos variáveis. Vale ressaltar que a alocação dinâmica de memória é empregada para criar um BigNumber, garantindo que os recursos necessários sejam alocados conforme a necessidade. Essa abordagem oferece vantagens na manipulação eficiente de números grandes, sem a restrição de um tamanho fixo.

INTERFACE PÚBLICA:

- BigNumber Construcao_bignumber(BigNumber num, char* valor)
- char* pegar_numero()
- void Imprimir_bignumber(BigNumber numero, int tam)
- void Soma_bignumber(BigNumber num1, BigNumber num2)
- void Subtracao_bignumber(BigNumber num1, BigNumber num2)
- void Destruir_bignumber(BigNumber num)
- void pot10(BigNumber num, int k)
- void Karatsuba_bignumber(BigNumber num1, BigNumber num2, BigNumber resp)

Essas funções são declaradas no arquivo de cabeçalho 'BigNumber.h' e são as partes do código que podem ser acessadas externamente.

MELHORA DE EXECUÇÃO:

Para otimizar o tempo de execução do código, empregamos o uso de ponteiros nas operações com a estrutura BigNumber. A abordagem consiste em passar apenas os endereços dos números envolvidos, evitando a criação de cópias desnecessárias. Além disso, realizamos modificações diretas em um dos números, eliminando a necessidade de criar uma nova instância de BigNumber. Essa prática foi aplicada em operações como soma e multiplicação, melhorando significativamente a eficiência do código ao evitar aplicações desnecessárias de memória e reduzir o tempo de execução.


DIVISÃO DE TRABALHO:
No desenvolvimento deste projeto, a divisão de trabalhos ficou definida da seguinte forma:

Fernanda:
Ficou encarregada de implementar as operações de soma e subtração, desempenhou um papel na fundamentação matemática do código. Além disso, contribuiu para ajustes na lógica da multiplicação. Foi responsável, também, pela elaboração do arquivo README e pelos comentários ao longo do código.

Renan H. B. Souza:
Responsável, também, pelas operações de soma e subtração, realizou os ajustes iniciais na estrutura do bignumber. Sua contribuição na fase inicial do projeto foi fundamental para estabelecer bases sólidas e garantir a consistência das operações fundamentais. Desenvolveu a função de multiplicação para todos os casos necessários.

Renan S. Ferreira:
Foi responsável pela tarefa de ajustar o bignumber para acomodar os valores máximos da máquina em sistema windows e linux. Além disso, ele desenvolveu o código inicial para a operação de multiplicação.





