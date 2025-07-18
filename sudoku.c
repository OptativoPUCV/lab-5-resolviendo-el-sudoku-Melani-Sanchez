#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int i,j,k;
   for(i=0; i < 9; i++) {
       for(j=0; j < 9; j++) {
         int num = n->sudo[i][j];
         if (num == 0) continue;
         if ( num < 1 || num > 9) return 0;
          
         for(k=0; k<9; k++) {
            if(k != j && n->sudo[i][k] == num) return 0;
            if(k != i && n->sudo[k][j] == num) return 0;
         }
          
         int startRow = (i / 3) * 3;
         int startCol = (j / 3) * 3;
         for(k= startRow; k < startRow + 3; k++) {
            for(int l=startCol; l < startCol + 3; l++) {
               if((k != i || l != j) && n->sudo[k][l] == num) return 0;
            }
         }
      }
   }

   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   Node* adj=NULL;
   int i,j;
   
   for(i = 0; i < 9; i++) {
       for(j = 0; j < 9; j++) {
          if(n->sudo[i][j] == 0) {
             int k = 1;
             for(k = 1; k <= 9; k++) {
                adj= copy(n);
                adj->sudo[i][j]=k;
               if(is_valid(adj)) {
                   pushBack(list, adj);
               }
               else free(adj);
             }
             return list;
          }
       }
   }
   return list;
}


int is_final(Node* n){
   int i,j;
   for(i = 0; i < 9; i++){
       for(j = 0; j < 9; j++){
          if(n->sudo[i][j] == 0) return 0;
       }
    }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   push(S, initial);
   *cont = 0;
   while(!is_empty(S)) {
      Node *current = top(S);
      pop(S);
      
      (*cont)++;
      if(is_final(current)) return current;

      List *adj = get_adj_nodes(current);
      Node *adj_node = first(adj);
      while(adj_node != NULL) {
          push(S, adj_node);
          adj_node = next(adj);
      }
   }
   
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/