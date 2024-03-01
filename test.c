#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dict.h"
#define VALKEY(X) (char *)(((void **)(((void **)(X->value))[0]))[0])
#define VALVAL(X) (((void **)(((void **)(X->value))[0]))[1])


void tolowercase(char *line);
void printkeys(List *list)
{
  for(int i = 0; i < list->size;i++)
  {
  printf("%s\n",(char *)listget(list,i));
  }
  return;
}


void dcttopten(Dict *dct);
void strip(char *line,char *cpline);

void main(int argc,char* argv[])
{
  double time1 = (double)clock(),timedif;
  time1 = time1/CLOCKS_PER_SEC;
  Dict *dct = Dictcreate(1,1);
  List *keys = listcreate();
  /*FILE *file = NULL;
  char line[1000];
  file = fopen("test.txt","r");
  while(fgets(line,1000,file))
  {
    char *token;
    tolowercase(line);
    token = strtok(line," \t\n\v\f\r");
    while(token){
      char stripedtoken[1000];
      strip(token,stripedtoken);
      if (stripedtoken[0])
      {
        char *ltoken = (char *)malloc(2000*sizeof(char));
        strcpy(ltoken,stripedtoken);
        if(Dictget(dct,ltoken))
        {
          Dictinsert(dct,ltoken, (void *)((long)Dictget(dct,ltoken)+1));
          free(ltoken);
        }
        else
        {
          listappend(keys,(char *)ltoken);
          Dictinsert(dct,ltoken,(void *)1);
        }
      }
      token = strtok(NULL," \t\n\v\f\r");
    }
  }
  Dictremove(dct,"situation");
  dcttopten(dct);*/
  for (int i = 0; i < 10000000; i++)
  {
    Dictinsert(dct,(void *)i,(void *)i);
  }

  printf("Dictcap:%d          Dict size:%d          list size:%d\n",dct->cap,dct->size,(dct->keys)->size);  
  listdestroy(keys);
  Dictdestroy(dct);
  timedif = (((double) clock()) / CLOCKS_PER_SEC)-time1;
  printf("running time:%f\n",timedif);
  //fclose(file);
return;
}

 void strip(char *line,char *cpline)
{
  
  int i = 0,j = 0;
  while(line[i])
  {
    if(!(line[i] >= 97 && line[i] <= 122))
    {
      cpline[j] = line[++i];
    }
    else
    {
      cpline[j++] = line[i++];
    }
  }
  cpline[j] = line[i];
}

void tolowercase(char *line)
{
  int i = 0;
  while(line[i])
  {
    if(line[i] >= 65 && line[i] <= 90)
    {
      line[i] = (line[i]+32);
    }
    else
    {
    
    }
    i++;
  }

}

int dctcomparator(const void *n1,const void *n2);
void dcttopten(Dict *dct)
{
  int i;
  Node **nodes;
  nodes = DictgetNodes(dct);
  qsort(nodes,dct->size,sizeof(Node *),&dctcomparator);
  for(i = 0; i < dct->size ;i++)
    {
      printf("%s (%lu)\n",VALKEY(nodes[i]),(long)VALVAL(nodes[i]));
    }
free(nodes);
}

int dctcomparator(const void *n1,const void *n2)
{
  const Node **node1 =(const Node **)n1;
  const Node **node2 =(const Node **)n2;
  long int num1 = (long)VALVAL((*node1));
  long int num2 = (long)VALVAL((*node2));

  if(num1-num2)
  {
    return (num2-num1);
  }
  else
  {
    return (long)strcmp(VALKEY((*node1)),VALKEY((*node2)));
  }
}
