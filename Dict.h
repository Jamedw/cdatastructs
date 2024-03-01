#include "List.h"
#include "Linkedlist.h"

typedef struct Dict {
    int cap;
    Linkedlist **array;
    int size;
    List *keys;
    int key_type;
    int value_type;
} Dict;

int Dictkeycmp(void *key1,void *key2,int key_type);
void Dictprint(Dict *dct);
Dict *Dictcreate(int,int);
Node **DictgetNodes(Dict *);
void *getNode(Dict *,void *);
void Dictdestroy(Dict *);
void Dictdestroynokeys(Dict *dct);
void *Dictget(Dict *, void *);
void Dictinsert(Dict *, void *, void *);
void Dictinsertnl(Dict *, void *, void *);
void Dictremove(Dict *, void *);
void Dictremovenl(Dict *, void *);
void **Dictkeys(Dict *);
void resize(Dict *);
