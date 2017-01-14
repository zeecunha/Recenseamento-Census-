/**
 *  @file adaoeeva.c
 *  @brief implementação de todas as funções do Programa.
 *
 *
 *  @author José Cunha (28018@ufp.edu.pt)
 *
 */

#include "adaoeeva.h"
#include "pessoa.h"
#include "stringsorting.h"
#include <string.h>
#include "lib_util.h"

extern pessoa* personsDB;
extern int personDBSize;

///funcao para o menu

void menu()
{
    system("cls");
    int opcao;
    printf("\t-------------------------------------\n");
    printf("\t------- AED 1 - RECENSEAMENTO -------\n");
    printf("\t-------------------------------------\n");
    printf("\t1. Mostrar conteudo BD\n");
    printf("\t2. Inserir pessoa\n");
    printf("\t3. Ordenar com MSD\n");
    printf("\t4. Ordenar com LSD\n");
    printf("\t5. Guardar em .txt\n");
    printf("\t6. Atualizar pessoa\n");
    printf("\t------------------------------------\n");
    printf("\t----- AED 1 - Jose Cunha 28018 -----\n");
    printf("\t------------------------------------\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        listar(personsDB, personDBSize);
        break;
    case 2:
        criarpessoa(personsDB, personDBSize);
        break;
    case 3:
        MSD_menu(personsDB, personDBSize);
        break;
    case 4:
        LSD_menu(personsDB, personDBSize);
        break;
    case 5:
        guarda_txt(personsDB,personDBSize);
        break;
    case 6:
        atualizardados(personsDB, personDBSize);
        break;
    default:
        printf("Escolha uma opcao valida!\n");
        break;
    }
}

///funcao para listar a BD

void listar(pessoa* personsDB, int personDBSize)
{
    system("cls");
    int i = 0;

    printf("\t---------------------------------------------\n");
    printf("\t--------- Conteudo da base de dados ---------\n");
    printf("\t---------------------------------------------\n");
    printf("\n");
    for (i = 0; i < personDBSize; i++)
    {
        printPerson(&personsDB[i]); ///chama a funcao printPerson fornecida pelo professor
    }
    char c;
    printf("\n\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }
}

///funcao para criar um utilizador

void criarpessoa()
{
    system("cls");
    pessoa new;

    printf("\t-------------------------------------------\n");
    printf("\t------------- Inserir pessoa --------------\n");
    printf("\t-------------------------------------------\n");

    printf("Insira o NIF (9 digitos!):\n");
    getchar();
    gets(new.nif);
    printf("Insira o Nome:\n");
    gets(new.nome);
    printf("Insira a Data de Nascimento (aaaammdd):\n");
    gets(new.datanascimento);
    printf("Insira o Codigo Postal(7 digitos!):\n");
    gets(new.cod_postal);
    printf("Insira freguesia:\n");
    gets(new.freguesia);

    printf("\nInserido com sucesso!\n");

    personsDB = addPerson2PersonArray(personsDB, personDBSize, &new);       ///chama a funcao addPerson2PersonArray cedida pelo professor
    personDBSize = personDBSize + 1;  ///Usa a BD e incrementa mais um utilizador

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }
}


///funcao para o menu de ordenação MSD

void MSD_menu(pessoa * pessoas, int n)
{
    system("cls");
    int opcao;
    printf("\t-------------------------------------\n");
    printf("\t---------- ORDENAR COM MSD ----------\n");
    printf("\t-------------------------------------\n");
    printf("\t1. Ordenar por NIF\n");
    printf("\t2. Ordenar por nome\n");
    printf("\t3. Ordenar por data\n");
    printf("\t4. Ordenar por Codigo Postal\n");
    printf("\t5. Ordenar por freguesia\n");
    printf("\t-------------------------------------\n");
    printf("\t----- AED 1 - Jose Cunha 28018 ------\n");
    printf("\t-------------------------------------\n");

    scanf("%d",&opcao);

    switch (opcao)
    {
    case 1:
        MSD_nif(personsDB,personDBSize);
        break;
    case 2:
        MSD_nome(personsDB,personDBSize);
        break;
    case 3:
        MSD_data(personsDB,personDBSize);
        break;
    case 4:
        MSD_codpostal(personsDB,personDBSize);
        break;
    case 5:
        MSD_freguesia(personsDB,personDBSize);
        break;
    case 's':
        menu();
        break;
    default:
        printf("Escolha uma opcao valida!\n");
        break;
    }


}

