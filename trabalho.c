#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct arquivobin{
	
	char index[7];
	char anoNascimento[5];
	char nome[12];
	char sexo [2];
	char quantidade[7];
	
}LINHA;

typedef struct lista{
	struct lista *prox;
	LINHA infos;
	
}LISTA;



// OBRIGATORIOS

void pesquisa_binaria(FILE *file1, char indice[50]){
	
	LINHA p;
	
	int inicio, meio, fim;
	
	inicio = 0;
	
	fim = (calcula_tamanho(file1)/sizeof(LINHA))-1;	
	
	while(inicio <=fim){
		meio = (inicio+fim)/2;
		fseek(file1, meio*sizeof(LINHA),SEEK_SET);
		fread(&p, sizeof(LINHA),1,file1);
			
		if(strcasecmp(indice,p.index)>0){
			inicio = meio+1;
			
		}else if(strcasecmp(indice,p.index)<0){
			fim = meio-1;
		}else{

			printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", p.index, p.anoNascimento, p.nome, p.sexo, p.quantidade);
		
			break;	
		}
	}
}

	

void consulta_dado(char indice[7]){
	
	FILE *file;
	file = fopen("binario.dat","rb");
	
	
	pesquisa_binaria(file,indice);
	
}


void gerar_arqbin(){
		
	FILE *file1;
	FILE *file2;
	
	char linha[sizeof(LINHA)];
	int i;
	LINHA p;
	LINHA c;
	file1 = fopen("textoArquivo.txt", "r");
	file2 = fopen("binario.dat","wb");	
	
	while(fscanf(file1,"%s %s %s %s %s", p.index, p.anoNascimento, p.nome, p.sexo, p.quantidade)!=-1){
	
	int tam = strlen(p.nome);

	for(i=tam;i<12;i++){
		if(i==11){
			p.nome[i] = '\0';
		}
		else{
				p.nome[i]=' ';		
		}
	}

	fwrite(&p,sizeof(LINHA),1,file2);

	}
		
}

void mostrar_dados(FILE *file2){
	
	LINHA c;
	
	while(fread(&c,sizeof(LINHA),1,file2)){
		
		printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", c.index, c.anoNascimento, c.nome, c.sexo, c.quantidade);

	}

}

int calcula_tamanho(FILE *file1){
	
	int tam;
	
	if(file1==NULL){
		return 0;
	}
	
	fseek(file1,0,SEEK_END);
	
	tam = ftell(file1);
	
	return tam;
	
}


// ARQUIVO

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void criarArquivoIndiceChaveUM(FILE *file1, int valor){
		
		LINHA c;
		
		FILE *file2;
		
		char ind[7];
		
		file2 = fopen("arquivoChaveUM.txt","w");
		
		while(fread(&c,sizeof(LINHA),1,file1)){	
		
		int val = atoi(c.quantidade);
		
		if(val>valor){
		
		strcpy(ind,c.index);
		
		fprintf(file2, "%s\n",c.index);
		
		}	
		
	}
	
}



void mostraOsnomesmaisdeX(){
	
		
		FILE *file1;	
		file1 = fopen("arquivoChaveUM.txt","r");
	
		FILE *file3;	
		file3 = fopen("binario.dat","rb");
		
		LINHA c;
		
	
		char indice[7];
		
	while(fscanf(file1, "%s\n", indice)!=EOF){	
		 
		int pos = atoi(indice);
		
		fseek(file3, pos*sizeof(LINHA),SEEK_SET);
		
		fread(&c, sizeof(LINHA),1,file3);		
				
		printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", c.index, c.anoNascimento, c.nome, c.sexo, c.quantidade);
	}


	
}


void mostrarporsexo(char sexo[2]){
		
		printf("aqui: %s", sexo);
		
		FILE *file1;	
		file1 = fopen("arquivomulheres.txt","r");
		
		FILE *file2;	
		file2 = fopen("arquivohomens.txt","r");	
	
		FILE *file3;	
		file3 = fopen("binario.dat","rb");
			
	
	LINHA c;
	char indice[7];
	char s[2];
	
	if(strcasecmp(sexo,"M")==0){
	
		while(fscanf(file2, "%s %s\n", indice,s)!=EOF){	
		 
			int pos = atoi(indice);
			
			printf("%s\n", indice);
			
//			printf("pos: %d\n", pos);
		
			fseek(file3, pos*sizeof(LINHA),SEEK_SET);
		
			fread(&c, sizeof(LINHA),1,file3);		
				
			printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", c.index, c.anoNascimento, c.nome, c.sexo, c.quantidade);
		
		}
	}
	else{
		while(fscanf(file1, "%s %s\n", indice,s)!=EOF){	
		 
			int pos = atoi(indice);
		
			printf("%s\n", indice);
			printf("pos: %d\n", pos);
		
			fseek(file3, pos*sizeof(LINHA),SEEK_SET);
		
			fread(&c, sizeof(LINHA),1,file3);		
				
			printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", c.index, c.anoNascimento, c.nome, c.sexo, c.quantidade);
		
		}
	
	}
}


