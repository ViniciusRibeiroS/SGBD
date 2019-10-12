#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgbd.h"

//Função Simples de Menu de Usuario
//Corrigir Loop Infinito de Entrada Invalida
//Adicionar Timer
void menu(){  
  printf("---------------- Banco de Dados ----------------\n");
  printf("---------------- ITP/PTP 2018.1 ----------------\n");
  printf("          Feito por Moises & Vinicius\n");
  printf("\n");

  int option;
  printf("Selecione uma opção:\n1.Criar Tabela\n2.Inserir itens na tabela\n3.Listar tabelas(To-Do)\n4.Mostrar dados da tabela\n5.Pesquisar na tabela\n6.Deletar item da Tabela\n7.Deletar Tabela\n" );

  while (option <  9) {
    scanf("%d", &option);

    switch (option)
    {
      case 1:
      insertItens();
      printf ("\n");
      break;

      case 2 :
      insertItensAfterFile();
      printf ("\n");
      break;
      
      //To-DO
      case 3 :
      //showAllTables();
      printf ("\n");
      break;

      case 4 :
      showTable();
      printf ("\n");
      break;

      case 5 :
      search();
      printf ("\n");
      break;

      case 6 :
      deleteItemTable();
      printf ("\n");
      break;

      case 7:
      deleteTable();
      printf ("\n");
      break;

      default:
      printf ("Valor inválido!\n");
    }
  }

  printf("Encerrando programa!\n");
}

//Finalizada
void writeFile(char *tableName, char *itemTable, char *operation){
  FILE *arq, *allTables;

  arq = fopen(tableName, operation);

  fprintf(arq, "%s ", itemTable);

  fclose(arq);
}

//Finalizada ,Insere Itens em uma Tabela e Cria a mesma
void insertItens() {
  int lines, colums;
  char ***table, tableName[100];
  FILE *arq;
 
  /* Por padrão se pergunta Colunas desejadas na tabela
   * e as Linhas tambem, É feita a criação da tabela tambem 
   * nessa função (Da pra dividir em duas Depois).
   * Table é a variavel que armazena a tabela e TableName o 
   * nome que a tabela recebe.
  */
  
  //Feita a Primeira Parte da alocação
  table = (char***) malloc(50 * sizeof(char **));
  
  printf("Digite o nome da tabela\n");
  scanf("%s", &tableName);
  
  printf("Digite a quantidade de Colunas\n");
  scanf("%d", &colums);
  printf("Digite a quantidade de Linhas\n");
  scanf("%d", &lines);

  arq = fopen(tableName, "w");
  {
    fprintf(arq, "%d %d", colums, lines);
    fprintf(arq, "\n");
  }

  fclose(arq);

  //Verificar Entradas Invalidas
  //Todo
  
  //Enquanto o valor de Linha não for Preenchido
  for (int i = 0; i <= lines; ++i)
  {
    //Feita a Segunda Parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    //Preencha a posição da coluna J na Linha
    for (int j = 0; j < colums; ++j)
    {
      //Feita a Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));

      //É feito o mapeamento das Colunas na Linha 0
      if (i == 0)
      {
        //J + 1 apenas para ser uma Boa Visualização para o User
        printf("Digite o nome da Coluna %d:\n", j + 1); 
        scanf("%s", table[i][j]);
      }

      //Caso não seja a Linha que contem o nome das Colunas é Considerado Inserção de Item na Tabela
      else
      {
        //É informado o nome da Coluna que tá sendo feita a Inserção
        printf("Digite o nome do elemento da coluna %s\n", table[0][j]);
        scanf("%s", table[i][j]);
      }
    } 
  }
  
  //Feita a Escrita da Tabela em um Arquivo com o Nome da Mesma
  //Segue a mesma lógica do For encadeado Acima
  for (int i = 0; i <= lines; i++)
  {
    for (int j = 0; j < colums; ++j)
    {
      //Função de Escrever no Arquivo
      writeFile(tableName, table[i][j], "a+");
    }
  }
  
  fclose(arq);
  free(table);

  menu();
}

