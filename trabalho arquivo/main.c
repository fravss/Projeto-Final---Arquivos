#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

void criar_arquivo();
void incluir_aluno();
void aluno_por_curso();
void situacao();

typedef struct{
    char prontuario[20], nome[50], curso[30];
    double nota1, nota2, media, situ;
} aluno;

int main()
{
           int x;

           printf("                     ___________________________________\n");
           printf("                    |_______________MENU________________|\n");
           printf("                    |                                   |\n");
           printf("                    | 1. Criar arquivo                  |\n");
           printf("                    | 2. Incluir aluno                  |\n");
           printf("                    | 3. Consultar aluno por curso      |\n");
           printf("                    | 4. Consultar aluno por situacao   |\n");
           printf("                    | 5. Finalizar                      |\n");
           printf("                    |                                   |\n");
           printf("                    |___________________________________|\n\n");
           x = getch();

           system("cls");

           if(x == 49)
               criar_arquivo();

           if(x == 50)
               incluir_aluno();

           if(x == 51)
               aluno_por_curso();

           if(x == 52)
              situacao();

            if( x == 53)
               exit(0);

    return 0;
}

void criar_arquivo()
{
   FILE *arq;
   char sn;
   int qtd = 0, n;
   aluno dados[100];
        arq = fopen("Alunos.dat", "rb");

        if(arq == NULL)
        {
            arq = fopen("Alunos.dat", "w+b");
        }

        qtd = fread(&dados, sizeof(aluno), 100, arq);

        if(qtd != 0)
        {

            printf("Ja existem dados cadastrados nesse arquivo. Deseja sobrescrever e perder os dados? S/N?\n");
            sn = getch();
            system("cls");

            if(sn == 'N' || sn == 'n')
            {
                main();
            }
        }

        fclose(arq);

       arq = fopen("Alunos.dat", "wb");
       if(arq != NULL)
       {
           printf("Arquivo criado com sucesso!\n");
       }
       if(arq == NULL)
       {
           printf("Nao foi possivel executar essa acao.\n");
           printf("\n1.Menu inicial\n2.Finalizar\n");
           n = getch();
           if(n == 49)
            main();
           if(n == 50)
            exit(0);
       }

       fclose(arq);

       printf("\n\n1. Menu inicial\n2. Finalizar\n");
       n = getch();

       while(n != 49 && n != 50)
       {   printf("\n\n1. Menu inicial\n2. Finalizar\n");
           n = getch();
       }
       system("cls");
       if(n == 49)
            main();
       if(n == 50)
            exit(0);
}

void incluir_aluno()
{
    FILE *arq;
    aluno dados;
    int qtd, n, num = 0;
    char pro[20];

    printf("Prontuario: ");
    scanf(" %[^\n]", pro);

    arq = fopen("Alunos.dat","rb");

    if(arq != NULL)
    {
        fread(&dados, sizeof(aluno), 1, arq);
        while(!feof(arq))
            {
                if(strcmp(pro, dados.prontuario)==0)
                    {
                        num++;
                    }

                fread(&dados, sizeof(aluno), 1, arq);
            }
    }

    fclose(arq);
    strcpy(dados.prontuario, pro);

    if(num > 0)
    {
        printf("\n________________________________________________________________________________\n\n");
        printf("Ja existe um aluno cadastrado com esse prontuario!\n\n\n1.Cadastrar novo aluno\n2.Voltar ao menu inicial\n");
        printf("\n________________________________________________________________________________\n\n");
        n = getch();
        system("cls");
        if(n == 49)
            incluir_aluno(arq);
        if(n == 50)
            main();
    }
    printf("\nNome: ");
    scanf(" %[^\n]", dados.nome);
    printf("\nCurso: ");
    scanf(" %[^\n]", dados.curso);
    printf("\nPrimeira nota: ");
    scanf("%lf", &dados.nota1);
    printf("\nSegunda nota: ");
    scanf("%lf", &dados.nota2);

    arq = fopen("Alunos.dat","ab");

    dados.media = (dados.nota1 + dados.nota2)/2;
         if(dados.media >= 6)
            dados.situ = 1;
         if(dados.media >= 4 && dados.media < 6)
            dados.situ = 2;
         if(dados.media < 4)
            dados.situ = 3;

    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o documento!\n");
        main();
    }
    qtd = fwrite(&dados, sizeof(aluno), 1, arq);
    if(qtd != 1)
    {
        printf("\nNao foi possivel ler o arquivo!\n");
    }
    fclose(arq);

    printf("\n______________________________________\n\n");
    printf("1. Incluir novo aluno\n2. Voltar ao menu inicial\n");
    n = getch();

    system("cls");
    if(n == 49)
        incluir_aluno(arq);
    if(n == 50)
        main();
}
void aluno_por_curso()
{
    FILE *arq;
    aluno dados;
    char curso2[20];
    int qtd, n, i;
    arq = fopen("Alunos.dat","rb");
    if(arq == NULL)
    {
        printf("Nao foi possivel acessar o documento!\n");
        main();
    }

    fread(&dados, sizeof(aluno), 1, arq);


    printf("Qual curso voce deseja pesquisar?\n");

    scanf(" %s", curso2);
    system("cls");

    for( i = 0; i < strlen(curso2); i++)
       curso2[i] = toupper(curso2[i]);

    while(!feof(arq))
    {
        for( i = 0; i < strlen(curso2); i++)
          dados.curso[i] = toupper(dados.curso[i]);

        if(strcmp(curso2, dados.curso) == 0)
        {
            printf("\n-> %s\n", dados.nome);
        }

         fread(&dados, sizeof(aluno), 1, arq);

    }
    fclose(arq);

    printf("\n____________________________________________");
    printf("\n\n1. Consultar outro curso\n2.Voltar para o menu\n");
    n = getch();

    system("cls");

    if(n == 49)
        aluno_por_curso(arq);
    if(n == 50)
         main();
}

void situacao()
{
    FILE *arq;
    int qtd, op, aux;
    aluno dados;

     arq = fopen("Alunos.dat", "rb");
    if(arq == NULL)
    {
        printf("Nao foi possivel acessar o arquivo!\n");
        main();
    }
    aux = fread(&dados, sizeof(aluno), 1, arq);
    if(aux != 1)
    {
        printf("\n Nao foi possivel ler o arquivo!\n");
        main();
    }

     printf("1. Aprovados\n");
     printf("2. Exame\n");
     printf("3. Reprovados\n");
     printf("4. Menu\n");
     op = getch();

     system("cls");
     if(op == 49)
        printf("APROVADOS:\n");
     if(op == 50)
        printf("EXAME:\n");
     if(op == 51)
        printf("REPROVADOS:\n");
     if(op == 52)
        main();


    while(!feof(arq))
    {
        if(dados.situ == (op - 48))
        {
            printf("\n\nProntuario: %s\n", dados.prontuario);
            printf("Nome: %s\n", dados.nome);
            printf("Media: %.2lf\n\n", dados.media);
        }
       fread(&dados, sizeof(aluno), 1, arq);

    }
    fclose(arq);

    printf("____________________________\n\n");
    printf("1. Consultar nova situacao\n");
    printf("2. Voltar ao menu inicial\n");
    op = getch();

    system("cls");

    if(op == 49)
        situacao(arq);
    if(op == 50)
        main();
}
