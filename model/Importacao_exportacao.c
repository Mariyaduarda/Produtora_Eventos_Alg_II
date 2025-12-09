/*
 * Módulo de Importação/Exportação - Sistema de Controle Gerencial para Produtora de Eventos
 * Disciplina: Algoritmos II
 * 
 * Implementação das funcionalidades de importação e exportação de dados em formato XML
 */

#include "importacao_exportacao.h"

// ========== FUNÇÕES AUXILIARES PARA XML ==========
void escreverTagXML(FILE* arquivo, const char* tag, const char* valor, int nivel) {
    for (int i = 0; i < nivel; i++) fprintf(arquivo, "  ");
    fprintf(arquivo, "<%s>%s</%s>\n", tag, valor, tag);
}

void escreverTagXMLInt(FILE* arquivo, const char* tag, int valor, int nivel) {
    for (int i = 0; i < nivel; i++) fprintf(arquivo, "  ");
    fprintf(arquivo, "<%s>%d</%s>\n", tag, valor, tag);
}

void escreverTagXMLFloat(FILE* arquivo, const char* tag, float valor, int nivel) {
    for (int i = 0; i < nivel; i++) fprintf(arquivo, "  ");
    fprintf(arquivo, "<%s>%.2f</%s>\n", tag, valor, tag);
}

void abrirTagXML(FILE* arquivo, const char* tag, int nivel) {
    for (int i = 0; i < nivel; i++) fprintf(arquivo, "  ");
    fprintf(arquivo, "<%s>\n", tag);
}

void fecharTagXML(FILE* arquivo, const char* tag, int nivel) {
    for (int i = 0; i < nivel; i++) fprintf(arquivo, "  ");
    fprintf(arquivo, "</%s>\n", tag);
}

// ========== EXPORTAÇÃO ==========

int exportarClientes(TipoCliente* clientes, int totalClientes, FILE* arquivo) {
    if (!arquivo || !clientes) return 0;
    
    abrirTagXML(arquivo, "clientes", 1);
    
    for (int i = 0; i < totalClientes; i++) {
        abrirTagXML(arquivo, "cliente", 2);
        escreverTagXMLInt(arquivo, "id", clientes[i].id, 3);
        escreverTagXMLInt(arquivo, "ativo", clientes[i].ativo ? 1 : 0, 3);
        escreverTagXMLInt(arquivo, "usa_CNPJ", clientes[i].usa_CNPJ ? 1 : 0, 3);
        escreverTagXML(arquivo, "nome", clientes[i].nome, 3);
        escreverTagXML(arquivo, "nomeContato", clientes[i].nomeDoContato, 3);
        escreverTagXML(arquivo, "cpf_cnpj", clientes[i].cpf_cnpj, 3);
        escreverTagXML(arquivo, "email", clientes[i].email, 3);
        escreverTagXML(arquivo, "telefone", clientes[i].telefone, 3);
        escreverTagXML(arquivo, "endereco", clientes[i].endereco, 3);
        fecharTagXML(arquivo, "cliente", 2);
    }
    
    fecharTagXML(arquivo, "clientes", 1);
    return 1;
}

