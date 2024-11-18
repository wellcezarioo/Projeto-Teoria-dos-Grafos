# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = dijkstra.bin

# Nome do arquivo fonte
SOURCE = Dijkstra.cpp

# Regra padrão
all: $(TARGET)
	mv $(TARGET) ../../Bat1
	chmod +x ../../Bat1/Bat1.sh
	cd ../../Bat1 && ./Bat1.sh
	
# regra para criar o executável diretamente a partir do código-fonte
$(TARGET): Dijkstra.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) -f entrada.tx -o saida.txt

move: $(TARGET)
	mv $(TARGET) ../../Bat1
