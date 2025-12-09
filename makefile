CC = gcc
INC_DIRS = model controller controller/menuCRUD utils view
CFLAGS = -Wall -g $(foreach dir,$(INC_DIRS),-I$(dir))

SRC_DIRS = model controller controller/menuCRUD utils view
SRCS = main.c $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS = $(SRCS:.c=.o)
TARGET = main.exe

OBJECTS = main.o \
    model/cliente.o \
    model/config.o \
    model/equipe.o \
    model/evento.o \
    model/feedback.o \
    model/fornecedor.o \
    model/Importacao_exportacao.o \
    model/model_arquivo.o \
    model/operador.o \
    model/produtora.o \
    model/recurso.o \
    model/transacao.o \
    controller/inicializarSistema.o \
    controller/menuController.o \
    controller/menuCrud/menuCliente.o \
    controller/menuCrud/menuConfig.o \
    controller/menuCrud/menuEquipe.o \
    controller/menuCrud/menuEvento.o \
    controller/menuCrud/menuFornecedor.o \
    controller/menuCrud/menuOperador.o \
    controller/menuCrud/menuProdutora.o \
    controller/menuCrud/menuRecurso.o \
    controller/menuCrud/menuTransacao.o \
    controller/menuCrud/menuImpoExpo.o \
    utils/recebeDados.o \
    utils/utils_cores.o \
    utils/utils_data.o \
    utils/utils_tela.o \
    utils/utils_validacoes.o \
    view/mensagens.o \
    view/mostrarItem.o \
    view/printMenu.o

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET) 2>nul || rm -f $(OBJS) $(TARGET)

help:
	@echo "==============================================="
	@echo " HELP - COMANDOS DISPONIVEIS NO MAKEFILE  "
	@echo "==============================================="
	@echo ""
	@echo "   make          || Compila, executa e limpa o projeto"
	@echo "   make clean    || Remove arquivos objetos e o executavel"
	@echo "   make help     || Mostra esta mensagem de ajuda"
	@echo ""
	@echo "-----------------------------------------------"
	@echo "⚙️  Compilador: $(CC)"
	@echo "📂 Diretorios de codigo-fonte: $(SRC_DIRS)"
	@echo "==============================================="
	@echo ""

.PHONY: all clean help
