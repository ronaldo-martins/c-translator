#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 80



typedef struct Arvore {

       char portugues[TAM];
       char ingles[TAM];
       struct Arvore *direita;
       struct Arvore *esquerda;

       }Arvore;



//FUNÇÕES

Arvore * inserir(Arvore *raiz, char *port, char *ing);
char lerTexto(FILE *arq);
Arvore *lerDicionario(FILE *dicionario, Arvore *raiz);
void traduzir(Arvore *raiz, FILE *arq);
void imprimirTexto(FILE *arq);
void escreverDicionario(FILE *fp, Arvore *raiz);
int contar(FILE *arq);
void leitura (char *, char * );
int menu();
void imprimir(Arvore *raiz);
void escreverTraducao( Arvore *raiz);
Arvore *buscar2(Arvore *raiz, char *portugues);
void InserirNova(char *palavraP, Arvore *raiz);
void buscarLetra(Arvore *raiz, char portugues);






int main(){ 


	FILE *dicionario = NULL, *texto = NULL, *traduzido = NULL;
	char *palavraDicionario;
	char *palavraTexto;
	char palavraBuscar;
	char um[TAM], dois[TAM];
	Arvore *palavra=NULL;
	Arvore *raiz = NULL;
 	Arvore *alocar = NULL;
 	int num1=0, num2=0, flagD=0, opcao=NULL;
 	
 	
 	setlocale(LC_ALL,"");


	 while(1){

    	system("cls");
    	printf("\n		   ***TRADUTOR DE PALAVRAS POTUGUES/INGLES***					");
        opcao = menu();

        switch(opcao){
            case 1 :
            		if(flagD==0){
            	    dicionario = fopen("dicionario.txt", "r");
            		if(raiz==NULL){
            			raiz = lerDicionario(dicionario, raiz);
					}
            		else{
            			lerDicionario(dicionario, raiz);
					}
					fclose(dicionario);
					flagD++;
					}
					else{
						printf("\n O dicionario ja foi carregado");
					}


                printf("\n");
				system("pause");
            	break;

            case 2 :
            	texto = fopen("texto.txt", "r");
            	if(texto){
            		lerTexto(texto);
            	}
				fclose(texto);
				printf("\n");
				system("pause");
            	break;

            case 3:
            	texto = fopen("texto.txt", "r");
            	if(texto){
            		traduzir(raiz, texto);
            	}
            	fclose(texto);
            	printf("\n");
				system("pause");
				break;

            case 4:
            	texto = fopen("texto.txt", "r");
            	if(texto)
           			imprimirTexto(texto);
           		fclose(texto);
          		traduzido = fopen("traduzido.txt", "r");
          		if(traduzido)
           			imprimirTexto(traduzido);
           		fclose(traduzido);
				printf("\n");
				system("pause");
				break;


            case 5:
            	if(raiz==NULL){
            		printf("Raiz nula, carregue o dicionario\n");
            		system("pause");
            		break;
				}
				else{
					printf("\n		  PALAVRAS TRADUZIDAS DA ARVORE DICIONARIO\n");
        	  		imprimir(raiz);
        	  	}

            	texto = fopen("texto.txt", "r");
            	if(texto!=NULL){
            		num1 = contar(texto);
            		printf("\nO texto em portugues tem %d palavras\n", num1);
            	}         
            	fclose(texto);
            	
            	traduzido = fopen("traduzido.txt", "r");
            	if(traduzido!=NULL){
            		num2 = contar(traduzido);
            		printf("\nO texto traduzido tem %d palavras\n", num2-1);
            	}
				fclose(traduzido);	
				printf("\n");
            	system("pause");
                break;


            case 6:
				printf("\nDigite a letra inicial da palavra para busca seletiva\n ->");
				scanf("%s", &palavraBuscar);
				if(raiz!=NULL){
					buscarLetra(raiz, palavraBuscar);
				}
				printf("\n");
				system("pause");
				break;

			case 7:
				printf("\n Digite a palavra\n ->");
                scanf("%s", um);
                printf(" Digite a traducao\n ->");
				scanf("%s", dois);
				dicionario = fopen("dicionario.txt", "w+");
				inserir(raiz, um, dois);
				escreverDicionario(dicionario, raiz);
				fclose(dicionario);
				printf("\n");
				system("pause");
				break;

            case 9 :
                dicionario = fopen("dicionario.txt", "w+");
             	if(raiz!=NULL){
                	escreverDicionario(dicionario, raiz);
            	}
            	fclose(dicionario);
                exit(0);

            default:
                opcao = 0;
                break;
        }
    }
    system("pause");
}

