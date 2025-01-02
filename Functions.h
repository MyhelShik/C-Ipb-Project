#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

void SnL() // save and list methods
{
    FILE *f1, *f2;
    int choice = 0;
    printf("Pretende salvar ou rever ultima sessao salvada?\n1 - salvar.\n2 - ver ultima sessao.\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        f1 = fopen("..\\leitores.txt", "w");

        if (f1 == NULL)
            printf("erro na abertura do ficheiro.\n");
        else
        {
            for (int i = 0; i < max_leitor; i++)
            {
                if (leitores[i]->id != 0)
                {
                    fprintf(f1, "%d, %s, %d\n", leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
                    printf("%d, %s %d\nEscrito com sucesso!\n", leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
                }
            }
            printf("Sucesso!");
        }
        fclose(f1);
    break;

    case 2:
        f2 = fopen("..\\leitores.txt", "r");

        if (f2 != NULL)
        {
            for (int i = 0; i < max_leitor; i++)
            {
                leitores[i] = malloc(sizeof(leitor)); // Allocate memory for each leitor SLOT aka array[i]
                if (leitores[i] == NULL)
                {
                    printf("Erro ao alocar memoria para leitores[%d]\n", i);
                    exit(1);
                }

                if (fscanf(f2, "%d, %50[^,], %d\n", &leitores[i]->id, leitores[i]->nome, &leitores[i]->cc) == 3) // Read three vars from the .txt and check if it equals 3 || or to consider that it can be changed to gets method and used different approach where ther would be a check for the next line until encounters empty.
                {
                    printf("Leitor carregado: %d, %s, %d\n", leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
                }
                else
                {
                    printf("Erro ao ler dados do arquivo para leitores[%d]\n", i);
                    free(leitores[i]); // Free memory if reading fails
                    leitores[i] = NULL;
                    break; // Stop if reading fails
                }
            }
            fclose(f2);
        }
    break;

    default:
        printf("Tenta os numeros entre 1-2.\n");
        break;
    }
}
void GerirLeitores()
{
    int temp_leitor = 0; // to move to structure public VAR
    int opcao;
    int removeID = 0;
    char continuar[50];
    FILE *ficheiro;
    leitor *novo_leitor;// Ponteiro para um leitor
    static int contador_id = 0; // Variável estática para manter o contador de IDs
    int id_remover;
    int encontrado = 0;
    FILE *ficheiro_temp;
    do
    {
        printf("\n Menu Leitores:\n"); 
        printf("1. Adicionar leitores\n"); 
        printf("2. Listar leitores\n"); 
        printf("3. Remover leitores\n");
        printf("6. Voltar ao menu principal\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: // Add readers
               
    
    // Abrir o ficheiro leitores.txt para leitura e encontrar o maior ID registrado
    ficheiro = fopen("leitores.txt", "r");
    if (ficheiro != NULL) {
        int maior_id = 0;
        int id;
        char linha[256];
        
        // Lê cada linha do ficheiro para encontrar o maior ID
        while (fgets(linha, sizeof(linha), ficheiro)) {
            // Extrai o ID da linha
            if (sscanf(linha, "Livro: ID %d", &id) == 1) {  // Ajustado para corresponder ao formato correto da linha
                if (id > maior_id) {
                    maior_id = id;
                }
            }
        }
        fclose(ficheiro);  // Fecha o ficheiro após ler
        contador_id = maior_id;  // Inicializa o contador_id com o maior ID encontrado
    }

    // Agora, o contador_id está correto. Vamos adicionar um novo leitor
    printf("Adicionando leitor... O próximo ID será %d\n", contador_id + 1);

    // Bloco para adicionar múltiplos leitor
    char continuar;
    do {
        printf("A adicionar leitor %d de %d\n", num_leitores_adicionados + 1, max_leitor);

        novo_leitor = (leitor*)malloc(sizeof(leitor));  // Aloca memória para um leitor
        if (novo_leitor == NULL) {
            printf("Falha na alocação de memória\n");
            return;
        }

        novo_leitor->id = ++contador_id;  // Aumenta o ID para o próximo leitor
        fflush(stdin);
        // Leitura do título com fgets
        printf("Nome do Leitor: \n");
        fgets(novo_leitor->nome, sizeof(novo_leitor->nome), stdin);
        novo_leitor->nome[strcspn(novo_leitor->nome, "\n")] = '\0';  // Remove o caractere de nova linha

        

        // Leitura do ano com fgets e conversão para inteiro
        printf("Numero de cc: \n");
        char ano_input[10];
        fgets(ano_input, sizeof(ano_input), stdin);
        sscanf(ano_input, "%d", &novo_leitor->cc);  // Converte a string para um inteiro

        // Exibe os dados do leitor adicionado
        printf("leitor adicionado: ID %d - Nome: %s, Cartao de cidadao: %d\n", novo_leitor->id, novo_leitor->nome,novo_leitor->cc);

        // Armazena o leitor no array
        leitores[num_leitores_adicionados++] = novo_leitor;
        
        // Grava o livro no ficheiro leitores.txt
        ficheiro = fopen("leitores.txt", "a");
        if (ficheiro != NULL) {
            fprintf(ficheiro, "leitor: ID %d - Nome: %s, Cartao de cidadao: %d\n", novo_leitor->id, novo_leitor->nome,novo_leitor->cc);  // Apenas o ID e informações
            fclose(ficheiro);
        } else {
            printf("Falha ao abrir o ficheiro para gravar\n");
        }

        // Pergunta ao utilizador se deseja adicionar mais leitores
        printf("Deseja adicionar outro leitor? (s/n): ");
        scanf(" %c", &continuar);  // Lê a resposta
        getchar();  // Limpa o buffer de entrada

    } while (continuar == 's' || continuar == 'S');  // Continuar enquanto a resposta for 's' ou 'S'

    return GerirLeitores();


            case 2: // List readers
                ficheiro = fopen("leitores.txt", "r");
                if (ficheiro == NULL) {
                    printf("Erro ao abrir o arquivo leitores.txt.\n");
                    return;
                }

                char linha[256];
                while (fgets(linha, sizeof(linha), ficheiro)) {
                    printf("%s", linha);
                }
                fclose(ficheiro);     
             break;
            
            
    
        
    

    case 3: // Remover leitores
    printf("Digite o ID do leitor que deseja remover: ");
    int id_remover;
    scanf("%d", &id_remover);

    // Abrir o arquivo original para leitura
    ficheiro = fopen("leitores.txt", "r");
    if (ficheiro == NULL) 
    {
        printf("Erro ao abrir o arquivo leitores.txt.\n");
        return GerirLeitores();  // Retorna ao menu
    }

    // Criar um arquivo temporário para armazenar os leitores que não serão removidos
    ficheiro_temp = fopen("leitores_temp.txt", "w");
    if (ficheiro_temp == NULL) 
    {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(ficheiro);
        return GerirLeitores();  // Retorna ao menu
    }

    // Ler o arquivo original linha por linha
    
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), ficheiro)) 
    {
        int leitor_id;
        char nome[100];
        int cc;

        // Tentativa de ler os dados do leitor na linha
        // Formato esperado: "leitor: ID X - Nome: Y, Cartao de cidadao: Z"
        int n = sscanf(linha, "leitor: ID %d - Nome: %99[^,], Cartao de cidadao: %d", &leitor_id, nome, &cc);

        // Verificar se a leitura foi bem-sucedida
        if (n == 3)  // O formato correto é ID, Nome, Cartão de Cidadão
        {
            printf("Lido ID: %d, Nome: %s, Cartão de Cidadão: %d\n", leitor_id, nome, cc);

            // Se o ID não corresponder ao ID a ser removido, escreva no arquivo temporário
            if (leitor_id != id_remover) 
            {
                fprintf(ficheiro_temp, "leitor: ID %d - Nome: %s, Cartao de cidadao: %d\n", leitor_id, nome, cc);
            } 
            else 
            {
                encontrado = 1;  // Leitor encontrado e removido
            }
        }
        else
        {
            // Caso o sscanf não consiga ler corretamente
            printf("Erro ao ler linha: %s", linha);
        }
    }

    // Fechar ambos os arquivos
    fclose(ficheiro);
    fclose(ficheiro_temp);

    // Se não encontrar o leitor para remover
    if (!encontrado) 
    {
        printf("Leitor com ID %d não encontrado.\n", id_remover);
        remove("leitores_temp.txt");  // Apaga o arquivo temporário em caso de erro
        return GerirLeitores();  // Retorna ao menu
    }

    // Apagar o arquivo original
    remove("leitores.txt");

    // Renomear o arquivo temporário para o nome original
    if (rename("leitores_temp.txt", "leitores.txt") != 0) 
    {
        printf("Erro ao atualizar o arquivo de leitores.\n");
        return GerirLeitores();  // Retorna ao menu
    }

    printf("Leitor removido com sucesso do arquivo.\n");
    return GerirLeitores();

        }

    } while (opcao != 6);
}
//menu principal

