#ifndef LISTALE_H
#define LISTALE_H

#include<stdio.h>
#include <stdlib.h>
		 
typedef int tp_it;

typedef struct tp_no{
  tp_it info;
  struct tp_no *prox;
} tp_listase;

tp_listase *inicializa_listase(){
		return NULL;
	}
	
int listase_vazia(tp_listase *lista){
	if(lista==NULL) return 1;
	return 0;
}

tp_listase *aloca_listase(){ // ela irá alocar um espaço na memória;
	tp_listase *novo_no;
	novo_no=(tp_listase*) malloc(sizeof(tp_listase));
	return novo_no;
}


int insere_listase_no_fim(tp_listase **lista, tp_it e){ // Esse **l é um ponteiro que está apontando para outro ponteiro para o endereço de memória original da listase*, o que está apontando para o NULL
tp_listase *novo_no, *atu;
novo_no=aloca_listase(); // aqui está pegando o novo nó e apontando para o NULL;
if(novo_no==NULL) return 0; // Não alocou memória
// atribuir os valores para o novo nó;
novo_no->info= e;
novo_no->prox=NULL;
//finaliza o encadeamento do nó
if(listase_vazia(*lista)){
*lista=novo_no;
} else{
	atu = *lista;
	while(atu->prox!=NULL){ 
	  atu=atu->prox; // aponta para o ultimo nó
	}
	atu->prox=novo_no;	
}
return 1;
}

void imprime_listase(tp_listase *lista){
	tp_listase *atu;
	atu=lista;
	while(atu!=NULL){
		printf("%d\n", atu->info);
		atu=atu->prox;
	}
}

int tamanho_listase(tp_listase *lista){
	int cont=0;
	tp_listase *atu;
	atu=lista;
	while(atu!=NULL){
		cont++;
		atu=atu->prox;
	}
	return cont;
}

int remove_listase(tp_listase **lista,tp_it e){
	tp_listase *ant, *atu;
	atu=*lista;
	ant=NULL;
	while((atu!=NULL)&&(atu->info!=e)){
		ant=atu;
		atu=atu->prox;
	}
	if(atu==NULL)return 0;
	if(ant==NULL){
		*lista=atu->prox;
	}
	else{
		ant->prox=atu->prox;
	}
	free(atu);
	atu=NULL;
	return 1;
}

tp_listase *busca_listase(tp_listase *lista, tp_it e){
	tp_listase *atu;
	atu=lista;
	while((atu!=NULL)&&(atu->info!=e)){
		atu=atu->prox;
	}
	if(atu==NULL) return NULL;
	return atu;
}

void destroi_listase(tp_listase **i){
	tp_listase *atu;
	atu=*i;
	while(atu!=NULL){
		*i=atu->prox;
		free(atu);
		atu=*i;
	}
	*i=NULL;
}

int quan_tida_de(tp_listase *lista,int n){
	int cont=0;
	tp_listase *atu;
	atu=lista;
	while(atu!=NULL){
		if(n<atu->info){
			cont++;
		}
		atu=atu->prox;
	}
	return cont;
}

int comp_arar(tp_listase *l1,tp_listase *l2){
    if(tamanho_listase(l1)!=tamanho_listase(l2)) return 0;
	tp_listase *atu1,*atu2;
	atu1=l1;
	atu2=l2;
	while(atu1!=NULL){
		if(atu1->info!=atu2->info)return 0;
			atu1=atu1->prox;
			atu2=atu2->prox;
		}
    return 1;
	}
	
void lista_circular	(tp_listase *l1,tp_listase *l2){
	tp_listase *atu1,*atu2;
	atu1=l1;
	atu2=l2;
	while(atu1->prox!=NULL){
			atu1=atu1->prox;
		}
		atu1->prox=l2;
	while(atu1->prox!=NULL){
		atu2=atu2->prox;
	}
	atu2->prox=l1;
	l1=l2;
	}
	
	
	
int *dividir_lista(tp_listase *lista,tp_listase *lista2 ,tp_it e){
	tp_listase *atu;tp_listase *ant;tp_it d;
	atu=lista;ant=NULL;
	while((atu!=NULL)&&(atu->info!=e)){
		ant=atu;
		atu=atu->prox;
	}
	if(atu==NULL){
		printf("\n Valores na lista 1\n");
		imprime_listase(lista);
		printf("\n Valores na lista 2");
		imprime_listase(lista2);
	}
	else{
		
	    
	    	ant=atu;
		    atu=atu->prox;
	    while(atu!=NULL){
	    	d=atu->info;
	    	insere_listase_no_fim(&lista2,d);
	    	atu=atu->prox;
		}	
	    ant->prox=NULL;	
		
		
	free(atu);
	atu=NULL;
	printf("\n Valores na lista 1\n");
		imprime_listase(lista);
		printf("\n Valores na lista 2\n");
		imprime_listase(lista2);
	}

}
#endif
