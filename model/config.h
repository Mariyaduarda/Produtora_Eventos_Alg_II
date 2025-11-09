#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>

// structs para configuracoes gerais do sistema
typedef struct {
    bool salvar_como_binario;   // Se true, salva em binario
    bool validar_dados; // Se true, desabilita a validacao de dados ao receber

} TipoConfig;

// assinaturas de funcoes
void configInit(TipoConfig *config);
int configSalvarTXT(TipoConfig config);
int configLerTXT(TipoConfig *config);
int configSalvarBIN(TipoConfig config);
int configLerBIN(TipoConfig *config);


#endif // CONFIG_H