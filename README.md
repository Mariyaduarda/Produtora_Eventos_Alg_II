# Produtora_Eventos_Alg_II
Projeto para a disciplina de algoritmos II, em 2025. Desenvolvido por Victor Luis e Maria Eduarda em linguagem c.

⚙️ Como usar o Makefile
Compilar e executar: make

Limpar todos os arquivos compilados: make clean

help:
	@echo "==============================================="
	@echo " HELP - COMANDOS DISPONÍVEIS NO MAKEFILE  "
	@echo "==============================================="
	@echo ""
	@echo "   make          || Compila, executa e limpa o projeto"
	@echo "   make clean    || Remove arquivos objetos e o executável"
	@echo "   make help     || Mostra esta mensagem de ajuda"
	@echo ""
	@echo "-----------------------------------------------"
	@echo "⚙️  Compilador: $(CC)"
	@echo "📂 Diretórios de código-fonte: $(SRC_DIRS)"
	@echo "==============================================="
	@echo ""

