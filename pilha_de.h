#ifndef PILHA_DE_H
#define PILHA_DE_H

#include <stdio.h>
#define MAX 52
#define TRUE 1
#define FALSE 0

//=======================================//

	//Estrutura da Carta
	typedef struct{
		    int numero;
	    	char naipe;
	    	int mostrar;
		    }tp_carta;
			 
	typedef tp_carta tp_item;

//=======================================//
		 	 	 
typedef struct {
	int topo;
	tp_item item[MAX];
} tp_pilha;

//Inicializa a pilha
void inicializa_pilha(tp_pilha *p) {
   p->topo = -1;	
}

//Verifica se a pilha está vazia
int pilha_vazia(tp_pilha *p){
	if (p->topo == -1) return TRUE; //TRUE
	return FALSE;  //FALSE
}

//Verifica se a pilha está cheia
int pilha_cheia(tp_pilha *p){
	if (p->topo == MAX-1) return TRUE; //TRUE
	return FALSE;  //FALSE
}

//Insere um elemento na pilha
int push(tp_pilha *p, tp_item e){
	if (pilha_cheia(p)==TRUE) return FALSE; // Insucesso
	p->topo++;
	p->item[p->topo]=e;
	return TRUE;  //Sucesso
}

//Remove um elemento da pilha
int pop(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)==TRUE) return FALSE; //Insucesso
	*e=p->item[p->topo];
	p->topo--;
	return TRUE; //Sucesso
}

//Verifica o elemento que está no topo sem desempilhar
int top(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)==TRUE) return FALSE;
	*e=p->item[p->topo];
	return TRUE;
}

//Verificar altura
int altura_pilha(tp_pilha *p){
	return p->topo+1;
}

//imprimir pilha
void imprime_pilha(tp_pilha p){
	tp_item e; tp_pilha aux; inicializa_pilha(&aux);
	if(pilha_vazia(&p)==TRUE){
		printf(" [ ]");
	}
	else{
	
	pop(&p,&e);
	e.mostrar=1;
	push(&p,e);
	
	while (pilha_vazia(&p)==FALSE){
		 pop(&p, &e);
		 push(&aux,e);	 
	}
	while (pilha_vazia(&aux)==FALSE){
		 pop(&aux, &e);
		 if(e.mostrar==0){
		 	printf(" [X]");
		 }
		 else{
		    printf(" [%d(%c)]",e.numero, e.naipe);	
		 }	 
	}
	}		 
}

#endif
