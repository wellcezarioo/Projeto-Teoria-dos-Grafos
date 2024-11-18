# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = kosaraju.bin

# Nome do arquivo fonte
SOURCE = Kosaraju.cpp

# Regra padrão
all: $(TARGET)
	mv $(TARGET) ../Bat1
	chmod +x ../Bat1/Bat1.sh
	cd ../Bat1 && ./Bat1.sh
	
# Como criar o executável diretamente a partir do código-fonte
$(TARGET): Kosaraju.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./kosaraju.bin -f entrada.txt -o saida.txt

move: $(TARGET)
	mv $(TARGET) ../Bat1
