/****************************************************************************/
/************ Joao Daniel Silva 86445, Francisco Sousa 86416 ****************/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************************/
/**************************** Definicao de constantes ***********************/
/****************************************************************************/
#define MAXCHARS 140
#define MAXMSGS 10000
#define MAXUSERS 1000
#define MAXDIGS 3
#define msgFrase(A) forum[A].frase
#define msgID(A) forum[A].id
#define less(A, B) strcmp(A, B) < 0

/*********************************************************************/
/*********** Prototipo de funcoes ****************/
/****************************************************************************/
int leID();//le o numero do user do input
void limpaVetor(int v[],int tamanho); //limpa conteudo do vetor
void adicionaMsg(); //add mensagem ao forum
void leMsg(char str[]);
void ordenaMsg();
void listaMsgs(); //lista todas as mensagens ja submetidas
void listaMsgsID(); //dado um utilizador, imprime todas as frases escritas por ele
void maiorMsg(); //procura a frase mais comprida no forum e imprime-a
void userMaisAtivo(); //imprime no ecra o id do user
void sortAlgoritmo(int aux[], int primsort);
int sortComparacao(int v, int aux_j, int primsort);
void listaMsgsOrd(int ord[]);
void limpaVetor(int v[], int tam);
//VER ABSTRACAO E IDIOMA E ORDEM DAS FUNCOES, 1000 users 3 digitos????

/****************************************************************************/
/*********** Declaracao da estrutura mensagem ****************/
/****************************************************************************/
typedef struct {
	char frase[MAXCHARS+1];
	int id;
	int compr;
} Mensagem;


/****************************************************************************/
/*********** Declaracao de variaveis globais ****************/
/****************************************************************************/
Mensagem forum[MAXMSGS]; //criacao do forum
int contadorAtiv[MAXUSERS+1]; //contadorAtiv guarda o n de msgs por user
int noMsg = 0;
char msg[MAXCHARS+1];

/****************************************************************************/
/*********** Funcoes ****************/
/****************************************************************************/
int main() {
	int done = 0; //variavel de controlo
	char command; //variavel que guarda o commando de cada input
	limpaVetor(contadorAtiv, MAXUSERS); //limpa o vetor que guarda a informacao do numero de mensagens de cada id
	while(!done) {
		scanf("\n%c", &command);
		switch (command) {
			case 'A':
				adicionaMsg(); //adiciona uma mensagem ao forum
				break;
			case 'L':
				listaMsgs(); //imprime no ecra todas as mensagens do forum
				break;
			case 'U':
				listaMsgsID(); //imprime todas as mensagens de um id
				break;
			case 'O':
				maiorMsg(); //procura as mensagens mais longas
				break;
			case 'T':
				if (noMsg){ //se houver mensagens
					userMaisAtivo();
				};
				break;
			case 'S':
				ordenaMsg(); //ordena as mensagens
				break;
			case 'X':
				printf("%d\n",noMsg); //imprime no ecra o numero de mensagens no forum
				done = 1; //altera o valor da variavel de controlo para interromper o ciclo
				break;
			default:
				printf("ERRO: Comando desconhecido\n");
		};
	};
	return 0;
};

int leID(){
	char idstr[3], c; int i = 0;
	getchar(); //limpar espaço
	while ('0' <= (c = getchar()) && c <= '9' && i<3){
		idstr[i++]=c;
	};
	return atoi(idstr);
};

void leMsg(char str[]){
	char c; int i = 0;
	while ((c = getchar())!='\n'){
		str[i++]=c;
	};
};

/* A */
void adicionaMsg() {
	forum[noMsg].id = leID();
	leMsg(forum[noMsg].frase);
    //printf("int: %d\n", forum[noMsg].id);
    //printf("msg: %s\n", forum[noMsg].frase);
	//pede o id do utilizador e a mensagem e adiciona ah estrutura
	contadorAtiv[forum[noMsg].id]++;
	noMsg++;
};

/* L */
void listaMsgs() {
	int i;
	printf("*TOTAL MESSAGES:%d\n", noMsg);
	for(i=0;i<noMsg;i++) { //percorre o vetor que armazena as mensagens e imprime as no ecra
		printf("%d:%s\n",forum[i].id,forum[i].frase);
	};
};

/* U */
void listaMsgsID() {
	int i, id;
	id = leID();
	printf("*MESSAGES FROM USER:%d\n",id);
	for(i=0;i<noMsg;i++) { //procura no vetor forum pelas mensagens do utilizador desejado
		if(forum[i].id==id) {
			printf("%s\n",forum[i].frase);
		};
	};
};

/* O */
void maiorMsg() { //NAO FUNCIONA BEM
	int i,max=0;
	for(i=0;i<noMsg;i++) { //procura a frase com o comprimento maior
		if(forum[i].compr>max) max = forum[i].compr;
	};
	for(i=0;i<noMsg;i++) { //imprime todas as frases que tenham esse comprimento
		if(forum[i].compr==max) {
			printf("*LONGEST SENTENCE:%d:%s\n",forum[i].id,forum[i].frase);
		};
	};
};

/* T */
void userMaisAtivo() {
	int u, j = 0, max = 1, users[noMsg];
	for (u = 0; u < MAXUSERS; u++) { //procura no vetor contador o user mais ativo
		if (contadorAtiv[u] > max) { //se o max for maior que os outros, guarda de novo
			j = 0;
			max = contadorAtiv[u];
			users[j++] = u;
		} else if (contadorAtiv[u] == max){ //se for igual
			users[j++] = u; //regista noutra posicao
		};
	};
	for (u = 0; u < j; u++) {
		printf("*MOST ACTIVE USER:%d:%d\n",users[u],max);
	};
};

//Preenche o vetor v de tamanho tam com zeros
void limpaVetor(int v[], int tam) {
	int i = 0;
	while (i <= tam) {
		v[i++] = 0;
	};
};

void listaMsgsOrd(int ord[]){
	//imprime as mensagens do forum pela ordem ord
    int i;
	printf("*SORTED MESSAGES:%d\n", noMsg);
    for (i = 0; i < noMsg; i++){
        printf("%d:%s\n", forum[ord[i]].id,forum[ord[i]].frase);
    };
};

int sortComparacao(int v, int aux_j, int primsort){
	//se for a primeira vez que corre o sort, compara ids
	//se for a segunda, compara as mensagens
	if (primsort){
		return forum[v].id < forum[aux_j].id;
	} else {
		return less(forum[v].frase, forum[aux_j].frase);
	};
};

void sortAlgoritmo(int aux[], int primsort) {
	int i, j;
	//Dispoe os numeros do vetor auxiliar de forma a que as Mensagem's
	//respectivas estejam ordenadas
    for (i = 1; i <= noMsg-1; i++) {
        int v = aux[i];
        j = i-1;
        while (j >= 0 && sortComparacao(v, aux[j], primsort)) {
            aux[j+1] = aux[j];
            j--;
        };
        aux[j+1] = v;
    };
};

/* S */
void ordenaMsg() {
	int aux[noMsg], i = 0;
	//Cria um vetor auxiliar de numeros ordenados. Cada numero eh o indice de uma
	//Mensagem no vetor forum[]. A ordem deles equivale ah ordem pela qual as
	//Mensagem's aparecem no forum
	while (i < noMsg){
		aux[i] = i;
		i++;
	};
	//Aplica o sort estavel duas vezes ao vetor
	sortAlgoritmo(aux, 1);
	sortAlgoritmo(aux, 0);
	listaMsgsOrd(aux);
};
