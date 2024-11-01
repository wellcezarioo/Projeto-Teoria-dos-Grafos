# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = dijkstra.bin

# Nome do arquivo fonte
SOURCE = Dijkstra.cpp

# Regra padrão
all: $(TARGET)
	mv dijkstra.bin ../Bat1
	chmod +x ../Bat1/Bat1.sh
	cd ../Bat1 && ./Bat1.sh
	
# Como criar o executável diretamente a partir do código-fonte
$(TARGET): Dijkstra.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)  # Executa o programa
	
# Regra para limpar arquivos gerados
clear:
	rm -f $(TARGET)
