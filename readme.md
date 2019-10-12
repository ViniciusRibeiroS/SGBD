# SGBD

Este programa tem com objetivo de Funcionar como um DBMS, o mesmo foi feito em C e se baseia em Leitura e Escrita de Informações em Arquivos.

## Compilação
Para gerar o executável utilize o seguinte comando no diretório do mesmo:

> $ gcc sgbdfunc.c sgbd.h main.c -o a

## Uso

> $ ./a

Para utilizar o SGBD é necessário apenas saber a função que se deseja utilizar (visualização disponível no menu) mas dentre elas existe a função de criar tabela, pesquisar itens, visualizar tabelas entre outras...

## Limitações

O SGBD ainda não trabalha com Strings com espaçamento e está em desenvolvimento a função de Busca Baseada em Parametros fornecidos pelo usuário, a versão atual retorna apenas se o elemento existe ou não na tabela fornecendo informações da linha e a coluna onde ele foi encontrado.

Tambem no momento não existe a possibilidade de acessar todas as tabelas guardadas pelo terminal, sendo necessário a checagem manual pela Interface.


## Componentes

Moises Sousa Araújo e Vinícius Ribeiro da Silva