int exportarFornecedores(TipoFornecedor* fornecedores, int totalFornecedores, FILE* arquivo) {
    if (!arquivo || !fornecedores) return 0;
    
    abrirTagXML(arquivo, "fornecedores", 1);
    
    for (int i = 0; i < totalFornecedores; i++) {
        abrirTagXML(arquivo, "fornecedor", 2);
        escreverTagXMLInt(arquivo, "id", fornecedores[i].id, 3);
        escreverTagXMLInt(arquivo, "ativo", fornecedores[i].ativo ? 1 : 0, 3);
        escreverTagXMLInt(arquivo, "usa_CNPJ", fornecedores[i].usa_CNPJ ? 1 : 0, 3);
        escreverTagXML(arquivo, "nomeFantasia", fornecedores[i].nomeFantasia, 3);
        escreverTagXML(arquivo, "razaoSocial", fornecedores[i].razaoSocial, 3);
        escreverTagXML(arquivo, "cpf_cnpj", fornecedores[i].cpf_cnpj, 3);
        escreverTagXML(arquivo, "endereco", fornecedores[i].endereco, 3);
        escreverTagXML(arquivo, "telefone", fornecedores[i].telefone, 3);
        escreverTagXML(arquivo, "tipoServico", fornecedores[i].tipoServico, 3);
        escreverTagXMLInt(arquivo, "tipoValor", fornecedores[i].tipoValor, 3);
        escreverTagXMLFloat(arquivo, "valor", fornecedores[i].valor, 3);
        fecharTagXML(arquivo, "fornecedor", 2);
    }
    
    fecharTagXML(arquivo, "fornecedores", 1);
    return 1;
}

int exportarEventos(TipoEvento* eventos, int totalEventos, FILE* arquivo) {
    if (!arquivo || !eventos) return 0;
    
    abrirTagXML(arquivo, "eventos", 1);
    
    for (int i = 0; i < totalEventos; i++) {
        abrirTagXML(arquivo, "evento", 2);
        escreverTagXMLInt(arquivo, "id", eventos[i].id, 3);
        escreverTagXML(arquivo, "nome", eventos[i].nome, 3);
        
        // Converter data para string
        char dataStr[11];
        strftime(dataStr, sizeof(dataStr), "%Y-%m-%d", &eventos[i].dataInicio);
        escreverTagXML(arquivo, "data", dataStr, 3);
        
        escreverTagXML(arquivo, "local", eventos[i].localEvento, 3);
        escreverTagXMLFloat(arquivo, "orcamento", eventos[i].valorFinal, 3);
        escreverTagXMLInt(arquivo, "idCliente", eventos[i].idCliente, 3);
        
        // Converter status enum para string
        const char* statusStr;
        switch(eventos[i].status) {
            case STATUS_APROVADO: statusStr = "confirmado"; break;
            case STATUS_ORCAMENTO: statusStr = "pendente"; break;
            case STATUS_CANCELADO: statusStr = "cancelado"; break;
            case STATUS_FINALIZADO: statusStr = "finalizado"; break;
            default: statusStr = "desconhecido"; break;
        }
        escreverTagXML(arquivo, "status", statusStr, 3);
        
        fecharTagXML(arquivo, "evento", 2);
    }
    
    fecharTagXML(arquivo, "eventos", 1);
    return 1;
}
int exportarRecurso(TipoRecurso* recursos, int totalRecursos, FILE* arquivo) {
    if (!arquivo || !recursos) return 0;
    
    abrirTagXML(arquivo, "recursos", 1);
    
    for (int i = 0; i < totalRecursos; i++) {
        abrirTagXML(arquivo, "recurso", 2);
        escreverTagXMLInt(arquivo, "id", recursos[i].id, 3);
        escreverTagXML(arquivo, "descricao", recursos[i].descricao, 3);
        escreverTagXML(arquivo, "categoria", recursos[i].categoria, 3);
        escreverTagXMLInt(arquivo, "quantidade", recursos[i].qtdEstoque, 3);
        escreverTagXMLFloat(arquivo, "precoCusto", recursos[i].precoCusto, 3);
        escreverTagXMLFloat(arquivo, "valorLocacao", recursos[i].valorLocacao, 3);
        fecharTagXML(arquivo, "recurso", 2);
    }
    
    fecharTagXML(arquivo, "recursos", 1);
    return 1;
}