Arvore *buscar2(Arvore *raiz, char *portugues){
			if(raiz==NULL){
				return raiz;
			}
	    
      		if (strcmp(portugues, raiz->portugues)==0){
      			printf("%s ", raiz->ingles);
      			escreverTraducao(raiz);
      			return raiz;
      		}
      		else{
      			if (strcmp(portugues, raiz->portugues)<0){
            		buscar2(raiz->direita, portugues);
            	}
      			else{
      				if (strcmp(portugues, raiz->portugues)>0){
            			buscar2(raiz->esquerda, portugues);
      				}
      				else{
      					return raiz;
				  	}	
            	}
        	}
}

void buscarLetra(Arvore *raiz, char portugues){
	if(raiz==NULL)return;

	buscarLetra(raiz->direita, portugues);
	if((raiz->portugues[0]) == portugues){
		printf("\n %s", raiz->portugues);
		printf(" - %s\n", raiz->ingles);
	}
	buscarLetra(raiz->esquerda, portugues);
}

Arvore *inserir(Arvore *raiz, char *port, char *ing){
		  
			if (raiz==NULL){
			                raiz = (Arvore *) malloc(sizeof(Arvore));
				            if (raiz==NULL){
       				           printf("Falta de memória");
                               system("pause");
       				           exit(0);
            	            }
                			strcpy(raiz->portugues, port);
                			strcpy(raiz->ingles, ing);
                			raiz->esquerda=NULL;
                        	raiz->direita=NULL;
                    		return raiz;
    		}

    			if(strcmp(raiz->portugues,port)<0){
        			raiz->esquerda=inserir(raiz->esquerda,port, ing);
    			}
    			else{
					if(strcmp(raiz->portugues,port)>0){
           				raiz->direita=inserir(raiz->direita,port, ing);
           			}
           			else{
           				return raiz;	
           			}	
       			}
}

char lerTexto(FILE *arq){
		int contLinha;
		char palavra[TAM], linha[100];
	 	if (arq == NULL){
    		printf("Problema na abertura do arquivo\n");
    		return(*palavra);
  		}
  		contLinha = 1;
  		while (!feof(arq)){
      		fgets(linha, 100, arq);
      		strcpy(palavra,linha);
      		if (palavra)
	  			printf("Linha %d : %s\n",contLinha,linha);
      			contLinha++;
  		}
}

Arvore *lerDicionario(FILE *dicionario, Arvore *raiz){

		int contLinha;
		char palavraPortugues[TAM], palavraIngles[TAM], linha[TAM];
	 	if (dicionario == NULL){
    		printf("Problema na abertura do arquivo\n");
    		return NULL;
  		}
  		contLinha = 1;
  		while (!feof(dicionario)){
      		fscanf(dicionario, "%s", palavraPortugues);
      		if (palavraPortugues){
	  			printf("\nPalavra %d : %s  ", contLinha, palavraPortugues);
			}
      		fscanf(dicionario, "%s", palavraIngles);
      		if(palavraIngles){
      			printf("\nTraducao %d : %s\n", contLinha, palavraIngles);
      			contLinha++;
      		}
      		if(raiz==NULL){
    			raiz = inserir(raiz, palavraPortugues, palavraIngles);
    		}
    		else{
    			inserir(raiz, palavraPortugues, palavraIngles);
			}
        }
        return raiz;
        fclose(dicionario);
}

