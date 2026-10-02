#ifndef LSD_H
#define LSD_H

typedef int LSD_Tipo;

/* Tipo opaco da Lista Sequencial Dinâmica. */
typedef struct lsd LSD;

/* Cria uma lista vazia. */
LSD *lsd_cria(void);
/* Destrói a lista. */
int lsd_destroi(LSD **l);
/* Verifica se a lista está vazia. */
int lsd_vazia(const LSD *l);
/* Retorna o tamanho da lista. */
int lsd_tamanho(const LSD *l);
/* Insere um elemento no final. */
int lsd_insere_final(LSD *l, LSD_Tipo elem);
/* Insere um elemento em uma posição. */
int lsd_insere_pos(LSD *l, int pos, LSD_Tipo elem);
/* Remove um elemento de uma posição. */
int lsd_remove_pos(LSD *l, int pos, LSD_Tipo *removido);
/* Consulta o elemento de uma posição. */
int lsd_consulta_pos(const LSD *l, int pos, LSD_Tipo *elem);
/* Busca um elemento na lista. */
int lsd_busca(const LSD *l, LSD_Tipo elem, int *pos);
/* Remove todos os elementos da lista. */
int lsd_limpa(LSD *l);
/* Imprime os elementos da lista. */
int lsd_imprime(const LSD *l);

#endif