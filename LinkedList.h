#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linked_list LinkedList;

LinkedList *create_linked_list(void);
int insert_node(LinkedList *l, int pos, int value);
int remove_node(LinkedList *l, int pos, int *value);
int get_node(const LinkedList *l, int pos, int *value);
int is_empty_list(const LinkedList *l);
int size_list(const LinkedList *l);
void free_linked_list(LinkedList **l);

#endif // LINKEDLIST_H