void menu_principal() 

{
    int opcao;
    do
    {
        printf("\nMenu Principal:\n"); 
        printf("1. Gerir Livros\n"); 
        printf("2. Gerir Leitores\n"); 
        printf("3. Registar Emprestimo\n"); 
        printf("4. Registar Devolução\n"); 
        printf("5. Exibir Relatorios\n"); 
        printf("6. Sair e salvar informacao\n"); 
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
                //ExibirRelatorio();
                break;
            case 6:
                //printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente...\n");
        }
    } while (opcao !=6);

return 0;
}
void GerirLivros()
{
    int opcao2;
    printf("\nMenu Principal:\n"); 
        printf("1. Adicionar Livro\n"); 
        printf("2. Listar Livros\n"); 
        printf("3. Pesquisar Livro\n"); 
        printf("4. Remover livro\n");  
        printf("5. Sair\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao2);

        switch(opcao2)
        {
            case 1:
                AdicionarLivro();
                break;
            case 2:
                ListarLivros();
                break;
            case 3:
                PesquisarLivro();
                break;
            case 4:
                RemoverLivro();
                break;
            case 5:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente...\n");
        }
     while (opcao2 !=5);
     return menu_principal();
}


void AdicionarLivro() {
    livro *novolivro;  // Ponteiro para um livro
    static int contador_id = 0;  // Variável estática para manter o contador de IDs
    FILE *ficheiro;
    
    // Abrir o ficheiro livros.txt para leitura e encontrar o maior ID registrado
    ficheiro = fopen("livros.txt", "r");
    if (ficheiro != NULL) {
        int maior_id = 0;
        int id;
        char linha[256];
        
        // Lê cada linha do ficheiro para encontrar o maior ID
        while (fgets(linha, sizeof(linha), ficheiro)) {
            // Extrai o ID da linha
            if (sscanf(linha, "Livro: ID %d", &id) == 1) {  // Ajustado para corresponder ao formato correto da linha
                if (id > maior_id) {
                    maior_id = id;
                }
            }
        }
        fclose(ficheiro);  // Fecha o ficheiro após ler
        contador_id = maior_id;  // Inicializa o contador_id com o maior ID encontrado
    }

    // Agora, o contador_id está correto. Vamos adicionar um novo livro.
    printf("Adicionando livro... O próximo ID será %d\n", contador_id + 1);

    // Bloco para adicionar múltiplos livros
    char continuar;
    do {
        printf("A adicionar livro %d de %d\n", num_livros_adicionados + 1, max_livros);

        novolivro = (livro *)malloc(sizeof(livro));  // Aloca memória para um livro
        if (novolivro == NULL) {
            printf("Falha na alocação de memória\n");
            return;
        }

        novolivro->id = ++contador_id;  // Aumenta o ID para o próximo livro
        fflush(stdin);
        // Leitura do título com fgets
        printf("Titulo do livro: \n");
        fgets(novolivro->titulo, sizeof(novolivro->titulo), stdin);
        novolivro->titulo[strcspn(novolivro->titulo, "\n")] = '\0';  // Remove o caractere de nova linha

        // Leitura do autor com fgets
        printf("Autor do livro: \n");
        fgets(novolivro->autor, sizeof(novolivro->autor), stdin);
        novolivro->autor[strcspn(novolivro->autor, "\n")] = '\0';  // Remove o caractere de nova linha

        // Leitura do ano com fgets e conversão para inteiro
        printf("Ano do livro: \n");
        char ano_input[10];
        fgets(ano_input, sizeof(ano_input), stdin);
        sscanf(ano_input, "%d", &novolivro->ano);  // Converte a string para um inteiro

        // Exibe os dados do livro adicionado
        printf("Livro adicionado: ID %d - Titulo: %s, Autor: %s, Ano: %d\n", novolivro->id, novolivro->titulo, novolivro->autor, novolivro->ano);

        // Armazena o livro no array
        livros[num_livros_adicionados++] = novolivro;
        
        // Grava o livro no ficheiro livros.txt
        ficheiro = fopen("livros.txt", "a");
        if (ficheiro != NULL) {
            fprintf(ficheiro, "Livro: ID %d - Titulo: %s, Autor: %s, Ano: %d\n", novolivro->id, novolivro->titulo, novolivro->autor, novolivro->ano);  // Apenas o ID e informações
            fclose(ficheiro);
        } else {
            printf("Falha ao abrir o ficheiro para gravar\n");
        }

        // Pergunta ao utilizador se deseja adicionar mais livros
        printf("Deseja adicionar outro livro? (s/n): ");
        scanf(" %c", &continuar);  // Lê a resposta
        getchar();  // Limpa o buffer de entrada

    } while (continuar == 's' || continuar == 'S');  // Continuar enquanto a resposta for 's' ou 'S'

    return GerirLivros();
}

void ListarLivros() 
{
    FILE *ficheiro = fopen("livros.txt", "r");  // Abre o arquivo para leitura
    if (ficheiro == NULL) {
        printf("Erro ao abrir o arquivo livros.txt.\n");
        return GerirLivros();  // Retorna ao menu de gerenciamento
    }

    char linha[256];
    int livroEncontrado = 0;  // Flag para verificar se há livros

    // Lê cada linha do arquivo e exibe os dados dos livros
    while (fgets(linha, sizeof(linha), ficheiro)) {
        printf("%s", linha);  // Exibe a linha do livro
        livroEncontrado = 1;
    }

    if (!livroEncontrado) {
        printf("Nenhum livro encontrado no sistema.\n");
    }

    fclose(ficheiro);  // Fecha o arquivo após leitura

    // Espera o usuário digitar 's' para sair
    char opcao;
    printf("Para sair, digite 's': ");
    scanf(" %c", &opcao);  // Lê a opção do usuário, com espaço para limpar o buffer
    if (opcao == 's' || opcao == 'S') {
        return GerirLivros();  // Retorna ao menu de gerenciamento
    }
}

void PesquisarLivro() 
{
    char opcao;
    do {
        getchar();  // Limpa o buffer de entrada
        char titulo_busca[100];
        printf("Digite o título do livro que deseja pesquisar: ");
        fgets(titulo_busca, sizeof(titulo_busca), stdin);
        titulo_busca[strcspn(titulo_busca, "\n")] = '\0';  // Remove o caractere de nova linha

        FILE *ficheiro = fopen("livros.txt", "r");  // Abre o arquivo para leitura
        if (ficheiro == NULL) {
            printf("Erro ao abrir o arquivo livros.txt.\n");
            return GerirLivros();  // Retorna ao menu de gerenciamento
        }

        char linha[256];
        int encontrado = 0;

        // Lê cada linha do arquivo e verifica se o título do livro contém a busca
        while (fgets(linha, sizeof(linha), ficheiro)) {
            if (strstr(linha, titulo_busca) != NULL) {  // Verifica se o título contém o texto buscado
                printf("%s", linha);  // Exibe a linha do livro encontrado
                encontrado = 1;
            }
        }

        if (!encontrado) {
            printf("Nenhum livro encontrado com o título '%s'.\n", titulo_busca);
        }

        fclose(ficheiro);  // Fecha o arquivo após leitura

        // Pergunta ao usuário se deseja procurar outro livro
        printf("Deseja procurar outro livro? (s/n): ");
        scanf(" %c", &opcao);  // Lê a opção do usuário, com espaço para limpar o buffer

    } while (opcao == 's' || opcao == 'S');  // Continua enquanto a resposta for 's' ou 'S'

    printf("--------------------\n");
    return GerirLivros();  // Retorna ao menu de gerenciamento
}

void RemoverLivro() 
{
    int id_remover;
    int encontrado = 0;
    FILE *ficheiro, *ficheiro_temp;
    char linha[256];

    // Solicitar o ID do livro que o usuário deseja remover
    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &id_remover);

    // Abrir o arquivo original para leitura
    ficheiro = fopen("livros.txt", "r");
    if (ficheiro == NULL) 
    {
        printf("Erro ao abrir o arquivo livros.txt.\n");
        return GerirLivros();  // Retorna ao menu
    }

    // Criar um arquivo temporário para armazenar os livros que não serão removidos
    ficheiro_temp = fopen("livros_temp.txt", "w");
    if (ficheiro_temp == NULL) 
    {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(ficheiro);
        return GerirLivros();  // Retorna ao menu
    }

    // Ler o arquivo original linha por linha
    while (fgets(linha, sizeof(linha), ficheiro)) 
    {
        int livro_id;
        char titulo[100], autor[100];
        int ano;

        // Tentativa de ler os dados do livro na linha
        // Formato esperado: "Livro: ID X - Titulo: Y, Autor: Z, Ano: W"
        int n = sscanf(linha, "Livro: ID %d - Titulo: %99[^,], Autor: %99[^,], Ano: %d", &livro_id, titulo, autor, &ano);
        
        // Depuração: Verificar se a leitura foi bem-sucedida
        if (n == 4) 
        {
            printf("Lido ID: %d, Titulo: %s, Autor: %s, Ano: %d\n", livro_id, titulo, autor, ano); // Verifique o que está sendo lido
            
            // Se o ID não corresponder ao ID a ser removido, escreva no arquivo temporário
            if (livro_id != id_remover) 
            {
                fprintf(ficheiro_temp, "Livro: ID %d - Titulo: %s, Autor: %s, Ano: %d\n", livro_id, titulo, autor, ano);
            } 
            else 
            {
                encontrado = 1;  // Livro encontrado e removido
            }
        }
        else
        {
            // Caso o sscanf não consiga ler corretamente
            printf("Erro ao ler linha: %s", linha);
        }
    }

    // Fechar ambos os arquivos
    fclose(ficheiro);
    fclose(ficheiro_temp);

    // Se não encontrar o livro para remover
    if (!encontrado) 
    {
        printf("Livro com ID %d não encontrado.\n", id_remover);
        remove("livros_temp.txt");  // Apaga o arquivo temporário em caso de erro
        return GerirLivros();  // Retorna ou chama GerirLivros()
    }

    // Apagar o arquivo original
    remove("livros.txt");

    // Renomear o arquivo temporário para o nome original
    if (rename("livros_temp.txt", "livros.txt") != 0) 
    {
        printf("Erro ao atualizar o arquivo de livros.\n");
        return;  // Retorna ou chama GerirLivros()
    }

    printf("Livro removido com sucesso do arquivo.\n");
    return GerirLivros();
}




