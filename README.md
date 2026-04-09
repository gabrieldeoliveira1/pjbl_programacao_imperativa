# PJBL_PROGRAMACAO_IMPERATIVA
Repositório para entrega da atividade avaliativa de programação imperativa -> Jogo do 15 em C. 

### **Objetivo**

- O presente trabalho tem como objetivo a utilização dos conceitos abordados na disciplina no decorrer do semestre, assim como conteúdos anteriormente vistos, visando a construção de uma aplicação parcial em Linguagem C com o intuito de criar uma aplicação de jogo que possibilite ao utilizador as funcionalidades descritas nos itens a seguir;
- O tema/abrangência é de escolha da equipe, dentro das opções propostas, desde que contemple *no mínimo* os itens solicitados;
    - Conceitos Presentes:
        - Ponteiros;
        - Alocação dinâmica de memória;
        - Manipulação de dados em memória;
        - Recursividade;
    - Conceitos Anteriores:
        - Matrizes (arrays bidimensionais);
        - Estruturas de controle (condições e repetições);
        - Lógica de programação;

### **Regras de Desenvolvimento**

- A aplicação deve contar com os seguintes requisitos não funcionais:
    - A implementação de todo o projeto deve ser feita em linguagem C;
    - O aplicativo deverá conter seu menu principal para a seleção das funcionalidades;
    - Cada menu deve ser impresso a partir de uma subrotina independente;
    - Toda a comunicação entre as subrotinas e o programa principal deverá ser via parâmetro (por valor ou referência). Somente as estruturas (struct), os protótipos das subrotinas podem ser declaradas fora da função `main` ou de outra subrotina. Naturalmente as bibliotecas e constantes (com `#define`) sempre são declaradas no início do programa antes da função `main`;
    - Todas as estruturas devem ser coesamente alocadas, seja estática ou dinamicamente, assim como qualquer vetor ou matriz de tipagem normal;

### **Jogo dos Quinze**

#### Descrição

- O Jogo dos Quinze é um quebra-cabeça composto por um tabuleiro 4x4, contendo números de 1 a 15 e um espaço vazio;

#### Regras do Jogo

- O jogador escolhe um número para mover;
- A movimentação só é válida se o número estiver adjacente ao espaço vazio;
- O número escolhido troca de posição com o espaço vazio;
- O objetivo é organizar os números na ordem correta:
    - 1  2  3  4
    5  6  7  8
    9 10 11 12
    13 14 15 [ ]
- O jogo termina quando a sequência estiver correta;

#### Desafios Principais

- Validar movimentos permitidos;
- Implementar troca de posições corretamente;
- Verificar condição de vitória;
- Criar embaralhamento válido;
- Verificação se o jogo é solucionável;

#### Questões de Implementação

- Criar um tabuleiro 4x4 e preencher com números de 1 a 15 e um espaço vazio;
- Embaralhar o tabuleiro inicial;
- Permitir movimentação das peças (cima (W), baixo (S), esquerda (A), direita (D) ou informando linha e coluna);
- Permitir troca com o espaço vazio;
- Verificar condição de vitória (ordem correta);
- Modo fácil: Criar um espaço vazio adicional fora do tabuleiro para movimentação de apoio;
- Modo normal: Cria o tabuleiro normal, sem espaço adicional;
