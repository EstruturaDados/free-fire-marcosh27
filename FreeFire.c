#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>      // Essencial para medir o tempo de execução (clock())
#include <stdbool.h>   // Para usar o tipo 'bool' e valores 'true'/'false'

/*
 ============================================================================
    Desafio Final: Torre de Resgate - Análise de Algoritmos
    Descrição: Sistema para gerenciar, ordenar e buscar componentes
               de uma torre de resgate, comparando o desempenho de
               diferentes algoritmos de ordenação.
 ============================================================================
*/

// --- 1. Definições e Estruturas Globais ---

#define MAX_COMPONENTES 20

// A struct 'Componente' armazena os dados de cada peça da torre.
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // Prioridade de montagem (1 a 10)
} Componente;

// Vetor global para armazenar os componentes da torre.
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;

// Flag para garantir que a busca binária só seja executada em um vetor ordenado por nome.
bool ordenadoPorNome = false;

// Contadores globais para medição de desempenho.
long long int contadorComparacoes = 0;
long long int contadorTrocas = 0; // Bônus: contar trocas também é um bom indicador.

// --- 2. Protótipos das Funções ---

void cadastrarComponente();
void mostrarComponentes(const char* titulo); // LINHA CORRIGIDA
void limparBuffer();

// Algoritmos de Ordenação
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();

// Algoritmo de Busca
void buscaBinariaPorNome();


// --- 3. Função Principal (main) ---
// Controla o fluxo do programa com um menu interativo.
int main() {
    int opcao;
    // Dados de exemplo para facilitar os testes
    // Se não quiser, basta comentar este bloco
    Componente exemplos[5] = {
        {"Chip Central", "Controle", 10},
        {"Placa de Energia", "Energia", 9},
        {"Antena de Sinal", "Comunicacao", 8},
        {"Motor de Propulsao", "Propulsao", 7},
        {"Base de Suporte", "Suporte", 5}
    };
    for(int i = 0; i < 5; i++) torre[i] = exemplos[i];
    totalComponentes = 5;
    // Fim do bloco de exemplos


    do {
        printf("\n\n========== PAINEL DE MONTAGEM DA TORRE DE RESGATE ==========\n");
        printf("Componentes cadastrados: %d/%d\n", totalComponentes, MAX_COMPONENTES);
        printf("------------------------------------------------------------\n");
        printf("1. Cadastrar Novo Componente\n");
        printf("2. Listar Componentes Atuais\n");
        printf("\n--- ESTRATEGIAS DE ORDENACAO ---\n");
        printf("3. Ordenar por NOME (Bubble Sort) - para busca rapida\n");
        printf("4. Ordenar por TIPO (Insertion Sort) - para agrupar pecas\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort) - para montagem critica\n");
        printf("\n--- ACIONAMENTO DA TORRE ---\n");
        printf("6. Buscar Componente-Chave (Busca Binaria por Nome)\n");
        printf("0. Sair e Iniciar Montagem Final\n");
        printf("------------------------------------------------------------\n");
        printf("Escolha sua estrategia: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                mostrarComponentes("LISTA ATUAL DE COMPONENTES");
                break;
            case 3: { // Bloco para declarar variáveis locais (start, end)
                printf("\nIniciando ordenacao por NOME com Bubble Sort...\n");
                // Medição de Desempenho
                contadorComparacoes = 0;
                contadorTrocas = 0;
                clock_t start = clock();
                bubbleSortNome(); // Chama o algoritmo
                clock_t end = clock();
                double tempoGasto = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n--- RELATORIO DE DESEMPENHO (Bubble Sort) ---\n");
                printf("Comparacoes realizadas: %lld\n", contadorComparacoes);
                printf("Trocas realizadas: %lld\n", contadorTrocas);
                printf("Tempo de execucao: %f segundos\n", tempoGasto);
                printf("---------------------------------------------\n");
                mostrarComponentes("Componentes Ordenados por Nome");
                break;
            }
            case 4: {
                printf("\nIniciando ordenacao por TIPO com Insertion Sort...\n");
                // Medição de Desempenho
                contadorComparacoes = 0;
                contadorTrocas = 0;
                clock_t start = clock();
                insertionSortTipo(); // Chama o algoritmo
                clock_t end = clock();
                double tempoGasto = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n--- RELATORIO DE DESEMPENHO (Insertion Sort) ---\n");
                printf("Comparacoes realizadas: %lld\n", contadorComparacoes);
                printf("Movimentacoes realizadas: %lld\n", contadorTrocas);
                printf("Tempo de execucao: %f segundos\n", tempoGasto);
                printf("-----------------------------------------------\n");
                mostrarComponentes("Componentes Ordenados por Tipo");
                break;
            }
            case 5: {
                printf("\nIniciando ordenacao por PRIORIDADE com Selection Sort...\n");
                // Medição de Desempenho
                contadorComparacoes = 0;
                contadorTrocas = 0;
                clock_t start = clock();
                selectionSortPrioridade(); // Chama o algoritmo
                clock_t end = clock();
                double tempoGasto = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n--- RELATORIO DE DESEMPENHO (Selection Sort) ---\n");
                printf("Comparacoes realizadas: %lld\n", contadorComparacoes);
                printf("Trocas realizadas: %lld\n", contadorTrocas);
                printf("Tempo de execucao: %f segundos\n", tempoGasto);
                printf("------------------------------------------------\n");
                mostrarComponentes("Componentes Ordenados por Prioridade");
                break;
            }
            case 6:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nEstrategia final definida. Iniciando montagem da torre... Boa sorte!\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha uma estrategia valida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- 4. Funções de Gerenciamento de Componentes ---

void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\nERRO: O inventario de componentes esta cheio!\n");
        return;
    }

    printf("\n--- Cadastro de Novo Componente ---\n");
    printf("Nome do componente: ");
    fgets(torre[totalComponentes].nome, 30, stdin);
    torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = 0;

    printf("Tipo (Controle, Suporte, Propulsao, etc.): ");
    fgets(torre[totalComponentes].tipo, 20, stdin);
    torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = 0;

    printf("Prioridade de montagem (1 a 10): ");
    scanf("%d", &torre[totalComponentes].prioridade);
    limparBuffer();

    totalComponentes++;
    ordenadoPorNome = false; // Qualquer adição invalida a ordenação anterior.
    printf("\nComponente '%s' cadastrado com sucesso!\n", torre[totalComponentes-1].nome);
}

void mostrarComponentes(const char* titulo) {
    printf("\n--- %s ---\n", titulo);
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("%-20s | %-15s | %d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
    printf("------------------------------------------------------------------\n");
}

// --- 5. Implementação dos Algoritmos de Ordenação ---

/**
 * @brief Ordena os componentes por NOME usando Bubble Sort.
 * É um algoritmo simples, mas ineficiente (O(n^2)).
 * Compara pares adjacentes e os troca se estiverem na ordem errada,
 * repetindo o processo até que a lista esteja ordenada.
 */
void bubbleSortNome() {
    if (totalComponentes < 2) return;

    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            contadorComparacoes++;
            // strcmp > 0 significa que a string 'j' vem depois da 'j+1'
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                contadorTrocas++;
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = true; // A flag é ATIVADA aqui
}

/**
 * @brief Ordena os componentes por TIPO usando Insertion Sort.
 * Também tem complexidade O(n^2), mas é eficiente para listas
 * pequenas ou parcialmente ordenadas.
 * Constrói a lista ordenada um item por vez, inserindo cada
 * novo elemento em sua posição correta na parte já ordenada.
 */
void insertionSortTipo() {
    if (totalComponentes < 2) return;

    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = torre[i];
        int j = i - 1;

        // Move os elementos que são maiores que a chave para uma posição à frente
        while (j >= 0) {
            contadorComparacoes++;
            if(strcmp(torre[j].tipo, chave.tipo) > 0) {
                contadorTrocas++; // Conta como movimentação
                torre[j + 1] = torre[j];
                j = j - 1;
            } else {
                break; // Encontrou a posição correta, não precisa comparar mais
            }
        }
        torre[j + 1] = chave;
    }
    ordenadoPorNome = false; // A ordenação por tipo DESATIVA a flag de nome.
}


/**
 * @brief Ordena os componentes por PRIORIDADE usando Selection Sort.
 * Complexidade O(n^2). É notável por minimizar o número de trocas.
 * A cada iteração, encontra o menor elemento restante e o coloca
 * no início da porção não ordenada da lista.
 */
void selectionSortPrioridade() {
    if (totalComponentes < 2) return;

    for (int i = 0; i < totalComponentes - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < totalComponentes; j++) {
            contadorComparacoes++;
            if (torre[j].prioridade > torre[min_idx].prioridade) { // Ordenando do maior para o menor
                min_idx = j;
            }
        }
        if(min_idx != i) {
            contadorTrocas++;
            Componente temp = torre[min_idx];
            torre[min_idx] = torre[i];
            torre[i] = temp;
        }
    }
    ordenadoPorNome = false; // A ordenação por prioridade DESATIVA a flag de nome.
}


