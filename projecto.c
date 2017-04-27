/****************************************************************************/
/************ Joao Daniel Silva 86445, Francisco Sousa 86416 ****************/
/********************************* Grupo 15 *********************************/
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
#define msgCompr(A) forum[A].compr
#define menor(A, B) strcmp(A, B) < 0
#define igual(A, B) strcmp(A, B) == 0


/****************************************************************************/
/*************************** Prototipo de funcoes ***************************/
/****************************************************************************/

int leID();
int leMsg(char str[]);
void adicionaMsg();
void listaMsgs();
void listaMsgsID();
void maiorMsg();
void userMaisAtivo();
void ordenaMsg();
void sortAlgoritmo(int aux[], int primsort);
void listaMsgsOrd(int ord[]);
void limpaVetor(int v[], int tam);
int sortComparacao(int v, int aux_j, int primsort);
void contaPalavra();
int limitePalavra(char c);


/****************************************************************************/
/********************* Declaracao da estrutura Mensagem *********************/
/****************************************************************************/

typedef struct {
	char frase[MAXCHARS+1];
	int id;
	int compr;
} Mensagem;


/*****************************************************************************/
/********************** Declaracao de variaveis globais **********************/
/*****************************************************************************/

Mensagem forum[MAXMSGS]; //criar o forum
int contadorAtiv[MAXUSERS+1]; //contadorAtiv guarda o n de msgs por user
int noMsg = 0;


/****************************************************************************/
/*********************************** Main ***********************************/
/****************************************************************************/

int main() {
	int done = 0; //variavel de controlo
	char command;
	limpaVetor(contadorAtiv, MAXUSERS); //limpa o vetor que guarda o numero de mensagens de cada id
	while (!done) {
		scanf("\n%c", &command); //le primeiro caracter introduzido
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
				if (noMsg) userMaisAtivo(); //se houver mensagens
				break;
			case 'C':
				contaPalavra();
				break;
			case 'S':
				ordenaMsg(); //ordena as mensagens
				break;
			case 'X':
				printf("%d\n", noMsg); //imprime no ecra o numero de mensagens no forum
				done = 1; //altera o valor da variavel de controlo para interromper o ciclo
				break;
			default:
				printf("ERRO: Comando desconhecido\n");
		};
	};
	return 0;
};

/******************************************************************************/
/***************************** Funcoes de Leitura *****************************/
/******************************************************************************/

int leID() {
	char id_str[4], c; int i = 0;
	getchar(); //saltar espaço
	while ('0' <= (c = getchar()) && c <= '9' && i < 3) {
		//le os digitos para um vetor de caracteres
		id_str[i++] = c;
	};
	id_str[i] = '\0';
	return atoi(id_str); //converte o vetor num inteiro
};

int leMsg(char str[]) {
	char c; int i = 0;
	while ((c = getchar()) != '\n') {
		str[i++] = c;
	};
	str[i] = '\0';
	return i;
};


/*****************************************************************************/
/************************************* A *************************************/
/*****************************************************************************/

void adicionaMsg() {
	msgID(noMsg) = leID();
	msgCompr(noMsg) = leMsg(msgFrase(noMsg));
	//pede o id do utilizador e a mensagem e adiciona ah estrutura
	contadorAtiv[msgID(noMsg)]++;
	noMsg++;
};

/*****************************************************************************/
/************************************* L *************************************/
/*****************************************************************************/

void listaMsgs() {
	int m;
	printf("*TOTAL MESSAGES:%d\n", noMsg);
	for (m = 0; m < noMsg; m++) {
		//percorre o forum e imprime as mensagens no ecra
		printf("%d:%s\n", msgID(m), msgFrase(m));
	};
};


/*****************************************************************************/
/************************************* U *************************************/
/*****************************************************************************/

void listaMsgsID() {
	int m, id = leID();
	printf("*MESSAGES FROM USER:%d\n", id);
	for (m = 0; m < noMsg; m++) {
		//procura no forum pelas mensagens do utilizador desejado
		if (msgID(m) == id) {
			printf("%s\n", msgFrase(m));
		};
	};
};


