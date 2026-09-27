#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"

#define MAX 1000

struct lse {
    int qtd;
    LSE_Tipo dados[MAX];
};

/* Cria uma lista vazia. */
LSE *lse_cria(void) {
    LSE *l = malloc(sizeof(LSE));

    if (!l) {
        return NULL;
    }

    l->qtd = 0;
    return l;
}

/* Destrói a lista. */
int lse_destroi(LSE **l) {
    if (!l) {
        return -1;
    }

    free(*l);
    *l = NULL;

    return 1;
}

/* Verifica se a lista está vazia. */
int lse_vazia(const LSE *l) {
    if (!l) {
        return -1;
    }

    if (l->qtd == 0) {
        return 1;
    }

    return 0;
}

/* Verifica se a lista está cheia. */
int lse_cheia(const LSE *l) {
    if (!l) {
        return -1;
    }

    if (l->qtd == MAX) {
        return 1;
    }

    return 0;
}

/* Retorna o tamanho da lista. */
int lse_tamanho(const LSE *l) {
    if (!l) {
        return -1;
    }

    return l->qtd;
}

/* Insere um elemento no final. */
int lse_insere_final(LSE *l, LSE_Tipo elem) {
    if (!l) {
        return -1;
    }

    if (lse_cheia(l)) {
        return 0;
    }

    l->dados[l->qtd] = elem;
    l->qtd++;

    return 1;
}

/* Insere um elemento em uma posição. */
int lse_insere_pos(LSE *l, int pos, LSE_Tipo elem) {
    if (!l) {
        return -1;
    }

    if (pos < 0 || pos > l->qtd) {
        return -1;
    }

    if (lse_cheia(l)) {
        return 0;
    }

    /* Desloca os elementos para a direita. */
    for (int i = l->qtd; i > pos; i--) {
        l->dados[i] = l->dados[i - 1];
    }

    l->dados[pos] = elem;
    l->qtd++;

    return 1;
}

/* Remove um elemento de uma posição. */
int lse_remove_pos(LSE *l, int pos, LSE_Tipo *removido) {
    if (!l) {
        return -1;
    }

    if (pos < 0 || pos >= l->qtd) {
        return -1;
    }

    if (removido != NULL) {
        *removido = l->dados[pos];
    }

    /* Desloca os elementos para a esquerda. */
    for (int i = pos; i < l->qtd - 1; i++) {
        l->dados[i] = l->dados[i + 1];
    }

    l->qtd--;

    return 1;
}

/* Consulta o elemento de uma posição. */
int lse_consulta_pos(const LSE *l, int pos, LSE_Tipo *elem) {
    if (!l || !elem) {
        return -1;
    }

    if (pos < 0 || pos >= l->qtd) {
        return -1;
    }

    *elem = l->dados[pos];

    return 1;
}

/* Busca um elemento na lista. */
int lse_busca(const LSE *l, LSE_Tipo elem, int *pos) {
    if (!l || !pos) {
        return -1;
    }

    *pos = -1;

    for (int i = 0; i < l->qtd; i++) {
        if (l->dados[i] == elem) {
            *pos = i;
            return 1;
        }
    }

    return 0;
}

/* Remove todos os elementos da lista. */
int lse_limpa(LSE *l) {
    if (!l) {
        return -1;
    }

    l->qtd = 0;

    return 1;
}

/* Imprime os elementos da lista. */

int lse_imprime(const LSE *l) {
    if (!l) {
        return -1;
    }

    printf("[");

    for (int i = 0; i < l->qtd; i++) {
        if (i > 0) {
            printf(", ");
        }

        printf("%d", l->dados[i]);
    }

    printf("]\n");
    return 1;
}
