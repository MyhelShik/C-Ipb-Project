#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"


int main()
{
    menu_principal();
    // GerirLeitores();
    // exibirRelatorioLeitoresAtivos();


    FILE *f; 
    f = fopen("..\\leitores.txt", "w");
    leitor cls[5];

    if(f == NULL)
        printf("erro na abertura do ficheiro.\n");

    else
    {
        for (int i = 0; i < max_leitor; i++)
        {
            if(leitores[i]->id != 0)
            {
                fprintf(f, "%d, %s %d\n",leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
                printf("%d, %s %d\nEscrito com sucesso!\n",leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
            }

        }
        printf("Sucesso!");
    }
    
    fclose(f);
    

    return 0;
    //while(fscanf(f,"%d,%[^\n]",&leitor[i]->id,&leitor.nome)!=EOF> || )

    //fprintf(f, "%d, %s\n",leitor[i]->id != NULL, leitor[i]->nome != "")

}
