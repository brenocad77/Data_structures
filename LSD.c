#include <stdio.h>
#include <stdlib.h>
#include "LSD.h"

struct lsd {
    int qtd;
    int cap; // capacidade
    LSD_Tipo* dados; // vamos fazer malloc depois
};

static int lsd_garante_capacidade(LSD *l) {
	if (!l) {
		return -1;
	}

	// verificar se tem espaço
	if (l->qtd < l->cap) {
		return 1; // siga em frente
	}

	// vamos alocar o espaço necessário
	if (l->cap == 0) {
		// Caso 1. Dados ainda não foi inicializado
		l->dados = malloc(8*sizeof(LSD_Tipo));
		if (!l->dados) {
			// erro de alocação
			return -1;
		}
		// se deu certo, atualiza cap
		l->cap = 8;
	} else {
		// Caso 2. Vamos dobrar a capacidade
		int nova_cap = l->cap*2;
		LSD_Tipo *novo = realloc(l->dados, nova_cap * sizeof(LSD_Tipo));
		// verificar realocação
		if (!novo) {
			return -1;
		}
		l->dados = novo;
		l->cap = nova_cap;
	}

	// tudo certo, há espaço para inserções
	return 1;
}

/* Cria uma lista vazia. */
LSD *lsd_cria(void) {
    LSD *l = malloc(sizeof(LSD));

    if (!l) {
        return NULL;
    }

    l->dados = NULL; // sem vetor
    l->cap = 0;
    l->qtd = 0;
    return l;
}

/* Destrói a lista. */
int lsd_destroi(LSD **l) {
    // verifica os ponteiros
    if (!l || !(*l)) {
        return -1;
    }

    // desaloca o vetor de dados
    free((*l)->dados);
    (*l)->dados = NULL;

    // desalocar a struct
    free(*l);
    *l = NULL;

    return 1;
}

/* Verifica se a lista está vazia. */
int lsd_vazia(const LSD *l) {
    if (!l) {
        return -1;
    }

    if (l->qtd == 0) {
        return 1;
    }

    return 0;
}

/* Retorna o tamanho da lista. */
int lsd_tamanho(const LSD *l) {
    if (!l) {
        return -1;
    }

    return l->qtd;
}

/* Insere um elemento no final. */
int lsd_insere_final(LSD *l, LSD_Tipo elem) {
    if (!l) {
        return -1;
    }

    if (lsd_garante_capacidade(l) != 1) {
        return 0;
    }

    l->dados[l->qtd] = elem;
    l->qtd++;

    return 1;
}

/* Insere um elemento em uma posição. */
int lsd_insere_pos(LSD *l, int pos, LSD_Tipo elem) {
    if (!l) {
        return -1;
    }

    if (pos < 0 || pos > l->qtd) {
        return -1;
    }

    if (lsd_garante_capacidade(l) != 1) {
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
int lsd_remove_pos(LSD *l, int pos, LSD_Tipo *removido) {
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
int lsd_consulta_pos(const LSD *l, int pos, LSD_Tipo *elem) {
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
int lsd_busca(const LSD *l, LSD_Tipo elem, int *pos) {
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
int lsd_limpa(LSD *l) {
    if (!l) {
        return -1;
    }

    l->qtd = 0;

    return 1;
}

/* Imprime os elementos da lista. */
int lsd_imprime(const LSD *l) {
    if (!l) {
        return -1;
    }
    printf("[");
    for (int i = 0; i < l->qtd; i++) {
        printf("%d", l->dados[i]);

        if (i < l->qtd - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    return 1;
}
