# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = floyd-warshall.bin

# Nome do arquivo fonte
SOURCE = Floyd-Warshall.cpp

# Regra padrão
all: $(TARGET)

# regra para criar o executável diretamente a partir do código-fonte
$(TARGET): Floyd-Warshall.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)

move: $(TARGET)
	mv $(TARGET) casos_teste
