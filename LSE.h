#ifndef LSE_H
#define LSE_H

typedef int LSE_Tipo;

/* Tipo opaco da Lista Sequencial Estática. */
typedef struct lse LSE;

/* Cria uma lista vazia. */
LSE *lse_cria(void);
/* Destrói a lista. */
int lse_destroi(LSE **l);
/* Verifica se a lista está vazia. */
int lse_vazia(const LSE *l);
/* Verifica se a lista está cheia. */
int lse_cheia(const LSE *l);
/* Retorna o tamanho da lista. */
int lse_tamanho(const LSE *l);
/* Insere um elemento no final. */
int lse_insere_final(LSE *l, LSE_Tipo elem);
/* Insere um elemento em uma posição. */
int lse_insere_pos(LSE *l, int pos, LSE_Tipo elem);
/* Remove um elemento de uma posição. */
int lse_remove_pos(LSE *l, int pos, LSE_Tipo *removido);
/* Consulta o elemento de uma posição. */
int lse_consulta_pos(const LSE *l, int pos, LSE_Tipo *elem);
/* Busca um elemento na lista. */
int lse_busca(const LSE *l, LSE_Tipo elem, int *pos);
/* Remove todos os elementos da lista. */
int lse_limpa(LSE *l);
/* Imprime os elementos da lista. */
int lse_imprime(const LSE *l);

#endif