void ordenamulheres(FILE *file1){
		
		LINHA p;
		
	
		FILE *file2;
		
		file2 = fopen("arquivomulheres.txt","w");
	
		while(fread(&p,sizeof(LINHA),1,file1)){
		
		if(strcasecmp(p.sexo,"F")==0){
		
		fprintf(file2,"%s %s\n", p.index, p.sexo);
		
		}
	}
	
}

void ordenahomens(FILE *file1){
		
		LINHA c;
		
		FILE *file2;
		
		file2 = fopen("arquivohomens.txt","w");
		
		while(fread(&c,sizeof(LINHA),1,file1)){	
	
		if(strcasecmp(c.sexo,"M")==0){
			
		fprintf(file2,"%s %s\n", c.index, c.sexo);
		
		}
		
	}
	
}

void ordenasexo(char sexo[2]){
	
	if(strcasecmp(sexo,"M")==0){

		mostrarporsexo(sexo);

	}else{

		mostrarporsexo(sexo);

	}
	
}



// ------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------------

// MEMÓRIA

void vetor_lista(LISTA *vet[26]){
	
	FILE *file1;
	
	file1 = fopen("binario.dat", "rb");
	
	LINHA c;
	
	while(fread(&c,sizeof(LINHA),1,file1)){	

	int valor = atoi(c.anoNascimento);
	
	int index = valor - 1880;
	
	LISTA *nodo = (LISTA *)malloc(sizeof(LISTA)); 
	
	if(vet[index]==NULL){	
		vet[index] = nodo;	
		nodo->infos = c;
		nodo->prox = NULL;
	}else{
		
		LISTA *aux = vet[index];
		
		while(aux->prox!=NULL){
    		aux=aux->prox;
		}	
			
		aux->prox=nodo;
		nodo->infos = c;
		nodo->prox = NULL;
			
		}

	}

}

LISTA *busca_no_vetor_indices_fim(LISTA *vet){
	
		return vet;
}
	
int numero_de_vezes(LISTA *vet){
	
	int cont = 1;
	
	while(vet->prox!=NULL){
    		vet=vet->prox;
		cont++;
		}
	
	return cont;
	
}

void pesquisabinvet(char *indice, int cont){
 	
	FILE *file1;
	
	file1 = fopen("binario.dat","rb");
	
	int inicio, meio, fim;
	
	LINHA p;
	LINHA c;
	
	inicio =0;

	fim = (calcula_tamanho(file1)/sizeof(LINHA))-1;
	
	while(inicio<=fim){	
		meio = (inicio+fim)/2;
		fseek(file1, meio*sizeof(LINHA), SEEK_SET);
		fread(&p,sizeof(LINHA),1,file1);
		if(strcasecmp(indice,p.index)>0){
			inicio= meio+1;
		}
		else if(strcasecmp(indice,p.index)<0){
				
					fim = meio-1;
			}
			else{
				
				printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", p.index, p.anoNascimento, p.nome, p.sexo, p.quantidade);
				
				while(fread(&c,sizeof(LINHA),1,file1)){
				
				if(strcasecmp(p.anoNascimento,c.anoNascimento)==0){
					printf("Index: %s\nAno nascimento: %s \nNome: %s \nSexo: %s \nquantidade: %s\n\n", c.index, c.anoNascimento, c.nome, c.sexo, c.quantidade);
					cont--;
					
					}

				}
	
			break;	
		
		}
				
	}
	
}

void busca_usando_Vetores(LISTA *vet[136], int ano){
	
	int index = ano - 1880;
	
	int	reg = numero_de_vezes(vet[index]);
	
	LISTA *c = busca_no_vetor_indices_fim(vet[index]);
	
	char indice[7];
	
	strcpy(indice,c->infos.index);
	
	pesquisabinvet(indice, reg);
		
}

void escreve_lista_alfa(LISTA *vet){
	
while(vet!=NULL){


	printf("Nome: %s \n ", vet->infos.nome);
	vet =vet->prox;
	
	}
	
}


