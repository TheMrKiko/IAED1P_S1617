/****************************************************************************/
/************ Joao Daniel Silva 86445, Francisco Sousa 86416 ****************/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

/****************************************************************************/
/**************************** Definicao de constantes ***********************/
/****************************************************************************/
#define MAXCHARS 140
#define MAXMSGS 10000
#define MAXUSERS 1000
#define MAXDIGS 3
#define MsgStr(A) forum[A].frase
#define less(A, B) strcmp(A, B) < 0

/*********************************************************************/
/*********** Prototipo de funcoes ****************/
/****************************************************************************/
void limpaVetor(int v[],int tamanho); //limpa conteudo do vetor
void addMsg(); //add mensagem ao forum
void leLinha();//le uma linha de input
int leID();//le o numero do user do input
void leMSG(char str[]);
void ordena();
//int leMsg(int posIni); //le a mensagem escrita por um user
void listaMsgs(); //lista todas as mensagens ja submetidas
void msgUser(); //dado um utilizador, imprime todas as frases escritas por ele
void longestMsg(); //procura a frase mais comprida no forum e imprime-a
void mostAtivityUser(); //imprime no ecra o id do user

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
int counterAtividade[MAXUSERS+1]; //counterAtividade guarda o n de msgs por user
int id = 0, noMsg = 0;
char input[MAXCHARS+MAXDIGS+1+3];
char msg[MAXCHARS+1];

