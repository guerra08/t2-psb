#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE{
   int freq;
   char letra;
   struct NODE* left;
   struct NODE* right;
} NODE;

void readAndCount(int vet[], char arquivo[]);
void insertNode(int count, char c);   

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
   NODE* temp = (NODE*) malloc(sizeof (NODE));

   int contagemLetras[256];
   for(int i = 0; i < 256; i++){
      contagemLetras[i] = 0;
   }

   char arquivo[] = "../texts/first.txt";

   readAndCount(contagemLetras,arquivo);

   for(int i = 0; i < 256; i++){
      if(contagemLetras[i] != 0){
         temp->letra = i;
         temp->freq = contagemLetras[i];
         head = temp;
      }
   }

   printf("%d", head->freq);

   return 0;
}