///Ordenação NIF pelo MSD

void MSD_nif(pessoa* pessoas, int N)
{
    system("cls");
    int i = 0;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    StringElementsArray aux;
    createStringElementsArrayAndFillNif(&a, N, pessoas);
    createStringElementsArray(&aux, N);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem MSD ---------\n");
    printf("\t------------------------------------\n");

    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    msd_sort_whithout_cutoff(&a, &aux, 0, N - 1, 0, ALFABETO);      ///chama a funcao MSD_sort_whithout_cutoff

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo com MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}
///Ordenação NOME pelo MSD

void MSD_nome(pessoa* pessoas, int N)
{
    system("cls");
    int i = 0;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    StringElementsArray aux;
    createStringElementsArrayAndFillNome(&a, N, pessoas);
    createStringElementsArray(&aux, N);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem MSD ---------\n");
    printf("\t------------------------------------\n");

    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    msd_sort_whithout_cutoff(&a, &aux, 0, N - 1, 0, ALFABETO);  ///chama a funcao MSD_sort_whithout_cutoff

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo com MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}
///Ordenação DATA pelo MSD

void MSD_data(pessoa* pessoas,int N)
{
    system("cls");
    int i;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArrayAndFillData(&a, N, pessoas);
    createStringElementsArray(&aux, N);

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].datanascimento;
        a.len[i] = strlen(pessoas[i].datanascimento);
    }
    createStringElementsArray(&aux,N);

    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    msd_sort_whithout_cutoff(&a,&aux,0,N-1,0,ALFABETO);     ///chama a funcao MSD_sort_whithout_cutoff

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo com MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu(personsDB,personDBSize);
    }

}
///Ordenação CODIGO POSTAL pelo MSD

void MSD_codpostal(pessoa* pessoas,int N)
{
    system("cls");
    int i;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArrayAndFillCodpostal(&a, N, pessoas);
    createStringElementsArray(&aux, N);

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].cod_postal;
        a.len[i] = strlen(pessoas[i].cod_postal);
    }

    createStringElementsArray(&aux,N);

    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    msd_sort_whithout_cutoff(&a,&aux,0,N-1,0,ALFABETO);

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo com MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\n\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }


}
///Ordenação FREGUESIA pelo MSD

void MSD_freguesia(pessoa* pessoas,int N)
{
    system("cls");
    int i;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    StringElementsArray aux;

    createStringElementsArrayAndFillFreguesia(&a, N, pessoas);
    createStringElementsArray(&aux, N);

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
    {
        a.str[i] = pessoas[i].freguesia;
        a.len[i] = strlen(pessoas[i].freguesia);
    }
    createStringElementsArray(&aux,N);

    for (i = 0; i < N; i++)
    {
        printf("\t%s\n",a.str[i]);

    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    msd_sort_whithout_cutoff(&a,&aux,0,N-1,0,ALFABETO); ///chama a funcao MSD_sort_whithout_cutoff

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo com MSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n",a.str[i]);

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\n\t------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}

///funcao para o menu de ordenação LSD


void LSD_menu(pessoa * pessoas, int n)
{
    system("cls");
    int opcao;
    printf("\t-------------------------------------\n");
    printf("\t---------- ORDENAR COM LSD ----------\n");
    printf("\t-------------------------------------\n");
    printf("\t1. Ordenar por NIF\n");
    printf("\t2. Ordenar por nome\n");
    printf("\t3. Ordenar por data\n");
    printf("\t4. Ordenar por Codigo Postal\n");
    printf("\t5. Ordenar por freguesia\n");
    printf("\t------------------------------------\n");
    printf("\t----- AED 1 - Jose Cunha 28018 -----\n");
    printf("\t------------------------------------\n");

    scanf("%d",&opcao);

    switch (opcao)
    {
    case 1:
        LSD_nif(personsDB,personDBSize);
        break;
    case 2:
        LSD_nome(personsDB,personDBSize);
        break;
    case 3:
        LSD_data(personsDB,personDBSize);
        break;
    case 4:
        LSD_codpostal(personsDB,personDBSize);
        break;
    case 5:
        LSD_freguesia(personsDB,personDBSize);
        break;
    default:
        printf("Escolha uma opcao valida!\n");
        break;
    }


}

///Ordenação NIF pelo LSD


void LSD_nif(pessoa* pessoas, int N)
{

    system("cls");
    int i = 0;
    int W = 8;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;
    StringElementsArray a;
    createStringElementsArrayAndFillNif(&a, N, pessoas);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    lsd_sort(&a, N, W, ALFABETO);   ///chama a funcao LSD_sort

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo COM LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);
    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}

