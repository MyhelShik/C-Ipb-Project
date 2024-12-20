#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char titulo[100], autor[100];
    int ano;
    int disponivel; //1 para disponivel e 0 se emprestado
}livro;

typedef struct 
{ 
    int id; 
    char nome[50]; 
    int cc;
    
}leitor;

typedef struct 
{ 
    int idLivro; 
    int idLeitor; 
    char dataEmprestimo[11]; 
    char dataDevolucao[11]; 
} emprestimo;


#define max_livros 1
#define max_leitor 3
#define max_emprestimo 50



leitor *leitores[max_leitor];

livro *livros[max_livros];  // Array de ponteiros para armazenar os livros
int num_livros_adicionados = 0;  // Contador de livros adicionados 