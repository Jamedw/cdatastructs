#include <stdlib.h>
#include "Linkedlist.h"


Linkedlist *Linkedlistcreate()
{
  Linkedlist *list = (Linkedlist *)malloc(sizeof(Linkedlist));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}


void Linkedlistdestroy(Linkedlist *list)
{
  if(list->head)
  {
  delNodes(list->head);
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  }
  
  free(list);
}

void *Linkedlistget(Linkedlist *list, int index)
{
  if (index >= list->size || index < 0)
  {
  return NULL;
  }
  else
  {
  return llrget(list->head,index);
  }
}

void *llrget(Node *node,int index)
{
  if(index == 0)
  {
    return ((void **)node->value)[0];
  }
  else
  {
    return llrget((Node *)((void **)node->value)[1],--index);
  }
}

void delNodes(Node *node)
{
  Node *next = (Node *)(((void **)node->value)[1]);
  if(!next)
  {
    free(node->value);
    free(node);
  }
  else
  {
    delNodes(next);
    free(node->value);
    free(node);
  }
}

void Linkedlistpreppend(Linkedlist *list,void *val)
{
  Node *node = Linkedlistnodecreate();

  ((void **)node->value)[0] = val;
  ((void **)node->value)[1] = NULL;
  /*if the head and tail are node this will be the first and only node
   * in the linked list so head & tail = this new node */
  if(!list->head && !list->tail)
  {
    // if the tail and head of the list are null then it is an empty list so assign
    // current node to head and tail
    list->head = node;
    list->tail = node;
  }
  else
  {
    //there is a tail so set the tail next to the new node then set list->tail 
    //to node
    ((void **)node->value)[1] = (void *)list->head;
    list->head = node;
  }
  list->size++;
}
void Linkedlistappend(Linkedlist *list,void *val)
{
  Node *node = Linkedlistnodecreate();

  ((void **)node->value)[0] = val;
  ((void **)node->value)[1] = NULL;
  /*if the head and tail are node this will be the first and only node
   * in the linked list so head & tail = this new node */
  if(!list->head && !list->tail)
  {
    // if the tail and head of the list are null then it is an empty list so assign
    // current node to head and tail
    list->head = node;
    list->tail = node;
  }
  else
  {
    //there is a tail so set the tail next to the new node then set list->tail 
    //to node
    ((void **)((list->tail)->value))[1] = (void *)node;
    list->tail = node;
  }
  list->size++;
}

void Linkedlistremove(Linkedlist *llist,int index)
{
  if(index < 0 || index >= llist->size)
  {
  
  }
  else if (index == 0)
  {
    Linkedlistremovefirst(llist);
  }
  else if (index == llist->size-1)
  {
    Linkedlistremovelast(llist);
  }else
  {
  Linkedlistrr(index,llist->head,llist->head);
  }
}
void Linkedlistremovelast(Linkedlist *list)
{
  if (list->size == 1)
  {
    removes1(list);
  }
  else
  {
    int i = 0;
    Node *tmp = list->tail,*traverser = list->head;
    while(i != list->size-2)
    {
    traverser = (Node *)(((void **)traverser->value)[1]);
    i++;
    }
    ((void **)(traverser->value))[1] = NULL;
    list->tail = traverser;
    free(tmp->value);
    free(tmp);
    list->size--;
  }
}
void Linkedlistremovefirst(Linkedlist *list)
{
  if (list->size == 1)
  {
    removes1(list);
  }
  else
  {
  Node *tmp = list->head;
  Node *next = (Node *)((void **)(tmp->value))[1];
  free(tmp->value);
  free(tmp);
  list->head = next;
  list->size--;
  }
}

void removes1(Linkedlist *list)
{
  free((list->head)->value);
  free(list->head);
  list->head = NULL;
  list->tail = NULL;
  list->size--;
}

void Linkedlistrr(int index,Node *pnode,Node *cnode)
{
  if(!index)
  {
    ((void **)(pnode->value))[1] = ((void **)(cnode->value))[1];
    free(cnode->value);
    free(cnode);
  }
  else
  {
  Linkedlistrr(--index,cnode,(Node *)(((void **)cnode->value)[1]));
  }

}

Node *Linkedlistnodecreate()
{
Node *node = nodecreate();
node->value = (void *)malloc(22*sizeof(void *));
return node;
}
Node *nodecreate()
{
  Node *node = (Node*)malloc(sizeof(Node));
  return node;
}