//Finalizada, Insere novos Items em uma tabela e agora Mostra a coluna onde tá sendo feita a inserção 
char *** insertItensAfterFile()
{
  /*Função para Inserir Itens em uma Tabela já Existente.
   * É necessário saber a quantidade de Itens que vai ser Inserida e em
   * Qual tabela 
  */
  
  char tableName[100], ***table;
  int lines, colums, new_lines;
  FILE *arq;
  
  //Pergunta-se qual vai ser a tabela que vai ser Alterada 
  printf("Digite o nome da tabela que se deseja inserir novos itens:\n");
  scanf("%s", tableName);
  
  //Verifica-se Se o arquivo Existe
  if(arq == NULL)
  {
    printf("Esse arquivo não existe\n");
    menu();
  }

  //O mesmo é aberto em modo de Leitura
  arq = fopen(tableName, "r");
  //Feita a Leitura de Colunas e Linhas
  fscanf(arq, "%d %d", &colums, &lines);

  //Feita a Primeira Parte da Alocação
  table = (char***) malloc(50 * sizeof(char **));

  for (int i = 0; i <= lines; ++i)
  {
    //Feita a Segunda Parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    for (int j = 0; j < colums; ++j)
    {
      //Feita a Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));
      fscanf(arq, "%s", table[i][j]);
    }
  }

  //Arquivo é fechado
  fclose(arq);

  //Pergunta-se a quantidade de Itens a ser inseridos 
  printf("Digite a quantidade de itens a ser Inserida(Linhas novas na Tabela):\n");
  scanf("%d", &new_lines);
  
  //O arquivo é reescrito agora com a nova quantidade de Linhas
  arq = fopen(tableName, "w");
  {
    fprintf(arq, "%d %d", colums, lines + new_lines);
    fprintf(arq, "\n");
  }
  
  for (int i = lines + 1; i <= (lines + new_lines); ++i)
  {
    //Feita a Segunda Parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    for (int j = 0; j < colums; ++j)
    {
      //Feita a Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));
      printf("Digite o nome do elemento da coluna %s\n", table[0][j]);
      scanf("%s", table[i][j]);
    }
  }

  for (int i = 0; i <= (lines + new_lines); i++)
  {
    for (int j = 0; j < colums; ++j)
    {
      //Função de Escrever no Arquivo
      writeFile(tableName, table[i][j], "a+");
    }
  }
  
  //Fecha-se o Arquivo e é liberada a memória
  free(table);
  fclose(arq);

  menu();
}

//Finalizada, Deleta o arquivo que guarda a Tabela do Diretório
void deleteTable() {
  int status;
  char tableName[100];

  printf("Digite o nome da tabela:\n");
  scanf("%s", tableName);
   
  status = remove(tableName);

  if (status == 0) {
    printf("Tabela removida com sucesso!\n");
  }else{
    printf("Erro ao deletar a tabela.\n");
  }
  menu();
}

//Finalizada
void showTable(){
  char tableName[100], ***table;
  int colums, lines;
  FILE *arq;
  
  /* Função para Mostrar a tabela
   * É feita a leitura do arquivo e o mesmo é armazenado em uma nova 
   * tabela, É necessario tratar uma formatação específica para evitar
   * espaçamentos distintos.
   * No geral funciona como esperado
  */


  //Entrada do Nome do arquivo que Deseja ser Lido
  printf("Digite o nome da tabela que deseja ver: ");
  scanf(" %s", tableName);
  
  //Verificação se esse Arquivo Existe
  if(arq == NULL)
  {
    printf("Esse arquivo não existe\n");
    menu();
  }
  
  //Se Existir é Aberto em Modo de Leitura
  arq = fopen(tableName, "r");
  
  //Feita a Leitura da Quantidade de Colunas e Linhas para alocação
  //da Tabela
  fscanf(arq, "%d %d", &colums, &lines);
  
  //Primeira Parte da Alocação
  table = (char***) malloc(50 * sizeof(char **));
  
  //For para Ler a Table do arquivo
  for (int i = 0; i <= lines; ++i)
  {
    //Feita a Segunda Parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    //Preencha a posição da coluna J na Linha
    for (int j = 0; j < colums; ++j)
    {
      //Feita a Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));
      //Leitura das Strings até o Final do arquivo
      fscanf(arq, " %s", table[i][j]);
    } 
  }
  
  int breakline = 0;

  //For Pra visualizar a Tabela do Arquivo
  for (int i = 0; i <= lines; i++)
  {
    breakline++;
    for (int j = 0; j < colums; ++j)
    {
      //Apenas Valor Estético
      if (breakline + 1 == colums)
      {
        //Garante a quebra de linha ao mudar
        printf("\n");
        //Informa a Linha da tabela, Vai ser Util para deletar Item
        printf("%d ->", i);
        breakline = 0;
      }
      //Print do Elemento da Tabela
      printf("%10s :", table[i][j]);
    }
  }
  
  //Estética
  printf("\n");
  
  //Fecha o Arquivo
  fclose(arq);
  //Free nos Ponteiros
  free(table);
  menu();
}