int exportarEquipe(TipoEquipe* equipes, int totalEquipes, FILE* arquivo) {
    if (!arquivo || !equipes) return 0;
    
    abrirTagXML(arquivo, "equipes", 1);
    
    for (int i = 0; i < totalEquipes; i++) {
        abrirTagXML(arquivo, "equipe", 2);
        escreverTagXMLInt(arquivo, "id", equipes[i].id, 3);
        escreverTagXMLInt(arquivo, "ativo", equipes[i].ativo ? 1 : 0, 3);
        escreverTagXML(arquivo, "nome", equipes[i].nome, 3);
        escreverTagXML(arquivo, "cpf", equipes[i].cpf, 3);
        escreverTagXML(arquivo, "funcao", equipes[i].funcao, 3);
        escreverTagXMLInt(arquivo, "tipoValor", equipes[i].tipoValor, 3);
        escreverTagXMLFloat(arquivo, "valor", equipes[i].valor, 3);
        fecharTagXML(arquivo, "equipe", 2);
    }
    
    fecharTagXML(arquivo, "equipes", 1);
    return 1;
}

void exportarDados(TipoCliente* cliente, int totalClientes,
                   TipoFornecedor* fornecedores, int totalFornecedores,
                   TipoEvento* eventos, int totalEventos, 
                   TipoRecurso* recursos, int totalRecursos,
                   TipoEquipe* equipes, int totalEquipes, 
                   int exportarCli, int exportarEquip, int exportarEv) {
    
    FILE* arquivo = fopen("dados_exportados.xml", "w");
    
    if (!arquivo) {
        printf("Erro ao criar arquivo de exportação!\n");
        return;
    }
    
    fprintf(arquivo, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    abrirTagXML(arquivo, "sistema_eventos", 0);
    
    if (exportarCli && cliente && totalClientes > 0) {
        exportarClientes(cliente, totalClientes, arquivo);
    }
    
    if (fornecedores && totalFornecedores > 0) {
        exportarFornecedores(fornecedores, totalFornecedores, arquivo);
    }
    
    if (exportarEv && eventos && totalEventos > 0) {
        exportarEventos(eventos, totalEventos, arquivo);
    }
    
    if (recursos && totalRecursos > 0) {
        exportarRecurso(recursos, totalRecursos, arquivo);
    }
    
    if (exportarEquip && equipes && totalEquipes > 0) {
        exportarEquipe(equipes, totalEquipes, arquivo);
    }
    
    fecharTagXML(arquivo, "sistema_eventos", 0);
    fclose(arquivo);
    
    printf("\n✓ Dados exportados com sucesso para 'dados_exportados.xml'!\n");
}

// ========== IMPORTAÇÃO ==========

int extrairValorTag(const char* linha, const char* tag, char* destino) {
    char tagAbertura[100], tagFechamento[100];
    sprintf(tagAbertura, "<%s>", tag);
    sprintf(tagFechamento, "</%s>", tag);
    
    char* inicio = strstr(linha, tagAbertura);
    if (!inicio) return 0;
    
    inicio += strlen(tagAbertura);
    char* fim = strstr(inicio, tagFechamento);
    if (!fim) return 0;
    
    int tamanho = fim - inicio;
    strncpy(destino, inicio, tamanho);
    destino[tamanho] = '\0';
    
    return 1;
}

int extrairValorTagInt(const char* linha, const char* tag) {
    char valor[100];
    if (extrairValorTag(linha, tag, valor)) {
        return atoi(valor);
    }
    return 0;
}

float extrairValorTagFloat(const char* linha, const char* tag) {
    char valor[100];
    if (extrairValorTag(linha, tag, valor)) {
        return atof(valor);
    }
    return 0.0f;
}

int importarClientes(const char* nomeArquivo, TipoCliente** clientes, int* totalClientes) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s!\n", nomeArquivo);
        return 0;
    }
    
    char linha[500];
    int capacidade = 10;
    *clientes = (TipoCliente*)malloc(capacidade * sizeof(TipoCliente));
    *totalClientes = 0;
    
    int dentroCliente = 0;
    TipoCliente clienteTemp;
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "<cliente>")) {
            dentroCliente = 1;
            memset(&clienteTemp, 0, sizeof(TipoCliente));
        }
        else if (strstr(linha, "</cliente>")) {
            if (*totalClientes >= capacidade) {
                capacidade *= 2;
                *clientes = (TipoCliente*)realloc(*clientes, capacidade * sizeof(TipoCliente));
            }
            (*clientes)[*totalClientes] = clienteTemp;
            (*totalClientes)++;
            dentroCliente = 0;
        }
        else if (dentroCliente) {
            if (strstr(linha, "<id>")) {
                clienteTemp.id = extrairValorTagInt(linha, "id");
            }
            else if (strstr(linha, "<ativo>")) {
                clienteTemp.ativo = extrairValorTagInt(linha, "ativo") != 0;
            }
            else if (strstr(linha, "<usa_CNPJ>")) {
                clienteTemp.usa_CNPJ = extrairValorTagInt(linha, "usa_CNPJ") != 0;
            }
            else if (strstr(linha, "<nomeFantasia>")) {
                extrairValorTag(linha, "nome", clienteTemp.nome);
            }
            else if (strstr(linha, "<razaoSocial>")) {
                extrairValorTag(linha, "nomeDoContato", clienteTemp.nomeDoContato);
            }
            else if (strstr(linha, "<cpf_cnpj>")) {
                extrairValorTag(linha, "cpf_cnpj", clienteTemp.cpf_cnpj);
            }
            else if (strstr(linha, "<email>")) {
                extrairValorTag(linha, "email", clienteTemp.email);
            }
            else if (strstr(linha, "<telefone>")) {
                extrairValorTag(linha, "telefone", clienteTemp.telefone);
            }
            else if (strstr(linha, "<endereco>")) {
                extrairValorTag(linha, "endereco", clienteTemp.endereco);
            }
        }
    }
    
    fclose(arquivo);
    printf("\n✓ %d cliente(s) importado(s) com sucesso!\n", *totalClientes);
    return 1;
}

