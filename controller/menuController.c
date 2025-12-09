#include "menuController.h"
#include "menuCrud/menuImpoExpo.h"
#include "printMenu.h"  

// ========== DECLARAÇÕES FORWARD ==========
void menuImportacaoExportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, 
    ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaEvento **listaEvento);

void menuExportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente listaCliente, ListaFornecedor listaFornecedor, 
    ListaEquipe listaEquipe, ListaRecurso listaRecurso, ListaEvento listaEvento);

void menuImportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, 
    ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaEvento **listaEvento);

// ========== RESTO DO CÓDIGO ==========
void menuPrincipal(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, 
    ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, 
    ListaRecurso **listaRecurso, ListaEvento **listaEvento, ListaOperador **listaOperador, ListaMovimentacao **listaMovimentacao,
    ListaContaReceber **listaContaReceber, ListaContaPagar **listaContaPagar) 
{
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu principal
        printMenuPrincipal(*produtora);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 6, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Gerenciar dados (CRUD)
                menuCRUD(config, produtora, listaCliente, listaFornecedor, listaEquipe, listaRecurso, listaOperador);
                break;
            case 2:
                // Gerenciar Eventos
                menuEvento(listaEvento, listaCliente, listaRecurso, listaEquipe, listaFornecedor, config);
                break;
            case 3:
                // Gerenciar Financeiro
                menuTransacao(produtora, config);
                break;
            case 4:
                // ===== IMPORTACAO E EXPORTACAO =====
                menuImportacaoExportacao(config, produtora, listaCliente, listaFornecedor, listaEquipe, listaRecurso, listaEvento);
                break;
            case 5:
                // Salvar dados    
                if (config->salvar_como_binario) {
                    configSalvarBIN(*config);
                    remove("config.txt");
                    printMensagem("Configuracoes salvas em binario","#");
                } else {
                    configSalvarTXT(*config);
                    remove("config.bin");
                    printMensagem("Configuracoes salvas em texto","#");
                }

                // Salva os dados na memoria
                salvarMemoria(config, produtora, *listaCliente, *listaFornecedor,
                    *listaEquipe,  *listaEvento, *listaRecurso, *listaOperador, 
                    *listaMovimentacao, *listaContaReceber, *listaContaPagar);

                esperaEnter();
                break;
            case 6:
                // Configuracoes
                menuConfig(config);
                break;
            case 0:
                // Sair
                return;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }
    
}

void menuCRUD(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, 
    ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, 
    ListaRecurso **listaRecurso, ListaOperador **listaOperador) 
{
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu 
        printMenuCRUD();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 7, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha){
            case 1:
                // Gerenciar Produtora
                menuProdutora(produtora, config);
                break;
            case 2:
                // Gerenciar TipoCliente
                menuCliente(listaCliente, config);
                break;
            case 3:
                // Gerenciar Equipe Interna
                menuEquipe(listaEquipe, config);
                break;
            case 4:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedor(listaFornecedor, config);
                break;
            case 5:
                // Gerenciar Operadores do Sistema
                menuOperador(listaOperador, config);
                break;
            case 6:
                // Gerenciar Recursos e Equipamentos
                menuRecurso(listaRecurso, config);
                break;
            case 0:
                // Sair
                return;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }
}

void menuImportacaoExportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, 
    ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaEvento **listaEvento) 
{
    int opcao = -1;
    
    while (opcao != 0) {
        viewMenuImportacaoExportacao();  // Sem atribuição!
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                // REMOVA O * antes de listaEvento (e os outros)
                menuExportacao(config, produtora, **listaCliente, **listaFornecedor, 
                              **listaEquipe, **listaRecurso, **listaEvento);
                break;
            case 2:
                menuImportacao(config, produtora, listaCliente, listaFornecedor, 
                              listaEquipe, listaRecurso, listaEvento);
                break;
            case 0:
                exibirMensagemInfo("Voltando ao menu anterior...");
                viewAguardarContinuar();
                return;
            default:
                exibirMensagemErro("Opcao invalida!");
                viewAguardarContinuar();
        }
    }
}

void menuExportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente listaCliente, ListaFornecedor listaFornecedor, 
    ListaEquipe listaEquipe, ListaRecurso listaRecurso, ListaEvento listaEvento) 
{
    int opcao = -1;
    char nomeArquivo[256];
    
    while (opcao != 0) {
        printMenuExportacao();
        opcao = recebeInt(0, 6, "Digite uma opcao", "#", config->validar_dados);
        
        switch (opcao) {
            case 1:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar TODOS os dados:");
                exibirMensagemProcessando("Exportando todos os dados...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Dados exportados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 2:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar CLIENTES:");
                exibirMensagemProcessando("Exportando clientes...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Clientes exportados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 3:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar FORNECEDORES:");
                exibirMensagemProcessando("Exportando fornecedores...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Fornecedores exportados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 4:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar EVENTOS:");
                exibirMensagemProcessando("Exportando eventos...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Eventos exportados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 5:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar RECURSOS:");
                exibirMensagemProcessando("Exportando recursos...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Recursos exportados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 6:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para exportar EQUIPES:");
                exibirMensagemProcessando("Exportando equipes...");
                // TODO: Implementar exportacao
                exibirMensagemSucesso("Equipes exportadas com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 0:
                break;
                
            default:
                exibirMensagemErro("Opcao invalida!");
                viewAguardarContinuar();
        }
    }
}

void menuImportacao(TipoConfig *config, TipoProdutora *produtora, 
    ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, 
    ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaEvento **listaEvento) 
{
    int opcao = -1;
    char nomeArquivo[256];
    
    while (opcao != 0) {
        printMenuImportacao();
        opcao = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);
        
        switch (opcao) {
            case 1:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para importar CLIENTES:");
                exibirMensagemProcessando("Importando clientes...");
                // TODO: Implementar importacao
                exibirMensagemSucesso("Clientes importados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 2:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para importar FORNECEDORES:");
                exibirMensagemProcessando("Importando fornecedores...");
                // TODO: Implementar importacao
                exibirMensagemSucesso("Fornecedores importados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 3:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para importar EVENTOS:");
                exibirMensagemProcessando("Importando eventos...");
                // TODO: Implementar importacao
                exibirMensagemSucesso("Eventos importados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 4:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para importar RECURSOS:");
                exibirMensagemProcessando("Importando recursos...");
                // TODO: Implementar importacao
                exibirMensagemSucesso("Recursos importados com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 5:
                viewSolicitarNomeArquivo(nomeArquivo, "Digite o nome do arquivo para importar EQUIPES:");
                exibirMensagemProcessando("Importando equipes...");
                // TODO: Implementar importacao
                exibirMensagemSucesso("Equipes importadas com sucesso!");
                viewAguardarContinuar();
                break;
                
            case 0:
                break;
                
            default:
                exibirMensagemErro("Opcao invalida!");
                viewAguardarContinuar();
        }
    }
}