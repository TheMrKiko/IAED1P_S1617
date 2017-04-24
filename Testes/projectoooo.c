/* <<< Joao Daniel Silva 86445, Francisco Sousa, 86416 >>> */
#include <stdio.h>
#include <string.h>

//Definicao de constantes
#define MAXCHARS 140
#define MAXMSGS 10000
#define MAXUSERS 1000
#define MAXDIGS 3

#define less(A,B) (strcmp(A,B)<0)
#define equal(A,B) (strcmp(A,B)==0)

//Definicao de estrutura mensagem
typedef struct {
	char frase[MAXCHARS+1];
	int id;
	int compr;
} Mensagem;

//Definicao de prototipo de funcoes
void limpaVetor(int v[],int tamanho); //limpa conteudo do vetor
void addMsg(); //add mensagem ao forum
void leLinha();//le uma linha de input
int leId();//le o numero do user do input
int leMsg(int posIni); //le a mensagem escrita por um user
void listaMsgs(); //lista todas as mensagens ja submetidas
void msgUser(); //dado um utilizador, imprime todas as frases escritas por ele
void longestMsg(); //procura a frase mais comprida no forum e imprime-a com o utilizador que a escreveu
void mostAtivityUser(); //imprime no ecra o id do user
void copiaForum(Mensagem a[]);
void sort(Mensagem a[], int l, int r);

//Declaracao de variaveis globais
Mensagem forum[MAXMSGS]; //criacao do forum
Mensagem forumAux[MAXMSGS];
int counterAtividade[MAXUSERS+1], noMsg = 0;
char input[148];
int id = 0;
char msg[MAXCHARS+1];


//Proj
int main() {
	int done; //variavel de controlo
	char command; //variavel que guarda o commando de cada input
	limpaVetor(counterAtividade,MAXUSERS); //limpa o vetor que guarda a informacao do numero de mensagens de cada id
	done = 0;
	while(!done) {
		leLinha();
		command = input[0];
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
				copiaForum(forumAux);
				sort(forumAux,0,noMsg-1);
				break;
			case 'X':
				printf("%d\n",noMsg); //imprime no ecra o numero de mensagens no forum
				done = 1; //altera o valor da variavel de controlo para interromper o ciclo
				break;
			default: printf("ERRO: Comando desconhecido\n");
		}
	}
	return 0;
};

void limpaVetor(int v[],int tamanho) {
	int i;
	for(i=0; i<tamanho; i++) {
		v[i]=0;
	};
};

void leLinha() {
	int c,i;
	for(i=0;i<147 &&(c=getchar()) != EOF && c != '\n';i++)
		input[i] = c;
	input[i]='\0';
	//printf("%s\n",input);
}

int leId() {
	int i;
	//como o numero do user comeca sempre na posicao 2, percorre o vetor no maximo 3 vezes e enquanto os carateres
	//digitados forem numeros, armazenando o numero do user na variavel id
	for(i=2;i<MAXDIGS+2 && '0'<=input[i] && input[i]<='9';i++) {
			id = id *10; //conversao do numero de ASCII para int
			id += input[i]-'0'; // ^
	}
	//printf("id = %d\n",id);
	return i+1; //retorna posicao com a qual o leMsg irah comecar

};

int leMsg(int posIni) {
	int i;
	//o ciclo comeca com a posicao devolvida pela funcao leId
	for(i=posIni;input[i]!='\0';i++) {
		msg[i-posIni]=input[i];  //copia para a msg na a mensagem do input
		//os indices encontram se desfazados pois a var i comeca num valor diferente de 0
	};
	msg[i-posIni]='\0'; //coloca se o \0 na ultima posicao da string
	//printf("msg= %s\n",msg);
	return i-posIni; //retorna o comprimento da string
};

void addMsg() {
	int pos,compr;
	pos=leId(); //le o id do user
	compr = leMsg(pos); //le a mensagem e guarda e o seu comprimento
	forum[noMsg].id=id; //guarda o numero do user no forum
	strcpy(forum[noMsg].frase,msg); //guarda a frase no forum
	forum[noMsg].compr = compr; //guarda o comprimento da frase
	counterAtividade[forum[noMsg].id]++; //incrementa a atividade do vetor
	//printf("msg=%s id=%d compr=%d atividade=%d\n",forum[noMsg].frase,forum[noMsg].id,forum[noMsg].compr,counterAtividade[forum[noMsg].id]);
	noMsg++; //incrementa o numero de mensagens no forum
	id = 0; //reset da variavel id
	msg[0] = '\0'; //reset da string da mensagem;
};

void listaMsgs() {
	int i;
	printf("*TOTAL MESSAGES:%d\n", noMsg);
	for(i=0;i<noMsg;i++) { //percorre o vetor que armazena as mensagens e imprime as no ecra
		printf("%d:%s\n",forum[i].id,forum[i].frase);
	}
}

void msgUser() {
	int i;
	leId();
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
void copiaForum(Mensagem a[]) {
	int i;
	for(i=0;i<noMsg;i++) {
		strcpy(a[i].frase,forum[i].frase);
		a[i].id = forum[i].id;
		a[i].compr = a[i].compr;
	}
}

void sort(Mensagem a[], int l, int r) {
	int i,j;
	Mensagem v;
	for (i = l+1; i <= r; i++) {
		strcpy(v.frase,a[i].frase);
		v.id= a[i].id;
		j = i-1;
		while ( j >= l &&less(v.frase, a[j].frase)) { //insertion sort normal para as mensagens p ordem alfabetica
			strcpy(a[j+1].frase,a[j].frase); //troca de msgs e id
			a[j+1].id = a[j].id;
			j--;
		}
		strcpy(a[j+1].frase,v.frase);
		a[j+1].id = v.id;
		//insertion sort para os ids. so acontece quando as mensagens sao iguais e os ids diferentes
		while(j>=l && equal(v.frase,a[j].frase) && v.id<a[j].id) {
			a[j+1].id = a[j].id;
			j--;
		}
		a[j+1].id = v.id;
	}
	for(i=0;i<noMsg;i++) { //DEVIAMOS FAZER ESTE FOR UMA FUNCAO
		printf("%d:%s\n",a[i].id,a[i].frase);
	}
}
