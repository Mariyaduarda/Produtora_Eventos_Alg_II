#include "menuController.h"

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
        escolha = recebeInt(0, 7, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Gerenciar dados (CRUD)
                menuCRUD(config, produtora, listaCliente, listaFornecedor, listaEquipe, listaRecurso, listaOperador);
                break;
            case 2:
                // Gerenciar Eventos
                menuEvento(NULL, listaEvento, *listaCliente, *listaRecurso, *listaEquipe, *listaFornecedor, config);
                break;
            case 3:
                // Gerenciar Financeiro
                menuTransacao(produtora, config);
                break;
            case 4:
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
            case 5:
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