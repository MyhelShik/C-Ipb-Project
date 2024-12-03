#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char titulo[100], autor[100];
    int ano[50];
    int disponivel; //1 para disponivel e 0 se emprestado
}livro;

typedef struct 
{ 
    int id; 
    char nome[50]; 
    int cc;
    } leitor;

typedef struct 
{ 
    int idLivro; 
    int idLeitor; 
    char dataEmprestimo[11]; 
    char dataDevolucao[11]; 
} emprestimo;

#define max_livros 100
#define max_leitor 50
#define max_emprestimo 50


void menu_principal()
{
    int opcao;
    do
    {
        printf("\nMenu Principal:\n"); 
        printf("1. Gerir Livros\n"); 
        printf("2. Gerir Leitores\n"); 
        printf("3. Registar Empréstimo\n"); 
        printf("4. Registar Devolução\n"); 
        printf("5. Exibir Relatórios\n"); 
        printf("6. Sair\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                GerirLivros();
                break;
            case 2:
                GerirLeitores();
                break;
            case 3:
                RegistarEmprestimo();
                break;
            case 4:
                RegistarDevolucao();
                break;
            case 5:
                ExibirRelatorio();
                break;
            case 6:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente...\n");
        }
    } while (opcao !=6);
    
}

int main()
{
    printf("Hello, from C-school-project!\n");
    printf("Sou gay");
    //asdasd
    // sadasd
    // mudanca no codigo
    //proximo 
    //sadsaddasdas
    }