// Função para registrar um empréstimo
void RegistarEmprestimo() {
    if (num_emprestimos >= MAX_EMPRESTIMOS) {
        printf("Número máximo de empréstimos atingido.\n");
        return;
    }

    int idLivro, idLeitor;
    printf("Digite o ID do livro para emprestar: ");
    scanf("%d", &idLivro);
    printf("Digite o ID do leitor: ");
    scanf("%d", &idLeitor);

    // Verifica se o livro está disponível
    livro *livroEmprestado = NULL;
    for (int i = 0; i < num_livros_adicionados; i++) {
        if (livros[i]->id == idLivro) {
            livroEmprestado = livros[i];
            break;
        }
    }

    if (!livroEmprestado) {
        printf("Livro com ID %d não encontrado.\n", idLivro);
        return;
    }

    if (livroEmprestado->disponivel == 0) {
        printf("Livro com ID %d já está emprestado.\n", idLivro);
        return;
    }

    // Verifica se o leitor existe
    leitor *leitorEmprestimo = NULL;
    for (int i = 0; i < max_leitor; i++) {
        if (leitores[i] != NULL && leitores[i]->id == idLeitor) {
            leitorEmprestimo = leitores[i];
            break;
        }
    }

    if (!leitorEmprestimo) {
        printf("Leitor com ID %d não encontrado.\n", idLeitor);
        return;
    }

    // Registra o empréstimo
    emprestimos[num_emprestimos].idLivro = idLivro;
    emprestimos[num_emprestimos].idLeitor = idLeitor;
    printf("Digite a data de empréstimo (dd/mm/aaaa): ");
    scanf("%s", emprestimos[num_emprestimos].dataEmprestimo);
    strcpy(emprestimos[num_emprestimos].dataDevolucao, ""); // Devolução ainda não realizada

    // Atualiza o status do livro
    livroEmprestado->disponivel = 0;

    printf("Empréstimo registrado com sucesso!\n");
    num_emprestimos++;
}

