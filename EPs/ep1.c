/*
Ep1
Disciplina: MAC0422
Nomes e Nusp: Gabriel da Silva Alves - 11208109
              Pedro Zamecki Andrade  - 11207800

*/

#include <stdio.h>

// Para os comandos de sistema {fork(); execve()}
#include <unistd.h>
// Para o comando wait()
#include <sys/wait.h>
// Para o comando chmod()
#include <sys/stat.h>
// Para o comando strcomp()
#include <string.h>

// Declara o que é a entrada padrão e a saída padrão
#define STD_IN 0
#define STD_OUT 1

//Checa se arquivo existe
int existe(char *caminho){
    if( access( caminho, F_OK ) == 0 ) {
        return 1;
    // arquivo existe
    } else {
        return 0;
    // arquivo nao existe
    }
}

// Coloca as permissões de 'caminho' para 0000
void nem_eu_nem_de_ninguem(char *caminho)
{
    // Simplesmente chamamos o comando chmod no arquivo no caminho pedido
    chmod(caminho, 0000);
    printf("Arquivo \"%s\" protegido!\n", caminho);
}

// Coloca as permissões de 'caminho' para 0700
void soh_eumesmo(char *caminho)
{
    // Simplesmente chamamos o comando chmod no arquivo no caminho pedido 
    chmod(caminho, 0700);   
    printf("Arquivo \"%s\" liberado!\n", caminho);
}

// Cria um novo processo, fecha o teclado e o terminal e abre o programa em 'caminho'
void sohroda(char *caminho)
{
    // Processo pai:
    if (fork() != 0)
    {
        // Volte para a shell
        return;
    }
    // Processo filho:
    else
    {
        // Execute o programa em 'caminho' (em background)
        // Fecha o teclado e o terminal (para rodar em background)
        close(STD_IN);
        close(STD_OUT);
        execve(caminho, NULL, NULL);        
    }
}

void rodaeolhe(char *caminho){
    // Processo pai:
    pid_t id = fork(); 

    if (id != 0)
    {
        waitpid(id,0,0); // Espera filho para sair
        printf("Programa '%s' retornou com código 0%d\n", caminho, id);
        return;
    }
    // Processo filho:
    else
    {
        // Execute o programa em 'caminho'
        execve(caminho, NULL, NULL);        
    }
}

int main (int argc, char **argv)
{
    char comando[32];
    // Loop infinito
    while (1)
    {
        printf("> ");
        scanf("%s", comando);
        // a) Comando 'nem_eu_nem_de_ninguem <caminho>'
        if(strcmp(comando, "nem_eu_nem_de_ninguem") == 0)
        {
            char caminho[256];
            scanf(" %s", caminho);

            if (existe(caminho)==1){
                nem_eu_nem_de_ninguem(caminho);
            }else{
                printf("Arquivo '%s' nao encontrado\n", caminho);
            }
        }
        // b) Comando 'soh_eumesmo <caminho>'
        else if(strcmp(comando, "soh_eumesmo") == 0)
        {
            char caminho[256];
            scanf(" %s", caminho);

            if (existe(caminho)==1){
                soh_eumesmo(caminho);
            }else{
                printf("Arquivo '%s' nao encontrado\n", caminho);
            }
            
        }
        // c) Comando 'rodaeolhe <caminho>'
        else if(strcmp(comando, "rodaeolhe") == 0)
        {
            char caminho[256];
            scanf(" %s", caminho);


            if (existe(caminho)==1){
                rodaeolhe(caminho);
            }else{
                printf("Arquivo '%s' nao encontrado\n", caminho);
            }
        }

        // d) Comando 'sohroda <caminho>'
        else if(strcmp(comando, "sohroda") == 0)
        {
            char caminho[256];
            scanf(" %s", caminho);


            if (existe(caminho)==1){
                sohroda(caminho);
            }else{
                printf("Arquivo '%s' nao encontrado\n", caminho);
            }  
        }
        // Comando extra para sair da shell
        else if(strcmp(comando, "sair") == 0)
        {
            printf("Saindo da shell\n");
            break;
        }
        else
        {
            printf("Opção inválida!\n");
        }
    }
    return 0;
}