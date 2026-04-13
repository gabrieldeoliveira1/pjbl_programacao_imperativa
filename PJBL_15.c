/*
Objetivo
O presente trabalho tem como objetivo a utilização dos conceitos abordados na disciplina no decorrer do semestre, assim como conteúdos anteriormente vistos, visando a construção 
de uma aplicação parcial em Linguagem C com o intuito de criar uma aplicação de jogo que possibilite ao utilizador as funcionalidades descritas nos itens a seguir;
O tema/abrangência é de escolha da equipe, dentro das opções propostas, desde que contemple no mínimo os itens solicitados;
Conceitos Presentes:
Ponteiros;
Alocação dinâmica de memória;
Manipulação de dados em memória;
Recursividade;
Conceitos Anteriores:
Matrizes (arrays bidimensionais);
Estruturas de controle (condições e repetições);
Lógica de programação;
Regras de Desenvolvimento
A aplicação deve contar com os seguintes requisitos não funcionais:
A implementação de todo o projeto deve ser feita em linguagem C;
O aplicativo deverá conter seu menu principal para a seleção das funcionalidades;
Cada menu deve ser impresso a partir de uma subrotina independente;
Toda a comunicação entre as subrotinas e o programa principal deverá ser via parâmetro (por valor ou referência). Somente as estruturas (struct), os protótipos das subrotinas podem ser declaradas fora da função main ou de outra subrotina. Naturalmente as bibliotecas e constantes (com #define) sempre são declaradas no início do programa antes da função main;
Todas as estruturas devem ser coesamente alocadas, seja estática ou dinamicamente, assim como qualquer vetor ou matriz de tipagem normal;
Jogo dos Quinze
Descrição
O Jogo dos Quinze é um quebra-cabeça composto por um tabuleiro 4x4, contendo números de 1 a 15 e um espaço vazio;
Regras do Jogo
O jogador escolhe um número para mover;
A movimentação só é válida se o número estiver adjacente ao espaço vazio;
O número escolhido troca de posição com o espaço vazio;
O objetivo é organizar os números na ordem correta:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 [ ]
O jogo termina quando a sequência estiver correta;
Desafios Principais
Validar movimentos permitidos;
Implementar troca de posições corretamente;
Verificar condição de vitória;
Criar embaralhamento válido;
Verificação se o jogo é solucionável;
Questões de Implementação
Criar um tabuleiro 4x4 e preencher com números de 1 a 15 e um espaço vazio;
Embaralhar o tabuleiro inicial;
Permitir movimentação das peças (cima (W), baixo (S), esquerda (A), direita (D) ou informando linha e coluna);
Permitir troca com o espaço vazio;
Verificar condição de vitória (ordem correta);
Modo fácil: Criar um espaço vazio adicional fora do tabuleiro para movimentação de apoio;
Modo normal: Cria o tabuleiro normal, sem espaço adicional;
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int verificar_Inversoes(int *vetor, int indice)

{
    //caso base:
    if(indice >= 15)
    {
        return 0;
    } 

    int i, inversoes = 0;

    if(vetor[indice] != 0)
    {
        for(i = indice + 1; i < 16; i++)
        {
            if(vetor[i] != 0 && vetor[indice] > vetor[i])
            {
                inversoes++;
            }
        }
    }

    return inversoes + verificar_Inversoes(vetor, indice + 1);
}

//verifica atraves de recursividade se o jogo e solucionavel
int verificar_Resolucao(int *vetor_randomico)
{
    /*matematica por tras: -> como tem que funcionar a nossa recursividade
    Para verificar se o tabuleiro pode ser solucionado temos que contar o numero de inversoes que devem ser feitas 
    A inversao so acontece quando um numero maior aparece antes de um numero menor. Alem disso, precisamos saber a 
    posicao do espaco vazio contando de baixo para cima. Caso o esapaco vazio esteja em uma linha par, o numero de 
    inversoes deve ser impar para o jogo ser solucionavel. Caso o espaco vazio esteja em uma linha impar, o numero
    de inversoes deve ser par. Caso o numero de inversoes seja impar e o espaco vazio esteja em uma linha impar tambem,
    o jogo nao e solucionavel. 
    */

    int i, pos_vazio = 0, linha_vazio, total_inversoes;

    for(i = 0; i < 16; i++)
    {
        if(vetor_randomico[i] == 0)
        {
            pos_vazio = i;
            break;
        }
    }

    linha_vazio = 4 - (pos_vazio / 4); 
    total_inversoes = verificar_Inversoes(vetor_randomico, 0);
    if(linha_vazio % 2 == 0)
    {
        return (total_inversoes % 2 != 0); 
    } else {
        return (total_inversoes % 2 == 0);
    }

}

