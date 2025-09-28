// Importação de bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Definição das Estruturas de Dados ---

// Define a capacidade máxima da mochila (inventário)
#define MAX_ITENS 10

// A struct 'Item' representa um objeto e suas caracteristicas no inventário do jogador
typedef struct {
    char nome[30];      // Nome do item (ex: "Pistola", "Kit Medico")
    char tipo[20];      // Categoria do item (ex: "Arma", "Cura", "Municao")
    int quantidade;     // Quantidade do item
} Item;

// Struct 'Nó' para a Lista Encadeada.
// Contém o item (dados) e um ponteiro para o próximo nó da lista.
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


// --- Variáveis Globais e Contadores ---

// Para a Mochila com VETOR
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
bool vetorOrdenado = false; // Flag para controlar se o vetor está ordenado para a busca binária

// Para a Mochila com LISTA ENCADEADA
No* mochilaLista = NULL; // O ponteiro inicial (cabeça) da lista é NULL (lista vazia)

// Contador para análise de desempenho das buscas
int contadorComparacoes = 0;


// --- Declaração das Funções ---

// Funções do menu principal
void menuVetor();
void menuLista();
void limparBuffer();

// Funções para a implementação com VETOR
// Funções de CRUD dos itens
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// Funções para a implementação com LISTA ENCADEADA
// Funções de CRUD dos itens
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();


