#include <stdio.h>
#include <string.h>
#include "produtora.h"

void produtoraInit(TipoProdutora *produtora){
    strcpy(produtora->nomeFantasia, "");
    strcpy(produtora->razaoSocial, "");
    strcpy(produtora->inscricaoEstadual, "");
    strcpy(produtora->cnpj, "");
    strcpy(produtora->endereco, "");
    strcpy(produtora->telefone, "");
    strcpy(produtora->email, "");
    strcpy(produtora->nomeDoResponsavel, "");
    strcpy(produtora->telefoneDoResponsavel, "");
    produtora->margemDeLucro = 0.0f;
}

int produtoraSalvarTXT(TipoProdutora *produtora) {
    FILE *arquivo = fopen("dados/produtora.txt", "w");
    if (arquivo == NULL) return 0;

    // Salva os registros um por linha
    fprintf(arquivo, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%.2f\n",
            produtora->nomeFantasia,
            produtora->razaoSocial,
            produtora->inscricaoEstadual,
            produtora->cnpj,
            produtora->endereco,
            produtora->telefone,
            produtora->email,
            produtora->nomeDoResponsavel,
            produtora->telefoneDoResponsavel,
            produtora->margemDeLucro);

    fclose(arquivo);
    return 1;
}

int produtoraLerTXT(TipoProdutora *produtora) {
    FILE *arquivo = fopen("dados/produtora.txt", "r");
    if (arquivo == NULL) return 0;

    // le os 10 atributos do arquivo, se n der os 10, retorna erro
    if (fscanf(arquivo, "%99[^,],%99[^,],%19[^,],%19[^,],%99[^,],%19[^,],%99[^,],%49[^,],%19[^,],%f\n",
               produtora->nomeFantasia,
               produtora->razaoSocial,
               produtora->inscricaoEstadual,
               produtora->cnpj,
               produtora->endereco,
               produtora->telefone,
               produtora->email,
               produtora->nomeDoResponsavel,
               produtora->telefoneDoResponsavel,
               &produtora->margemDeLucro) != 10) {
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    return 1;
}

int produtoraSalvarBIN(TipoProdutora *produtora) {
    FILE *arquivo = fopen("dados/produtora.bin", "wb");
    if (arquivo == NULL) return 0;

    if (fwrite(produtora, sizeof(TipoProdutora), 1, arquivo) != 1) {
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    return 1;
}

int produtoraLerBIN(TipoProdutora *produtora) {
    FILE *arquivo = fopen("dados/produtora.bin", "rb");
    if (arquivo == NULL) return 0;

    if (fread(produtora, sizeof(TipoProdutora), 1, arquivo) != 1) {
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    return 1;
}