//Finalizada, Apaga um Item Especifico ou a Linha toda
void deleteItemTable(){
  char tableName[100], ***table;
  char colum_check [100], colum_name[100];
  int colums, lines, delete_line, delete_colum;

  FILE *arq;
  
  /* Função para Deletar Item Específico ou uma Linha Inteira de
   * Uma Tabela, Parte do Códio de Show Table foi Reaproveitado
   */

  //Entrada do Nome do arquivo que Deseja ser Lido
  printf("Digite o nome da tabela que deseja ver: ");
  scanf(" %s", tableName);
  
  //Verificação se esse Arquivo Existe
  if(arq == NULL)
  {
    printf("Esse arquivo não existe\n");
    menu();
  }
  
  //Se Existir é Aberto em Modo de Leitura
  arq = fopen(tableName, "r");
  
  //Feita a Leitura da Quantidade de Colunas e Linhas para alocação
  //da Tabela
  fscanf(arq, "%d %d", &colums, &lines);
  
  //Primeira Parte da Alocação
  table = (char***) malloc(50 * sizeof(char **));
  
  //For para Ler a Table do arquivo
  for (int i = 0; i <= lines; ++i)
  {
    //Feita a Segunda Parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    //Preencha a posição da coluna J na Linha
    for (int j = 0; j < colums; ++j)
    {
      //Feita a Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));
      //Leitura das Strings até o Final do arquivo
      fscanf(arq, " %s", table[i][j]);
    } 
  }
  
  //Variavel Para visualização da quebra de Linha
  int breakline = 0;

  //For Pra visualizar a Tabela do Arquivo
  for (int i = 0; i <= lines; i++)
  {
    breakline++;
    for (int j = 0; j < colums; ++j)
    {
      //Apenas Valor Estético
      if (breakline + 1 == colums)
      {
        //Garante a quebra de linha ao mudar
        printf("\n");
        //Informa a Linha da tabela, Vai ser Util para deletar Item
        printf("%d ->", i);
        breakline = 0;
      }
      //Print do Elemento da Tabela
      printf("%10s :", table[i][j]);
    }
  }
  
  //Estética
  printf("\n");

  //Fecha o Arquivo
  fclose(arq);
  
  //É feito o Mapeamento do Item a ser Apagado
  printf("Digite o nome Colunas que se encontra o Item\n");
  scanf("%s", &colum_name);
  printf("Digite o Número que se encontra o Item a ser deletado\n");
  scanf("%d", &delete_line);
  
  //Confere Primeiro se Existe Tal Coluna
  for (int i = 0; i <= 0; i++)
  {
    for (int j = 0; j < colums; ++j)
    {
      //É feito a cópia daquela Posição da Coluna
      //Para uma String de Filtragem
      strcpy(colum_check,table[i][j]);
      
      //Se a Coluna Existir ele Avisa
      if(strcmp(colum_name, colum_check) == 0){
        delete_colum = j;
      }
    }
  }
  
  //O Item é Deletado e no Lugar Fica o * para simbolizar
  //Que o Item foi eleminado da tabela após ser Inserido
  strcpy(table[delete_line][delete_colum], "*");
  
  //O Arquivo é Reescrito
  arq = fopen(tableName, "w");
  fprintf(arq, "%d %d", colums, lines);
  fprintf(arq, "\n");
  
  //É feita a Reescrita do Arquivo
  for (int i = 0; i <= lines; i++)
  {
    for (int j = 0; j < colums; ++j)
    {
      //Função de Escrever no Arquivo
      writeFile(tableName, table[i][j], "a+");
    }
  }
  
  //O arquivo é Fechado
  fclose(arq);
  
  //É possível apagar a Linha toda agora
  char decision[10];
  
  //É Oferecida a Escolha de Apagar a Linha do Elemento por Inteira
  printf("Deseja Apagar a Linha toda do Elemento? [Y/N]\n");
  scanf("%s", &decision);
  
  //Se a entrada for Y é deletada toda a linha
  if(strcmp(decision, "Y") == 0 || strcmp(decision, "y") == 0)
  {
    //O Arquivo é Reescrito do 0 com as novas Linhas e Colunas
    arq = fopen(tableName, "w");
    fprintf(arq, "%d %d", colums, lines - 1);
    fprintf(arq, "\n");

    //É feita a Reescrita do Arquivo
    for (int i = 0; i <= lines; i++)
    {
      //Monitoramento do Delete Line
      if (i == delete_line)
      {
        printf("Deletando Items da Linha %d...\n", delete_line);
      } 
      //Se não for a Linha Removida é feita a escrita no Arquivo normalmente
      else 
      {
        for (int j = 0; j < colums; ++j)
        {
          //Função de Escrever no Arquivo
          writeFile(tableName, table[i][j], "a+");
        }
      }
    }
  }

  
  fclose(arq);
  free(table);

  menu();
}

