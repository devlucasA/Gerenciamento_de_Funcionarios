#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "Departamento.h"

// Definição da estrutura Funcionario
typedef struct Funcionario {
    char nome[50];
    char cpf[13];
    int idade;
    float sal_B; // Salário bruto do funcionário
    float sal_L; // Salário Líquido
    struct Departamento *dep; // Ponteiro para o departamento
    struct Funcionario *prox;
    struct Funcionario *ant;
} Funcionario;

// Definição da estrutura FuncionarioList
typedef struct FuncionarioList {
    Funcionario *cabeca; // Nó cabeça da lista
} FuncionarioList;

// Protótipos das funções
FuncionarioList *criarL();
void inserir_F(FuncionarioList *lista, Departamento *departamento);
void calcularSalarioLiquido(Funcionario *funcionario);
void exibirFuncionarios(FuncionarioList *lista, Departamento *departamento);
void exibirDepartamentosComFuncionarios(FuncionarioList *lista_funcionarios, Lista *lista_departamentos);
void ordenaFuncionario(FuncionarioList *lista, Departamento *departamento);
void removerFuncionarioPorCPF(FuncionarioList *lista, char cpf[]);
void buscarFuncionarioPorCPF(FuncionarioList *lista, char cpf[]);
void removerDepartamentoPorCodigo( FuncionarioList *lista, int codigo);
void removerDepartamentoPorCodigo(FuncionarioList *lista, int codigo);
bool validarCPF(char *cpf);

#endif /* FUNCIONARIO_H */




