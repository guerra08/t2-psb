#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    int contagemLetras[256];
    for(int i = 0; i < 256; i++){
        contagemLetras[i] = 0;
    }

    char arquivo[] = "../texts/first.txt";

    readAndCount(contagemLetras,arquivo);

    for(int i = 0; i < 256; i++){
         if(contagemLetras[i] != 0){
            printf("%c -- %d\n",i,contagemLetras[i]);
         }
    }

    return 0;
}