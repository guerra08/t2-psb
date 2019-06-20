#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE{
   int freq;
   char letra;
   struct NODE* left;
   struct NODE* right;
   struct NODE* next;
} NODE;

void readAndCount(int vet[], char arquivo[]);

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

int main(){

   NODE* head = NULL; 
   NODE* aux = NULL;

   int contagemLetras[256];
   for(int i = 0; i < 256; i++){
      contagemLetras[i] = 0;
   }

   char arquivo[] = "../texts/first.txt";

   readAndCount(contagemLetras,arquivo);
   
   int count = 0;

   for(int i = 0; i < 256; i++){
      if(contagemLetras[i] != 0){
         NODE* temp = (NODE*) malloc(sizeof (NODE));
         temp->letra = i;
         temp->freq = contagemLetras[i];
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

   NODE* perc = head;
   while(perc->next != NULL){
      printf("%d",perc->freq);
      perc = perc->next;
   }
   printf("%d",perc->freq);

   return 0;
}