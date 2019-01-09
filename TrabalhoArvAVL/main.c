#include "arvore.h"
#define MAX 1000000 
#define START 10000

int main() {
    struct Node *root = NULL;
    int quantidade = START, i, j, k, cont = 0;
    int max = -1, key, media[20], flag = FALSE;
    srand(time(NULL));
    for(i = 0;i < 20; i++)
    {
        for(j = 0;j < 10; j++)
        {
            for(k = 0;k < quantidade;k++)
            {
                key = rand() % MAX;
                root = insert(root, key, &cont);
                if(key > max)
                    max = key;
            }
            
            while(root != NULL)
            {
                flag = FALSE;
                key = rand() % (max + 1);
                root = deleteNode(root, key, &cont, &flag);
                if(flag == FALSE)
                    root = deleteNode(root, root->key, &cont, &flag);
            }
        }
        printf(" %d", quantidade);
    quantidade += START;  
    media[i] = cont / 10;
    cont = 0;
    }
    FILE  * arq;
    arq = fopen("rotacoes.txt", "w");
    quantidade = 10;
    for(i = 0;i < 20; i++)
    {
        fprintf(arq, "%dk\t%d\n", quantidade, media[i]);
        quantidade += 10;
    }   
} 