int importarFornecedores(const char* nomeArquivo, TipoFornecedor** fornecedores, int* totalFornecedores) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s!\n", nomeArquivo);
        return 0;
    }
    
    char linha[500];
    int capacidade = 10;
    *fornecedores = (TipoFornecedor*)malloc(capacidade * sizeof(TipoFornecedor));
    *totalFornecedores = 0;
    
    int dentroFornecedor = 0;
    TipoFornecedor fornecedorTemp;
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "<fornecedor>")) {
            dentroFornecedor = 1;
            memset(&fornecedorTemp, 0, sizeof(TipoFornecedor));
        }
        else if (strstr(linha, "</fornecedor>")) {
            if (*totalFornecedores >= capacidade) {
                capacidade *= 2;
                *fornecedores = (TipoFornecedor*)realloc(*fornecedores, capacidade * sizeof(TipoFornecedor));
            }
            (*fornecedores)[*totalFornecedores] = fornecedorTemp;
            (*totalFornecedores)++;
            dentroFornecedor = 0;
        }
        else if (dentroFornecedor) {
            if (strstr(linha, "<id>")) {
                fornecedorTemp.id = extrairValorTagInt(linha, "id");
            }
            else if (strstr(linha, "<ativo>")) {
                fornecedorTemp.ativo = extrairValorTagInt(linha, "ativo") != 0;
            }
            else if (strstr(linha, "<usa_CNPJ>")) {
                fornecedorTemp.usa_CNPJ = extrairValorTagInt(linha, "usa_CNPJ") != 0;
            }
            else if (strstr(linha, "<nomeFantasia>")) {
                extrairValorTag(linha, "nomeFantasia", fornecedorTemp.nomeFantasia);
            }
            else if (strstr(linha, "<razaoSocial>")) {
                extrairValorTag(linha, "razaoSocial", fornecedorTemp.razaoSocial);
            }
            else if (strstr(linha, "<cpf_cnpj>")) {
                extrairValorTag(linha, "cpf_cnpj", fornecedorTemp.cpf_cnpj);
            }
            else if (strstr(linha, "<endereco>")) {
                extrairValorTag(linha, "endereco", fornecedorTemp.endereco);
            }
            else if (strstr(linha, "<telefone>")) {
                extrairValorTag(linha, "telefone", fornecedorTemp.telefone);
            }
            else if (strstr(linha, "<tipoServico>")) {
                extrairValorTag(linha, "tipoServico", fornecedorTemp.tipoServico);
            }
            else if (strstr(linha, "<tipoValor>")) {
                fornecedorTemp.tipoValor = extrairValorTagInt(linha, "tipoValor");
            }
            else if (strstr(linha, "<valor>")) {
                fornecedorTemp.valor = extrairValorTagFloat(linha, "valor");
            }
        }
    }
    
    fclose(arquivo);
    printf("\n✓ %d fornecedor(es) importado(s) com sucesso!\n", *totalFornecedores);
    return 1;
}

