# Definição de variáveis
CC = g++                          # Compilador a ser usado
CFLAGS = -Wall                    # Flags de compilação

# Nome do executável
TARGET = prim.bin

# Nome do arquivo fonte
SOURCE = Prim.cpp

# Regra padrão
all: $(TARGET)
	mv $(TARGET) ../Bat1
	chmod +x ../Bat1/Bat1.sh
	cd ../Bat1 && ./Bat1.sh
	
# Como criar o executável diretamente a partir do código-fonte
$(TARGET): Prim.cpp
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) -f entrada.txt -o saida.txt -i 1 -s

move: $(TARGET)
	mv $(TARGET) ../Bat1
