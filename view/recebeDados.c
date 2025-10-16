#include "recebeDados.h"

//=======================================================
// RECEBE OS TIPOS

// Recebe uma String
void recebeString(char *str, int maxTam, char *msg1, char *msg2){
    // Recebe uma String de no maximo 'maxTam' caracteres
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe a string
        fgets(str, maxTam, stdin);
        str[strcspn(str, "\n")] = 0; // remove \n
        
        // Confere se a string e' valida
        if (strlen(str) > 0 && strlen(str) < maxTam) break;
        printMensagem("Tamanho excede o maximo!","ERRO");
    }
}

// Recebe um inteiro entre min e max
int recebeInt(int min, int max, char *msg1, char *msg2){
    int n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o inteiro
        scanf("%d",&n);
        getchar(); // Limpa o buffer do teclado
        
        // Confere se o int e' valido
        if (n >= min && n <= max) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

// Recebe um float entre min e max
float recebeFloat(float min, float max, char *msg1, char *msg2){
    float n;
    while (1) {
        // Mostra a mensagem
        printMensagem(msg1, msg2);
        printf("\n => ");

        // Realmente recebe o float
        scanf("%f",&n);
        getchar(); // Limpa o buffer do teclado
        
        // Confere se o float e' valido
        if (n >= min && n <= max) break;
        printMensagem("Valor excede os limites!","ERRO");
    }
    return n;
}

//=======================================================
// RECEBE COM VALIDACAO

// Recebe um cpf em string - ja faz a validacao
void recebeCPF(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CPF","11 Digitos");

        // aqui vai a validacao
        if (validarCPF(str)) break;
        printMensagem("CPF invalido!","ERRO");
    }
}

// Recebe um CNPJ em string - ja faz a validacao
void recebeCNPJ(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o CNPJ","14 Digitos");

        // aqui vai a validacao
        if (validarCNPJ(str)) break;
        printMensagem("CNPJ invalido!","ERRO");
    }
}

// Recebe um Email em string - ja faz a validacao
void recebeEmail(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 100, "Digite o Email","Max. 100");

        // aqui vai a validacao
        if (validarEmail(str)) break;
        printMensagem("Email invalido!","ERRO");
    }
}

// Recebe um Telefone em string - ja faz a validacao
void recebeTelefone(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Telefone","10 ou 11 Digitos");

        // aqui vai a validacao
        if (validarTelefone(str)) break;
        printMensagem("Telefone invalido!","ERRO");
    }

}

void recebeSenha(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite a senha","No minimo que tenha: "
                                               "ou letra maiscul, ou minuscula ou caracteres "
                                               "especiais ou numeros");
        // aqui vai a validacao
        if (validarSenha(str)) break;
        printMensagem("Senha invalida!","ERRO");
    }
}

void recebeNome(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Nome","no minimo 3 caracteres");

        // aqui vai a validacao
        if (validarNome(str)) break;
        printMensagem("Nome invalido!","ERRO");
    }
}

void recebeUsuario(char *str){
    while (1){
        // recebe o dado em si
        recebeString(str, 20, "Digite o Usuario"," de 3 até 20 digitos");

        // aqui vai a validacao
        if (validarUsuario(str)) break;
        printMensagem("Usuario invalido!","ERRO");
    }
}

int recebeID(){
    return recebeInt(1, 1000000, "Digite o ID", "Min. 1");
}