///Ordenação NOME pelo LSD

void LSD_nome(pessoa* pessoas, int N)
{
    system("cls");
    int i = 0;
    int W = 8;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;

    StringElementsArray a;
    createStringElementsArrayAndFillNome(&a, N, pessoas);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    lsd_sort(&a, N, W, ALFABETO);       ///chama a funcao LSD_sort

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo COM LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);
    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}

///Ordenação DATA pelo LSD

void LSD_data(pessoa* pessoas, int N)
{
    system("cls");
    int i = 0;
    int W = 8;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;

    StringElementsArray a;
    createStringElementsArrayAndFillData(&a, N, pessoas);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    lsd_sort(&a, N, W, ALFABETO);   ///chama a funcao LSD_sort

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo COM LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
   if (c=='s' || c=='S')
    {
        menu();
    }

}

///Ordenação CODIGO POSTAL pelo LSD

void LSD_codpostal(pessoa* pessoas,int N)
{
    system("cls");
    int i = 0;
    int W = 8;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;


    StringElementsArray a;
    createStringElementsArrayAndFillCodpostal(&a, N, pessoas);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    lsd_sort(&a, N, W, ALFABETO);   ///chama a funcao LSD_sort

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo COM LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }
    freeStringElementsArray(&a);

    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }

}

///Ordenação FREGUESIA pelo LSD

void LSD_freguesia(pessoa* pessoas,int N)
{
    system("cls");
    int i = 0;
    int W = 8;
    long long int startTime = 0;
    long long int finishTime = 0;
    long long int diffTime = 0;

    StringElementsArray a;
    createStringElementsArrayAndFillFreguesia(&a, N, pessoas);
    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo sem LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++){
        printf("\t%s\n", a.str[i]);
    }

    gettimeuseconds(&startTime);     ///obter o tempo no inicio

    lsd_sort(&a, N, W, ALFABETO);       ///chama a funcao LSD_sort

    gettimeuseconds(&finishTime);       ///obter o tempo no final da execucao

    printf("\t------------------------------------\n");
    printf("\t--------- Conteudo COM LSD ---------\n");
    printf("\t------------------------------------\n");
    for (i = 0; i < N; i++)
        printf("\t%s\n", a.str[i]);
    freeStringElementsArray(&a);
    diffTime = finishTime - startTime;      ///calcular diferenca de tempo inicial - tempo final
    printf("\nA funcao demorou: %lld\n", diffTime);     ///imprimir tempo

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    getchar();
    c=getchar();
   if (c=='s' || c=='S')
    {
        menu();
    }

}

///FUNCAO PARA EXPORTAR A BASE DE DADOS

void guarda_txt(pessoa * personsDB,int personDBSize)
{
    system("cls");
    char export[100];
    printf("\t-----------------------------------------------\n");
    printf("\t------------------Exportar como:---------------\n");
    printf("\t---(insira um nome para exportar o ficheiro)---\n");
    printf("\t-----------------------------------------------\n");
    getchar();
    gets(export);       ///NOME PARA GRAVAR O FICHEIRO TXT
    FILE *f=NULL;
    strcat(export,".txt");
    f = fopen(export, "w");

    int i = 0;
    if (f != NULL)
    {
        fprintf(f,"%d\n",personDBSize);     ///CICLO PARA ANDAR LINHA A LINHA A IMPRIMIR OS UTILIZADORES
        while (i < personDBSize)
        {
            fprintf(f,"%s;%s;%s;%s;%s\n",personsDB[i].nif,personsDB[i].nome,personsDB[i].datanascimento,personsDB[i].cod_postal,personsDB[i].freguesia);
            i++;
        }
        fclose(f);
    }

    printf("\n Criado ficheiro %s!\n",export);

    char c;
    printf("\t--------------------------------------------\n");
    printf("\t--Pressione S para voltar ao menu anterior--\n");
    printf("\t--------------------------------------------\n");
    c=getchar();
    if (c=='s' || c=='S')
    {
        menu();
    }
}

///FUNCAO PARA ATUALIZAR DADOS DOS UTILIZADORES

