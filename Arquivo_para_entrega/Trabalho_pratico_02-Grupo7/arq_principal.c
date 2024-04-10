

#include <stdlib.h>
#include <stdio.h>
#include "Funcionarios.h"
#include "Departamento.h"

/*

    Lucas Araújo de Oliveira - 12221BCC025, 
    Gustavo Marques Oliveira -12221BCC021, 
    Natália Kenedy -12121BSI254, 
    Matheus Matos Andrade - 12211BBC025

*/

// Compilar: gcc -o a arq_principal.c Funcionarios.c Departamento.c


int main() {

    FuncionarioList *funcionarioLista = criarL(); 
    Lista *departamentoLista = criar(); 

    int opcao;
    do {

        printf("\n\n");

        printf("   ____ _____ ____  _____ _   _  ____ ___    _    __  __ _____ _   _ _____ ___      ____  _____      _____ _   _ _   _  ____ ___ ___  _   _   __  ____  ___ ___  ____  \n");
        printf("  / ___| ____|  _ \\| ____| \\ | |/ ___|_ _|  / \\  |  \\/  | ____| \\ | |_   _/ _ \\    |  _ \\| ____|    |  ___| | | | \\ | |/ ___|_ _/ _ \\| \\ | | /_/ |  _ \\|_ _/ _ \\/ ___| \n");
        printf(" | |  _|  _| | |_) |  _| |  \\| | |    | |  / _ \\ | |\\/| |  _| |  \\| | | || | | |   | | | |  _|      | |_  | | | |  \\| | |    | | | | |  \\| | /_\\ | |_) || | | | \\___ \\ \n");
        printf(" | |_| | |___|  _ <| |___| |\\  | |___ | | / ___ \\| |  | | |___| |\\  | | || |_| |   | |_| | |___     |  _| | |_| | |\\  | |___ | | |_| | |\\  |/ _ \\|  _ < | | |_| |___) |\n");
        printf("  \\____|_____|_| \\_\\_____|_| \\_|\\____|___/_/   \\_\\_|  |_|_____|_| \\_| |_| \\___/    |____/|_____|    |_|    \\___/|_| \\_|\\____|___\\___/|_| \\_/_/ \\_\\_| \\_\\___\\___/|____/ \n");
        printf("                                                                                                                                                                        \n");
    

        printf("\n\n");

        printf("## MENU ##\n");
        printf("1. Inserir novo departamento\n");
        printf("2. Inserir novo funcionario\n");
        printf("3. Exibir funcionarios de um departamento\n");
        printf("4. Remover funcionario por CPF\n");
        printf("5. Remover departamento por codigo\n");
        printf("6. Buscar funcionario por CPF\n");
        printf("7. Exibir Departamentos e funcionarios\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Inserir novo departamento
                departamentoLista = inserir(departamentoLista);
                break;
            }
            case 2: {
                // Inserir novo funcionário
                printf("\n### INSERIR NOVO FUNCIONARIO ###\n");
                printf("Escolha o departamento para o novo funcionario:\n");
                exibirDepartamentos(departamentoLista);
                printf("Codigo do departamento: ");
                int codigoDepartamento;
                scanf("%d", &codigoDepartamento);

                // Buscar o departamento pelo codigo
                Departamento *departamento = departamentoLista->ini;
                while (departamento != NULL && departamento->cod != codigoDepartamento) {
                    departamento = departamento->prox;
                }

                if (departamento != NULL) {
                    // Se o departamento existir, inserir o funcionario
                    inserir_F(funcionarioLista, departamento);
                } else {
                    printf("Departamento nao encontrado.\n");
                }
                break;
            }
            case 3: {
                // Exibir funcionários de um departamento
                printf("\n### EXIBIR FUNCIONARIOS DE UM DEPARTAMENTO ###\n");
                printf("Codigo do departamento: ");
                int codigoDepartamento;
                scanf("%d", &codigoDepartamento);

                // Buscar o departamento pelo codigo
                Departamento *departamento = departamentoLista->ini;
                while (departamento != NULL && departamento->cod != codigoDepartamento) {
                    departamento = departamento->prox;
                }

                if (departamento != NULL) {
                    exibirFuncionarios(funcionarioLista, departamento);
                } else {
                    printf("Departamento nao encontrado.\n");
                }
                break;
            }
            case 4: {
                // Remover funcionário por CPF
                char cpf[13];
                printf("CPF do funcionario a ser removido: ");
                scanf("%s", cpf);
                removerFuncionarioPorCPF(funcionarioLista, cpf);
                break;
            }
            case 5: {
                // Remover departamento por codigo
                int codigo;
                printf("Codigo do departamento a ser removido: ");
                scanf("%d", &codigo);
                removerDepartamentoPorCodigo(funcionarioLista, codigo);
                break;
            }
            case 6: {
                // Buscar funcionario por CPF
                char cpf[13];
                printf("CPF do funcionario a ser buscado: ");
                scanf("%s", cpf);
                buscarFuncionarioPorCPF(funcionarioLista, cpf);
                break;
            }
            case 7:{

                exibirDepartamentosComFuncionarios(funcionarioLista, departamentoLista);
                break;
            }
            case 8: {
       
                printf("Saindo...\n");
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 8);



    return 0;
}
