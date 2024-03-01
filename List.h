/*this will be an arraylist structure it will come with functions
 * that allow for resizing inserting ect..
 * a double void point will allow arraylist to handle 
 * multiple types*/

typedef struct List
{
int size;
int cap;
int lindex;
void **array;
} List;

int comparestrings(void*,void*);
List *listcreate();
void listremovevalue(List *,void *,int (*)(void *,void *));
void listdestroy(List *);
void *listget(List *,int);
void listappend(List *,void *);
void listprepend(List *,void *);
void listresize(List *);
void listinsert(List *,int, void *);
void listremove(List *,int);
int listcontains(List *,void *,int (*)(void*,void*));
