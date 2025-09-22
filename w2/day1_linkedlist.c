#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  float value;
  struct Node* next;
} Node;

Node* seq(int n){
  Node* arr = malloc(n * sizeof(Node));
  if(arr == NULL){
    return NULL;
  }
  for (int i=0; i< n; i++){
    arr[i].value = i;
    if(i < n-1){
      arr[i].next = &arr[i+1];
    }else{
      arr[i].next = NULL;
    }
  }
  return &arr[0];
}


Node* random_(int n){
  Node* head = NULL;
  Node* prev = NULL;
  for(int i=0; i<n; i++){
    Node* curr = malloc(sizeof(Node));
    if(curr == NULL){
      return NULL;
    }
    curr->value = i;
    if(prev == NULL){
      head = curr;
    }else{
      prev->next= curr;
    }
    prev = curr;
  }
  return head;
}

int main(){
  int n = 1000000;
  Node* head1 = seq(n);
  Node* head2 = random_(n);
  printf("%f \n", head1->value);
  printf("%f \n", head2->value); return 0; }
