#include <stdio.h>
#include "funcoes.c"

int main(int argc, char const *argv[]){
    // Cadastrar NOME, MATRICULA, CPF, DATA DE NASCIMENTO E NOTAS
    // Cadastrar, Consultar, Remover e Alterar registros
    // No Cadastrar e Alterar o sistema devera validar se o CPF eh valido
    // Consultar deve apresentar todos os dados, incluindo a idade do aluno baseado na data de nascimento
    // Sistema deve persistir em arquivos

    int opcMenu;
    char menuStr[] = "";

    while (opcMenu != 5){
        printf("\nSistema de Gestao de Alunos\n");
        printf("1 - Cadastrar\n2 - Consultar\n3 - Alterar\n4 - Remover\n5 - Sair\nEscolha uma opcao: \n");
        scanf("%s", menuStr);
        opcMenu = atoi(menuStr);
        switch (opcMenu){
            case 1:
                printf("Cadastrar\n");
                cadastrar();
                break;
            case 2:
                printf("Consultar\n");
                consultar();
                break;
            case 3:
                printf("Alterar\n");
                alterar();
                break;
            case 4:
                printf("Remover\n");
                remover();
                break;
            case 5:
                printf("Sair\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
