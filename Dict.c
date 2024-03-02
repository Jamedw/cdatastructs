#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Dict.h"

#define NEXTNODE(X) (Node *)(((void **)(X->value))[1])
#define VALARR(X) (((void **)(X->value))[0])
#define VALKEY(X) (((void **)(((void **)(X->value))[0]))[0])
#define VALVAL(X) (((void **)(((void **)(X->value))[0]))[1])
#define STRING 0
#define INTEGER 1
double maxload = 1;

unsigned long int Dicthash(int cap,void *key,int key_type)
{
    unsigned long int code = 0, i;
    switch(key_type)
    {
      case STRING:
      for (i = 0; i < 8 && ((char *)key)[i] != '\0'; i++)
      {
        code = ((char *)key)[i] + code;
      }
      break;
      case INTEGER:
        code = (long)key;
      break;
    }

 return code % cap;
}

/* dctcreate: Creates a new empty dictionary.
 * TODO: Implement this function. It should return a pointer to a newly
 *       dynamically allocated dictionary with an empty backing array. */
Dict *Dictcreate(int key_type,int val_type) {
  int i;
  Dict *ptr = (Dict *)malloc(sizeof(Dict)); 
  Linkedlist **array = (Linkedlist **)malloc(sizeof(Linkedlist *)*16);
  List *keys = listcreate();
  
  for(i = 0; i < 16;i++){
    array[i] = NULL;
  }
  ptr->key_type = key_type;
  ptr->value_type = val_type;
  ptr->array = array;
  ptr->keys = keys;
  ptr->cap = 16;
  ptr->size = 0;
  
  return ptr;
}

/* dctdestroy: Destroys an existing dictionary.
 * TODO: Implement this function. It should deallocate a dictionary, its
 *       backing array, and all of its nodes. */
void Dictdestroy(Dict *dict) {
  int size = dict->size, i;
  for(i = 0;i < size;i++)
  {
    int hash = Dicthash(dict->cap,listget(dict->keys,i),dict->key_type);
    Linkedlist *list;
    if ((list = dict->array[hash]))
    {
      Node *head = list->head; 
      while(head)
      {
        free(VALARR(head));
        head = NEXTNODE(head);
      }
      Linkedlistdestroy(list);
      dict->array[hash] = NULL;
    }
    else
    {
    }
  }
  listdestroy(dict->keys);
  free(dict->array);
  free(dict);
}

void Dictdestroynokeys(Dict *dict)
{
  int i;
  for(i = 0;i < dict->cap;i++)
  {
    int hash = i;
    Linkedlist *list;
    if ((list = dict->array[hash]))
    {
      Node *head = list->head; 
      while(head)
      {
        free(VALARR(head));
        head = NEXTNODE(head);
      }
      Linkedlistdestroy(list);
      dict->array[hash] = NULL;
    }
    else
    {
    }
  }
  listdestroy(dict->keys);
  free(dict->array);
  free(dict);
}



void *Dictget(Dict *dct,void *key) {
  unsigned long int hash = Dicthash(dct->cap,key,dct->key_type);
  Linkedlist *current;
  if(!(current = (dct->array[hash])))
  { 
  return NULL;
  }
  else
  {
  Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        return VALVAL(head);
      }
      else
      {
      head = NEXTNODE(head);
      }
    }
    return NULL;
  }

}

void Dictinsert(Dict *dct, void *key, void *val)
{
  unsigned long int hash = Dicthash(dct->cap,key,dct->key_type);
  Linkedlist *current;
  if(!(current = (dct->array[hash])))
  { 
    current = Linkedlistcreate();
    void *ptr = (void *)malloc(2*sizeof(void *));
    (((void **)(ptr))[0]) = key;
    (((void **)(ptr))[1]) = val;
    Linkedlistappend(current,ptr);
    listappend(dct->keys,key);
    dct->array[hash] = current;
    dct->size++;
    resize(dct);
    return;
  }
  else
  {
    Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        VALVAL(head) = val;
        return;
      }
      else
      {
      head = NEXTNODE(head);
      }
    }
     void *ptr = (void **)malloc(2*sizeof(void *));
    (((void **)(ptr))[0]) = key;
    (((void **)(ptr))[1]) = val;
    Linkedlistappend(current,ptr);
    listappend(dct->keys,key);
    dct->size++;
    dct->array[hash] = current;
    resize(dct);
    return;
  }

}
/* dctinsert: Inserts a key, overwriting any existing value.
 * TODO: Implement this function. It should insert "key" mapped to "val".
 * NOTE: Depending on how you use this dictionary, it may be useful to insert a
 *       dynamically allocated copy of "key", rather than "key" itself. Either
 *       implementation is acceptable, as long as there are no memory leaks. */
