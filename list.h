typedef struct ListType * List;

typedef struct Node {
  void * data;
  struct Node * next;
} Node;

List ListInit();

void ListAppend(List list, void * data);

void ListPrepend(List list, void * data);

void ListPop(List list);

Node * ListHead(List list);