//funcao criar tabuleiro com alocacao dinamica
int** criar_Tabuleiro(int modo_jogo) //mexer na parte de criar um espaço adicional ainda -> Perguntar para o professor 
{
    int **tabuleiro;
    int i, j, temp, numero_aleatorio, contador = 0;
    int vetor_randomico[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //criar um vetor e embaralhar ele
    int solucionavel = 0; //variavel de controle para verificar se e possivel resolver o tabuleiro 

    srand(time(NULL)); //inicializa o gerador numeros aleatorios
    
    
    do {
    for(j = 15; j > 0; j--)
    {
        numero_aleatorio = rand() % (j + 1); //randomiza um numero de j ate 0

        temp = vetor_randomico[j]; //pega o valor do vetor na posicao j e guarda
        vetor_randomico[j] = vetor_randomico[numero_aleatorio]; //o valor atual do vetor vai para a posicao do numero aleatorio
        vetor_randomico[numero_aleatorio] = temp; //o valor de temp vai pra posicao do numero aleatorio
    }
    solucionavel = verificar_Resolucao(vetor_randomico); //verifica se o vetor randomico e solucionavel
    } while(!solucionavel); //repete ate que o vetor seja solucionavel

    if(modo_jogo == 1)
    {
        //modo facil
        tabuleiro = (int**)malloc(5 * sizeof(int*)); //cria os espacos de memoria para as linhas -> so pra nao se perder
        for(i = 0; i < 5; i++)
        {
            tabuleiro[i] = (int*)malloc(4 * sizeof(int)); //cria efetivamente os espacos das onde ficam os inteiros -> so pra nao se perder
        }
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                tabuleiro[i][j] = vetor_randomico[contador]; //preenche o tabuleiro com os numeros do vetor randomico
                contador++;
            }
        }

        tabuleiro[4][0] = 0; //espaço vazio adicional fora do tabuleiro

        //preenche o resto dos espacos vazios com -1 (Nao tem como criar matrizes que nao sao quadradas usando o malloc)
        tabuleiro[4][1] = -1;
        tabuleiro[4][2] = -1;
        tabuleiro[4][3] = -1;
    }
    else if(modo_jogo == 2)
    {
        //modo normal
        tabuleiro = (int**)malloc(4 * sizeof(int*)); //cria os espacos de memoria para as linhas -> so pra nao se perder
        for(i = 0; i < 4; i++)
        {
            tabuleiro[i] = (int*)malloc(4 * sizeof(int)); //cria efetivamente os espacos das onde ficam os inteiros -> so pra nao se perder
        }
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                tabuleiro[i][j] = vetor_randomico[contador]; //preenche o tabuleiro com os numeros do vetor randomico
                contador++;
            }
        }
    }

    return tabuleiro;
}

int verificar_Vitoria()
{

}

int verificar_Movimento()
{

}

//conta o numero de inversoes do tabuleiro


//funcao para imprimir o tabuleiro
void imprimir_Tabuleiro(int **tabuleiro, int modo_jogo)
{
    int i, j, total_linhas;

    if (modo_jogo == 1)
    {
        total_linhas = 5;
    } 
    else
    {
        total_linhas = 4;
    }

    printf("\n=== JOGO DOS QUINZE by Gabriel Oliveira e Luiza Beber ===\n\n"); 

    for(i = 0; i < total_linhas; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(tabuleiro[i][j] == -1)
            {
                printf("    "); //espaço vazio pra tirar os -1
            }
            else if(tabuleiro[i][j] == 0)
            {
                printf("[  ]"); 
            }
            else
            {
                printf("[%2d]", tabuleiro[i][j]); //imprime os numeros do tabuleiro
            }
        }

        printf("\n");
    }
    printf("\n");
}

int main()
{

    int modo; 
    int **tabuleiro_jogo;

    printf("Bem-vindo ao Jogo dos Quinze!\n");
    printf("Selecione o modo de jogo:\n");
    printf("1. Modo Facil\n");
    printf("2. Modo Normal\n");
    scanf("%d", &modo);

    while(modo != 1 && modo != 2)
        {
            printf("Opcao invalida. Por favor, selecione uma opcao valida (1 ou 2): ");
            scanf("%d", &modo);
        }

    if(modo == 1)
    {
        printf("Modo Facil selecionado!\n");
    }
    else if(modo == 2)
    {
        printf("Modo Normal selecionado!\n");
    }

    tabuleiro_jogo = criar_Tabuleiro(modo);
    imprimir_Tabuleiro(tabuleiro_jogo, modo);
}