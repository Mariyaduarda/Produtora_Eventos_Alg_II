#include "recebeDados.h"

// Recebe um ID
int recebeID() {
    int id;
    //enquanto o id for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o ID (maior ou igual a 0):\n");

        //le o id
        scanf("%d", &id);
        getchar(); // Limpa o buffer do teclado

    } while (id < 0);

    return id;
}

// Recebe um nome
void recebeNome(char *nome, int maxTam) {
    //enquanto o nome for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o nome (max %d caracteres):\n", maxTam - 1);

        //le o nome
        fgets(nome, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nome[strcspn(nome, "\n")] = 0;

    } while (strlen(nome) == 0 || strlen(nome) >= maxTam);
}

// Recebe um CPF
void recebeCPF(char *cpf) {
    //enquanto o cpf for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o CPF (somente numeros, 11 digitos):\n");

        //le o cpf
        fgets(cpf, 12, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        cpf[strcspn(cpf, "\n")] = 0;

    } while (strlen(cpf) > 11);
}

// Recebe um CNPJ
void recebeCNPJ(char *cnpj) {
    //enquanto o cnpj for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o CNPJ (somente numeros, 14 digitos):\n");

        //le o cnpj
        fgets(cnpj, 15, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        cnpj[strcspn(cnpj, "\n")] = 0;

    } while (strlen(cnpj) > 14);
}

// Recebe um telefone
void recebeTelefone(char *telefone) {
    //enquanto o telefone for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o telefone (somente numeros, max 15 digitos):\n");

        //le o telefone
        fgets(telefone, 16, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        telefone[strcspn(telefone, "\n")] = 0;

    } while (strlen(telefone) == 0 || strlen(telefone) > 15);
}

// Recebe um email
void recebeEmail(char *email, int maxTam) {
    //enquanto o email for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o email (max %d caracteres):\n", maxTam - 1);

        //le o email
        fgets(email, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        email[strcspn(email, "\n")] = 0;

    } while (strlen(email) == 0 || strlen(email) >= maxTam);
}

// Recebe um nome de contato
void recebeNomeDoContato(char *nomeDoContato, int maxTam) {
    //enquanto o nome do contato for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o nome do contato (max %d caracteres):\n", maxTam - 1);

        //le o nome do contato
        fgets(nomeDoContato, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeDoContato[strcspn(nomeDoContato, "\n")] = 0;

    } while (strlen(nomeDoContato) == 0 || strlen(nomeDoContato) >= maxTam);
}

// Recebe uma funcao
void recebeFuncao(char *funcao, int maxTam) {
    //enquanto a funcao for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a funcao (max %d caracteres):\n", maxTam - 1);

        //le a funcao
        fgets(funcao, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        funcao[strcspn(funcao, "\n")] = 0;

    } while (strlen(funcao) == 0 || strlen(funcao) >= maxTam);
}

// Recebe um valor de diaria
float recebeValorDiaria() {
    float valor;
    //enquanto o valor for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o valor da diaria (maior ou igual a 0):\n");

        //le o valor
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

    } while (valor < 0);

    return valor;
}

// Recebe um valor de hora
float recebeValorHora() {
    float valor;
    //enquanto o valor for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o valor da hora (maior ou igual a 0):\n");

        //le o valor
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

    } while (valor < 0);

    return valor;
}

// Recebe um nome fantasia
void recebeNomeFantasia(char *nomeFantasia, int maxTam) {
    //enquanto o nome fantasia for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o nome fantasia (max %d caracteres):\n", maxTam - 1);

        //le o nome fantasia
        fgets(nomeFantasia, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeFantasia[strcspn(nomeFantasia, "\n")] = 0;

    } while (strlen(nomeFantasia) == 0 || strlen(nomeFantasia) >= maxTam);
}

// Recebe uma razao social
void recebeRazaoSocial(char *razaoSocial, int maxTam) {
    //enquanto a razao social for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a razao social (max %d caracteres):\n", maxTam - 1);

        //le a razao social
        fgets(razaoSocial, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        razaoSocial[strcspn(razaoSocial, "\n")] = 0;

    } while (strlen(razaoSocial) == 0 || strlen(razaoSocial) >= maxTam);
}

