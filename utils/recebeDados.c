#include "recebeDados.h"

//=======================================================
// LE OS TIPOS BASICOS (Sem validacao nenhuma)

int lerInt(){
    int num;
    scanf("%d",&num);
    getchar();
    return num;
}

float lerFloat(){
    float num;
    scanf("%f",&num);
    getchar();
    return num;
}

void lerString(char *str, int maxTam){
    fgets(str, maxTam, stdin);
    str[strcspn(str, "\n")] = 0; // remove \n
}


//=======================================================
// RECEBE DADOS GENERICOS (Com validacao basica)

// Recebe uma String
void recebeString(char *str, int maxTam, char *msg1, char *msg2, bool validacao){
    // Recebe uma String de no maximo 'maxTam' caracteres
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe a string
        lerString(str, maxTam);
        
        // Confere se a string e' valida
        if ((strlen(str) > 0 && strlen(str) < maxTam) || !validacao) break;
        printMensagem("Tamanho excede o maximo!","ERRO");
    }
}

// Recebe um inteiro entre min e max
int recebeInt(int min, int max, char *msg1, char *msg2, bool validacao){
    int n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o inteiro
        n = lerInt();
        
        // Confere se o int e' valido
        if ((n >= min && n <= max) || !validacao) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

// Recebe um float entre min e max
float recebeFloat(float min, float max, char *msg1, char *msg2, bool validacao){
    float n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o float
        n = lerFloat();
        
        // Confere se o float e' valido
        if ((n >= min && n <= max) || !validacao) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

int recebeConfirma(){
    // guarda a escolha
    int confirma; 

    // Enquanto usuario n digitar 1 ou 0, fica perguntando
    do{
        printMensagem("Voce tem certeza?", "1.Sim | 0.Nao");
        printf("\n =>");
        confirma = lerInt();

    }while ( confirma != 1 && confirma != 0);
    
    //retorna a escolha
    return confirma;
}

//=======================================================
// RECEBE DADOS ESPECIFICOS (Com validacao complexa)

// Recebe um cpf em string - ja faz a validacao
void recebeCPF(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CPF","11 Digitos", validacao);

        // aqui vai a validacao
        if (validarCPF(str) || !validacao) break;
        printMensagem("CPF invalido!","ERRO");
    }
}

// Recebe um CNPJ em string - ja faz a validacao
void recebeCNPJ(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CNPJ","14 Digitos", validacao);

        // aqui vai a validacao
        if (validarCNPJ(str) || !validacao) break;
        printMensagem("CNPJ invalido!","ERRO");
    }
}

// pede ao usuario para escolher
void recebeCPFCNPJ(char *str, bool* usa_CNPJ, bool validacao) {
    while (1) {
        *usa_CNPJ = recebeInt(0,1,"Como quer cadastrar?","0. CPF | 1. CNPJ", validacao);

        if (*usa_CNPJ == 0) {
            recebeCPF(str, validacao);
            break;
        }
        else if (*usa_CNPJ == 1) {
            recebeCNPJ(str, validacao);
            break;
        } else {
            printOpcaoInvalida();
        }
    }
}

// Recebe um Email em string - ja faz a validacao
void recebeEmail(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 100, "Digite o Email","Max. 100", validacao);

        // aqui vai a validacao
        if (validarEmail(str) || !validacao) break;
        printMensagem("Email invalido!","ERRO");
    }
}

// Recebe um Telefone em string - ja faz a validacao
void recebeTelefone(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Telefone","10 ou 11 Digitos", validacao);

        // aqui vai a validacao
        if (validarTelefone(str) || !validacao) break;
        printMensagem("Telefone invalido!","ERRO");
    }

}

void recebeSenha(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite a senha","No minimo que tenha: "
                                               "ou letra maiscul, ou minuscula ou caracteres "
                                               "especiais ou numeros", validacao);
        // aqui vai a validacao
        if (validarSenha(str) || !validacao) break;
        printMensagem("Senha invalida!","ERRO");
    }
}

void recebeNome(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Nome","no minimo 3 caracteres", validacao);

        // aqui vai a validacao
        if (validarNome(str) || !validacao) break;
        printMensagem("Nome invalido!","ERRO");
    }
}

void recebeUsuario(char *str, bool validacao){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Usuario"," de 3 até 20 digitos", validacao);

        // aqui vai a validacao
        if (validarUsuario(str) || !validacao) break;
        printMensagem("Usuario invalido!","ERRO");
    }
}

int recebeID(bool validacao){
    return recebeInt(1, 1000000, "Digite o ID", "Min. 1", validacao);
}