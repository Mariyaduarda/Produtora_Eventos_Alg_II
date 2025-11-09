#include "config.h"

// inicializa a config com valores padrao
void configInit(TipoConfig *config){
    config->salvar_como_binario = false; // por padrao salva em texto
    config->validar_dados = true;        // por padrao valida dados ao receber
}

//==================================================
// Arquivos TXT
int configSalvarTXT(TipoConfig config) {
    FILE *fp = fopen("dados/config.txt", "w");
    if (fp == NULL) return 0;

    // salva os dados como inteiros (0 ou 1)
    fprintf(fp, "%d\n", config.salvar_como_binario ? 1 : 0);
    fprintf(fp, "%d\n", config.validar_dados ? 1 : 0);

    fclose(fp);
    return 1;
}

int configLerTXT(TipoConfig *config) {
    FILE *fp = fopen("dados/config.txt", "r");
    if (fp == NULL) return 0;

    int salvarBinTemp, validarDadosTemp;

    // le os dados como inteiros
    if (fscanf(fp, "%d\n%d\n", &salvarBinTemp, &validarDadosTemp) != 2) {
        fclose(fp);
        return 0;
    }

    // atribui os valores lidos aos booleanos
    config->salvar_como_binario = (salvarBinTemp != 0);
    config->validar_dados = (validarDadosTemp != 0);

    fclose(fp);
    return 1;
}

//==================================================
// Arquivos BIN
int configSalvarBIN(TipoConfig config) {
    FILE *fp = fopen("dados/config.bin", "wb");
    if (fp == NULL) return 0;

    // salva os dados como bytes
    fwrite(&config.salvar_como_binario, sizeof(bool), 1, fp);
    fwrite(&config.validar_dados, sizeof(bool), 1, fp);

    fclose(fp);
    return 1;
}

int configLerBIN(TipoConfig *config) {
    FILE *fp = fopen("dados/config.bin", "rb");
    if (fp == NULL) return 0;

    // le os dados como bytes
    if (fread(&config->salvar_como_binario, sizeof(bool), 1, fp) != 1 ||
        fread(&config->validar_dados, sizeof(bool), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}