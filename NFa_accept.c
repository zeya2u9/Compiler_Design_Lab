#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct state{
  char final;
  int value;
  struct transition *transList;
};
 
struct stateList{
  int value;
  struct state *statePtr;
  struct stateList *next;
};
 
struct transition{
  char symbol;
  struct state *statePtr;
  struct transition *next;
};
 
int dfa(char * input, struct state *s);
void freemem(struct stateList * sList);
int main(){
  struct stateList *sList = NULL, *sListPtr=NULL, *tmpListPtr = NULL;
  struct state *sPtr, *tmpStatePtr;
  struct transition *tPtr,*tmpTransPtr;
  int stateNo;
  char final='N';
  char symbol=' ';
  char input[80];
  do{
    printf("Enter State No (0 to Quit ): ");
    scanf("%d",&stateNo);
    getchar();
    if(stateNo != 0){
    printf("Final State ? (Y?N) ");
    scanf("%c",&final);
    if(sList == NULL){
      sList = (struct stateList*) malloc(sizeof(struct stateList));
      sList -> value = stateNo;
      sList -> statePtr = (struct state *) malloc (sizeof(struct state));
      sList -> statePtr -> value = stateNo;
      sList -> statePtr -> final = final;
      sList -> statePtr -> transList = NULL;
      sList -> next= NULL;
    }else{
      sListPtr = sList;
      while(sListPtr -> next != NULL){
        sListPtr = sListPtr->next;
      }
      sListPtr->next = (struct stateList*) malloc(sizeof(struct stateList));
      sListPtr = sListPtr->next;
      sListPtr -> value = stateNo;
      sListPtr -> statePtr = (struct state *) malloc (sizeof(struct state));
      sListPtr -> statePtr -> value = stateNo;
      sListPtr -> statePtr -> final = final;
      sListPtr -> statePtr -> transList = NULL;
      sListPtr -> next= NULL;
      }
    }
  }while(stateNo != 0);
   
  sListPtr = sList;
  while(sListPtr != NULL){
    printf("\n\nEnter Transitions from state %d \n",sListPtr->value);
    printf("To State (0 to Quit) : ");
    scanf("%d",&stateNo);
    while(stateNo != 0){
    tmpListPtr = sList;
    while(tmpListPtr != NULL){
      if(tmpListPtr-> value == stateNo){
        break;
      }
      tmpListPtr = tmpListPtr ->next;
    }
 
 
    if(tmpListPtr == NULL){
      printf("Invalid State\n");
    }else{
      getchar();
      printf("Enter symbol : ");
      scanf("%c",&symbol);
      sPtr = sListPtr -> statePtr;
      
      if(sPtr->transList == NULL){
        sPtr->transList = (struct transition *) malloc (sizeof (struct transition));
        tPtr = sPtr->transList;
      }else{
        tPtr = sPtr->transList;
        while(tPtr->next != NULL){
        tPtr = tPtr->next;
        }
        tPtr -> next = (struct transition *) malloc (sizeof (struct transition));
        tPtr = tPtr ->next;  
      }
      tPtr -> symbol = symbol;
      tPtr -> statePtr = tmpListPtr->statePtr;
      tPtr -> next = NULL;
       
    }
    printf("\nTo State (0 to Quit) : ");
    scanf("%d",&stateNo);
    }
    sListPtr = sListPtr -> next;
  }
  if(sList != NULL){
    printf("\nEnter String : ");
    scanf("%s",input);
    while(strcmp(input,"q") != 0){
    if( dfa(input,sList->statePtr )){
      printf("String Accepted.");
    }
    else{
      printf("String Not accepted!!! . ");
    }
    printf("\nEnter String (q to Quit): ");
    scanf("%s",input);
    }
  }  
   
  freemem(sList);
}
 
int dfa(char * input, struct state *s){
  struct transition * t;
  int accept =0;
  // printf("\nInput: %s\n",input);
  // printf("Value : %d\n",s->value);
  //printf("Final: %c\n",s->final);
 
  if(s == NULL){
    return 0;
  }else{
    t = s -> transList;
    if(input[0] == '\0' && s -> final == 'Y'){
    return 1;
    }
     
    while( t != NULL && accept ==0){
    //  printf("State Transition symbol : %c\n",t->symbol);
    if(t -> symbol == input[0]){
      //printf("Transist to the state : %d\n",t->statePtr->value);
      accept= dfa(input+1,t->statePtr); 
      }
    t = t -> next;
    }
  }
  return accept;
} 
 
void freemem(struct stateList * sList){
  struct stateList *tsList;
  struct state * tstate;
  struct transition *trans, *trans2;
  while(sList != NULL){
    tsList = sList->next;
     
    tstate = sList -> statePtr;
    trans = tstate -> transList;
    while(trans != NULL){
    trans2 = trans->next;
    free(trans);
    trans = trans2;
    }
    free(tstate);
    free(sList);
    sList = tsList;
  }
}
