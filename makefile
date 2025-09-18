# Compilador e flags
CC = gcc
CFLAGS = -Wall -g

# Nome do executável
TARGET = produtora_eventos.exe


# Diretórios do projeto
SRC_DIRS = . controller controller\menuCrud model model\functions utils view
INCLUDES = -Imodel\entities -Icontroller -Iview -Iutils

# Encontra todos os arquivos .c em todos os diretórios
SRCS = $(wildcard *.c) \
	$(wildcard controller/*.c) \
	$(wildcard controller/menuCrud/*.c) \
	$(wildcard model/*.c) \
	$(wildcard model/functions/*.c) \
	$(wildcard utils/*.c) \
	$(wildcard view/*.c)

# Gera lista de arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJS)
	@echo Compilando o executavel $(TARGET)...
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)

# Como gerar os arquivos objeto
%.o: %.c
	@echo Compilando $<...
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpar arquivos gerados
clean:
	@echo Limpando arquivos gerados...
	del /F /Q *.o 2>nul || exit 0
	del /F /Q controller\*.o 2>nul || exit 0
	del /F /Q controller\menuCrud\*.o 2>nul || exit 0
	del /F /Q model\functions\*.o 2>nul || exit 0
	del /F /Q utils\*.o 2>nul || exit 0
	del /F /Q view\*.o 2>nul || exit 0
	del /F /Q $(TARGET) 2>nul || exit 0
	@echo Limpeza concluida!

# Regra para recompilar tudo
rebuild: clean all

# Marcar alvos que não são arquivos
.PHONY: all clean rebuild