int importarEventos(const char* nomeArquivo, TipoEvento** eventos, int* totalEventos) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo %s!\n", nomeArquivo);
        return 0;
    }
    
    char linha[500];
    int capacidade = 10;
    *eventos = (TipoEvento*)malloc(capacidade * sizeof(TipoEvento));
    *totalEventos = 0;
    
    int dentroEvento = 0;
    TipoEvento eventoTemp;
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "<evento>")) {
            dentroEvento = 1;
            memset(&eventoTemp, 0, sizeof(TipoEvento));
        }
        else if (strstr(linha, "</evento>")) {
            if (*totalEventos >= capacidade) {
                capacidade *= 2;
                *eventos = (TipoEvento*)realloc(*eventos, capacidade * sizeof(TipoEvento));
            }
            (*eventos)[*totalEventos] = eventoTemp;
            (*totalEventos)++;
            dentroEvento = 0;
        }
        else if (dentroEvento) {
            if (strstr(linha, "<id>")) {
                eventoTemp.id = extrairValorTagInt(linha, "id");
            }
            else if (strstr(linha, "<nome>")) {
                extrairValorTag(linha, "nome", eventoTemp.nome);
            }
            else if (strstr(linha, "<data>")) {
                char dataStr[20];
                extrairValorTag(linha, "data", dataStr);
                // Parse data YYYY-MM-DD para struct tm
                sscanf(dataStr, "%d-%d-%d", 
                       &eventoTemp.dataInicio.tm_year,
                       &eventoTemp.dataInicio.tm_mon,
                       &eventoTemp.dataInicio.tm_mday);
                eventoTemp.dataInicio.tm_year -= 1900;
                eventoTemp.dataInicio.tm_mon -= 1;
            }
            else if (strstr(linha, "<local>")) {
                extrairValorTag(linha, "local", eventoTemp.localEvento);
            }
            else if (strstr(linha, "<orcamento>")) {
                eventoTemp.valorFinal = extrairValorTagFloat(linha, "orcamento");
            }
            else if (strstr(linha, "<idCliente>")) {
                eventoTemp.idCliente = extrairValorTagInt(linha, "idCliente");
            }
            else if (strstr(linha, "<status>")) {
                char statusStr[20];
                extrairValorTag(linha, "status", statusStr);
                if (strcmp(statusStr, "confirmado") == 0) {
                    eventoTemp.status = STATUS_APROVADO;
                } else if (strcmp(statusStr, "pendente") == 0) {
                    eventoTemp.status = STATUS_ORCAMENTO;
                } else if (strcmp(statusStr, "cancelado") == 0) {
                    eventoTemp.status = STATUS_CANCELADO;
                } else if (strcmp(statusStr, "finalizado") == 0) {
                    eventoTemp.status = STATUS_FINALIZADO;
                }
            }
        }
    }
    
    fclose(arquivo);
    printf("\n✓ %d evento(s) importado(s) com sucesso!\n", *totalEventos);
    return 1;
}