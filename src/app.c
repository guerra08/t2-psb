#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE{
   int freq;
   char letra;
   struct NODE* left;
   struct NODE* right;
   struct NODE* next;
   bool used;
} NODE;

typedef struct TREENODE{ //LEFT = 0, RIGHT = 1
   int freq;
   struct NODE* left;
   struct NODE* right;
} TREENODE;

void readAndCount(int vet[], char arquivo[]);
void sort(struct NODE **head);

void readAndCount(int vet[], char arquivo[]){
   FILE *fp;
   char ch;

   fp = fopen(arquivo, "r");
   if (fp == NULL){
      perror("Error while opening the file.\n");
      return;
   }

   while((ch = fgetc(fp)) != EOF)
      vet[ch] = vet[ch]+1;
 
   fclose(fp);
}

void sort(struct NODE **head){
    struct NODE *temp1;
    struct NODE *temp2;

    temp1=*head; //Início da lista

    while(temp1 != NULL)
      {
        for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next) //Loop para
          { 
            if(temp2->freq < temp1->freq)
              {   
                  int freq = temp1->freq;
                  char letra = temp1->letra;
                  struct NODE* left = temp1->left;
                  struct NODE* right = temp1->right;
                  
                  temp1->freq = temp2->freq;
                  temp1->letra = temp2->letra;
                  temp1->left = temp2->left;
                  temp1->right = temp2->right;

                  temp2->freq = freq;
                  temp2->letra = letra;
                  temp2->left = left;
                  temp2->right = right;
              }
           }
         temp1=temp1->next;
       }
}

int main(){

   //head é a referencia para a lista
   NODE *head = NULL;
   NODE *aux = NULL;
   TREENODE *first;

   int contagemLetras[256];
   for(int i = 0; i < 256; i++){
      contagemLetras[i] = 0;
   }

   char arquivo[] = "../texts/first.txt";

   readAndCount(contagemLetras,arquivo);
   
   int count = 0;

   for(int i = 0; i < 256; i++){ //Monta a linked list sem ordenar
      if(contagemLetras[i] != 0){
         NODE* temp = (NODE*) malloc(sizeof (NODE));
         temp->letra = i;
         temp->freq = contagemLetras[i];
         temp->used = false;
         if(count == 0){
            head = temp;
            aux = head;
         }
         else{
            aux->next = temp;
            aux = temp;
         }
         count++;
      }
   }

   sort(&head); //Ordena a lista

   //Testes para verificar ordem
   struct NODE *toPrint = head;
   while(toPrint->next != NULL){
      printf("%d - %c\n",toPrint->freq,toPrint->letra);
      toPrint = toPrint->next;
   }
   printf("%d - %c\n",toPrint->freq,toPrint->letra);

   struct NODE *treeAux = head;
   
   first->freq = treeAux->freq + treeAux->next->freq;
   first->left = treeAux;
   first->right = treeAux->next;
   treeAux->used = true;
   treeAux->next->used = true;

   treeAux = treeAux->next;

   printf("First treenode: %d\n",first->freq);

   //FIRST é o primeiro nodo

   while(treeAux->next != NULL){
      if(treeAux->freq + treeAux->next->freq > first->freq){ //Cria um novo TREENODE com o next
         printf("treenode com o next\n");
         treeAux=treeAux->next;
      }
   }

   return 0;
}