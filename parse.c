#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

enum{
  ROOT_STATE,
  LIST_STATE,
  TOKEN_STATE,
  ERROR_STATE
};

enum{
  PARSE1_LIST_TYPE,
  PARSE1_CHAR_TYPE
};

typedef struct Parse1GenericType {
  int type;
} Parse1GenericType;

typedef struct Parse1ListType {
  int type;
  List list;
} Parse1ListType;

typedef struct Parse1CharType {
  int type;
  char c;
} Parse1CharType;

int handleRootState(char currentChar, List stack);
void addList(List list, List item);
void addChar(List list, char c);
int handleListState(char currentChar, List stack);
int handleTokenState(char currentChar, List stack);

List parseFile(char *fileName){
  FILE *fp;
  fp = fopen(fileName, "r");
  char currentChar = fgetc(fp);
  int currentState = ROOT_STATE;
  List stack = ListInit();
  List rootList = ListInit();

  ListPrepend(stack, rootList);

  while (currentChar != EOF){
    switch(currentState){
      case ROOT_STATE:
        currentState = handleRootState(currentChar, stack);
        break;
      case LIST_STATE:
        currentState = handleListState(currentChar, stack);
        break;
      case TOKEN_STATE:
        currentState = handleTokenState(currentChar, stack);
        break;
      default:
        break;
    }
    currentChar = fgetc(fp);
  }

  return rootList;
  fclose(fp);
}

int handleRootState(char currentChar, List stack){
  List newList;
  List currentList = (List)ListHead(stack)->data;
  switch(currentChar){
    case '\n':
    case ' ':
      return ROOT_STATE;
    case '(':
      newList = ListInit();
      ListPrepend(stack, newList);
      addList(currentList, newList);
      return LIST_STATE;
    default:
      return ERROR_STATE;
  }
}

int handleListState(char currentChar, List stack){
  List newList;
  List currentList = (List)ListHead(stack)->data;
  switch(currentChar){
    case '\n':
    case ' ':
      return LIST_STATE;
    case '(':
      newList = ListInit();
      ListPrepend(stack, newList);
      addList(currentList, newList);
      return LIST_STATE;
    case ')':
      printf("end list");
      ListPop(stack);
      return LIST_STATE;
    default:
      newList = ListInit();
      ListPrepend(stack, newList);
      addList(currentList, newList);
      addChar(newList, currentChar);
      return TOKEN_STATE;
  }
}

int handleTokenState(char currentChar, List stack){
  List currentList = (List)ListHead(stack)->data;
  switch(currentChar){
    case '\n':
    case ' ':
      ListPop(stack);
      return LIST_STATE;
    case ')':
      ListPop(stack);
      ListPop(stack);
      return LIST_STATE;
    default:
      addChar(currentList, currentChar);
      return TOKEN_STATE;
  }
}

void addList(List list, List item){
  printf("make new list\n");
  Parse1ListType * data;
  data = (Parse1ListType*)malloc(sizeof(Parse1ListType));
  data->type = PARSE1_LIST_TYPE;
  data->list = item;
  ListAppend(list, data);
}

void addChar(List list, char c){
  printf("add token %c\n", c);
  Parse1CharType * data;
  data = (Parse1CharType*)malloc(sizeof(Parse1CharType));
  data->type = PARSE1_CHAR_TYPE;
  data->c = c;
  ListAppend(list, data);
}



