#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"


List *listcreate()
{
  int i;
  List *list = (List *)malloc(sizeof(List));
  list->size = 0;
  list->cap = 16;
  list->array = (void **)malloc(32*sizeof(void *));
  for(i = 0;i < 32;i++)
  {
    list->array[i] = NULL;
  }
  return list;
}


void listdestroy(List *list){
free(list->array);
free(list);
}

void listresize(List *list)
{
  int psize,i,nsize;
  void **newarray;
  psize = list->cap;
  list->cap = list->cap*2;
  nsize = list->cap;
  newarray = (void **)malloc(sizeof(void *)*nsize);

  for(i = 0; i < psize; i++)
    {
    newarray[i] = list->array[i];
    }

  for(i=psize; i < nsize;i++)
    {
  newarray[i] = NULL;
    }

  free(list->array);
  list->array = newarray;
}


void listclear(List *list){
void **clist = (void **)malloc(32*sizeof(void *));
free(list->array);
list->array = clist;
list->cap = 32;
list->size = 0;
}


void *listget(List *list,int index){
if (index >= list->size || index < 0){
  return NULL;
}else 
return list->array[index];
}

void listappend(List *list,void *val)
{
  if ((list->size+2) >= list->cap)
  {
    listresize(list);
  }
  list->array[list->size] = val;
  list->size++;
}

void listprepend(List *list,void *val){
  int i;
  void **copyarray;
  if ((list->size+2) >= list->cap)
  {
    listresize(list);
  }
  copyarray = (void **)malloc(list->cap*sizeof(void *));
  for (i = 0;i < list->size; i++)
  {
  copyarray[i+1] = list->array[i];
  }
  copyarray[0] = val;
  free(list->array);
  list->array = copyarray;
  list->size++;

}

/* this insert function will only allow the user to insert 
 * from 0...size, this simplifies the function and the arraylist
 * implementation;*/
void listinsert(List *list,int index, void *val)
{
  int i;
  void **arrcp;
  if(index < 0 || index > list->size)
  {
  return;
  }

  if ((list->size+2) >= list->cap)
  {
    listresize(list);
  }

  if(index == 0)
  {
    listprepend(list,val);
  }
  else if(index == list->size)
  {
  listappend(list,val);
  }else
  {
    arrcp = (void **)malloc(list->cap*sizeof(void *));
    for(i = 0;i < list->size;i++)
    {
      if(i >= index)
      {
        arrcp[i+1] = list->array[i];
      }else
        arrcp[i] = list->array[i];
    }
    free(list->array);
    arrcp[index] = val;
    list->array = arrcp;
    list->size++;
  }
}


void listremove(List *list,int index)
{
  void **arrcp;
  int i;
  if(list->size == 0){
    return;
  }
  if(index < 0 || index >= list->size)
  {
    return;
  }
  i = 0;
  arrcp = (void **)malloc(list->cap*sizeof(void *));
  while(i != list->size)
  {
    if (i >= index){
    arrcp[i] = list->array[i+1];
    i++;
    }
    else
    {
    arrcp[i] = list->array[i];
    i++;
    }
  }
free(list->array);
list->array = arrcp;
list->size--;
return;
}

void listremovevalue(List *list,void *value,int (*comparator)(void *,void *))
{
int i;

for(i = 0;i < list->size;i++)
{
  if (comparator(list->array[i],value) == 0){
    listremove(list,i--);
  }
}

}

/*Assumes that two void pointers will be ints then compares them
 * returns 0 if they are the same int 
 * returns <0 if val1 is smaller 
 * returns >0 if val2 bigger*/
int compareints(void *val1,void *val2)
{
return ((int *)val1-(int *)val2);
}

int comparestrings(void *v1,void *v2)
{
return strcmp((char *)v1,(char *)v2);
}
int listcontains(List *list,void *value,int (*comparator)(void *,void *))
{
int i;
for(i = 0;i < list->size;i++){
 if(!comparator(value,list->array[i]))  
  {
  return 1;
  }
 }
return 0;
}