//=======================================================
//VELHO
/*
// Recebe um ID
int recebeID() {
    int id;
    //enquanto o id for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o ID ]=============================================[Min. 1] ");
        printf("\n => ");

        //le o id
        scanf("%d", &id);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (id >= 1) break;
        printValorInvalido();
    }

    return id;
}

// Recebe um nome
void recebeNome(char *nome, int maxTam) {
    //enquanto o nome for invalido, pede para digitar novamente

    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o nome ]==============================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");


        //le o nome
        fgets(nome, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nome[strcspn(nome, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(nome) > 0 && strlen(nome) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um CPF
void recebeCPF(char *cpf) {
    //enquanto o cpf for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o CPF ]========================================[11 digitos] ");
        printf("\n => ");

        //le o cpf
        fgets(cpf, 12, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        cpf[strcspn(cpf, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(cpf) <= 11) break;
        printValorInvalido();
    }
    
}

// Recebe um CNPJ
void recebeCNPJ(char *cnpj) {
    //enquanto o cnpj for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o CNPJ ]=======================================[14 digitos] ");
        printf("\n => ");

        //le o cnpj
        fgets(cnpj, 15, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        cnpj[strcspn(cnpj, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(cnpj) <= 14) break;
        printValorInvalido();
    }
}

// Recebe um telefone
void recebeTelefone(char *telefone) {
    //enquanto o telefone for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Telefone ]=============================[10 ou 11 digitos] ");
        printf("\n => ");

        //le o telefone
        fgets(telefone, 12, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        telefone[strcspn(telefone, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(telefone) <= 10 || strlen(telefone) <= 11) break;
        printValorInvalido();
    }
}

// Recebe um email
void recebeEmail(char *email, int maxTam) {
    //enquanto o email for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Email ]=============================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o email
        fgets(email, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        email[strcspn(email, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(email) > 0 && strlen(email) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um nome de contato
void recebeNomeDoContato(char *nomeDoContato, int maxTam) {
    //enquanto o nome do contato for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Nome do Contato ]===================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o nome do contato
        fgets(nomeDoContato, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeDoContato[strcspn(nomeDoContato, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(nomeDoContato) > 0 && strlen(nomeDoContato) < maxTam) break;
        printValorInvalido();
    }
    
}

// Recebe uma funcao
void recebeFuncao(char *funcao, int maxTam) {
    //enquanto a funcao for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Funcao ]============================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le a funcao
        fgets(funcao, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        funcao[strcspn(funcao, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(funcao) > 0 && strlen(funcao) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um valor de diaria
float recebeValorDiaria() {
    float valor;
    //enquanto o valor for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Valor da Diaria ]================================[Min. 0] ");
        printf("\n => ");

        //le o valor
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (valor >= 0) break;
        printValorInvalido();
    }

    return valor;
}

// Recebe um valor de hora
float recebeValorHora() {
    float valor;
    //enquanto o valor for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Valor da Hora ]==================================[Min. 0] ");
        printf("\n => ");

        //le o valor
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (valor >= 0) break;
        printValorInvalido();
    }

    return valor;
}

// Recebe um nome fantasia
void recebeNomeFantasia(char *nomeFantasia, int maxTam) {
    //enquanto o nome fantasia for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Nome Fantasia ]=====================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o nome fantasia
        fgets(nomeFantasia, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeFantasia[strcspn(nomeFantasia, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(nomeFantasia) > 0 && strlen(nomeFantasia) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe uma razao social
void recebeRazaoSocial(char *razaoSocial, int maxTam) {
    //enquanto a razao social for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Razao Social ]======================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le a razao social
        fgets(razaoSocial, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        razaoSocial[strcspn(razaoSocial, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(razaoSocial) > 0 && strlen(razaoSocial) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um endereco
void recebeEndereco(char *endereco, int maxTam) {
    //enquanto o endereco for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Endereco ]==========================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o endereco
        fgets(endereco, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        endereco[strcspn(endereco, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(endereco) > 0 && strlen(endereco) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um tipo de servico
void recebeTipoServico(char *tipoServico, int maxTam) {
    //enquanto o tipo de servico for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Tipo de Servico ]===================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o tipo de servico
        fgets(tipoServico, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        tipoServico[strcspn(tipoServico, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(tipoServico) > 0 && strlen(tipoServico) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe um nome de usuario
void recebeNomeUsuario(char *nomeUsuario, int maxTam) {
    //enquanto o nome de usuario for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Nome de Usuario ]===================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le o nome de usuario
        fgets(nomeUsuario, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        nomeUsuario[strcspn(nomeUsuario, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(nomeUsuario) > 0 && strlen(nomeUsuario) < maxTam) break;
        printValorInvalido();
    }
    
}

// Recebe uma senha
void recebeSenha(char *senha, int maxTam) {
    //enquanto a senha for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Senha ]=============================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le a senha
        fgets(senha, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        senha[strcspn(senha, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(senha) > 0 && strlen(senha) < maxTam) break;
        printValorInvalido();
    }
    
}

// Recebe uma inscricao estadual
void recebeInscricaoEstadual(char *inscricaoEstadual) {
    //enquanto a inscricao estadual for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Inscricao Estadual ]==========================[9 digitos] ");
        printf("\n => ");

        //le a inscricao estadual
        fgets(inscricaoEstadual, 10, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        inscricaoEstadual[strcspn(inscricaoEstadual, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(inscricaoEstadual) <= 9) break;
        printValorInvalido();
    }
    
}

// Recebe uma margem de lucro
float recebeMargemDeLucro() {
    float margem;
    //enquanto a margem de lucro for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Margem de Lucro ]=========================[Entre 0 e 100] ");
        printf("\n => ");

        //le a margem de lucro
        scanf("%f", &margem);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (margem >= 0 && margem <= 100) break;
        printValorInvalido();
    }
    

    return margem;
}

// Recebe uma descricao
void recebeDescricao(char *descricao, int maxTam) {
    //enquanto a descricao for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Descricao ]=========================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le a descricao
        fgets(descricao, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        descricao[strcspn(descricao, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(descricao) > 0 && strlen(descricao) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe uma categoria
void recebeCategoria(char *categoria, int maxTam) {
    //enquanto a categoria for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Categoria ]=========================[Max. %3d caracteres] ", maxTam - 1);
        printf("\n => ");

        //le a categoria
        fgets(categoria, maxTam, stdin);

        // tira o \n do final da string, ja que o fgets pega ele
        categoria[strcspn(categoria, "\n")] = 0;

        //confere se ta tudo ok
        if (strlen(categoria) > 0 && strlen(categoria) < maxTam) break;
        printValorInvalido();
    }
}

// Recebe uma quantidade em estoque
int recebeQuantidadeEstoque() {
    int qtd;
    //enquanto a quantidade em estoque for invalida, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite a Qtd. em Estoque ]================================[Min. 0] ");
        printf("\n => ");

        //le a quantidade em estoque
        scanf("%d", &qtd);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (qtd >= 0) break;
        printValorInvalido();
    }

    return qtd;
}

// Recebe um preco de custo
float recebePrecoCusto() {
    float preco;
    //enquanto o preco de custo for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Preco de Custo ]=================================[Min. 0] ");
        printf("\n => ");

        //le o preco de custo
        scanf("%f", &preco);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (preco >= 0) break;
        printValorInvalido();
    }

    return preco;
}

// Recebe um valor de locacao
float recebeValorLocacao() {
    float valor;
    //enquanto o valor de locacao for invalido, pede para digitar novamente
    while (1)
    {
        //mensagem pro usuario
        printf(" [ Digite o Valor de Locacao ]===============================[Min. 0] ");
        printf("\n => ");

        //le o valor de locacao
        scanf("%f", &valor);
        getchar(); // Limpa o buffer do teclado

        //confere se ta tudo ok
        if (valor >= 0) break;
        printValorInvalido();
    }

    return valor;
}

*/