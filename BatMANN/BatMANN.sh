#!/bin/bash

# Loop para testar várias instâncias
for arquivo_teste in Source/*.txt
do
    # Mostra qual instância está sendo testada
    echo -e "\e[33mInstância $arquivo_teste\e[0m"

    # Gera a saída do algoritmo e redireciona para um arquivo temporário
    ./floyd-warshall.bin -s -f $arquivo_teste > temp

    # Extrai o nome base do arquivo para encontrar o gabarito correspondente
    arquivo_gabarito=./Gabarito/gabarito_$(basename $arquivo_teste)

    # Compara o arquivo temporário com o gabarito
    if diff -w temp "$arquivo_gabarito" > /dev/null; then
        # Mostra OK em verde
        echo -e "\e[32mOK\e[0m"
    else
        # Mostra ERRO em vermelho
        echo -e "\e[31mErro\e[0m"
    fi

    # Remove o arquivo temporário
    rm temp

done