void Dictinsertnl(Dict *dct, void *key, void *val)
{
unsigned long int hash = Dicthash(dct->cap,key,dct->key_type);
  Linkedlist *current;
  if(!(current = (dct->array[hash])))
  { 
    current = Linkedlistcreate();
    void *ptr = malloc(2*sizeof(void *));
    (((void **)(ptr))[0]) = key;
    (((void **)(ptr))[1]) = val;
    Linkedlistappend(current,ptr);
    dct->array[hash] = current;
    return;
  }
  else
  {
    Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        VALVAL(head) = val;
        return;
      }
      else
      {
      head = NEXTNODE(head);
      }
    }
     void *ptr = (void **)malloc(2*sizeof(void *));
    (((void **)(ptr))[0]) = key;
    (((void **)(ptr))[1]) = val;
    Linkedlistappend(current,ptr);
    return;
  }

}

/* dctremove: Removes a key and the value to which it is mapped.
 * TODO: Implement this function. It should remove "key" and return the value
 *       to which it was mapped, or NULL if it did not exist. */
void Dictremove(Dict *dct, void *key)
{
  unsigned long int hash = Dicthash(dct->cap,key,dct->key_type), i = 0;
  Linkedlist *current;
  if((current = dct->array[hash]))
  {
    Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        free(VALARR(head));
        Linkedlistremove(current,i);
        dct->size--;
        listremovevalue(dct->keys,key,&comparestrings);
        if(current->size == 0)
        {
          dct->array[hash] = NULL;
          Linkedlistdestroy(current);
          resize(dct);
          return;
        }
        else
        {
          resize(dct);
          return;
        }
      }
      else
      {
        head = NEXTNODE(head);
        i++;
      }
    }
  }
  else 
  {
    return;
  }
}
void Dictremovenl(Dict *dct, void *key)
{
  unsigned long int hash= Dicthash(dct->cap,key,dct->key_type), i = 0;
  Linkedlist *current;
  if((current = dct->array[hash]))
  {
    Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        free(VALARR(head));
        Linkedlistremove(current,i);
        if(current->size == 0)
        {
          dct->array[hash] = NULL;
          Linkedlistdestroy(current);
          return;
        }
        else
        {
          return;
        }
      }
      else
      {
        head = NEXTNODE(head);
        i++;
      }
    }
  }
  else 
  {
    return;
  }
}


/* dctkeys: Enumerates all of the keys in a dictionary.
 * TODO: Implement this function. It should return a dynamically allocated array
 *       of pointers to the keys, in no particular order, or NULL if empty. */
void **Dictkeys(Dict *dct) 
{
  return ((dct->keys)->array);
}


void resize(Dict *dct)
{
  if((((double)dct->size)/dct->cap) >= maxload)
  {
   
    List *keys = dct->keys;
    int precap = dct->cap, newcap = (dct->cap*4), i;
    dct->array = (Linkedlist **)realloc(dct->array,newcap*sizeof(Linkedlist *));
    for(i = precap; i < newcap;i++)
    {
      dct->array[i] = NULL;
    }
    for(i = 0; i < dct->size;i++)
    {
        void *key = listget(keys,i);
        if(Dicthash(precap,key,dct->key_type) == Dicthash(newcap,key,dct->key_type))
        {
        }
        else
        {
          void *tmp = Dictget(dct,key);
          Dictremovenl(dct,key);
          dct->cap = newcap;
          Dictinsertnl(dct,key,tmp);
          dct->cap = precap;
        }
    }
    dct->cap = newcap;
  }
  }

Node **DictgetNodes(Dict *dct)
{
  List *keys = dct->keys;
  Node **nodeset = (Node **)malloc((dct->size)*sizeof(void *));
  for(int i = 0; i < dct->size;i++)
  {
    nodeset[i] = getNode(dct,((keys->array)[i]));
  }
  return nodeset;
}

void *getNode(Dict *dct,void *key)
{
  unsigned long int hash = Dicthash(dct->cap,key,dct->key_type);
  Linkedlist *current;
  if(!(current = (dct->array[hash])))
  { 
  return NULL;
  }
  else
  {
  Node *head = current->head;
    while(head)
    {
      if(!Dictkeycmp(VALKEY(head),key,dct->key_type))
      {
        return (void *)head;
      }
      else
      {
      head = NEXTNODE(head);
      }
    }
    return NULL;
  }
}



int Dictkeycmp(void *key1,void *key2,int key_type)
{
  switch(key_type)
  {
  case STRING:
    return strcmp((char *)key1,(char *)key2);
  case INTEGER:
    return (((long)key1)-((long)key2));
  default:
    return 0;
  }
return 0;
}

void Dictprint(Dict *dct)
{
  int key_type = dct->key_type,val_type = dct->value_type;;
  List *keys = dct->keys;
  for(int i = 0; i < keys->size;i++)
  {
  switch(key_type)
  {
      case STRING:
        printf("key: %-10s",(char *)((keys->array)[i]));
        break;
      case INTEGER:
        printf("key: %-10ld",(long)((keys->array)[i]));
        break;
      default:
        break;
    }
    switch(val_type)
    {
      case STRING:
        printf("value: %-10s\n",(char *)Dictget(dct,((keys->array)[i])));
        break;
      case INTEGER:
        printf("value: %-10ld\n",(long)Dictget(dct,((keys->array)[i])));
        break;
      default:
        printf("unknown type\n");
        break;
    }
  }
return;
}
