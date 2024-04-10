#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Funcionarios.h"


FuncionarioList * criarL(){
    FuncionarioList * lista = (FuncionarioList*)malloc(sizeof(FuncionarioList));
    if(lista == NULL){
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    lista->cabeca = (Funcionario*)malloc(sizeof(Funcionario));

    if(lista->cabeca == NULL){
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    lista->cabeca->prox = NULL;
    lista->cabeca->ant = NULL;
    return lista;

}

bool validarCPF(char *cpf) {
    // Verifica se o CPF tem 11 dígitos
    if (strlen(cpf) != 11)
        return false;

    // Verifica se todos os dígitos são iguais
    bool todosDigitosIguais = true;
    for (int i = 1; i < 11; ++i) {
        if (cpf[i] != cpf[0]) {
            todosDigitosIguais = false;
            break;
        }
    }
    if (todosDigitosIguais)
        return false;

    // Calcula o primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; ++i) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int digito1 = (soma * 10) % 11;
    if (digito1 == 10)
        digito1 = 0;

    // Verifica o primeiro dígito verificador
    if (cpf[9] - '0' != digito1)
        return false;

    // Calcula o segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; ++i) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int digito2 = (soma * 10) % 11;
    if (digito2 == 10)
        digito2 = 0;

    // Verifica o segundo dígito verificador
    if (cpf[10] - '0' != digito2)
        return false;

    // CPF válido
    return true;
}

void inserir_F(FuncionarioList * lista, Departamento * departamento){  

    Funcionario *novo = (Funcionario*)malloc(sizeof(Funcionario));
    if(novo == NULL){
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    printf("\n Insira o nome do funcionario: ");
    scanf("%s", &novo->nome);
    printf("\nInsira a idade do funcionario: ");
    scanf("%d", &novo->idade);
    printf("\nInsira o CPF do funcionario: ");
    scanf("%s", &novo->cpf);

        if (!validarCPF(novo->cpf)) {
        printf("CPF invalido. Funcionario nao cadastrado.\n");
        free(novo);
        return;
    }

    printf("\nInsira o salario Bruto do funcionario: ");
    scanf("%f", &novo->sal_B);

    novo->dep = departamento; //Define o departamento do funcionário

    //Inserir novo funcionário na lista
    novo->prox = NULL;
    if(lista->cabeca->prox == NULL){ //Se a lista estiver vazia o novo funcionário se torna o primeiro
        
        lista->cabeca->prox = novo;
        novo->ant = NULL;

    }else{
        //Ou percorre a lista até encontrar o último funcionário , e raliza a inserção após ele
        Funcionario *final;
        final = lista->cabeca->prox;
        while(final->prox != NULL){
            final = final->prox;
        }
        final->prox = novo;
        novo->ant = final;
    }


}


void calcularSalarioLiquido(Funcionario *funcionario) {
    if (funcionario == NULL) {
        printf("Funcionario nao informado.\n");
        return;
    }

    if (funcionario->dep == NULL) {
        printf("Departamento nao informado para o funcionario %s.\n", funcionario->nome);
        return;
    }

    float bonificacao = funcionario->sal_B * (funcionario->dep->bonus / 100.0);
    funcionario->sal_L = funcionario->sal_B + bonificacao;

    printf("\nSalario liquido de %s: %.2f\n", funcionario->nome, funcionario->sal_L);
}


//Função para exibir os funcionários de um determinado departamento e em ordem alfabética

void exibirFuncionarios(FuncionarioList *lista, Departamento *departamento){ //Função que exibe os funcionários de um determinado departamento

    if(lista == NULL || lista->cabeca->prox == NULL){ //Verifica se a lista está vazia ou se o departamento não tem funcionários
    printf("\nNao ha funcionarios cadastrados.\n");
    exit(1);

    }

    Funcionario * novo;
    novo = lista->cabeca->prox;
    printf("Lista de funcionarios do departamento %s: \n", departamento->nome);
    while(novo != NULL){ //Nessa parte eu percorro a lista de funcionários, e os indico a partir de um departamento específico
        if(novo->dep == departamento){
            calcularSalarioLiquido(novo);
            printf("\n[Nome: %s\n", novo->nome);
            printf("Idade: %d\n", novo->idade);
            printf("CPF: %s\n", novo->cpf);
            printf("Salario Bruto: %.2f]\n", novo->sal_B);
             printf("Salario Liquido: %.2f]\n", novo->sal_L);
        }
        novo = novo->prox;
    }
    
}

void exibirDepartamentosComFuncionarios(FuncionarioList* lista_funcionarios, Lista* lista_departamentos) {
    if (lista_departamentos == NULL || lista_departamentos->ini == NULL) {
        printf("Nenhum departamento cadastrado.\n");
        return;
    }

    // Ordenar os departamentos por código antes de exibir
    ordenarDepartamentos(lista_departamentos);

    printf("Departamentos cadastrados (em ordem crescente de codigo):\n");
    Departamento* atual_dep = lista_departamentos->ini;
    printf("\n\t------DEPARTAMENTOS INSERIDOS------\n");
    while (atual_dep != NULL) {
        printf("\n[Codigo: %d\n", atual_dep->cod);
        printf("Nome: %s\n", atual_dep->nome);
        printf("Bonificacao: %.2f]\n", atual_dep->bonus);

        // Exibir informações dos funcionários do departamento
        Funcionario* atual_func = lista_funcionarios->cabeca->prox;
        printf("Funcionarios do departamento %s:\n", atual_dep->nome);
        while (atual_func != NULL) {
            calcularSalarioLiquido(atual_func);
            if (atual_func->dep == atual_dep) {
                printf("\tNome: %s\n", atual_func->nome);
                printf("\tCPF: %s\n", atual_func->cpf);
                printf("\tIdade: %d\n", atual_func->idade);
                printf("\tSalario Bruto: %.2f\n", atual_func->sal_B);
                printf("\tSalario Liquido: %.2f\n", atual_func->sal_L);
            }
            atual_func = atual_func->prox;
        }
        atual_dep = atual_dep->prox;
    }
}

void ordenaFuncionario(FuncionarioList *lista, Departamento * departamento){ 
    int troca; //Variável para o loop de ordenação

    if(lista == NULL || lista->cabeca->prox == NULL){ //Verifica se a lista está vazia ou se o departamento não tem funcionários
    printf("\nNao ha funcionarios cadastrados.\n");
    exit(1);

    }
    //Ordenação dos funcionários
    do{ //Nesse algoritmo de ordenação, se nehum dado for ordenado o valor de 'troca' permanece 0 e o loop encerra; porém se houver a necessidade de ordenação a variável 'troca' permanece com o valor 1 até que tudo seja ordenado

        troca = 0;
        Funcionario * novo;
        novo = lista->cabeca->prox;
        while(novo->prox != NULL){
            if(novo->dep == departamento && strcmp(novo->nome, novo->prox->nome)>0){ //Troca os funcionários de lugar na lista
            Funcionario *aux;
            aux = novo->prox;
            if(aux->prox != NULL){
                aux->prox->ant = novo;
            }
            aux->ant = novo->ant;
            aux->prox = novo;
            if(novo->ant != NULL){
                novo->ant->prox = aux;
            }
            novo->ant = aux;
            if(lista->cabeca->prox == novo){
                lista->cabeca->prox = aux;
            }
            troca = 1;

            }
            novo = novo->prox;
        }
    }while(troca);
}


void removerFuncionarioPorCPF(FuncionarioList *lista, char cpf[]) {
    // Verifica se a lista de funcionarios esta vazia
    if (lista == NULL || lista->cabeca->prox == NULL) {
        printf("\nLista de funcionarios vazia.\n");
        return;
    }

    // Inicia a partir do primeiro da lista
    Funcionario *atual = lista->cabeca->prox;
    while (atual != NULL) {
        // Verifica se o CPF do funcionario atual corresponde ao CPF informado
        if (strcmp(atual->cpf, cpf) == 0) {
            // Atualiza os ponteiros para remover o funcionario da lista
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            }
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            }

            // Se o funcionario a ser removido é o primeiro da lista, atualiza o ponteiro da lista
            if (lista->cabeca->prox == atual) {
                lista->cabeca->prox = atual->prox;
            }

            // Libera a memoria alocada para o funcionario removido
            free(atual);
            printf("\nFuncionario removido com sucesso.\n");
            return;
        }
        atual = atual->prox; // Move para o próximo funcionario na lista
    }

    printf("\nFuncionario com CPF %s nao encontrado.\n", cpf);
}


void buscarFuncionarioPorCPF(FuncionarioList *lista, char cpf[]) {
    // Verifica se a lista esta vazia
    if (lista == NULL || lista->cabeca->prox == NULL) {
        printf("\nLista de funcionarios vazia.\n");
        return;
    }

    // Inicia a busca percorrendo a lista de funcionarios
    Funcionario *atual = lista->cabeca->prox;
    while (atual != NULL) {
        // Verifica se o CPF do funcionario atual é o mesmo do CPF fornecido
        if (strcmp(atual->cpf, cpf) == 0) {
            // Exibe as informacoes do funcionario encontrado
            printf("\nFuncionario encontrado:\n");
            printf("Nome: %s\n", atual->nome);
            printf("CPF: %s\n", atual->cpf);
            printf("Idade: %d\n", atual->idade);
            printf("Salario Bruto: %.2f\n", atual->sal_B);
            printf("Departamento: %s\n", atual->dep->nome);
            printf("Bonificacao do Departamento: %.2f\n", atual->dep->bonus);
            return;
        }
        atual = atual->prox; // Move para o proximo funcionário na lista
    }
    printf("\nFuncionario com CPF %s nao encontrado.\n", cpf);
}


void removerDepartamentoPorCodigo(FuncionarioList *lista, int codigo) {
    // Verifica se a lista esta vazia
    if (lista == NULL || lista->cabeca->prox == NULL) {
        printf("\nLista de departamentos vazia.\n");
        return;
    }

    // Inicia a remocao percorrendo a lista de funcionarios
    Funcionario *atual = lista->cabeca->prox;
    while (atual != NULL) {
        // Verifica se o departamento do funcionario atual possui o codigo fornecido
        if (atual->dep->cod == codigo) {
            // Verifica se existem funcionarios vinculados ao departamento
            Funcionario *verifica = lista->cabeca->prox;

            int funcionariosVinculados = 0;
            //Conta os funcionários - sem essa contagem o departamento ainda é removido se houver 1 funcionario
            while (verifica != NULL) {
                if (verifica->dep->cod == codigo) {
                    funcionariosVinculados++;
                }
                verifica = verifica->prox;
            }
            if (funcionariosVinculados > 0) {
                printf("\nDepartamento nao pode ser removido.\nExistem funcionarios vinculados a ele.\n");
                return;
            }

            // Remove o departamento da lista
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            }
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                lista->cabeca->prox = atual->prox;
            }
            free(atual->dep); // Libera a memoria alocada para o departamento removido
            printf("\nDepartamento removido com sucesso.\n");
            return;
        }
        atual = atual->prox; // Move para o proximo funcionário na lista
    }
    printf("\nDepartamento com codigo %d nao encontrado.\n", codigo);
}