//Finalizada, Serve Para Buscas Especificas de Item
void search(){
  int lines, colums, search_colum, search_line, found_status = 0;
  char ***table, tableName[100], search_item[100], search_colum_name[100];
  FILE *arq;
  
  //Pergunta-se o nome da tabela
  printf("Digite o nome da Tabela que vai ser relizada a Pesquisa\n");
  scanf("%s", &tableName);
  
  //Verifica-se a existencia do Arquivo
  if(arq == NULL)
  {
    printf("Esse arquivo não existe\n");
    menu();
  }

  arq = fopen(tableName, "r");
  fscanf(arq, "%d %d", &colums, &lines);
  
  //Primeira Parte da Alocação da Tabela
  table = (char***) malloc(50 * sizeof(char **));
  
  //Armazena-se a Tabela Novamente
  for(int i = 0; i <= lines; i++ )
  {
    //Segunda parte da Alocação
    table[i] = (char**) malloc(50 * sizeof(char*));
    for (int j = 0; j < colums; j++) 
    {
      //Terceira Parte da Alocação
      table[i][j] = (char*) malloc(50 * sizeof(char));
      fscanf(arq, "%s", table[i][j]);
    }
  }

  fclose(arq);
  
  //Mostra-se as Colunas que compoem as Tabela
  printf("A tabela Possui as Seguintes Colunas: ");
  for (int j = 0; j < colums; ++j)
  { 
    printf("%10s", table[0][j]);
  }
  
  //Quebra de Linha para Valor Estético
  printf("\n");

  printf("Digite o Item que deseja Buscar\n");
  scanf("%s", &search_item);
  
  for (int i = 0; i <= lines; ++i)
  {
    for (int j = 0; j < colums; j++)
    {
      //Se o Item for Achado
      if (strcmp(table[i][j], search_item) == 0)
      {
        //Formatação das Colunas
        for (int l = 0; l < colums; ++l)
        { 
          printf("%10s :",table[0][l]);
        }

        //Estética
        printf("\n");

        //Se existir elemento o Status vira 1
        found_status = 1;

        //Por Coveniência Se Printa a linha toda
        for (int k = 0; k < colums; ++k)
        { 
          printf("%10s :", table[i][k]);
        }
        
        //Estética
        printf("\n");

        //Se Informa a Posição da Linha e a Coluna
        printf("O item foi Achado na Linha %d, da Coluna %d.\n", i ,j + 1);
        printf("\n");
      }

      if (i == lines && j + 1 == colums && found_status == 0)
      {
        printf("Elemento não encontrado!!!");
      }
    }
  }

  printf("\n");

  free(table);

  menu();
}

//To-Do
//searchbyparameters