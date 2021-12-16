#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>
#include "pilha_de.h"
#include "listale.h"
#define MAX 52

	//=======================================//
	//Função Criar Cartas
void criar_cartas(tp_carta carta[MAX],int valor[13],char cor[4]){

	int i=0;
        for(int j=0;j<4;j++){

        	for(int k=0;k<13;k++){
        		carta[i].numero=valor[k];
        		carta[i].naipe=cor[j];
        		carta[i].mostrar=0;
        		i++;
			}
		}	
}
	
	//=======================================//
	//Embaralha Cartas
void embaralha_cartas(tp_carta carta[MAX]){
	
	for(int m=0;m<52;m++){
			tp_carta aux;
			int n = rand()%52;
			aux = carta[m];
			carta[m] = carta[n];
			carta[n] = aux;
		}
}

    //=======================================//
    //Preencher Monte/Cave
void preenche_monte(tp_carta carta[MAX],tp_pilha montes[2]){
	for(int b=0;b<24;b++){
			carta[b].mostrar=1;
			push(&montes[0],carta[b]);
		}
		//imprime_pilha(montes[1]);
}    
	
	//=======================================//
	//Preencher Mesa
void preenche_mesa(tp_carta carta[MAX],tp_pilha pilhas_mesa[7]){
    carta[24].mostrar=1;
	push(&pilhas_mesa[0],carta[24]);
		for(int x=1;x<3;x++){
			if(x==2){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[1],carta[24+x]);	
		}
		for(int x=3;x<6;x++){
			if(x==5){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[2],carta[24+x]);	
		}
		for(int x=6;x<10;x++){
			if(x==9){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[3],carta[24+x]);	
		}
		for(int x=10;x<15;x++){
			if(x==14){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[4],carta[24+x]);	
		}
		for(int x=15;x<21;x++){
			if(x==20){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[5],carta[24+x]);	
		}
		for(int x=21;x<28;x++){
			if(x==27){
				carta[24+x].mostrar=1;
			}
			push(&pilhas_mesa[6],carta[24+x]);	
		}
}

//função comparar
int compara_carta_mesa(tp_pilha *pilha_mov,tp_pilha *p){
	tp_item e1,e2;
	top(pilha_mov,&e1);
	top(p,&e2);
	if((pilha_vazia(p)==1)&&(e1.numero==13)){
		//sucesso
		while(pilha_vazia(pilha_mov)!=1){
			pop(pilha_mov,&e1);
			push(p,e1);	
		}
		return 1;
	}
	else if (((((e1.naipe)=='P')||((e1.naipe)=='E'))&&(((e2.naipe)=='O')||((e2.naipe)=='C')))||((((e2.naipe)=='P')||((e2.naipe)=='E'))&&(((e1.naipe)=='O')||((e1.naipe)=='C')))){
		if(e1.numero==(e2.numero)-1){
			while(pilha_vazia(pilha_mov)!=1){
				pop(pilha_mov,&e1);
				push(p,e1);	
				//sucesso	
			}
			return 1;	
		}
		else{
			//insucesso
			return 0;
		}
	}
	else{
		//insucesso
		return 0;
	}
	
}

