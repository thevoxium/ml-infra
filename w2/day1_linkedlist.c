
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  Node** arr = malloc(n * sizeof(Node*));
  if(arr == NULL){
    return NULL;
  }
  for(int i=0; i<n; i++){
    arr[i] = malloc(sizeof(Node));
    if(arr[i] == NULL){
      return NULL;
    }
    arr[i]->value = i;
    arr[i]->next = NULL;
  }
  for(int i=n-1; i>0; i--){
    int j = rand() % (i+1);
    Node* tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
  for(int i=0; i<n-1; i++){
    arr[i]->next = arr[i+1];
  }
  arr[n-1]->next = NULL;
  Node* head = arr[0];
  free(arr);
  return head;
}

double traverse(Node* head) {
    double sum = 0;
    while (head) {
        sum += head->value;
        head = head->next;
    }
    return sum;
}

int main(){
  srand(time(NULL));
  int n = 1000000;
  Node* head1 = seq(n);
  Node* head2 = random_(n);
  printf("Seq sum: %f\n", traverse(head1));
  printf("Random sum: %f\n", traverse(head2));
  return 0;
}