/*****************************************************************************/
/************************************* O *************************************/
/*****************************************************************************/

void maiorMsg() {
	int m, max = 0;
	for (m = 0; m < noMsg; m++) {
		//procura a mensagem com o comprimento maior
		if (msgCompr(m) > max) {
			max = msgCompr(m);
		};
	};
	for (m = 0; m < noMsg; m++) {
		//imprime todas as mensagens que tenham esse comprimento
		if (msgCompr(m) == max) {
			printf("*LONGEST SENTENCE:%d:%s\n", msgID(m), msgFrase(m));
		};
	};
};


/*****************************************************************************/
/************************************* T *************************************/
/*****************************************************************************/

void userMaisAtivo() {
	int u, lim = 0, max = 1, users[noMsg];
	for (u = 0; u < MAXUSERS; u++) {
		//procura no vetor contador o user mais ativo
		if (contadorAtiv[u] > max) {
			//se o max for maior que os outros, guarda no inicio dos users
			lim = 0;
			max = contadorAtiv[u];
			users[lim++] = u;
		} else if (contadorAtiv[u] == max) {
			//se for igual, guarda na posicao seguinte
			users[lim++] = u;
		};
	};
	for (u = 0; u < lim; u++) {
		printf("*MOST ACTIVE USER:%d:%d\n", users[u], max);
	};
};


/*****************************************************************************/
/************************************* C *************************************/
/*****************************************************************************/

void contaPalavra() {
	int m, i = 0, j = 0, contador = 0;
	char palavra[MAXCHARS+1], str_aux[MAXCHARS+1];
	getchar(); //saltar o espaco
	leMsg(palavra);
	for (m = 0; m < noMsg; m++) {
		while (msgFrase(m)[i] != '\0'){
			//percorre-se a mensagem e copia-se palavra a palavra
			while (!limitePalavra(msgFrase(m)[i])) {
				str_aux[j++] = msgFrase(m)[i++];
			};
			str_aux[j] = '\0';
			if (igual(str_aux, palavra)) {
				contador++;
			};
			i++;
			j = 0;
		};
		i = 0;
	};
	printf("*WORD %s:%d\n", palavra, contador);
};

int limitePalavra(char c) {
	return ((c == ' ' || c == '\0' || c == ',' || c == '.'|| c == ';' || c == '\t' || c == '\n') ? 1 : 0);
};


/*****************************************************************************/
/************************************* S *************************************/
/*****************************************************************************/

void ordenaMsg() {
	int aux[noMsg], i = 0;
	//Cria um vetor auxiliar de numeros ordenados. Cada numero eh o indice de uma
	//Mensagem no vetor forum[]. A ordem deles equivale ah ordem pela qual as
	//Mensagem's aparecem no forum
	while (i < noMsg) {
		aux[i] = i;
		i++;
	};
	//Aplica o sort estavel duas vezes ao vetor
	sortAlgoritmo(aux, 1);
	sortAlgoritmo(aux, 0);
	listaMsgsOrd(aux);
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

int sortComparacao(int v, int aux_j, int primsort) {
	//se for a primeira vez que corre o sort, compara ids
	//se for a segunda, compara as mensagens
	if (primsort) {
		return msgID(v) < msgID(aux_j);
	} else {
		return menor(msgFrase(v), msgFrase(aux_j));
	};
};

void listaMsgsOrd(int ord[]) {
	//imprime as mensagens do forum pela ordem ord
	int i;
	printf("*SORTED MESSAGES:%d\n", noMsg);
	for (i = 0; i < noMsg; i++) {
		printf("%d:%s\n", msgID(ord[i]), msgFrase(ord[i]));
	};
};

void limpaVetor(int v[], int tam) {
	//Preenche o vetor v de tamanho tam com zeros
	int i = 0;
	while (i <= tam) {
		v[i++] = 0;
	};
};

/*****************************************************************************/
/************************************* C *************************************/
/*****************************************************************************/