// --- Função principal ---
int main() {
    int opcao;
    // loop para exibição do menu enquanto a opção for diferente de 0(sair do jogo)
    do {
        printf("\n========== ESCOLHA A ESTRUTURA DE DADOS ==========\n");
        printf("1. Gerenciar Mochila com VETOR (Lista Sequencial)\n");
        printf("2. Gerenciar Mochila com LISTA ENCADEADA\n");
        printf("0. Sair do Jogo\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();  // Limpa o buffer após ler o número
        // O switch gerencia a chamada da função referente a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("\nSaindo do sistema de loot!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
    return 0;
}


// --- Menus ---

// Menu com uso de vetor
void menuVetor() {
    int opcao;
    // loop para exibição do menu 'mochila(vetor)' enquanto a opção for diferente de 0(voltar ao menu principal)
    do {
        printf("\n--- Mochila (VETOR) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("5. Ordenar Itens (para Busca Binaria)\n");
        printf("6. Buscar (Binaria)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer após ler o número

        // O switch gerencia a chamada da função referente a opção escolhida pelo usuário
        switch (opcao) {
            
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
// Menu com uso de lista
void menuLista() {
    int opcao;
    // loop para exibição do menu 'mochila(lista encadeada)' enquanto a opção for diferente de 0(voltar ao menu principal)
    do {
        printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();// Limpa o buffer após ler o número

        // O switch gerencia a chamada da função referente a opção escolhida pelo usuário
        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// --- Funções VETOR ---

// Cadastra o nome do item
void inserirItemVetor() {
    // Verifica se a mochila atingiu a capacidade máxima.
    if (totalItensVetor >= MAX_ITENS) {
        printf("\nERRO: Mochila (vetor) cheia!\n");
        return;
    }
    Item novoItem;
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;  // Remove o '\n' do final
    printf("Tipo do item: ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;  // Remove o '\n' do final
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer(); // Limpa o buffer após ler o número

    // Adiciona o novo item na próxima posição livre do vetor.
    mochilaVetor[totalItensVetor] = novoItem;
    totalItensVetor++; // Incrementa o contador de itens.
    vetorOrdenado = false; // A inserção desordena o vetor
    printf("Item '%s' inserido no vetor.\n", novoItem.nome);
}

// Remove um item da mochila com base no seu nome.
void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }
    char nomeParaRemover[30];
    printf("Nome do item a remover: ");
    fgets(nomeParaRemover, 30, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0; // Remove o '\n'

    int indice = -1;
    // Laço para buscar o item
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeParaRemover) == 0) {
            indice = i;
            break;
        }
    }
     // Se o item foi encontrado (indiceEncontrado é diferente de -1).
    if (indice != -1) {
        // Para remover, desloca todos os elementos seguintes uma posição para a esquerda
        for (int i = indice; i < totalItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        totalItensVetor--; // Decrementa o número total de itens.
        vetorOrdenado = false; // A remoção pode desordenar
        printf("Item '%s' removido do vetor.\n", nomeParaRemover);
    } else {
        printf("Item '%s' nao encontrado no vetor.\n", nomeParaRemover);
    }
}

// Exibe todos os itens registrados na mochila.
void listarItensVetor() {
    printf("\n--- Itens na Mochila (VETOR) [%d/%d] ---\n", totalItensVetor, MAX_ITENS);
    // Verifica se a mochila está vazia.
    if (totalItensVetor == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Nome: %-20s | Tipo: %-15s | Qtd: %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Ordena o vetor
void ordenarVetor() {
    // verifica se os itens são menores que 2, se sim retorna que não precisa ordenar
    if (totalItensVetor < 2) {
        printf("\nNao ha itens suficientes para ordenar.\n");
        vetorOrdenado = true;
        return;
    }
    // usando Bubble Sort para ordenar por nome
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    vetorOrdenado = true;
    printf("\nMochila (vetor) ordenada por nome com sucesso!\n");
    listarItensVetor();
}
// Realiza uma busca sequencial por um item na mochila.
void buscarSequencialVetor() {
    // Verifica se a mochila está vazia.
    if (totalItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }
    char nomeBusca[30];
    // pega a entrada do item que deverá ser buscado
    printf("Nome do item para busca sequencial: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0;
    bool encontrado = false; // Flag para indicar se o item foi encontrado.

    // loop de busca do item
    for (int i = 0; i < totalItensVetor; i++) {
        contadorComparacoes++; // Incrementa a cada comparação
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %-20s | Tipo: %-15s | Qtd: %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            encontrado = true;
            break;
        }
    }
    // se a flag permancer com false, o item não foi encontrado!!!
    if (!encontrado) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf(">>>>> Busca Sequencial (Vetor) realizou %d comparacoes.\n", contadorComparacoes);
}

// Busca de forma binaria o item no vetor
void buscarBinariaVetor() {
    // verifica se o vetor ta ordenado para poder realizar a busca
    if (!vetorOrdenado) {
        printf("\nERRO: O vetor precisa estar ordenado. Use a opcao 5 primeiro.\n");
        return;
    }
    // Verifica se a mochila está vazia.
    if (totalItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }

    char nomeBusca[30];
    // pega a entrada do item que deverá ser buscado
    printf("Nome do item para busca binaria: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0;
    bool encontrado = false;
    int inicio = 0, fim = totalItensVetor - 1;
    
    // loop de busca do item
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        contadorComparacoes++; // Incrementa a cada comparação no laço
        int res = strcmp(mochilaVetor[meio].nome, nomeBusca);
        if (res == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %-20s | Tipo: %-15s | Qtd: %d\n", mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            encontrado = true;
            break;
        }
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    // se a flag permancer com false, o item não foi encontrado!
    if (!encontrado) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf(">>>>> Busca Binaria (Vetor) realizou %d comparacoes.\n", contadorComparacoes);
}


// --- FUNÇÕES LISTA ENCADEADA ---

// Cadastra um novo item na mochila.
void inserirItemLista() {
    // Aloca memória dinamicamente para um novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("ERRO: Falha ao alocar memoria para a lista.\n");
        return;
    }
    
    Item novoItem;
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    printf("Tipo do item: ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    novoNo->dados = novoItem;
    // Insere o novo nó no início da lista (operação mais rápida)
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
    printf("Item '%s' inserido na lista.\n", novoItem.nome);
}
// Remove um item da mochila com base no seu nome.
void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\nMochila (lista) vazia!\n");
        return;
    }
    char nomeParaRemover[30];
    printf("Nome do item a remover: ");
    fgets(nomeParaRemover, 30, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0;

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nomeParaRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) { // Encontrou o item
        if (anterior == NULL) { // O item a ser removido é o primeiro da lista
            mochilaLista = atual->proximo;
        } else { // O item está no meio ou no fim
            anterior->proximo = atual->proximo;
        }
        free(atual); // Libera a memória do nó removido
        printf("Item '%s' removido da lista.\n", nomeParaRemover);
    } else {
        printf("Item '%s' nao encontrado na lista.\n", nomeParaRemover);
    }
}

void listarItensLista() {
    printf("\n--- Itens na Mochila (LISTA ENCADEADA) ---\n");
    if (mochilaLista == NULL) {
        printf("Vazia.\n");
        return;
    }
    No* temp = mochilaLista;
    while (temp != NULL) {
        printf("Nome: %-20s | Tipo: %-15s | Qtd: %d\n", temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

void buscarSequencialLista() {
     if (mochilaLista == NULL) {
        printf("\nMochila (lista) vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("Nome do item para busca sequencial: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    contadorComparacoes = 0;
    bool encontrado = false;
    No* temp = mochilaLista;

    while (temp != NULL) {
        contadorComparacoes++;
        if (strcmp(temp->dados.nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %-20s | Tipo: %-15s | Qtd: %d\n", temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
            encontrado = true;
            break;
        }
        temp = temp->proximo;
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf(">>>>> Busca Sequencial (Lista) realizou %d comparacoes.\n", contadorComparacoes);
}

// Limpa o buffer de memória

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}