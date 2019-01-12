/* Trabalho 3 de AEDs 2, contagem de rotações na inserção e remoção de 
   uma arvore AVL
    Nome: Vitor Hugo da Costa Luz 2018.1.08.023
          Pedro Paulo Miranda Afonso 2018.1.08.001*/
#include "arvore.h"
#define MAX 1000000 
#define START 10000

int main() {
    struct Node *root = NULL;
    int quantidade = START, i, j, k, cont = 0;
    int max = -1, key, media[20], flag = FALSE;
    srand(time(NULL));
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 10; j++) {
            k = 0;
            while (k < quantidade) {
                key = rand() % MAX;
                flag = FALSE;
                root = insert(root, key, &cont, &flag);
                if (flag) {
                    k++;
                    if (key > max)
                        max = key;
                }
            }

            while (root != NULL) {
                flag = FALSE;
                key = rand() % (max + 1);
                root = deleteNode(root, key, &cont, &flag);
                if (flag == FALSE) {
                    struct Node * aux;
                    aux = minValueNode(root);
                    root = deleteNode(root, aux->key, &cont, &flag);
                }
            }
        }
        printf(" %d", quantidade);
        quantidade += START;
        media[i] = cont / 10;
        cont = 0;
    }
    FILE * arq;
    arq = fopen("rotacoes.txt", "w");
    quantidade = 10;
    for (i = 0; i < 20; i++) {
        fprintf(arq, "%dk\t%d\n", quantidade, media[i]);
        quantidade += 10;
    }
} 