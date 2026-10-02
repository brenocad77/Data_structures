#include <stdlib.h>
#include "LinkedList.h"

// definir struct que representa um nó
typedef struct node {
	int data; // inteiro
	// ponteiro para o próximo (mesmo tipo)
	struct node *next; 
} Node;

struct linked_list {
	// ponteiro para o primeiro nó
	Node *head;
	// opcionalmente, uma variável para saber
	// quantos elementos a lista tem
	// sem ela, seria necessário percorrer
	// toda a lista contando ...
	int qtd;
};

// criar uma lista encadeada e retornar o ponteiro
// para ela
LinkedList *create_linked_list(void) {
	LinkedList *l = malloc(sizeof(LinkedList));
	if (!l) {
		// falha ao alocar
		return NULL;
	}
	// se alocou, preciso preencher os campos
	l->head = NULL;
	l->qtd = 0; // lista vazia
	// sucesso
	return l;
}

// insere um elemento na lista em qualquer pos
int insert_node(LinkedList *l, int pos, int value) {
	// lista é válida?
	if (!l) {
		return -1;
	}
	// posição é válida?
	if ((pos < 0) || (pos > l->qtd)) {
		return -1; // inválida
	}
	// alocar o elemento novo
	Node *novo = malloc(sizeof(Node));
	// sugestão: verificar se o malloc funcionou,
	// assim como fizemos em create_linked_list
	// if (!novo) {
	//     return -1;
	// }
	novo->data = value;
	// quando inserimos na primeira posição,
	// precisamos ajustar o head
	if (pos == 0) {
		novo->next = l->head;
		l->head = novo;
	} else {
		// agora percorremos a lista encadeada
		// procurando pos-1 para apontar o novo->next
		Node *tmp = l->head; // nó temporário para percorrer que começa em head (primeiro elemento)
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// inserir
		novo->next = tmp->next;
		tmp->next = novo;
	}
	// incrementa o qtd
	l->qtd++;
	return 1; //sucesso
}

int remove_node(LinkedList *l, int pos, int *value) {
	// verifica lista alocada
	if (!l) {
		return -1;
	}
	// existem elementos e 0 a qtd-1
	if (pos < 0 || pos >= l->qtd) {
		return -1;
	}
	// cria ponteiro que irá apontar para o elemento a ser removido
	Node *rem;
	// vamos encontrar o elemento para remover
	// caso 1. é o primeiro elemento
	if (pos == 0) {
		rem = l->head;
		l->head = rem->next;
	} else {
		// caso 2. está em outra posição
		// cria ponteiro tmp p/ percorrer a lista
		Node *tmp = l->head;
		// vamos percorrer até pos-1
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// estou em pos-1
		rem = tmp->next;
		// para ajustar o ponteiro
		// o antecessor passa a "pular"
		// o elemento removido
		tmp->next = rem->next;
	}
	// caso o usuário deseje, salvar o valor que
	// será removido
	if (value) {
		*value = rem->data;
	}
	// faz free no rem (elemento removido)
	free(rem);
	// decrementa a quantidade
	l->qtd--;
	// retorno operação concluída com sucesso
	return 1;
}

int get_node(const LinkedList *l, int pos, int *value) {
	// verifica lista alocada
	if (!l) {
		return -1;
	}
	// existem elementos e 0 a qtd-1
	if (pos < 0 || pos >= l->qtd) {
		return -1;
	}
	// value não ponte apontar para NULO
	if (!value) {
		return -1;
	}
	// sugestão: como aqui não removemos nada, não é
	// necessário parar em pos-1 (isso só serve para
	// ajustar o ponteiro do antecessor). dá para
	// percorrer direto até pos, sem separar o caso 0:
	// Node *tmp = l->head;
	// for (int i = 0; i < pos; i++) {
	//     tmp = tmp->next;
	// }
	// *value = tmp->data;
	// return 1;
	// (o nome rem também poderia ser trocado, ex: atual)
	// cria ponteiro que irá apontar para o elemento a ser lido
	Node *rem;
	// vamos encontrar o elemento para obter o valor
	// caso 1. é o primeiro elemento
	if (pos == 0) {
		rem = l->head;
	} else {
		// caso 2. está em outra posição
		// cria ponteiro tmp p/ percorrer a lista
		Node *tmp = l->head;
		// vamos percorrer até pos-1
		for (int i = 0; i < pos-1; i++) {
			tmp = tmp->next;
		}
		// estou em pos-1
		rem = tmp->next;
	}
	// salvar o valor da posição pos
	*value = rem->data;
	// retorno operação concluída com sucesso
	return 1;
}

int is_empty_list(const LinkedList *l) {
	// verifica se ponteiro para a lista é válido
	if (!l) {
		return -1;
	}
	// verifica se o head aponta para NULL
	// se sim, lista vazia
	// (alternativa equivalente: verificar se l->qtd == 0)
	if (!l->head) {
		return 1; // true: vazia
	}
	return 0; // false: não vazia
}

int size_list(const LinkedList *l) {
	// verifica se ponteiro para a lista é válido
	if (!l) {
		return -1;
	}
	// retorna o tamanho
	return l->qtd;
}

void free_linked_list(LinkedList **l) {
	// verifica se ponteiros são nulos
	if (!l || !(*l)) {
		return;
	}
	// sugestão: os três casos abaixo podem ser
	// substituídos apenas pelo while do último caso.
	// se a lista estiver vazia, head é NULL e o laço
	// nem executa; se tiver um elemento, executa uma vez.
	// versão enxuta:
	// Node *tmp = (*l)->head;
	// while (tmp != NULL) {
	//     Node *rem = tmp;
	//     tmp = tmp->next;
	//     free(rem);
	// }
	// free(*l);
	// *l = NULL;
	if ((*l)->qtd == 0) {
		// libera diretamente a lista
		// não há nós para fazer free
		free(*l);
	} else if ((*l)->qtd == 1) {
		// faz free no primeiro (único elemento)
		free((*l)->head);
		// não precisa, pois será apagado
		(*l)->head = NULL;
		// libera a lista
		free(*l);
	} else {
		// se são mais elementos, precisamos
		// percorrer e fazer o free
		Node *rem;
		Node *tmp = (*l)->head;
		while (tmp != NULL) {
			rem = tmp;
			tmp = tmp->next;
			free(rem);
		}
		// não precisa, porque faremos free(l)
		// mas, se não fizessemos free(l),
		// precisariamos ajustar:
		(*l)->head = NULL;
		(*l)->qtd = 0;
		// libera a lista da memória
		free(*l);
	}
	*l = NULL;
}