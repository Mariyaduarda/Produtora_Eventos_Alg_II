CC = gcc
CFLAGS = -Wall -g
SRC_DIRS = model controller controller/menuCrud utils view
SRCS = main.c $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS = $(SRCS:.c=.o)
TARGET = main.exe


# Alvo padrão: compila, executa e limpa
all: $(TARGET)
	./$(TARGET)
	$(MAKE) clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	del /Q $(OBJS) $(TARGET) 2>nul || rm -f $(OBJS) $(TARGET)

.PHONY: all clean