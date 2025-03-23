#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINHAS 10
#define MAX_COLUNAS 10

int lerInteiroPositivo() {
    int valor;
    while (1) {
        if (scanf("%d", &valor) != 1 || valor <= 0) {
            printf("Erro: valor invalido. Digite um numero inteiro positivo: ");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return valor;
}

void alocarMatriz(int ***matriz, int linhas, int colunas) {
    *matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        (*matriz)[i] = (int *)malloc(colunas * sizeof(int));
    }
}

void liberarMatriz(int ***matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free((*matriz)[i]);
    }
    free(*matriz);
}

void lerMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Digite o valor da posicao [%d][%d]: ", i, j);
            while (scanf("%d", &matriz[i][j]) != 1) {
                printf("Entrada invalida! Digite um numero inteiro para a posicao [%d][%d]: ", i, j);
                while (getchar() != '\n');
            }
        }
    }
}

void imprimirMatriz(int **matriz, int linhas, int colunas) {
    printf("\nMatriz:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void somarMatrizes(int **matriz1, int **matriz2, int **resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
}

void subtrairMatrizes(int **matriz1, int **matriz2, int **resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = matriz1[i][j] - matriz2[i][j];
        }
    }
}

void gerarIdentidade(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (i == j) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

void transpostaMatriz(int **matriz, int **resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[j][i] = matriz[i][j];
        }
    }
}

void multiplicarMatrizes(int **matriz1, int **matriz2, int **resultado, int linhas1, int colunas1, int linhas2, int colunas2) {
    if (colunas1 != linhas2) {
        printf("Erro: as matrizes nao podem ser multiplicadas (dimensoes incompativeis).\n");
        return;
    }

    for (int i = 0; i < linhas1; i++) {
        for (int j = 0; j < colunas2; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < colunas1; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}

int main() {
    int **matriz1, **matriz2, **resultado;
    int linhas1, colunas1, linhas2, colunas2;
    int opcao;

    do {
        printf("\nDigite o numero de linhas e colunas para a primeira matriz (max %dx%d): ", MAX_LINHAS, MAX_COLUNAS);
        linhas1 = lerInteiroPositivo();
        colunas1 = lerInteiroPositivo();
        if (linhas1 > MAX_LINHAS || colunas1 > MAX_COLUNAS) {
            printf("Erro: o tamanho da matriz e muito grande. Tente novamente.\n");
            continue;
        }
        alocarMatriz(&matriz1, linhas1, colunas1);
        lerMatriz(matriz1, linhas1, colunas1);

        printf("\nDigite o numero de linhas e colunas para a segunda matriz (max %dx%d): ", MAX_LINHAS, MAX_COLUNAS);
        linhas2 = lerInteiroPositivo();
        colunas2 = lerInteiroPositivo();
        if (linhas2 > MAX_LINHAS || colunas2 > MAX_COLUNAS) {
            printf("Erro: o tamanho da matriz e muito grande. Tente novamente.\n");
            continue;
        }
        alocarMatriz(&matriz2, linhas2, colunas2);
        lerMatriz(matriz2, linhas2, colunas2);

        alocarMatriz(&resultado, linhas1, colunas2);

        printf("\n=== Escolha a operacao desejada ===\n\n");
        printf("1. Soma de Matrizes\n");
        printf("2. Subtracao de Matrizes\n");
        printf("3. Gerar Matriz Identidade\n");
        printf("4. Transposta de Matrizes\n");
        printf("5. Multiplicacao de Matrizes\n");
        printf("6. Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (linhas1 == linhas2 && colunas1 == colunas2) {
                    printf("\n======= Matriz 1 ========\n");
                    imprimirMatriz(matriz1, linhas1, colunas1);
                    printf("\n======= Matriz 2 ========\n");
                    imprimirMatriz(matriz2, linhas2, colunas2);
                    somarMatrizes(matriz1, matriz2, resultado, linhas1, colunas1);
                    printf("\n=== Resultado da Soma ===\n");
                    imprimirMatriz(resultado, linhas1, colunas1);
                } else {
                    printf("Erro: as matrizes devem ter as mesmas dimensoes para soma.\n");
                }
                break;

            case 2:
                if (linhas1 == linhas2 && colunas1 == colunas2) {
                    printf("\n========== Matriz 1 ==========\n");
                    imprimirMatriz(matriz1, linhas1, colunas1);
                    printf("\n========== Matriz 2 ==========\n");
                    imprimirMatriz(matriz2, linhas2, colunas2);
                    subtrairMatrizes(matriz1, matriz2, resultado, linhas1, colunas1);
                    printf("\n=== Resultado da Subtracao ===\n");
                    imprimirMatriz(resultado, linhas1, colunas1);
                } else {
                    printf("Erro: as matrizes devem ter as mesmas dimensoes para subtracao.\n");
                }
                break;

            case 3:
                if (linhas1 == colunas1) {
                    gerarIdentidade(matriz1, linhas1, colunas1);
                    printf("\n====== Matriz Identidade ======\n");
                    imprimirMatriz(matriz1, linhas1, colunas1);
                } else {
                    printf("Erro: para gerar uma matriz identidade, a matriz deve ser quadrada.\n");
                }
                break;

            case 4:
                printf("\n ========== Matriz 1 ==========\n");
                imprimirMatriz(matriz1, linhas1, colunas1);
                transpostaMatriz(matriz1, resultado, linhas1, colunas1);
                printf("\n====== Matriz Transposta ======\n");
                imprimirMatriz(resultado, colunas1, linhas1);
                break;

            case 5:
                printf("\n============ Matriz 1 ============\n");
                imprimirMatriz(matriz1, linhas1, colunas1);
                printf("\n============ Matriz 2 ============\n");
                imprimirMatriz(matriz2, linhas2, colunas2);
                multiplicarMatrizes(matriz1, matriz2, resultado, linhas1, colunas1, linhas2, colunas2);
                printf("\n=== Resultado da Multiplicacao ===\n");
                imprimirMatriz(resultado, linhas1, colunas2);
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        liberarMatriz(&matriz1, linhas1);
        liberarMatriz(&matriz2, linhas2);
        liberarMatriz(&resultado, linhas1);

    } while (opcao != 6);

    return 0;
}
