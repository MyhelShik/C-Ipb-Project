#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"


int main()
{
    menu_principal();
    // GerirLeitores();
    // exibirRelatorioLeitoresAtivos();
    return 0;


    FILE *f; 
    f = fopen("..\\test.txt", "w");
    leitor cls[] = max_leitor;

    for (int i = 0; i < max_leitor; i++)
    {
        fprintf(f, "%d, %s %d\n",leitores[i]->id != NULL, leitores[i]->nome != "", leitores[i]->cc);
    }
    
    fclose(f);

    //while(fscanf(f,"%d,%[^\n]",&leitor[i]->id,&leitor.nome)!=EOF> || )

    //fprintf(f, "%d, %s\n",leitor[i]->id != NULL, leitor[i]->nome != "")

}
