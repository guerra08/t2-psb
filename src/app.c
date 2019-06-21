#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10 

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
void printTree(NODE *root, int space);
void printCall(NODE *root);
void printPreorder(struct NODE* node, char dir);

void printPreorder(struct NODE* node, char dir) { 

   if (node == NULL){
      printf("\n"); 
      return;
   }
   if(dir == 'l'){
      printf("0");
   }
   if(dir == 'r'){
      printf("1");
   }

   printf("%c", node->letra);  

   printPreorder(node->left,'l');   

   printPreorder(node->right,'r'); 
} 

//Lê o arquivo desejado e armazena a quantidade de cada caractere em um vetor
//A posição no vetor corresponde ao valor decimal do caractere lido.
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

//Realiza um Bubble Sort na lista encadeada, ordenando de forma crescente.
//Código utilizado inspirado por: https://stackoverflow.com/questions/40623432/sort-a-linked-list-using-c
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

//Realiza o output da árvore gerada.
//Código utilizado adaptado de: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void printTree(NODE *root, int space) { 
   if (root == NULL) 
      return; 

   space += COUNT; 

   printTree(root->right, space); 

   printf("\n"); 
   for (int i = COUNT; i < space; i++) 
      printf(" "); 
   printf("%c\n", root->letra); 

   // Process left child 
   printTree(root->left, space); 
} 

//Chamada principal para realizar o output da arvore.
//Código utilizado adaptado de: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void printCall(NODE *root) { 
   printTree(root, 0); 
} 

//MAIN METHOD
int main(){

   //head é a referencia para a lista
   //Inicializa as variáveis necessárias
   NODE *head = NULL;
   NODE *aux = NULL;
   NODE *treeN = NULL;
   NODE *lastTN = NULL;
   NODE *treeRoot = NULL;

   //Vetor para armazenar a contagem de cada caractere lido
   int contagemLetras[5000];
   for(int i = 0; i < 5000; i++){
      //Inicializa a contagem com 0
      contagemLetras[i] = 0;
   }

   //Arquivo a ser lido
   char arquivo[] = "../texts/teste02.txt";

   //Lê o arquivo e armazena as contagems em contagemLetras
   readAndCount(contagemLetras,arquivo);
   
   int count = 0;
   //Bloco que monta a lista encadeada sem ordenar os seus elementos
   for(int i = 0; i < 5000; i++){
      //Percorre todo o vetor com as contagens
      if(contagemLetras[i] != 0){
         //Se houver pelo menos uma ocorrência do caractere
         printf("%c -- %d\n", i,contagemLetras[i]);
         //Cria-se um novo nodo na heap
         NODE* temp = (NODE*) malloc(sizeof (NODE));
         temp->letra = i;
         temp->freq = contagemLetras[i];
         temp->used = false;
         //Se for a primeira iteração, realiza-se a criação do head da lista
         if(count == 0){
            head = temp;
            aux = head;
         }
         //Caso contrário, o nodo da heap é colocado como next do head.
         else{
            aux->next = temp;
            aux = temp;
            //Aux torna-se o novo nodo adicionado
         }
         count++;
         
      }
   }

   //Ordena a lista encadeada criada no bloco anterior.
   //Passa-se se o endereço do head.
   sort(&head);

   //Escreve os elementos da lista encadeada de maneira ordenada.
   struct NODE *toPrint = head;

   while(toPrint->next != NULL){
      printf("%d - %c\n",toPrint->freq,toPrint->letra);
      toPrint = toPrint->next;
   }

   printf("%d - %c\n",toPrint->freq,toPrint->letra);

   struct NODE *treeAux = head;

   //É alocado espaço na heap para armazenar o último nodo da árvore (dois caracteres com menor quantidade)
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

   while((treeAux->next != NULL)){
      struct NODE* new = (NODE*) malloc(sizeof (NODE));
      if((treeAux->freq + treeAux->next->freq) < (treeN->freq + treeAux->freq)){ //Cria um novo TREENODE com o next + atual
         new->freq = treeAux->freq + treeAux->next->freq;
         new->left = treeAux;
         new->right = treeAux->next;
         treeAux->used = true;
         treeAux->next->used = true;
         lastTN = treeN;
         treeN = new;
      }
      else{
         new->freq = treeAux->freq + treeN->freq;
         new->left = treeAux;
         new->right = treeN;
         treeAux->used = true;
         treeAux->next->used = true;
         lastTN = treeN;
         treeN = new;
      }
      treeAux=treeAux->next;
   }

   treeRoot = (NODE*) malloc(sizeof (NODE));;
   treeRoot->freq = lastTN->freq + treeN->freq;
   treeRoot->left = lastTN;
   treeRoot->right = treeN;

   //Output da árvore criada
   printCall(treeRoot); 

   printPreorder(treeRoot,'n'); 

   return 0;
}