int comparar_carta_final(tp_pilha *pilha_mov,tp_pilha *p){
	tp_item e1,e2;
	top(pilha_mov,&e1);
	top(p,&e2);
	if(altura_pilha(pilha_mov)==1){
		if(pilha_vazia(p)==1){
			if(e1.numero==1){
				pop(pilha_mov,&e1);
				push(p,e1);
				return 1;
			}
			else{
				return 0;	
			}	
		}
		else if((e1.naipe==e2.naipe)&&(e1.numero==(e2.numero)+1)){
			pop(pilha_mov,&e1);
			push(p,e1);
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}
//Função de movimento
int Movimentar(tp_pilha pilhas_mesa[7], tp_pilha pilha_final[4], tp_pilha pilha_mov){
	tp_item e;
	int b=-1;
	while((b<0)||(b>1)){
		printf("\n\n Escolha entre jogar nas mesas ou nas finais");
		printf("\n Digite aqui 0 para as mesas ou 1 para as finais: ");
		scanf("%d",&b);	
	}
	if(b==0){
		int b=0;
		while((b<1)||(b>7)){
			printf("\n\n Escolha em qual coluna jogar");
			printf("\n Digite aqui a coluna de 1 a 7: ");
			scanf("%d",&b);	
		}
		
	 	if(compara_carta_mesa(&pilha_mov,&pilhas_mesa[b-1])!=1){
	 		return 0;
		 }
		 else{
		 	return 1;
		 }
	}
	else{
		int b=0;
		while((b<1)||(b>4)){
			printf("\n\n Escolha em qual das pilhas finais jogar");
			printf("\n Digite aqui a coluna de 1 a 4: ");
			scanf("%d",&b);	
		}
		if(comparar_carta_final(&pilha_mov,&pilha_final[b-1])!=1){
	 		return 0;
		 }
		 else{
		 	return 1;
		 }
	}
}

void jogar_montes(tp_pilha montes[2], tp_pilha pilhas_mesa[7], tp_pilha pilha_final[4], tp_pilha pilha_mov){
	
		 	//monte 0 e 1 vazio
		 if((pilha_vazia(&montes[1])==1)&&(pilha_vazia(&montes[0])==1))	{
		 	printf("\n\n Não há nada nos montes.");
		 }
		 else{
		 	//monte 1 vazio
		 	if((pilha_vazia(&montes[1])==1)){
			 	tp_item cav;
			 	pop(&montes[0],&cav);
			 	push(&montes[1],cav);
		 	}
		 	//monte 0 vazio
			else if(pilha_vazia(&montes[0])==1){
			    int b=-1;
			    while((b<0)||(b>1)){
			    	printf("\n\n Digite 0 para pegar carta ou 1 para restaurar o monte 0");
		 		    printf("\n Digite aqui: ");
					 scanf("%d",&b);	
				}
				//monte 0 vazio e restaura o monte 0
				if(b==1){
					while(pilha_vazia(&montes[1])!=1){
			 			tp_item cav;
			 			pop(&montes[1],&cav);
			 			push(&montes[0],cav);
					}
				}
				//monte 0 vazio e pega carta do monte 1
				else{
					tp_item cav;
			 		pop(&montes[1],&cav);
			 		push(&pilha_mov,cav);
			 		if(Movimentar(pilhas_mesa, pilha_final, pilha_mov)!=1){
			 			pop(&pilha_mov,&cav);
			 			push(&montes[1],cav);	
					}
				}
			 	
			}
			// monte 0 e 1 não vazio 
			else{
				int b=-1;
			    while((b<0)||(b>1)){
			    	printf("\n\n Digite 0 para desempilhar o monte0 ou 1 para cavar a carta no topo do monte1");
		 		    printf("\n Digite aqui: ");
					 scanf("%d",&b);	
				}
				//desempilhar o monte 0
				if(b==0){
					tp_item cav;
			 		pop(&montes[0],&cav);
			 		push(&montes[1],cav);	
				}
				//cavar o monte 1
				else{
					tp_item cav;
			 		pop(&montes[1],&cav);
			 		push(&pilha_mov,cav);
			 		if(Movimentar(pilhas_mesa, pilha_final, pilha_mov)!=1){
			 			pop(&pilha_mov,&cav);
			 			push(&montes[1],cav);	
					}
				}
			}	
		}
	
}

void jogar_mesa(tp_pilha pilhas_mesa[7], tp_pilha pilha_final[4], tp_pilha pilha_mov){
		int b=0;
		while((b<1)||(b>7)){
			printf("\n\n Escolha de qual coluna deseja retirar ");
			printf("\n Digite aqui a coluna de 1 a 7: ");
			scanf("%d",&b);	
		}
		if(pilha_vazia(&pilhas_mesa[b-1])==1){
			printf("\n\nPilha vazia");
		}
		else{
			int c=0;
			
				printf("\n Escolha quantas cartas deseja retirar da coluna escolhida");
				printf("\n Digite a quantidade aqui: ");
				scanf("%d",&c);	
				if((c<1)||(c>13)){
					printf("\n Lembre-se,se o número de cartas que deseja retirar for maior que o permitido não será considerado o movimento");
					printf("\n O número máximo de cartas que pode ser retirada da coluna vai de 1 a 13 cartas e elas precisam estar à mostra");
				}
				else{
					
					for(int i=0;i<c;i++){
						
						tp_item e;
						top(&pilhas_mesa[b-1],&e);
						if(e.mostrar==1){
							pop(&pilhas_mesa[b-1],&e);
							push(&pilha_mov,e);
						}
						else{
							printf("\nExcedeu o máximo de cartas disponiveis");
						}
					}
					if(Movimentar(pilhas_mesa, pilha_final, pilha_mov)!=1){
						while(pilha_vazia(&pilha_mov)!=1){
							tp_item e;
							pop(&pilha_mov,&e);
			 				push(&pilhas_mesa[b-1],e);
						}	
					}
					else{
						tp_item e;
						pop(&pilhas_mesa[b-1],&e);
						e.mostrar=1;
						push(&pilhas_mesa[b-1],e);
					}
				}
				
		}
}


void jogar_final(tp_pilha pilhas_mesa[7], tp_pilha pilha_final[4], tp_pilha pilha_mov){
		int b=0;
		while((b<1)||(b>4)){
			printf("\n\n Escolha em qual das pilhas finais retirar");
			printf("\n Digite aqui a coluna de 1 a 4: ");
			scanf("%d",&b);	
		}
		
		if(pilha_vazia(&pilha_final[b-1])==1){
			printf("\n\nPilha vazia");
		}
		else{
			tp_item cav;
			pop(&pilha_final[b-1],&cav);
			push(&pilha_mov,cav);
			if(Movimentar(pilhas_mesa, pilha_final, pilha_mov)!=1){
				pop(&pilha_mov,&cav);
				push(&pilha_final[b-1],cav);	
			}
			
		}
		
}

void jogar(tp_pilha montes[2], tp_pilha pilhas_mesa[7], tp_pilha pilha_final[4], tp_pilha pilha_mov){
tp_listase *lista1; lista1=inicializa_listase(); 
tp_item topo;
    while((pilha_cheia(&pilha_final[0])==0)||(pilha_cheia(&pilha_final[1])==0)||(pilha_cheia(&pilha_final[2])==0)||(pilha_cheia(&pilha_final[3])==0)){
       
	   //=======================================//
	   //Mostrar altura do monte
	   printf("=======================================");
	   printf("\nMonte0[%d]",altura_pilha(&montes[0]));
	   //Mostrar a carta do segundo monte
	   if(pilha_vazia(&montes[1])!=1){
	   	    top(&montes[1],&topo);
	   		printf(" Monte1[%d(%c)]",topo.numero, topo.naipe);
	   }
	   else{
	   		printf("Monte1[ ]\n");
	   }
	   //=======================================//
	   //Estrutura dinamica
	   int u=1; 
		while(listase_vazia(lista1)!=1){
			
			remove_listase(&lista1,u);
			u++;
		}
	    int o=1;
	   	for(int u=0;u<4;u++){
	   	    
	   		if(pilha_cheia(&pilha_final[u])==1){
	   			insere_listase_no_fim(&lista1,o);
	   			o++;
	   		}
	   	}
	   printf("\n %d pilhas finais completas.",tamanho_listase(lista1)); 
	    
	   //=======================================//
	   //Mostrar pilhas finais
	   	printf("\n\nPilhas finais");
	   for(int b=0;b<4;b++){
		   	if(pilha_vazia(&pilha_final[b])!=1){
		   		tp_item topo;
		   		top(&pilha_final[b],&topo);
		   		printf(" [%d(%c)]",topo.numero, topo.naipe);
			   }
			else{
			  	printf("[ ]");
			}
	    } 
	    
		//=======================================//
	    //Mostrar mesa
	    for(int b=0;b<7;b++){
			printf("\n\nColuna %d: ",b+1);
			imprime_pilha(pilhas_mesa[b]);
		}
		
		//=======================================//
		//Menu para jogar  
		 int b=-1;
		 while((b<0)||(b>2)){
		 	printf("\n\n Digite 0 para pegar algo dos montes,1 para as colunas ou 2 para as finais");
		 	printf("\n Digite aqui: ");
		 	scanf("%d",&b);
		 }
		 //=======================================//
		 //Mexer nos montes
		 if(b==0){
		 	jogar_montes(montes, pilhas_mesa, pilha_final,  pilha_mov);
		}
		//=======================================//
		 //Mexer na mesa
		 else if(b==1){
		 	jogar_mesa(pilhas_mesa, pilha_final,  pilha_mov);
		 }
		 //=======================================//
		 //Mexer nas pilhas finais
		 else{
		 	jogar_final(pilhas_mesa, pilha_final,  pilha_mov);
		 }
		 
		 
		 system("cls");
			
}
printf("\n\nPARABÉNS, VOCÊ VENCEU!");

}
		
int main(){setlocale(LC_ALL,"portuguese");
  
    //Designa quantidade de itens dentro de cada objeto...		
	tp_carta carta[52];
	char naipe[4];
    
	//=======================================//
	    
	    //Designar valores e naipes	    
        int valor[13]={1,2,3,4,5,6,7,8,9,10,11,12,13};
        char cor[4]={'E','C','P','O'};
    
	//=======================================//

	    //Criar Cartas
	    criar_cartas(carta,valor,cor);
	    //Embaralha Cartas
        embaralha_cartas(carta);

	//=======================================//
		
		//Cria e inicializa decks
		tp_pilha montes[2], pilhas_mesa[7], pilha_final[4], pilha_mov;
		
		inicializa_pilha(&pilha_mov);
		for(int b=0;b<2;b++){
			inicializa_pilha(&montes[b]);	
		}
		for(int b=0;b<7;b++){
			inicializa_pilha(&pilhas_mesa[b]);	
		}
		for(int b=0;b<4;b++){
			inicializa_pilha(&pilha_final[b]);	
		}
	
	//=======================================//
	
	    //Preencher Monte/Cave
		preenche_monte(carta,montes);
		//Preencher Mesa		
	    preenche_mesa(carta,pilhas_mesa);

	//=======================================//
	
	int menu;
	printf("Bem-vindo ao Jogo paciencia!\n\n");  
	printf("Escolha a opção que deseja!\n\n");           
	printf("1 - Instruções\n2 - Iniciar Jogo\n3 - Créditos\n4 - Exit\n");
	scanf("%d", &menu);
	
	while(menu!=4){
		switch(menu){
		case 1: printf("O jogo inicia-se com todas as peças embaralhadas e sobrepostas umas sobre as outras (são 7 montes com números diferentes de cartas e o estoque contendo o restante das cartas). O objetivo de jogo é mover todas as 52 cartas para as funções em ordem crescente de cada naipe. O jogador pode colocar as cartas nas pilhas de forma alternada de cores e ao acessar o estoque, ele só pode movimentar a carta mais à direita (são três cartas). O jogo termina se o jogador conseguir preencher completamente as fundações dos 4 naipes.");
		break;
		case 2: jogar(montes, pilhas_mesa, pilha_final, pilha_mov);
		menu=4;                                    
		break;
		case 3: printf("Jogo da Mémoria em C desenvolvido por Lucca Tourinho, João Carvalho, Ian Rezende e Sophia Leite , estudantes do Centro Universitário SENAI Cimatec.\nOrientados pelo Professor Márcio Soussa.\nObrigado por Jogar!!");
		break;
		case 4: return 0;
		break;
		}
		scanf("\n%d", &menu);
	}
     
    return 0;
}
