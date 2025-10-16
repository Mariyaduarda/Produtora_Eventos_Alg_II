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

    // calcula o primeiro dig verificador do cpf
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
    return (digito1 == (numeros[9] - '0')) && (digito2 == (numeros[10] - '0'));
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

    return (digito1 == (numeros[12] - '0')) && (digito2 == (numeros[13] - '0'));
}

// funcao unica p/ cpf e cnpj
bool validarCPF_CNPJ(const char *documento, bool usa_CPF) {
    if ( usa_CPF) { // usa cpf é uma flag, podia ser usaCNPJ tb
        return validarCPF(documento); // doc é minha string const
                                      // q vai escolher entre cpf e cnpj
    }
    else {
        return validarCNPJ(documento);
    }
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
    for (i = 0; telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            digitos++;
        } else if (telefone[i] != ' ' && telefone[i] != '(' &&
                    telefone[i] !=  ')' && telefone[i] != '-') {
            return false; // caracter invalido
        }
    }
    // aceitando tel fixo ou de celular
    return (digitos == 10 || digitos == 11);
}

// //===== FUNCAO AUXILIARES PARA UTF-8 =====
// // retorna qnts bytes um caractere UTF-8 ocupa
// int bytes_utf8(unsigned char caracter) {
//     if (caracter < 0x80) returb 1;
//     if (caracter >= 0xC2)
// }

// // ===== VALIDACAO DO NOME ======
bool validarNome(const char *nome) {
    int i = 0, len = strlen(nome), total_letras = 0;
    bool tem_espaco = false;

    // tamanho minimo para ser aceito
    if (len < 3) return false;

    // assegura nao comecar nem terminar com espaco
    if (nome[0] == ' ' || nome[len-1] == ' ') return false;

    // verifica caracteres validos e presenca de espaço
    for (i = 0; i < len; i++) {
        if (isalpha(nome[i]) || nome[i] == ' ' || nome[i] == '\''
            || nome[i] == '-' || nome[i] == '.' || nome[i] >= 0xC0) { // 0xC0 p/ carcateres acentuados
            if (nome[i] == ' ') tem_espaco = true;
        } else {
            return false;
        }
    }
    // retornar false se não tem espaço
    if (!tem_espaco) return false;
    return true;
}


bool validarSenha(const char *senha) {
    int i, len = strlen(senha);
    bool tem_maiuscula = false, tem_minuscula = false;
    bool tem_numero = false, tem_especial = false;

    // minimo do tamanho da senha
    if (len < 6) return false;

    // verifica se requisitos foram feitos
    for (i = 0; i < len; i++) {
        if (isupper(senha[i])) tem_maiuscula = true;
        else if (islower(senha[i])) tem_minuscula = true;
        else if (isdigit(senha[i])) tem_numero = true;
        else if (strchr("!@#$%^&*()_+-=[]{}|;:,.<>?", senha[i]))
            tem_especial = true;
    }
    //contando quantos dos 4 tipos de caracter a sneha possui
    int requisitos = tem_maiuscula + tem_minuscula + tem_numero + tem_especial;
    return requisitos >= 2;
}

// ====== VALIDACAO DE USUARIO=====
bool validarUsuario(const char *usuario) {
    int i, len = strlen(usuario);

    // minimo e maximo para tamanho de usuario
    if (len < 3 || len > 20) return false;

    // deve comecar com letra
    if (!isalpha(usuario[0])) return false;

    // verifica carcaters validos como alfanumericos, underline
    for (i = 1; i < len; i++) {
            if (!isalnum(usuario[i]) && usuario[i] != '_') {
                return false;
            }
        }
    return true;
    }
