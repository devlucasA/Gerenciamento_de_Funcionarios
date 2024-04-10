#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Departamento.h"
#include "Funcionarios.h"


// Implementação das funções

Lista *criar() {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    novo->ini = NULL;
    novo->fim = NULL;
    return novo;
}


Lista *inserir(Lista * lista){
    Departamento * novoD = (Departamento*)malloc(sizeof(Departamento)); //novo Deparatamento. Alocando espaço para o departamento
        if(novoD== NULL){
            printf("Erro na alocação de memória!\n");
            return lista; //Retorna a lista original caso a memória não seja alocada
        }

    //Informações do Deparatamento
    printf("\nInsira o codigo do departamento: ");
    scanf("%d", &novoD->cod);
    printf("\nInsira o nome do departamento: ");
    scanf("%s", &novoD->nome);
    printf("\nInsira a bonificacao que o departamento oferece: ");
    scanf("%f", &novoD->bonus);

    novoD->prox = NULL; //Definindo o próximo como NULL, pois o novo departamento será o último da lista

    if(lista->ini == NULL){
        //Se a lista estiver vazia, seu primeiro elemento será o novo departamento
        lista->ini = novoD;

    }else{
        lista->fim->prox = novoD;
    }

    lista->fim = novoD;
    return lista;
}


//Alogrítmo bublesort para ordenar os departamentos e exibi-los
// Função para trocar dois departamentos de lugar na lista
void trocarDepartamentos(Departamento* a, Departamento* b) {
    int tempCodigo = a->cod;
    float tempBonus = a->bonus;
    char tempNome[50];

    strcpy(tempNome, a->nome);

    a->cod = b->cod;
    a->bonus = b->bonus;
    strcpy(a->nome, b->nome);

    b->cod = tempCodigo;
    b->bonus = tempBonus;
    strcpy(b->nome, tempNome);
}



// Função para ordenar os departamentos por código (Bubble Sort)
void ordenarDepartamentos(Lista* lista) {
    int trocado;
    Departamento *atual;
    Departamento *anterior = NULL;

    if (lista == NULL || lista->ini == NULL) {
        return;
    }

    do {
        trocado = 0;
        atual = lista->ini;

        while (atual->prox != anterior) {
            if (atual->cod > atual->prox->cod) {
                trocarDepartamentos(atual, atual->prox);
                trocado = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocado);
}

// Função para exibir todos os departamentos cadastrados em ordem crescente de código
void exibirDepartamentos(Lista* lista) {
    if (lista == NULL || lista->ini == NULL) {
        printf("Nenhum departamento cadastrado.\n");
        return;
    }

    // Ordenar os departamentos por código antes de exibir
    ordenarDepartamentos(lista);

    printf("Departamentos cadastrados (em ordem crescente de codigo):\n");
    Departamento* atual = lista->ini;
    printf("\n\t------DEPARTAMENTOS INSERIDOS------");
    while (atual != NULL) {
        printf("\n[Codigo: %d\n", atual->cod);
        printf("Nome: %s\n", atual->nome);
        printf("Bonificacao: %.2f]\n", atual->bonus);
        atual = atual->prox;
    }
}


