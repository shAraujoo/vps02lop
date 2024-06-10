#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j;

typedef struct {
    int matricula;
    char funcionario[50];
    char data[20];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

void gerarRelatorioMarkdown(Viagem viagens[], int total_viagens, char funcionarios[][50], float totais[], int total_funcionarios, float total_geral) {
    FILE *mdFile = fopen("RelatorioViagens.md", "w");
    if (!mdFile) {
        perror("Não foi possível criar o arquivo markdown");
        return;
    }

    fprintf(mdFile, "# Viagens ACME:\n\n");
    fprintf(mdFile, "|Matricula|Funcionario|Data|Origem|Destino|Distância|Preço|Total|\n");
    fprintf(mdFile, "|-|-|-|-|-|-|-|-:|\n");

    for (i = 0; i < total_viagens; i++) {
        Viagem v = viagens[i];
        fprintf(mdFile, "| %d | %s | %s | %s | %s | %d | %.2f | %.2f |\n", 
                v.matricula, v.funcionario, v.data, v.origem, v.destino, v.distancia, v.preco, v.total);
    }

    for (i = 0; i < total_funcionarios; i++) {
        fprintf(mdFile, "|||||||**Subtotal %s**|**R$ %.2f**|\n", funcionarios[i], totais[i]);
    }

    fprintf(mdFile, "\n## O total geral de reembolsos = R$ %.2f\n", total_geral);

    fclose(mdFile);
}

int main() {
    FILE *file = fopen("viagens.csv", "r");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return EXIT_FAILURE;
    }

    char linha[256];
    fgets(linha, sizeof(linha), file);

    Viagem viagens[100];
    int total_viagens = 0;

    while (fgets(linha, sizeof(linha), file)) {
        Viagem viagem;
        sscanf(linha, "%d;%49[^;];%19[^;];%49[^;];%49[^;];%d;%f", 
               &viagem.matricula, viagem.funcionario, viagem.data, 
               viagem.origem, viagem.destino, &viagem.distancia, &viagem.preco);
        viagem.total = (viagem.preco * viagem.distancia) / 3;
        viagens[total_viagens++] = viagem;
    }
    fclose(file);

    printf("Tabela de Viagens:\n");
    printf("| Matricula | Funcionario | Data       | Origem              | Destino              | Distancia | Preco | Total   |\n");
    printf("|-----------|-------------|------------|---------------------|----------------------|-----------|-------|---------|\n");
    for (i = 0; i < total_viagens; i++) {
        Viagem v = viagens[i];
        printf("| %-9d | %-11s | %-10s | %-19s | %-20s | %-9d | %-5.2f | %-7.2f |\n", 
               v.matricula, v.funcionario, v.data, v.origem, v.destino, v.distancia, v.preco, v.total);
    }

    float totais[100] = {0};
    char funcionarios[100][50];
    int total_funcionarios = 0;

    for (i = 0; i < total_viagens; i++) {
        Viagem v = viagens[i];

        int found = -1;
        for (j = 0; j < total_funcionarios; j++) {
            if (strcmp(funcionarios[j], v.funcionario) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            strcpy(funcionarios[total_funcionarios], v.funcionario);
            totais[total_funcionarios] = v.total;
            total_funcionarios++;
        } else {
            totais[found] += v.total;
        }
    }

    printf("\nRelatório de Reembolsos:\n");
    printf("========================\n");
    for (i = 0; i < total_funcionarios; i++) {
        printf("Funcionário: %s - Total de Reembolso: R$ %.2f\n", funcionarios[i], totais[i]);
    }

    float total_geral = 0;
    for (i = 0; i < total_funcionarios; i++) {
        total_geral += totais[i];
    }
    printf("\nTotal Geral de Reembolsos: R$ %.2f\n", total_geral);

    gerarRelatorioMarkdown(viagens, total_viagens, funcionarios, totais, total_funcionarios, total_geral);

    return 0;
}

