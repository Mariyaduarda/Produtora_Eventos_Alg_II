#include "recebeDados.h"

//=======================================================
// RECEBE OS TIPOS

// Recebe uma String
void recebeString(char *str, int maxTam, char *msg1, char *msg2){
    // Recebe uma String de no maximo 'maxTam' caracteres
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe a string
        fgets(str, maxTam, stdin);
        str[strcspn(str, "\n")] = 0; // remove \n
        
        // Confere se a string e' valida
        if (strlen(str) > 0 && strlen(str) < maxTam) break;
        printMensagem("Tamanho excede o maximo!","ERRO");
    }
}

// Recebe um inteiro entre min e max
int recebeInt(int min, int max, char *msg1, char *msg2){
    int n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o inteiro
        scanf("%d",&n);
        getchar(); // Limpa o buffer do teclado
        
        // Confere se o int e' valido
        if (n >= min && n <= max) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

// Recebe um float entre min e max
float recebeFloat(float min, float max, char *msg1, char *msg2){
    float n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o float
        scanf("%f",&n);
        getchar(); // Limpa o buffer do teclado
        
        // Confere se o float e' valido
        if (n >= min && n <= max) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

//=======================================================
// RECEBE COM VALIDACAO

// Recebe um cpf em string - ja faz a validacao
void recebeCPF(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CPF","11 Digitos");

        // aqui vai a validacao
        if (1) break;
        printMensagem("CPF invalido!","ERRO");
    }
}

// Recebe um CNPJ em string - ja faz a validacao
void recebeCNPJ(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CNPJ","14 Digitos");

        // aqui vai a validacao
        if (1) break;
        printMensagem("CNPJ invalido!","ERRO");
    }
}

// Recebe um Email em string - ja faz a validacao
void recebeEmail(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 100, "Digite o Email","Max. 100");

        // aqui vai a validacao
        if (1) break;
        printMensagem("Email invalido!","ERRO");
    }
}

// Recebe um Telefone em string - ja faz a validacao
void recebeTelefone(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Telefone","10 ou 11 Digitos");

        // aqui vai a validacao
        if (1) break;
        printMensagem("Telefone invalido!","ERRO");
    }

}

int recebeID(){
    return recebeInt(1, 1000000, "Digite o ID", "Min. 1");
}