/****************************************************************************/
/*********** Funcoes ****************/
/****************************************************************************/
int main() {
	int done = 0; //variavel de controlo
	char command; //variavel que guarda o commando de cada input
	limpaVetor(counterAtividade,MAXUSERS); //limpa o vetor que guarda a informacao do numero de mensagens de cada id
	while(!done) {
		scanf("\n%c", &command);
		//printf("COMANDO %c\n", command);
		//leLinha();
		//command = input[0];
		switch (command) {
			case 'A':
				addMsg(); //adiciona uma mensagem ao forum
				break;
			case 'L':
				listaMsgs(); //imprime no ecra todas as mensagens do forum
				break;
			case 'U':
				msgUser(); //imprime todas as mensagens de um id
				break;
			case 'O':
				longestMsg(); //procura as mensagens mais longas
				break;
			case 'T':
				mostAtivityUser(); //procura user mais ativo
				break;
			case 'S':
				ordena(); //procura user mais ativo
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
	int id = 0;//falta restringir o numero
	scanf("%d ", &id);
	return id;
};

void leMSG(char str[]){
	char c; int i=0;
	while ((c = getchar())!='\n'){
		str[i++]=c;
	};
};

void addMsg() {
	forum[noMsg].id = leID();
	leMSG(forum[noMsg].frase);
    //printf("int: %d\n", forum[noMsg].id);
    //printf("msg: %s\n", forum[noMsg].frase);
	//pede o id do utilizador e a mensagem e adiciona ah estrutura
	counterAtividade[forum[noMsg].id]++;
	noMsg++;
};

/*void addMsg() {
	int pos,compr;
	pos = leID();
	compr = leMsg(pos);
	forum[noMsg].id = id; //guarda o numero do user no forum
	strcpy(forum[noMsg].frase, msg); //guarda a frase no forum
	forum[noMsg].compr = compr; //guarda o comprimento da frase
	counterAtividade[forum[noMsg].id]++; //incrementa a atividade do vetor
	printf("msg=%s id=%d compr=%d atividade=%d\n", forum[noMsg].frase, forum[noMsg].id, forum[noMsg].compr, counterAtividade[forum[noMsg].id]);
	noMsg++; //incrementa o numero de mensagens no forum
	id = 0; msg[0] = '\0'; //reset da string da mensagem
};

int leID() {
	int i;
	//como o numero do user comeca sempre na posicao 2, percorre o vetor no maximo 3 vezes e enquanto os carateres
	//digitados forem numeros, armazenando o numero do user na variavel id
	for(i=2; i<MAXDIGS+2 && '0'<=input[i] && input[i]<='9'; i++) {
		id = id *10; //conversao do numero de ASCII para int
		id += input[i]-'0'; // ^
	}
	printf("id = %d\n",id);
	return i+1; //retorna posicao com a qual o leMsg ira' comecar
};

int leMsg(int posIni) {
	int i;
	//o ciclo comeca com a posicao devolvida pela funcao leID
	for(i=posIni; input[i]!='\0'; i++) {
		msg[i-posIni]=input[i];  //copia para a msg na a mensagem do input
		//os indices encontram se desfazados pois a var i comeca num valor diferente de 0
	};
	msg[i-posIni]='\0'; //coloca se o \0 na ultima posicao da string
	printf("msg= %s\n",msg);
	return i-posIni; //retorna o comprimento da string
};*/


void listaMsgs() {
	int i;
	printf("*TOTAL MESSAGES:%d\n", noMsg);
	for(i=0;i<noMsg;i++) { //percorre o vetor que armazena as mensagens e imprime as no ecra
		printf("%d:%s\n",forum[i].id,forum[i].frase);
	}
}

void msgUser() {
	int i;
	leID();
	printf("*MESSAGES FROM USER:%d\n",id);
	for(i=0;i<noMsg;i++) { //procura no vetor forum pelas mensagens do utilizador desejado
		if(forum[i].id==id) {
			printf("%s\n",forum[i].frase);
		}
	}
}

void longestMsg() {
	int i,max=0;
	for(i=0;i<noMsg;i++) { //procura a frase com o comprimento maior
		if(forum[i].compr>max) max = forum[i].compr;
	}
	for(i=0;i<noMsg;i++) { //imprime todas as frases que tenham esse comprimento
		if(forum[i].compr==max) {
			printf("*LONGEST SENTENCE:%d:%s\n",forum[i].id,forum[i].frase);
		}
	}
}

void mostAtivityUser() {
	int i,max=0,user=0;
	for(i=0;i<MAXUSERS;i++) { //procura no vetor counter qual das posicoes q identifica cada user tem o valor maior
		if(counterAtividade[forum[i].id]>max) {
			max = counterAtividade[forum[i].id];  //guarda o valor da atividade
			user = forum[i].id; //guarda o numero do user
		}
	}
	printf("*MOST ACTIVE USER:%d:%d\n",user,max);
}

//Preenche o vetor v de tamanho tam com zeros
void limpaVetor(int v[], int tam) {
	int i;
	for(i=0; i<tam; i++) {
		v[i]=0;
	};
};

//Le a linha no stdin e armazena no vetor input[].
// a linha tem o formato 'COMANDO USER MENSAGEM' (tamanho maximo '1 3 140')
void leLinha() {
	int c, i;
	for(i=0; i<147 && (c = getchar() )!=EOF && c!='\n'; i++){
		input[i] = c;
	};
	input[i] = '\0';
	//printf("%s\n",input);
};

void imprime(int H[]){
    int i;
	printf("SORTED MESSAGES:%d\n", noMsg);
    for (i = 0; i < noMsg; i++){
        printf("%d:%s\n", forum[H[i]].id,forum[H[i]].frase);
    };
};


int CompMsg(int v, int aux_j, int primsort){
	if (primsort){
		return forum[v].id < forum[aux_j].id;
	} else {
		return less( MsgStr(v), MsgStr(aux_j));
	}
}

void sort_algoritmo(int aux[], int primsort, int (*comp)(int, int, int)) {
	int i, j;
	//Aplica o sort
    for (i = 1; i <= noMsg-1; i++) {
        int v = aux[i];
        j = i-1;
        while (j >= 0 && comp(v, aux[j], primsort)) {
            aux[j+1] = aux[j];
            j--;
        };
        aux[j+1] = v;
    };
    imprime(aux);
};

void ordena() {
	int aux[noMsg], i = 0;
	//Cria vetor auxiliar
	while (i < noMsg){
		aux[i] = i;
		i++;
	};
	sort_algoritmo(aux, 1, CompMsg);
	sort_algoritmo(aux, 0, CompMsg);
};
