#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//verifica atraves de recursividade o numero de inversoes
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

//verifica se o tabuleiro e solucionavel
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

//verifica se o tabuleiro esta em ordem (resolvido)
int verificar_Vitoria(int **tabuleiro)
{

    int contador = 1;
    int i, j;

    for(i = 0; i < 4; i++) //apenas a matriz principal 4x4
    {
        for(j = 0; j < 4; j++)
        {
            if(i == 3 && j == 3) //testar a ultima casa pra ver se eh 0 mesmo
            {
                if(tabuleiro[i][j] != 0)
                {
                    return 0;
                }
            } else 
            {
                if(tabuleiro[i][j] != contador)
                {
                    return 0;
                }
                contador++;
            }
        }
    }
    return 1;
}

//funcao que permite a movimentacao das casas dentro do tabuleiro
void verificar_Movimento(int **tabuleiro, int modo_jogo, int *pontuacao_movimentos, int *desistiu)
{

    //linha_zero e coluna_zero sao variaveis pra achar a posicao vazia dentro da matriz
    int coluna_zero;
    int linha_zero;
    int qntd_linhas;
    int i, j;
    int jogada_valida = 0; //variavel de controle pra garantir que o usuario digite w, a, s, d ou c
    char movimento;
    int linha_movimento = 0;
    int coluna_movimento = 0;

    if(modo_jogo == 1)
    {
        qntd_linhas = 5;
    } else 
    {
        qntd_linhas = 4;
    }

    //loop pra achar o zero (espaco vazio) dentro do tabuleiro
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(tabuleiro[i][j] == 0)
            {
                linha_zero = i;
                coluna_zero = j;
            }
        }
    }

    printf("OPCOES DE MOVIMENTACAO: ");
    printf("\n[W] -> Movimenta a casa para cima.");
    printf("\n[S] -> Movimenta a casa para baixo.");
    printf("\n[A] -> Movimenta a casa para esquerda.");
    printf("\n[D] -> Movimenta a casa para direita.");
    printf("\n[C] -> Para informar a linha e a coluna.");
    printf("\n[E] -> Desistir do jogo");
    printf("\nPara inserir numeros no espaco livre extra no modo facil, utilize o comando [C]");



    while(jogada_valida == 0)
    {
        printf("\nInsira o movimento: ");
        scanf(" %c", &movimento);

        switch(movimento)
        {
            case 'e':
            case 'E':
                *desistiu = 1;
                jogada_valida = 1;
                break;

            case'w':
            case'W': 
                if(linha_zero < 3) //o zero so nao pode descer caso esteja na ultima linha do tab
                {
                    tabuleiro[linha_zero][coluna_zero] = tabuleiro[linha_zero + 1][coluna_zero];
                    tabuleiro[linha_zero + 1][coluna_zero] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else {
                    printf("Nao eh possivel movimentar a peca atual para cima");
                }
                break;

            case 's':
            case 'S':
                if(linha_zero > 0) //o zero so nao pode subir caso esteja na primeira linha do tab
                {
                    tabuleiro[linha_zero][coluna_zero] = tabuleiro[linha_zero - 1][coluna_zero];
                    tabuleiro[linha_zero - 1][coluna_zero] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else {
                    printf("Nao eh possivel movimentar a peca atual para baixo");
                }
                break;
            
            case 'a':
            case 'A':
                if(coluna_zero < 3)
                {
                    tabuleiro[linha_zero][coluna_zero] = tabuleiro[linha_zero][coluna_zero + 1];
                    tabuleiro[linha_zero][coluna_zero + 1] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else {
                    printf("Nao eh possivel movimentar a peca atual para esquerda");
                }
                break;

            case 'd':
            case 'D':
                if(coluna_zero > 0)
                {
                    tabuleiro[linha_zero][coluna_zero] = tabuleiro[linha_zero][coluna_zero - 1];
                    tabuleiro[linha_zero][coluna_zero - 1] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else {
                    printf("Nao eh possivel movimentar a peca atual para direita");
                }
                break;
            
            case 'c':
            case 'C': 
                printf("Digite a linha do numero a mover (1 A %d): ", qntd_linhas);
                scanf("%d", &linha_movimento);
                printf("Digite a coluna do numero a mover (1 a 4): ");
                scanf("%d", &coluna_movimento);

                linha_movimento--;
                coluna_movimento--;

                if(linha_movimento < 0 || coluna_movimento < 0 || linha_movimento >= qntd_linhas || coluna_movimento > 3)
                {
                    printf("\nCoordenada Invalida!");
                } else if (linha_movimento > 0 && tabuleiro[linha_movimento - 1][coluna_movimento] == 0)
                {
                    tabuleiro[linha_movimento - 1][coluna_movimento] = tabuleiro[linha_movimento][coluna_movimento];
                    tabuleiro[linha_movimento][coluna_movimento] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else if(linha_movimento < qntd_linhas - 1 && tabuleiro[linha_movimento + 1][coluna_movimento] == 0) {
                    tabuleiro[linha_movimento + 1][coluna_movimento] = tabuleiro[linha_movimento][coluna_movimento];
                    tabuleiro[linha_movimento][coluna_movimento] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else if(coluna_movimento > 0 && tabuleiro[linha_movimento][coluna_movimento - 1] == 0){
                    tabuleiro[linha_movimento][coluna_movimento - 1] = tabuleiro[linha_movimento][coluna_movimento];
                    tabuleiro[linha_movimento][coluna_movimento] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else if(coluna_movimento < 3 && tabuleiro[linha_movimento][coluna_movimento + 1] == 0)
                {
                    tabuleiro[linha_movimento][coluna_movimento + 1] = tabuleiro[linha_movimento][coluna_movimento];
                    tabuleiro[linha_movimento][coluna_movimento] = 0;
                    jogada_valida = 1;
                    (*pontuacao_movimentos)++;
                } else {
                    printf("\nNao eh possivel movimentar a peca para esta localizacao.");
                }
                break;
            
            default:
                printf("Opcao Invalida! Insira [W], [A], [S], [D] ou [C]");
        }
    }

}

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

int exibir_Menu()
{
    int opcao;
    
    printf("\n--------------------------------------------\n");
    printf("   JOGO DOS QUINZE - by Gabriel e Luiza");
    printf("\n--------------------------------------------\n");
    printf("[1] Iniciar Partida - Modo Facil (Com 1 espaco extra)\n");
    printf("[2] Iniciar Partida - Modo Normal (Classico 4x4)\n");
    printf("[3] Sair do Jogo\n");
    printf("-----------------------------------------------\n");
    printf("Escolha uma opcao: ");
    
    scanf("%d", &opcao);
    
   
    while (opcao != 1 && opcao != 2 && opcao != 3) {
        printf("[!] Opcao invalida. Tente novamente: ");
        scanf("%d", &opcao);
    }
    
    return opcao;
}

int main()
{

    int opcao_menu = 0; 
    int **tabuleiro_jogo;
    int venceu;
    int placar_movimentos;
    int i, total_linhas;
    

    while (opcao_menu != 3) {
        system("cls");
        
        opcao_menu = exibir_Menu();

        if (opcao_menu == 1 || opcao_menu == 2) {
            venceu = 0;
            placar_movimentos = 0; 
            int desistiu = 0;
            tabuleiro_jogo = criar_Tabuleiro(opcao_menu);
    
        while(venceu == 0 && desistiu == 0)
        {
            system("cls"); //comando pra limpar o terminal
            printf("\n--- PLACAR: %d Movimentos ---\n", placar_movimentos);
            imprimir_Tabuleiro(tabuleiro_jogo, opcao_menu);
            verificar_Movimento(tabuleiro_jogo, opcao_menu, &placar_movimentos, &desistiu);

            if (desistiu == 1) {
                    break; 
            }
            
            venceu = verificar_Vitoria(tabuleiro_jogo);
        }

        system("cls");
            imprimir_Tabuleiro(tabuleiro_jogo, opcao_menu);

            if(venceu == 1){
                printf("----- PARABENS! VOCE RESOLVEU O TABULEIRO EM %d MOVIMENTOS! -----", placar_movimentos);
            } else {
                printf("\n----- VOCE DESISTIU DA PARTIDA :( -----\n");
            }
            printf("\nPressione [ENTER] para voltar ao Menu Principal...");
            getchar(); //limpa o buffer
            getchar(); //espera o enter pra voltar


            //free na matriz
            if (opcao_menu == 1) {
                total_linhas = 5;
            } else {
                total_linhas = 4;
            }
            
            for(i = 0; i < total_linhas; i++) {
                free(tabuleiro_jogo[i]);
            }
            free(tabuleiro_jogo);
        }
    }
}