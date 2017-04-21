/* <<< Joao Daniel Silva 86445, Francisco Sousa, 86416 >>> */
#include <stdio.h>
#define MAXCHARS 140
#define MAXMSGS 10000
#define MAXUSERS 1000

//Definicao de prototipo de funcoes
void limpaVetor(int v[],int tamanho); //limpa conteudo do vetor
void addMsg(); //add mensagem ao forum

//Definicao de estrutura mensagem
typedef struct {
	char str[MAXCHARS+1];
	int id;
} Mensagem;

Mensagem forum[MAXMSGS]; //criacao do forum
int counterAtividade[MAXUSERS+1], noMsg = 0;

int main() {
	char opcao;
	limpaVetor(counterAtividade,MAXUSERS);
	scanf("%c ", &opcao);
	switch (opcao) {
		case 'A':
            addMsg();
			//break;
			main();
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
	leMSG(forum[noMsg].str);
    printf("int: %d\n", forum[noMsg].id);
    printf("msg: %s\n", forum[noMsg].str);
	//pede o id do utilizador e a mensagem e adiciona ah estrutura
	counterAtividade[forum[noMsg].id]++;
	noMsg++;
};


void limpaVetor(int v[],int tamanho) {
	int i;
	for(i=0; i<tamanho; i++) {
		v[i]=0;
	};
};
