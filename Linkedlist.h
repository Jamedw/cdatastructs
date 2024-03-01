typedef struct Node 
{
void *value;
}Node;


typedef struct Linkedlist{
Node *head;
Node *tail;
int size;
}Linkedlist;

void Linkedlistdestroy(Linkedlist *);
Linkedlist *Linkedlistcreate();

Node *nodecreate();
Node *Linkedlistnodecreate();
void *llrget(Node *node,int index);
void delNodes(Node *);
Linkedlist *Linkedlistcreate();
void Linkedlistremove(Linkedlist *list,int i);
void Linkedlistappend(Linkedlist *list,void *);
void Linkedlistpreppend(Linkedlist *list,void *);
void removes1(Linkedlist *);
void Linkedlistremovelast(Linkedlist *list);
void Linkedlistremovefirst(Linkedlist *list);
void *Linkedlistget(Linkedlist *,int);
int Linkedlistcontains(void*);
void Linkedlistinsert(int,void*);
void Linkedlistrr(int index,Node *pnode,Node *cnode);
