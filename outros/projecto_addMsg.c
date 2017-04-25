/* <<< Joao Daniel Silva 86445, Francisco Sousa, 86416 >>> */
#include <stdio.h>
#include <string.h>

//Definicao de constantes
#define MAXCHARS 140
#define MAXMSGS 10000
#define MAXUSERS 1000
#define MAXDIGS 3

//Definicao de prototipo de funcoes
void limpaVetor(int v[],int tamanho); //limpa conteudo do vetor
void addMsg(); //add mensagem ao forum
void leLinha();//le uma linha de input
int leId();//le o id do user do input
int leMsg(int posIni);

//Definicao de estrutura mensagem
typedef struct {
	char frase[MAXCHARS+1];
	int id;
	int compr;
} Mensagem;


//Declaracao de variaveis
Mensagem forum[MAXMSGS]; //criacao do forum
int counterAtividade[MAXUSERS+1], noMsg = 0;
char input[148];
int id = 0;
char msg[MAXCHARS+1];


//Proj
int main() {
	char opcao;
	limpaVetor(counterAtividade,MAXUSERS);
	leLinha();
	opcao = input[0];
	switch (opcao) {
		case 'A':
			addMsg();
	}
	return 0;
};

void leLinha() {
	int c,i;
	for(i=0;i<147 &&(c=getchar()) != EOF && c != '\n';i++)
		input[i] = c;
	input[i]='\0';
	//printf("%s\n",input);	
}

void limpaVetor(int v[],int tamanho) {
	int i;
	for(i=0; i<tamanho; i++) {
		v[i]=0;
	};
};

int leId() {
	int i;
	for(i=0;i<MAXDIGS;i++) {
		if('0'<input[i+2] && input[i+2]<'9') {
			id = id *10;
			id += input[i+2]-'0';
			//printf("%c\n",input[i+2]);
		}
	}
	printf("id = %d\n",id);
	/*printf("%c\n",input[2]);
	printf("%c\n",input[3]);
	printf("%c\n",input[4]);*/
	return i+3; //retorna posicao para o leMsg comecar

};

int leMsg(int posIni) {
	int i;
	for(i=posIni;input[i]!='\0';i++) {
		msg[i-posIni]=input[i];
	};
	msg[i]='\0';
	printf("msg= %s\n",msg);
	return i-posIni; //retorna o comprimento da string
};

void addMsg() {
	int pos,compr;
	pos=leId();
	compr = leMsg(pos);
	forum[noMsg].id=id;
	strcpy(forum[noMsg].frase,msg);
	forum[noMsg].compr = compr;
	counterAtividade[forum[noMsg].id]++;
	printf("msg=%s id=%d compr=%d atividade=%d\n",forum[noMsg].frase,forum[noMsg].id,forum[noMsg].compr,counterAtividade[forum[noMsg].id]);
	noMsg++;
};

