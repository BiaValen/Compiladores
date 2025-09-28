// 
// proAFD_simples.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <cstdio> // stdio.h
#include <string.h> // string.h

// Estados do AFD
typedef enum { Q0, Q1, Q2, QLixo } Estado;

typedef struct Lexema {
	char tipo[50] = "";
	char valor[50] = "";
};

// Função para verificar se um dado caracter c é 
// um caracter alfabético: [a-zA-Z]
bool eh_letra(char c) {
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
		return true;
	}

	return false;
}

// Função para verificar se um dado caracter c é 
// reservada {if, repeat, until, end, write, read}
bool eh_reservada(char* c) {
	const char* reservadas[] = { "if", "repeat", "until", "end", "write", "read" };
    int num_reservadas = 6; // O número de palavras na lista

    for (int i = 0; i < num_reservadas; i++) {
        // strcmp retorna 0 se as duas strings forem idênticas
        if (strcmp(reservadas[i], c) == 0) {
            return true; // Encontrou!
        }
    }
	return false; // Não é reservada
}

// Função para verificar se um dado caracter c é 
// um caracter numérico: [0-9]
bool eh_digito(char c) {
	if ((c >= '0') && (c <= '9')) {
		return true;
	}

	return false;
}

// Programação do autômato de numero
// [0-9]*
int AFD_NUM(char* cadeia, bool verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";
		//lexema[1000] = "";

	//Lexema lexema;


	Estado q = Q0; // Start
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	//int i;

	if (!eh_digito(c)) {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}
	else {

		if (eh_digito(c)){
            strcpy(lexema->tipo, "NUM");
		}

		int i_lexema = 0;

		lexema->valor[i_lexema] = c;
		i_lexema = i_lexema + 1;

		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
		i = i + 1;
		for (/*i = 1*/; q != Q2; i++) {
			c = cadeia[i]; // i-ésimo caractere

			if (eh_digito(c)) {
				q = Q1;
				if (verbose) {
					strcat(traco, "->Q1");
				}
				lexema->valor[i_lexema] = c;
				i_lexema = i_lexema + 1;

			}
			else {
				q = Q2;
				if (verbose) {
					strcat(traco, "->Q2");
				}
				i = i - 1;
				//break;
			}
		}
		lexema->valor[i_lexema] = '\0';
		*k = *k + 1;
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

	/*if (q == Q2) {
		return true;
	}
	else {
		return false;
	}*/
}

int AFD_ID(char* cadeia, bool verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";
		//lexema[1000] = "";

	//Lexema lexema;


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

		if (eh_letra(c)){
            strcpy(lexema->tipo, "ID");
		}

		int i_lexema = 0;

		lexema->valor[i_lexema] = c;
		i_lexema = i_lexema + 1;

		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
		i = i + 1;
		for (/*i = 1*/; q != Q2; i++) {
			c = cadeia[i]; // i-ésimo caractere

			if (eh_letra(c) || eh_digito(c)) {
				q = Q1;
				if (verbose) {
					strcat(traco, "->Q1");
				}
				lexema->valor[i_lexema] = c;
				i_lexema = i_lexema + 1;

			}
			else {
				q = Q2;
				if (verbose) {
					strcat(traco, "->Q2");
				}
				i = i - 1;
				//break;
			}
		}
		lexema->valor[i_lexema] = '\0';
		*k = *k + 1;
	}
	if (eh_reservada(lexema->valor)) {
            // Se for reservada, corrige o tipo!
            strcpy(lexema->tipo, "RESERVADA"); 
        }
	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

	/*if (q == Q2) {
		return true;
	}
	else {
		return false;
	}*/
}


bool eh_simbolo(char c) {
	if (strchr("+-*/;=>", c) != NULL) { // c in "+-*/;=>"
		return true;
	}
	else {
		return false;
	}
}



int AFD_simbolos(char* cadeia, bool verbose, int i, Lexema *lexema, int *k) {


	char traco[1000] = "";

	//Lexema lexema;
	Estado q = Q0;
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	if (eh_simbolo(c)) {
		lexema->tipo[0] = c; // (*lexema).tipo[0] = c;
		lexema->tipo[1] = '\0';

		lexema->valor[0] = c;
		lexema->valor[1] = '\0';
		i = i + 1; // Estratégia lookahead;
		*k = *k + 1;
		
		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
	}
	else {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

}

static void varredura(char* cadeia) {

	Lexema lexema[100];
	int k = 0;

	for (int i = 0; cadeia[i] != '\0'; ) {

		if (cadeia[i] == ' ') {
			i = i + 1;
			continue;
		}


		i = AFD_ID(cadeia, false, i, &lexema[k], &k);

		i = AFD_simbolos(cadeia, false, i, &lexema[k], &k);

		i = AFD_NUM(cadeia, false, i, &lexema[k], &k);

	}

	for(int j = 0; j < k; j++) 
		printf("\nLexema: <%s,%s>\n", lexema[j].tipo, lexema[j].valor);

}

int main() {
	char teste[100] = "if2  =   repeat + 234;";

	varredura(teste);

	/*bool aceita = AFD(teste, true);

	if (aceita) {
		printf("A string %s eh aceita pelo AFD!", teste);
	}
	else {
		printf("A string %s nao eh aceita pelo AFD!", teste);
	}
	*/
}