// Recebe um endereco
void recebeEndereco(char *endereco, int maxTam) {
    //enquanto o endereco for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o endereco (max %d caracteres):\n", maxTam - 1);

        //le o endereco
        fgets(endereco, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        endereco[strcspn(endereco, "\n")] = 0;

    } while (strlen(endereco) == 0 || strlen(endereco) >= maxTam);
}

// Recebe um tipo de servico
void recebeTipoServico(char *tipoServico, int maxTam) {
    //enquanto o tipo de servico for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o tipo de servico (max %d caracteres):\n", maxTam - 1);

        //le o tipo de servico
        fgets(tipoServico, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        tipoServico[strcspn(tipoServico, "\n")] = 0;

    } while (strlen(tipoServico) == 0 || strlen(tipoServico) >= maxTam);
}

// Recebe um nome de usuario
void recebeNomeUsuario(char *nomeUsuario, int maxTam) {
    //enquanto o nome de usuario for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o nome de usuario (max %d caracteres):\n", maxTam - 1);

        //le o nome de usuario
        fgets(nomeUsuario, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeUsuario[strcspn(nomeUsuario, "\n")] = 0;

    } while (strlen(nomeUsuario) == 0 || strlen(nomeUsuario) >= maxTam);
}

// Recebe uma senha
void recebeSenha(char *senha, int maxTam) {
    //enquanto a senha for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a senha (max %d caracteres):\n", maxTam - 1);

        //le a senha
        fgets(senha, maxTam, stdin);
        // tira o \n do final da string, ja que o fgets pega ele
        senha[strcspn(senha, "\n")] = 0;

    } while (strlen(senha) == 0 || strlen(senha) >= maxTam);
}

// Recebe uma inscricao estadual
void recebeInscricaoEstadual(char *inscricaoEstadual) {
    //enquanto a inscricao estadual for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a inscricao estadual (somente numeros, 10 digitos):\n");

        //le a inscricao estadual
        fgets(inscricaoEstadual, 11, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        inscricaoEstadual[strcspn(inscricaoEstadual, "\n")] = 0;

    } while (strlen(inscricaoEstadual) != 10);
}

// Recebe uma margem de lucro
float recebeMargemDeLucro() {
    float margem;
    //enquanto a margem de lucro for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a margem de lucro (entre 0 e 100):\n");

        //le a margem de lucro
        scanf("%f", &margem);
        getchar(); // Limpa o buffer do teclado

    } while (margem < 0 || margem > 100);

    return margem;
}

// Recebe uma descricao
void recebeDescricao(char *descricao, int maxTam) {
    //enquanto a descricao for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a descricao (max %d caracteres):\n", maxTam - 1);

        //le a descricao
        fgets(descricao, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        descricao[strcspn(descricao, "\n")] = 0;

    } while (strlen(descricao) == 0 || strlen(descricao) >= maxTam);
}

// Recebe uma categoria
void recebeCategoria(char *categoria, int maxTam) {
    //enquanto a categoria for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a categoria (max %d caracteres):\n", maxTam - 1);

        //le a categoria
        fgets(categoria, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        categoria[strcspn(categoria, "\n")] = 0;

    } while (strlen(categoria) == 0 || strlen(categoria) >= maxTam);
}

// Recebe uma quantidade em estoque
int recebeQuantidadeEstoque() {
    int qtd;
    //enquanto a quantidade em estoque for invalida, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite a quantidade em estoque (maior ou igual a 0):\n");

        //le a quantidade em estoque
        scanf("%d", &qtd);
        getchar(); // Limpa o buffer do teclado

    } while (qtd < 0);

    return qtd;
}

// Recebe um preco de custo
float recebePrecoCusto() {
    float preco;
    //enquanto o preco de custo for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o preco de custo (maior ou igual a 0):\n");

        //le o preco de custo
        scanf("%f", &preco);
        getchar(); // Limpa o buffer do teclado

    } while (preco < 0);

    return preco;
}

// Recebe um valor de locacao
float recebeValorLocacao() {
    float valor;
    //enquanto o valor de locacao for invalido, pede para digitar novamente
    do {
        //mensagem pro usuario
        printf("\n => Digite o valor de locacao (maior ou igual a 0):\n");

        //le o valor de locacao
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

    } while (valor < 0);

    return valor;
}