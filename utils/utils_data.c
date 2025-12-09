
#include "utils_data.h"

int dataParaDias(const struct tm data) {
    // converte uma data em numero de dias desde ano 0
    // ignora um monte de coisa pra simplificar
    return data.tm_year * 365 + data.tm_mon * 30 + data.tm_mday;
}

int periodosConflitam(struct tm i1, struct tm f1, struct tm i2, struct tm f2) {
    // confere se dois periodos de datas tem conflito
    // - i1 e f1 = inicio e fim do periodo A
    // - i2 e f2 = inicio e fim do periodo B

    // converte as datas em valor absoluto de dias
    int A_ini = dataParaDias(i1);
    int A_fim = dataParaDias(f1);

    int B_ini = dataParaDias(i2);
    int B_fim = dataParaDias(f2);

    // se A comeca depois de B acabar, n tem conflito
    if(A_ini > B_fim) return 0;
    // se B comeca depois de A acabar, n tem conflito
    if(B_ini > A_fim) return 0;
    // senao, tem conflito
    else return 1;    
}

int calculaDiferencaDias(struct tm inicio, struct tm fim) {
    // calcula a diferenca em dias entre duas datas
    
    int diasInicio = dataParaDias(inicio);
    int diasFim = dataParaDias(fim);

    return diasFim - diasInicio;
}