void traduzir(Arvore *raiz, FILE *arq){
		int flag = 0;
		Arvore *offdicionario;
		FILE *traduzido = fopen("traduzido.txt", "w+");
		FILE *dicionario;
		char palavraP[TAM], palavraI[TAM], insere[TAM], linha[TAM];
		
		if(raiz==NULL){
			printf("Raiz nula, importe o dicionario");
			return;
		}
	 	if (arq == NULL){
    		printf("Problema na abertura do arquivo\n");
  			return;
  		}
  		fprintf(traduzido, "");
  		fclose(traduzido);
  		
  		while (!feof(arq)){
      		fscanf(arq, "%s", palavraP);
      		if(raiz==NULL)printf("doidera");
      		if (palavraP){
      			if(raiz==NULL)printf("doidera");
      			offdicionario = buscar2(raiz, palavraP);

      			if(offdicionario==NULL && flag==0){
      				InserirNova(palavraP, raiz);
      				flag++;
      				system("cls");
      				traduzir(raiz, arq);
				}
    
	      	}

		}
		flag=0;
		return;
}

void imprimirTexto(FILE *arq){
		int contLinha;
		char *palavra, linha[100];
		printf("\n");
	 	if (arq == NULL){
    		printf("Problema na abertura do arquivo\n");
    		return;
  		}
  		contLinha = 1;
  		while (!feof(arq)){
      		palavra = fgets(linha, 100, arq);
      		if (palavra)
	  			printf("%s",linha);
      			contLinha++;
  		}
}

void escreverDicionario(FILE *fp, Arvore *raiz){

		if(raiz == NULL)
			return;

    	fprintf(fp,"\n%s\n", raiz->portugues);
    	fprintf(fp,"%s", raiz->ingles);
    	escreverDicionario(fp, raiz->esquerda);
    	escreverDicionario(fp, raiz->direita);
}

void escreverTraducao(Arvore *raiz){
		FILE *fp = fopen("traduzido.txt", "a+");
					
		fprintf(fp, "%s ", raiz->ingles);
    	fclose(fp);
    	return;
}

int contar(FILE *arq){
		int contPalavras;
		char palavra[TAM];
	 	if (arq == NULL){
    		printf("Problema na abertura do arquivo\n");
    		return 0;
 		}
 		else{
  			contPalavras = 0;
  			while (!feof(arq)){
      			fscanf(arq, "%s", palavra);
      	
      			if (palavra){
      				contPalavras++;
      			}
  			}
  			return contPalavras;
  		}
}

void imprimir(Arvore *raiz){
	if(raiz==NULL)return;

	imprimir(raiz->direita);
	printf("\n %s", raiz->portugues);
	printf(" - %s\n", raiz->ingles);
	imprimir(raiz->esquerda);

}

void InserirNova(char *palavraP, Arvore *raiz){
		FILE *texto = fopen("texto.txt","r");
		FILE *dicionario = fopen("dicionario.txt","w+");
		char insere[TAM];
		
			printf("\n\nPalavra: %s nao encontrada no dicionario, insira abaixo a traducao", palavraP);
            printf("\n Digite a traducao\n ->");
			scanf("%s", insere);
			escreverDicionario(dicionario, inserir(raiz, palavraP, insere));
			fclose(dicionario);
			traduzir(raiz, texto);
			fclose(texto);
			return;
}

int menu(){

    int op;
    printf("\n\n   Digite: \n");
    printf("\n '1' Importar dicionario\n '2' Ler texto em portugues\n '3' Traduzir o texto\n '4' Imprimir ambos os textos na tela\n '5' Imprimir arvore alfabeticamente/indicar numero de palavras \n '6' Buscar palavras atraves da inicial\n '7' Inserir nova palavra ao dicionario\n '9' Sair\n -> ");
    scanf("%d",&op);
    if (op < 1 || op > 9)
    {op = 0;}
    return op;
}