void vetorlistaalfabetico(LISTA *vetalfa[26]){
	
	int i = 0;
	
	FILE *file1;
	
	file1 = fopen("binario.dat", "rb");
	
	LINHA c;
	
	while(fread(&c,sizeof(LINHA),1,file1)){	

	int index = toupper(c.nome[0])-'A';
	

	
	LISTA *nodo = (LISTA *)malloc(sizeof(LISTA)); 
	
	if(vetalfa[index]==NULL){	
		vetalfa[index] = nodo;	
		nodo->infos = c;
		nodo->prox = NULL;

	}else{
		
		LISTA *aux = vetalfa[index];
		
		while(aux->prox!=NULL){
    		aux=aux->prox;
		}	
			
		aux->prox=nodo;
		nodo->infos = c;
		nodo->prox = NULL;

			i++;
		}

	}

}



//PERGUNTAS

// ---------------------------------------------------------------------------------------------------------------------------

void escreve_nome_comum(LISTA *vet){

	
	int mais=0;
	LISTA *c;
	
while(vet!=NULL){
	
	int val = atoi(vet->infos.quantidade);
	
	if(mais<val){
		
		c = vet;
		mais = val;
	}
	
	vet =vet->prox;
	
	}
	
	printf("Nome: %s \nQuantidade: %s\n", c->infos.nome, c->infos.quantidade);

}


void nome_mais_ocorrencia_ano(LISTA *vet[136], int ano){
	
	int index = ano - 1880;
	printf("Ano: %d\n", ano);
	escreve_nome_comum(vet[index]);
	
}

// ---------------------------------------------------------------------------------------------------------------------------

void escreve_lista(LISTA *vet){

	
while(vet!=NULL){


	printf("Nome: %s \n ", vet->infos.nome);
	vet =vet->prox;
	
	}
	
}


void todos_nomes_ano(LISTA *vet[136], int ano){
	
	int index = ano - 1880;
	
	escreve_lista(vet[index]);
	
	
}


// ---------------------------------------------------------------------------------------------------------------------------

// inciar VETOR

void inicializa_vet(LISTA *vet[136]){
		
	int i;
	for(i=0; i<136; i++){
			
		vet[i] = NULL;
	
	}
	
}

// inciar VETOR alfa

void inicializa_vet_alfa(LISTA *vet[26]){
		
	int i;
	for(i=0; i<26; i++){
			
		vet[i] = NULL;
	
	}
	
}


// ---------------------------------------------------------------------------------

int main(){	
	
	FILE *file = fopen("binario.dat", "r");
	
	if(file==NULL){
		
		gerar_arqbin();
		
	}
	
	
/*		
//	 OBRIGATORIOS	


----------------------------------------------------------------------------------------------------
	
//		consulta de 000000 até 224691
	
		consulta_dado("178923");
		
		mostrar_dados(file1);
	
		calcula_tamanho(arquivo de parametro);

*/

/*

// INDICE ARQUIVO


------------------------------------------------------------------------------------------------------	
		
		FILE *file1;
		file1 = fopen("binario.dat", "rb");
		criarArquivoIndiceChaveUM(file1, 5000);

		mostraOsnomesmaisdeX();	
		
-------------------------------------------------------------------------------------------------------
	
		FILE *file1;
		FILE *file2;
	
		file1 = fopen("binario.dat","rb");
		file2 = fopen("binario.dat","rb");
			
		ordenamulheres(file1);	
		ordenahomens(file2);
	
		ordenasexo("m");
	
------------------------------------------------------------------------------------------------------

*/



/*


//	 INDICE MEMORIA
--------------------------------------------------------------------------------------------------
	
//	vetor de lista ano
	
		LISTA *vet[136];
		inicializa_vet(vet);
		vetor_lista(vet);

		busca_usando_Vetores(vet,1880); // MOSTRA TODOS OS NOMES USANDO O ANO COMO INDICE

--------------------------------------------------------------------------------------------------
		
//		vetor de lista nome
		
		LISTA *vetalfa[26];
		inicializa_vet_alfa(vetalfa);
		vetorlistaalfabetico(vetalfa);
		
		// alterar o primeiro A para a letra (MAIUSCULA) que quiser
		
		int index  = 'A' - 'A';
		
		escreve_lista_alfa(vetalfa[index]);

--------------------------------------------------------------------------------------------------

*/
		
		
/*		
	 PERGUNTAS
----------------------------------------------------------------------------------------------------	
	 
//	PRECISA CRIAR OS VETORES POR ANO
		
	LISTA *vet[136];
	inicializa_vet(vet);
	vetor_lista(vet);
	
	todos_nomes_ano(vet,1880);	
	
	nome_mais_ocorrencia_ano(vet, 2015);
	
----------------------------------------------------------------------------------------------------
*/ 
	return 0;

}