// --- 6. Implementação da Busca Binária ---

/**
 * @brief Busca um componente por NOME usando Busca Binária.
 * Requer que o vetor esteja PRÉ-ORDENADO por nome.
 * É um algoritmo muito eficiente (O(log n)), que repetidamente
 * divide o intervalo de busca pela metade.
 */
void buscaBinariaPorNome() {
    if (!ordenadoPorNome) {
        printf("\nALERTA: A busca binaria requer que os componentes estejam ordenados por nome!\n");
        printf("Use a opcao 3 (Ordenar por Nome) antes de tentar buscar.\n");
        return;
    }

    if (totalComponentes == 0) {
        printf("\nNenhum componente para buscar.\n");
        return;
    }

    char chave[30];
    printf("\nDigite o nome do componente-chave para ativar a torre: ");
    fgets(chave, 30, stdin);
    chave[strcspn(chave, "\n")] = 0;

    contadorComparacoes = 0;
    int inicio = 0;
    int fim = totalComponentes - 1;
    bool encontrado = false;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        contadorComparacoes++;
        int res = strcmp(torre[meio].nome, chave);

        if (res == 0) { // Encontrou!
            printf("\n--- COMPONENTE-CHAVE LOCALIZADO! ---\n");
            printf("Nome: %s, Tipo: %s, Prioridade: %d\n", torre[meio].nome, torre[meio].tipo, torre[meio].prioridade);
            printf("Torre pronta para ativacao!\n");
            encontrado = true;
            break;
        }
        if (res < 0) { // O item procurado está na metade direita
            inicio = meio + 1;
        } else { // O item procurado está na metade esquerda
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\nFALHA NA ATIVACAO: Componente-chave '%s' nao encontrado!\n", chave);
    }
    printf(">>>>> Busca Binaria realizou %lld comparacoes.\n", contadorComparacoes);
}


// --- 7. Função Utilitária ---

// Limpa o buffer de entrada para evitar problemas entre scanf e fgets.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}