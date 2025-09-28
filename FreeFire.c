// Importação de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Definição da Estrutura de Dados ---

// Define a capacidade máxima da mochila (inventário)
#define MAX_ITENS 10

// A struct 'Item' representa um objeto e suas caracteristicas no inventário do jogador
typedef struct {
    char nome[30];      // Nome do item (ex: "Pistola", "Kit Medico")
    char tipo[20];      // Categoria do item (ex: "Arma", "Cura", "Municao")
    int quantidade;     // Quantidade do item
} Item;


// --- Variáveis Globais ---

// 'Mochila' armazena todos os itens do inventário
// É uma lista sequencial baseada em um array de structs referentes ao 'Item'
Item mochila[MAX_ITENS];

// 'totalItens' controla o número atual de itens na mochila
int totalItens = 0;


// --- Declaração das Funções ---

// Funções de CRUD dos itens
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// Função auxiliar de limpeza de buffer de memória
void limparBuffer();

// --- Função principal ---
int main() {
    int opcao;

    // loop para exibição do menu enquanto a opção for diferente de 0(sair do jogo)
    do {
        printf("\n--- MOCHILA DE LOOT INICIAL ---\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item\n");
        printf("4. Listar Itens (Atual)\n");
        printf("0. Sair do Jogo\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer após ler o número

        // O switch gerencia a chamada da função referente a opção escolhida pelo usuário
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                listarItens();
                break;
            case 0:
                printf("\nSaindo do sistema de loot!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// --- Funções ---

 // Limpa o buffer de entrada do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastra um novo item na mochila.
void inserirItem() {

    // Verifica se a mochila atingiu a capacidade máxima.
    if (totalItens >= MAX_ITENS) {
        printf("\n--- ERRO: Mochila cheia! Nao e possivel adicionar mais itens. ---\n");
        return;
    }

    printf("\n--- Cadastro de Novo Item ---\n");
    Item novoItem;

    // Cadastra o nome do item
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; // Remove o '\n' do final

    // Cadastra o tipo de item;
    printf("Tipo do item (Arma, Municao, Cura, etc.): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0; // Remove o '\n' do final

    // Cadastra a quantidade de item
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    // Limpa o buffer para a próxima leitura do menu
    limparBuffer();

    // Adiciona o novo item na próxima posição livre do vetor.
    mochila[totalItens] = novoItem;
    totalItens++; // Incrementa o contador de itens.

    printf("\n>>> Item '%s' cadastrado com sucesso! <<<\n", novoItem.nome);

    // Lista itens
    listarItens();
}

 // Remove um item da mochila com base no seu nome.
void removerItem() {
    if (totalItens == 0) {
        printf("\n--- AVISO: Mochila ja esta vazia. ---\n");
        return;
    }

    char nomeParaRemover[30];
    int indiceEncontrado = -1;

    printf("\n--- Remocao de Item ---\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeParaRemover, 30, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0; // Remove o '\n'

    // Laço para buscar o item
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    // Se o item foi encontrado (indiceEncontrado é diferente de -1).
    if (indiceEncontrado != -1) {

        // looop para deslocar os itens à direita do item removido para a esquerda.
        for (int i = indiceEncontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--; // Decrementa o número total de itens.
        printf("\n>>> Item '%s' removido com sucesso! <<<\n", nomeParaRemover);
        
        // lista itens
        listarItens();
    } else {
        printf("\n--- ERRO: Item '%s' nao encontrado na mochila. ---\n", nomeParaRemover);
    }
}

// Exibe todos os itens registrados na mochila.
void listarItens() {
    printf("\n================ INVENTARIO ================\n");
    // Verifica se a mochila está vazia.
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("--------------------------------------------------\n");
        printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("--------------------------------------------------\n");
        // looop percorre a mochila e lista os itens.
        for (int i = 0; i < totalItens; i++) {
            printf("%-20s | %-15s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("==================================================\n");
}


// Realiza uma busca sequencial por um item na mochila.
void buscarItem() {
    if (totalItens == 0) {
        printf("\n--- AVISO: Mochila vazia. ---\n");
        return;
    }

    char nomeParaBuscar[30];
    int encontrado = 0; // Flag para indicar se o item foi encontrado.

    printf("\n--- Busca de Item ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeParaBuscar, 30, stdin);
    nomeParaBuscar[strcspn(nomeParaBuscar, "\n")] = 0; // Remove o '\n'

    // loop de busca do item
    for (int i = 0; i < totalItens; i++) {
        // A função 'strcmp' compara o nome buscado com o nome do item atual.
        // Retorna 0 se as strings forem idênticas.
        if (strcmp(mochila[i].nome, nomeParaBuscar) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("------------------------\n");
            encontrado = 1; // Ativa a flag para indicar sucesso.
            break;
        }
    }

    // se a flag permancer com 0, o item não foi encontrado!!!
    if (!encontrado) {
        printf("\n--- Item '%s' nao foi encontrado na mochila. ---\n", nomeParaBuscar);
    }
}