void atualizardados()
{
    system("cls");
    int opcao;
    char c;
    int i=0;
    char nif[15];
    char nome[15];
    char datanascimento[15];
    char cod_postal[15];
    char freguesia[12];
    printf("\t------------------------------------\n");
    printf("\t--------- atualizar pessoa ---------\n");
    printf("\t------------------------------------\n");
    printf("1. NIF BD\n");
    printf("2. Nome BD\n");
    printf("3. Data de Nascimento\n");
    printf("4. Codigo Postal\n");
    printf("5. Freguesia\n");
    scanf("%d",&opcao);
    switch (opcao)
    {
    case 1:

        printf("Inserir o NIF da pessoa a atualizar:\n");
        getchar();
        gets(nif);

        for(i=0; i<personDBSize; i++)       ///PERCORRE A BASE DE DADOS
        {
            if(strcmp(personsDB[i].nif,nif)==0)
            {
                printf("\nNIF novo:\n");
                gets(personsDB[i].nif);         ///SUBSITUI PELO NOVO VALOR

            }
        }

        printf("\t--------------------------------------------\n");
        printf("\t--Pressione S para voltar ao menu anterior--\n");
        printf("\t--------------------------------------------\n");

        c=getchar();
      if (c=='s' || c=='S')
        {
            menu();
        }
        break;
    case  2:

        printf("Inserir o nome da pessoa a atualizar:\n");
        getchar();
        gets(nome);

        for(i=0; i<personDBSize; i++)        ///PERCORRE A BASE DE DADOS
        {
            if(strcmp(personsDB[i].nome,nome)==0)       ///COMPARA O VALOR ORIGInAL
            {
                printf("\n Novo nome:\n");
                gets(personsDB[i].nome);

            }
        }

        printf("\t--------------------------------------------\n");
        printf("\t--Pressione S para voltar ao menu anterior--\n");
        printf("\t--------------------------------------------\n");


        c=getchar();
        if (c=='s' || c=='S')
        {
            menu();
        }
        break;
    case 3:
        printf("Inserir a data de nascimento da pessoa a atualizar (yyyymmdd):\n");
        getchar();
        gets(datanascimento);

        for(i=0; i<personDBSize; i++)        ///PERCORRE A BASE DE DADOS
        {
            if(strcmp(personsDB[i].datanascimento,datanascimento)==0)       ///COMPARA O VALOR ORIGInAL
            {
                printf("\n Nova data de nascimento:\n");
                gets(personsDB[i].datanascimento);  ///SUBSITUI PELO NOVO VALOR

            }
        }

        printf("\t--------------------------------------------\n");
        printf("\t--Pressione S para voltar ao menu anterior--\n");
        printf("\t--------------------------------------------\n");


        c=getchar();
        if (c=='s' || c=='S')
        {
            menu();
        }
        break;
    case 4:
        printf("Inserir o codigo postal da pessoa a atualizar:\n");
        getchar();
        gets(cod_postal);

        for(i=0; i<personDBSize; i++)        ///PERCORRE A BASE DE DADOS
        {
            if(strcmp(personsDB[i].cod_postal,cod_postal)==0)       ///COMPARA O VALOR ORIGInAL
            {
                printf("\n Nova codigo postal:\n");
                gets(personsDB[i].cod_postal);      ///SUBSITUI PELO NOVO VALOR

            }
        }

        printf("\t--------------------------------------------\n");
        printf("\t--Pressione S para voltar ao menu anterior--\n");
        printf("\t--------------------------------------------\n");


        c=getchar();
        if (c=='s' || c=='S')
        {
            menu();
        }
        break;
    case 5:
        printf("Inserir a freguesia da pessoa a atualizar (yyyymmdd):\n");
        getchar();
        gets(freguesia);

        for(i=0; i<personDBSize; i++)    ///PERCORRE A BASE DE DADOS
        {
            if(strcmp(personsDB[i].freguesia,freguesia)==0)     ///COMPARA O VALOR ORIGInAL
            {
                printf("\n Nova freguesia:\n");
                gets(personsDB[i].freguesia);       ///SUBSITUI PELO NOVO VALOR

            }
        }

        printf("\t--------------------------------------------\n");
        printf("\t--Pressione S para voltar ao menu anterior--\n");
        printf("\t--------------------------------------------\n");


        c=getchar();
        if (c=='s' || c=='S')
        {
            menu();
        }
        break;

    default:
        printf("Escolha uma opcao valida!\n");
        break;
    }
}
