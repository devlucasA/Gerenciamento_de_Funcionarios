#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <stdbool.h>

// Definição da estrutura Departamento
typedef struct Departamento {
    int cod; // Código
    char nome[50];
    float bonus; // Bonificação
    struct Departamento *prox; // Ponteiro para o próximo elemento de departamento
} Departamento;

// Definição da estrutura Lista
typedef struct Lista {
    Departamento *ini; // Início da Lista Departamento
    Departamento *fim; // Fim da Lista
} Lista;

// Protótipos das funções
Lista *criar();
Lista *inserir(Lista *lista);
void ordenarDepartamentos(Lista *lista);
void exibirDepartamentos(Lista *lista);
void trocarDepartamentos(Departamento* a, Departamento* b);

#endif /* DEPARTAMENTO_H */
