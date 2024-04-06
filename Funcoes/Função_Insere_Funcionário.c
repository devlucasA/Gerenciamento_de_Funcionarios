#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Implementando a função inserir Deparatamneto (Será implementado no arquivo de cabeçalho)
typedef struct Departamento {
    int cod; //Código
    char nome[50];
    float bonus; //Bonificação
   struct Departamento * prox; //Ponteiro para o próximo elemento de departamento
}Departamento;

//Estrutura para funcionário
typedef struct Funcionario{
    char nome[50];
    char cpf[13];
    int idade;
    float sal_B; //Salário bruto do funcionário
    float sal_L; //Salário Líquido
    struct Departamento *dep; //Ponteiro para o departamento
    struct Funcionario *prox;
    struct Funcionario *ant;

}Funcionario;

//Lista duplamente encadeada com nó cabeça
typedef struct FuncionarioList{
    Funcionario * cabeca; //Nó cabeça da lista

}FuncionarioList;

//Criando a lista
FuncionarioList * criarL(){
    FuncionarioList * lista = (FuncionarioList*)malloc(sizeof(FuncionarioList));
    if(lista == NULL){
        printf("Erro na alocacao de memoria!\n");
        return 2;
    }
    lista->cabeca = (Funcionario*)malloc(sizeof(Funcionario));

    if(lista->cabeca == NULL){
        printf("Erro na alocacao de memoria\n");
        return 1;
    }

    lista->cabeca->prox = NULL;
    lista->cabeca->ant = NULL;
    return lista;

}

//Função para inserir funcionários
void inserir_F(FuncionarioList * lista, Departamento * departamento){  

    Funcionario *novo = (Funcionario*)malloc(sizeof(Funcionario));
    if(novo == NULL){
        printf("Erro na alocacao de memoria!\n");
        return 2;
    }
    printf("\n Insira o nome do funcionario: ");
    scanf("%s", &novo->nome);
    printf("\nInsira a idade do funcionario: ");
    scanf("%d", &novo->idade);
    printf("\nInsira o CPF do funcionario: ");
    scanf("%s", &novo->cpf);
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

//Função para exibir os funcionários de um determinado departamento e em ordem alfabética

void exibirFuncionarios(FuncionarioList *lista, Departamento *departamento){ //Função que exibe os funcionários de um determinado departamento

    if(lista == NULL || lista->cabeca->prox == NULL){ //Verifica se a lista está vazia ou se o departamento não tem funcionários
    printf("\nNao ha funcionarios cadastrados.\n");
    return 1;

    }

    Funcionario * novo;
    novo = lista->cabeca->prox;
    printf("Lista de funcionarios do departamento %s: \n", departamento->nome);
    while(novo != NULL){ //Nessa parte eu percorro a lista de funcionários, e os indico a partir de um departamento específico
        if(novo->dep == departamento){
            printf("\n[Nome: %s\n", novo->nome);
            printf("Idade: %d\n", novo->idade);
            printf("CPF: %s", novo->cpf);
            printf("Salario Bruto: %f]\n", novo->sal_B);
        }
        novo = novo->prox;
    }
    
}
// Função para ordenar os funcionários de um departamento em ordem alfabética
void ordenaFuncionario(FuncionarioList *lista, Departamento * departamento){ 
    int troca; //Variável para o loop de ordenação

    if(lista == NULL || lista->cabeca->prox == NULL){ //Verifica se a lista está vazia ou se o departamento não tem funcionários
    printf("\nNao ha funcionarios cadastrados.\n");
    return 1;

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

int main(){ //Função principal de teste
    // Criar lista de funcionários
    FuncionarioList *listaFuncionarios = criarL();

    // Criar departamento
    Departamento *departamento = (Departamento *)malloc(sizeof(Departamento));
    if (departamento == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }
    departamento->cod = 1; // Exemplo de código de departamento
    strcpy(departamento->nome, "Departamento 1"); // Exemplo de nome de departamento
    departamento->bonus = 500.0; // Exemplo de bonificação do departamento

    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir novo funcionario\n");
        printf("2. Exibir funcionarios do departamento\n");
        printf("3. Ordenar funcionarios do departamento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                inserir_F(listaFuncionarios, departamento);
                break;
            case 2:
                exibirFuncionarios(listaFuncionarios, departamento);
                break;
            case 3:
                ordenaFuncionario(listaFuncionarios, departamento);
                printf("Funcionários do departamento %s ordenados por nome.\n", departamento->nome);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar memória alocada para a lista de funcionários e departamento
    // Código para liberar memória deve ser adicionado aqui

    return 0;

}