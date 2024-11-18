# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = floyd-warshall.bin

# Nome do arquivo fonte
SOURCE = Floyd-Warshall.cpp

# Regra padrão
all: $(TARGET)
	mv $(TARGET) ../../BatMANN
	chmod +x ../../BatMANN/BatMANN.sh
	cd ../../BatMANN && ./BatMANN.sh
	
# regra para criar o executável diretamente a partir do código-fonte
$(TARGET): Floyd-Warshall.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) -f entrada.txt -s -o saida.txt

move: $(TARGET)
	mv $(TARGET) ../../BatMANN
