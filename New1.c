#include <stdio.h>

 
typedef struct
{
    char nome[50];
    int salario;
}class;

int main()
{
    FILE *f; 
    f = fopen("..\\test.txt", "w");
    class cls[5];

    for (int i = 0; i < 2; i++)
    {
        printf("type some names... 5 names\n");
        scanf(" %[^\n]", &cls[i].nome);
        printf("type some salaries... 5 salaries\n");
        scanf("%d", &cls[i].salario);
    }
    

    if(f == NULL)
        printf("erro na abertura do ficheiro.\n");

    /*
    while(fgets(str,sizeof(str),f)!=NULL)
    {
        printf("%s"str);
    }
    */
    else
    {
        for (int i = 0; i < 2; i++)
        {
            fprintf(f, "Nome: %s, Salario: %d\n",cls[i].nome,cls[i].salario);
        }
        
        printf("Successo!\n");
    }
    
    fclose(f);
}