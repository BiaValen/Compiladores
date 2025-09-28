// 
// proAFD_simples.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <cstdio>
#include <string.h>

// Estados do AFD
typedef enum {Q0, Q1, Q2, QLixo} Estado;

// Função para verificar se um dado caracter c é 
// um caracter alfabético: [a-zA-Z]
bool eh_letra(char c) {
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
		return true;
	}

	return false;
}

// Função para verificar se um dado caracter c é 
// um caracter numérico: [0-9]
bool eh_digito(char c) {
	if ((c >= '0') && (c <= '9')) {
		return true;
	}

	return false;
}

// Programação do autômato
// [a-zA-Z]([a-zA-Z0-9]*)
int AFD(char* cadeia, bool verbose, int i =0) {

	char traco[1000] = "",
		 lexema[1000] = "";


	Estado q = Q0; // Start
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	//int i;

	if (!eh_letra(c)) {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}
	else {

		lexema[0] = c;

		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
		i = i+1;
		for (i=i;q != Q2; i++) {
			c = cadeia[i]; // i-ésimo caractere

			if (eh_letra(c) || eh_digito(c)) {
				q = Q1;
				if (verbose) {
					strcat(traco, "->Q1");
				}
				lexema[i] = c;

			}
			else {
				q = Q2;
				if (verbose) {
					strcat(traco, "->Q2");
				}
				//break;
			}
		}
		lexema[i] = '\0';
		/*
		if ((q == Q1) && (cadeia[i] == '\0')) {
			q = Q2;
			if (verbose) {
				strcat_s(traco, "->Q2");
			}
		}
		else {
			q = QLixo;
			if (verbose) {
				strcat_s(traco, "->QLixo");
			}
		}
		*/ //excluiu por causa do tamanho do for estar certo com o Q2
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: %s\n", lexema);
	}

	if (q == Q2) {
		return true;
	}
	else {
		return false;
	}	
}

static void varredura(char* cadeia, int i = 0){

	bool aceita = AFD(cadeia, true);

}

int main(){
	char teste[100] = "10+mouse";

	bool aceita = AFD(teste, true);

	if (aceita) {
		printf("A string %s eh aceita pelo AFD!", teste);
	}
	else {
		printf("A string %s nao eh aceita pelo AFD!", teste);
	}
}