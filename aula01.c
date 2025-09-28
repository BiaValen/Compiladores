#include <stdio.h>
#include <string.h> // Para a função strlen()
#include <ctype.h>  // Essencial para a função isalpha()

//estado do automato
typedef enum {Q0, Q1, Q2, Qlixo} Estado;

//ve se é um caracter do alfabeto
//[a-z A-Z]
int ehletra(char c){
    if (isalpha(c)){
        return 1;
    } else {
        return 0;
    }
}

//ve se é um numero
//[0-9]
int ehnumero(char c){
    if (isdigit(c)){
        return 1;
    } else {
        return 0;
    }
}

//programação do automato
//[a-zA-Z]([a-zA-Z0-9]*)
int DFA(char* cadeia){
    
    Estado q = Q0; // estado de inicio

    char c = cadeia[0];
    int i;

    if (!ehletra(c)){
        q = Qlixo;
    } else {
        q = Q1;

        for(i = 1; cadeia[i] != '\0'; i ++){
        c = cadeia[i];

        if (ehletra(c) || ehnumero(c)){
            q = Q1;
        }
        else {
            q = Q2;
            break;
        }
    }

    if ((q == Q1) && (cadeia[i] == '\0')){
        q = Q2;
    }else{
        q = Qlixo;
    }
    } 

}

int main() {
    char teste [] = "Curso12";
    
    int aceita = DFA(teste);
    if (aceita){
        printf("A string %s eh aceita pelo DFA", teste);
    } else{
        printf("A string %s NAO eh aceita pelo DFA", teste);
    }
} 