#!/bin/bash

# Diretórios de entrada e saída
input_dir="Source"
output_dir="Gabarito"

# Certifica-se de que a pasta de saída existe
mkdir -p "$output_dir"

# Loop para executar o programa com diferentes entradas
for i in {1..20}; do
    # Nome do arquivo de entrada e saída
    input_file="$input_dir/teste_Grafo_$i.txt"
    output_file="$output_dir/gabarito_teste_Grafo_$i.txt"

    # Verifica se o arquivo de entrada existe
    if [ -f "$input_file" ]; then
        # Executa o arquivo floyd_warshall.bin com a flag -f e salva a saída no arquivo de saída
        ./floyd-warshall.bin -s -f "$input_file" > "$output_file"

        # Mensagem de confirmação
        echo "Saída de $input_file salva em $output_file"
    else
        echo "Arquivo de entrada $input_file não encontrado, pulando."
    fi

done
