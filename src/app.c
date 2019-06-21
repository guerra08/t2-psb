#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE{
   int freq;
   char letra;
   struct NODE* next;
   struct NODE* left;
   struct NODE* right;
   bool used;
} NODE;

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

    while(temp1 != NULL) //Percorre toda a lista encadeada
      {
        for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next) //Loop para verificar todos
          { 
            if(temp2->freq < temp1->freq)
              {   
                  int freq = temp1->freq;
                  char letra = temp1->letra;
                  
                  temp1->freq = temp2->freq;
                  temp1->letra = temp2->letra;

                  temp2->freq = freq;
                  temp2->letra = letra;
              }
           }
         temp1=temp1->next;
       }
}

int main(){

   //head é a referencia para a lista
   NODE *head = NULL;
   NODE *aux = NULL;
   NODE *treeN = NULL;
   NODE *lastTN = NULL;
   NODE *treeRoot = NULL;

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

   struct NODE *last_tree = (NODE*) malloc(sizeof (NODE));
   
   last_tree->freq = treeAux->freq + treeAux->next->freq;
   last_tree->left = treeAux;
   last_tree->right = treeAux->next;
   treeAux->used = true;
   treeAux->next->used = true;

   treeAux = treeAux->next;
   treeAux = treeAux->next;

   treeN = last_tree;

   //FIRST é o primeiro nodo

   int caux = 0;

   while(treeAux->next != NULL){
      struct NODE* new = (NODE*) malloc(sizeof (NODE));
      if((treeAux->freq + treeAux->next->freq) < (treeN->freq + treeAux->freq)){ //Cria um novo TREENODE com o next + atual
         printf("treenode com o next\n");
         new->freq = treeAux->freq + treeAux->next->freq;
         new->left = treeAux;
         new->right = treeAux->next;
         treeAux->used = true;
         treeAux->next->used = true;
         treeN = new;
      }
      else{
         printf("treenode com o anterior\n");
         printf("Aux - %d\n",treeAux->freq);
         new->freq = treeAux->freq + treeN->freq;
         new->left = treeAux;
         new->right = treeN;
         treeAux->used = true;
         treeAux->next->used = true;
         treeN = new;
      }

      printf("NEW -> %d\n",new->freq);
      treeAux=treeAux->next;
   }

   return 0;
}