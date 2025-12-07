#include "utils_validacao.h"

// Funcao para eliminar os espacos da string
void eliminar_espacos(char *str) {

}

// Funcao que valida CPF/CNPJ
int validar_cpf_cnpj(const char *cpf_cnpj){

 
if (strlen(cpf_cnpj) == 0){
    printf("CPF/CNPJ nao pode ser vazio.\n");
    return 0;
 }

 // Verifica se o CPF/CNPJ tem 11 ou 14 caracteres
 if (strnlen(cpf_cnpj)  != 11 || strnlen(cpf_cnpj)  != 14){
    printf("CPF/CNPJ invalido. Deve conter 11 ou 14 caracteres.\n");
    return;
 }
 // Verifica se todos os caracteres sao digitos
 for (int i = 0; i < )}

 // 112.401.556-62                                                                                                                                                                                              