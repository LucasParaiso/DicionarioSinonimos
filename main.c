#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "avl.h"

#define MAX_LEN 31
#define ARQUIVO "dicionario.txt"

int main() {
    setlocale(LC_ALL, "Portuguese");
    FILE * arq;
    avl_tree p = NULL;
    avl_tree s = NULL;
    char linha[MAX_LEN], escolhaPalavra[21], escolhaSinonimo[21];
    char *palavra, *sinonimo;
    bool h;
    int menu = -1;

    //Criando a arvore AVL com os dados do arquivo "dicionario.txt"
    if ((arq = fopen(ARQUIVO, "r")) == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", ARQUIVO);
        return 1;
    }
    
    while (fgets(linha, MAX_LEN, arq) != NULL) { 
        palavra = strtok(linha, " \n");
        sinonimo = strtok(NULL, " \n"); 
        
        if (strlen(palavra) > 1 && strlen(sinonimo) > 1) { 
            avl_search(&p, palavra, sinonimo, &h); 
        }
    } 
    fclose(arq);

    while (menu != 0) {
        printf("\nDicionario de Sinônimos\n");
        printf("[1] - Inserir uma palavra e seu sinônimo\n");
        printf("[2] - Procurar um sinônimo\n");
        printf("[3] - Substituir um sinônimo\n");
        printf("[4] - Excluir uma palavra e seu sinônimo\n");
        printf("[5] - Mostrar na tela a arvore AVL\n");
        printf("[0] - Encerrar o programa\n");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                printf("\nInsira a palavra: ");
                scanf(" %20[^\n]", escolhaPalavra);

                printf("\nInsira o sinônimo: ");
                scanf(" %20[^\n]", escolhaSinonimo);

                s = procuraSinonimo(p, escolhaPalavra);
                if (s != NULL) {
                    strcpy(s->dado.sinonimo, escolhaSinonimo);
                    printf("\nAtualização efetuada!\n");
                } else {
                    avl_search(&p, escolhaPalavra, escolhaSinonimo, &h);
                    printf("\nInserção efetuada!\n");
                }

                break;

            case 2:
                printf("\nInsira a palavra: ");
                scanf(" %20[^\n]", escolhaPalavra);

                s = procuraSinonimo(p, escolhaPalavra);
                if (s != NULL) {
                    printf("O sinônimo de %s é: %s\n", s->dado.chave, s->dado.sinonimo);
                } else {
                    printf("A palavra não está no dicionário\n");
                }

                break;

            case 3:
                printf("\nInsira a palavra: ");
                scanf(" %20[^\n]", escolhaPalavra);

                s = procuraSinonimo(p, escolhaPalavra);

                if (s != NULL) {
                    printf("O sinônimo atual de %s e: %s\n", s->dado.chave, s->dado.sinonimo);
                } else {
                    printf("A palavra não está no dicionário\n");
                }

                printf("\nInsira o novo sinônimo: ");
                scanf(" %20[^\n]", escolhaSinonimo);
                
                strcpy(s->dado.sinonimo, escolhaSinonimo);
                printf("Agora o sinônimo de %s é %s\n", s->dado.chave, s->dado.sinonimo);
                
                break;

            case 4:
                printf("\nInsira a palavra: ");
                scanf(" %20[^\n]", escolhaPalavra);

                if (delete(&p, escolhaPalavra, &h)) {
                    printf("Remoção efetuada com sucesso!\n");
                } else {
                    printf("Essa palavra não está no dicionário!\n");
                }

                break;

            case 5:
                puts("");
                print_tree(p);
                break;

            case 0:
                printf("\nEncerrando o Programa!");
                break;
        }
    }
    
    if ((arq = fopen(ARQUIVO, "w")) == NULL) {
        printf("Erro de abertura de arquivo");
    }

    //Função que realiza o backup das informações em um arquivo de texto .txt
    backup(p, arq);
    fclose(arq);

    return 0;
}
