#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100

void cadastrarTarefa(char tarefas[][4][50], int *quantidade) {
    if (*quantidade >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido!\n");
        return;
    }

    printf("Título: ");
    fgets(tarefas[*quantidade][0], 50, stdin);
    tarefas[*quantidade][0][strcspn(tarefas[*quantidade][0], "\n")] = 0;

    printf("Descrição: ");
    fgets(tarefas[*quantidade][1], 50, stdin);
    tarefas[*quantidade][1][strcspn(tarefas[*quantidade][1], "\n")] = 0;

    printf("Prioridade (Alta, Média, Baixa): ");
    fgets(tarefas[*quantidade][2], 50, stdin);
    tarefas[*quantidade][2][strcspn(tarefas[*quantidade][2], "\n")] = 0;

    printf("Status (Pendente, Concluído): ");
    fgets(tarefas[*quantidade][3], 50, stdin);
    tarefas[*quantidade][3][strcspn(tarefas[*quantidade][3], "\n")] = 0;

    (*quantidade)++;
    printf("Tarefa cadastrada com sucesso!\n");
}

void listarTarefas(char tarefas[][4][50], int quantidade) {
    printf("\n--- Tarefas Cadastradas ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Tarefa %d:\n", i + 1);
        printf("Título: %s\n", tarefas[i][0]);
        printf("Descrição: %s\n", tarefas[i][1]);
        printf("Prioridade: %s\n", tarefas[i][2]);
        printf("Status: %s\n\n", tarefas[i][3]);
    }
}

void editarTarefa(char tarefas[][4][50], int indice) {
    printf("Editando Tarefa %d\n", indice + 1);

    printf("Novo Título: ");
    fgets(tarefas[indice][0], 50, stdin);
    tarefas[indice][0][strcspn(tarefas[indice][0], "\n")] = 0;

    printf("Nova Descrição: ");
    fgets(tarefas[indice][1], 50, stdin);
    tarefas[indice][1][strcspn(tarefas[indice][1], "\n")] = 0;

    printf("Nova Prioridade: ");
    fgets(tarefas[indice][2], 50, stdin);
    tarefas[indice][2][strcspn(tarefas[indice][2], "\n")] = 0;

    printf("Novo Status: ");
    fgets(tarefas[indice][3], 50, stdin);
    tarefas[indice][3][strcspn(tarefas[indice][3], "\n")] = 0;

    printf("Tarefa editada com sucesso!\n");
}

void excluirTarefa(char tarefas[][4][50], int *quantidade, int indice) {
    for (int i = indice; i < *quantidade - 1; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(tarefas[i][j], tarefas[i + 1][j]);
        }
    }
    (*quantidade)--;
    printf("Tarefa excluída com sucesso!\n");
}

void salvarTarefasEmArquivo(char tarefas[][4][50], int quantidade) {
    FILE *arquivo = fopen("tarefas.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "Tarefa %d: %s - Prioridade: %s - Status: %s\n",
                i + 1, tarefas[i][0], tarefas[i][2], tarefas[i][3]);
    }

    fclose(arquivo);
    printf("Tarefas salvas em tarefas.txt!\n");
}

int main() {
    char tarefas[MAX_TAREFAS][4][50];
    int quantidade = 0;
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento de Tarefas ===\n");
        printf("1. Cadastrar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Editar Tarefa\n");
        printf("4. Excluir Tarefa\n");
        printf("5. Salvar Tarefas em Arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o '\n' do buffer

        switch (opcao) {
            case 1:
                cadastrarTarefa(tarefas, &quantidade);
                break;
            case 2:
                listarTarefas(tarefas, quantidade);
                break;
            case 3: {
                int indice;
                printf("Digite o número da tarefa a editar: ");
                scanf("%d", &indice);
                getchar();
                if (indice >= 1 && indice <= quantidade) {
                    editarTarefa(tarefas, indice - 1);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
            }
            case 4: {
                int indice;
                printf("Digite o número da tarefa a excluir: ");
                scanf("%d", &indice);
                getchar();
                if (indice >= 1 && indice <= quantidade) {
                    excluirTarefa(tarefas, &quantidade, indice - 1);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
            }
            case 5:
                salvarTarefasEmArquivo(tarefas, quantidade);
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 6);

    return 0;
}