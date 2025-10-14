//
// Created by alunos on 07/10/2025.
//
#include "utils_bibliotecas.h"

#include <ctype.h>
// ===== VALIDACAO DO CPF ======
bool validarCPF(const char *cpf_cnpj) {
    int i, j = 0, digito1 = 0, digito2 = 0;

    // remover caracteres nao numericos
    char numeros[11+1] = {0};
    for (i = 0; cpf_cnpj[i] != '\0'; i++) {
        if (isdigit(cpf_cnpj[i])) {
            numeros[j++] = cpf_cnpj[i];
        }
    }
    // cpf deve ter 11 digitos
    if (strlen(numeros) != 11) return false;

    // conferir se todos os digitos sao iguais
    bool todos_iguais = true;
    for (i = 1; i < 11; i++) {
        if (numeros[i] != numeros[0]) {
            todos_iguais = false;
            break;
        }
    }
    // mas se todos igual retorno falso pois vale a validade e nao se todos sao iguais
    if (todos_iguais) return false;

    for (i = 0, j = 10; i < 9; i++, j--) {
        // converte char/caracterr para int
        digito1 += (numeros[i] - '0') * j;
    }
    // resto define o digito 1
    digito1 = ((digito1 % 11)<2)? 0: 11 - (digito1%11);

    // calcula o segundo digito
    for (i = 0, j = 11; i < 9;i++, j--) {
        digito2 += (numeros[i] - '0') *j;
    }
    digito2 = ((digito2%11)<2)? 0: 11 - (digito2%11);

    // verifica se os digitos conferem com suas respectivas posicoes
    return (digito1 == (numeros[9] && digito2 == (numeros[10])));
}

// ===== VALIDACAO DO CNPJ ======
bool validarCNPJ(const char *cpf_cnpj) {
    int i, j = 0, digito1 = 0, digito2 = 0;
    // formato = 12.345.678/0001-95
    int peso1[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int peso2[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};

    char numeros[14+1] = {0};

    for (i = 0; cpf_cnpj[i] != '\0'; i ++) {
        if (isdigit(cpf_cnpj[i])) {
            numeros[j++] = cpf_cnpj[i];
        }
    }
    if (strlen(numeros) != 14) return false;

    bool todos_iguais = true;
    for (i = 1; i < 14; i++) {
        if (numeros[i] != numeros[0]) {
            todos_iguais = false;
            break;
        }
    }
    // mas se todos igual retorno falso pois vale a validade e nao se todos sao iguais
    // sequencia como "00000000000000" sao invalidas
    if (todos_iguais) return false;

    for (i = 0; i < 12; i++) {
        digito1 += (numeros[i] - '0') * peso1[i];
    }
    digito1 = (digito1 % 11) < 2? 0: 11 - (digito1 %11);

    for (i = 0; i < 13; i++) {
        digito2 += (numeros[i] - '0') * peso2[i];
    }
    digito2 = (digito2 % 11) < 2? 0: 11 - (digito2 % 11);

    return (digito1 == numeros[12] && digito2 == numeros[13]);
}

// ===== VALIDACAO DO EMAIL ======
bool validarEmail(const char *email) {
    int i, arroba = -1, ponto = -1; // arroba e ponto nao encontrado (-1)
    int len_email = strlen(email);
    // valida quantidade de caracteres no email: m@m.v
    if (len_email < 3) return false;

    // verificar caracteres validos e posicao do @
    for (i = 0; i < len_email; i++) {
        if (email[i] == '@') {
            if (arroba != -1) return false;
            arroba = i;
        } else if (email[i] == '.' && arroba != -1) {
            ponto = i;
        } else if (!isalnum(email[i]) && email[i] != '.'
                    && email[i] != '_' && email[i] != '-') {
            return false;
        }
    }
    // verifica esqueleto basico
    if (arroba <= 0 || arroba == len_email -1 ) return false;
    if (ponto == -1 || ponto <= arroba + 1 || ponto == len_email - 1) return false;
    if (email[0] == '.' || email[len_email - 1] == '.') return false;

    return true;
}

// ===== VALIDACAO DO TELEFONE ======
bool validarTelefone(const char *telefone) {
    int i, digitos = 0;

    // conta apenas digitos
    for (i = 0, telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            digitos++;
        } else if (telefone[i] != ' ' && telefone[i] != '(' &&
                    telefone[i] !=  ')' && telefone[i] != '-') {
            return false;
        }
    }
    return (digitos == 10 || digitos == 11);
}

// // ===== VALIDACAO DO NOME ======
bool validarNome(const char *nome) {
    int i, len = strlen(nome);
    bool tem_espaco = false;

    if (len < 3) return false;

    for (i = 0; i < len; i++) {
        if (isalpha(nome[i]) || nome[i] == ' ' || nome[i] == '\''
            || nome[i] == '-' || nome[i] == '.' || (unsigned char)nome[i] >= 0xC0) {}
    }
}