// Função para registrar a devolução de um livro
void RegistarDevolucao() {
    int idLivro;
    printf("Digite o ID do livro para devolução: ");
    scanf("%d", &idLivro);

    // Encontra o empréstimo ativo para o livro
    int encontrado = 0;
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].idLivro == idLivro && strcmp(emprestimos[i].dataDevolucao, "") == 0) {
            encontrado = 1;

            // Registra a devolução
            printf("Digite a data de devolução (dd/mm/aaaa): ");
            scanf("%s", emprestimos[i].dataDevolucao);

            // Atualiza o status do livro
            for (int j = 0; j < num_livros_adicionados; j++) {
                if (livros[j]->id == idLivro) {
                    livros[j]->disponivel = 1;
                    break;
                }
            }

            printf("Devolução registrada com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Nenhum empréstimo ativo encontrado para o livro com ID %d.\n", idLivro);
    }
}



// I think the next code is kinda useless, no offense
/*
{
                printf("menu \"Exibir Relat�rios\":\n");
                printf("1. Relat�rio de Livros Dispon�veis\n");
                printf("2. Relat�rio de Livros Emprestados\n");
                printf("3. Relat�rio de Leitores Ativos\n");
                printf("4. Voltar ao Menu Principal\n");
                printf("Escolha uma op��o: ");
                
                int subOpcao;
                scanf("%d", &subOpcao);

                switch (subOpcao) 
                {
                    case 1:
                        exibirRelatorioLivrosDisponiveis();
                        break;
                    case 2:
                        exibirRelatorioLivrosEmprestados();
                        break;
                    case 3:
                        exibirRelatorioLeitoresAtivos();
                        break;
                    case 4:
                        printf("Voltando ao Menu Principal\n");
                        break;
                    default:
                        printf("Op��o inv�lida! Tente novamente.\n");
                        break;
                }
}
*/