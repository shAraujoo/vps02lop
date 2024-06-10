#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define NUM_MACHINES 4

int i,j;

typedef struct {
    char date[11];
    int machine_count[NUM_MACHINES];
} DailyProduction;

void processCSV(FILE *file, int *total_count, DailyProduction *daily_production, int *daily_count) {
    char line[MAX_LINE_LENGTH];
    char *token;
    int day_index = -1;

    
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        
        token = strtok(line, ";");
        char date[11];
        strcpy(date, token);

        token = strtok(NULL, ";");
        char time[6];
        strcpy(time, token);

        token = strtok(NULL, ";");
        int machine = atoi(token) - 1;

        
        total_count[machine]++;

        
        int found = 0;
        for (i = 0; i <= day_index; i++) {
            if (strcmp(daily_production[i].date, date) == 0) {
                daily_production[i].machine_count[machine]++;
                found = 1;
                break;
            }
        }
        
        
        if (!found) {
            day_index++;
            strcpy(daily_production[day_index].date, date);
            for (i = 0; i < NUM_MACHINES; i++) {
                daily_production[day_index].machine_count[i] = 0;
            }
            daily_production[day_index].machine_count[machine]++;
        }
        (*daily_count) = day_index + 1;
    }
}

void printReport(int *total_count, DailyProduction *daily_production, int daily_count) {
    
    printf("Contagem Total por Maquina\n\n");
    printf("| Maquina | Quantidade |\n");
    printf("|---------|------------|\n");
    for (i = 0; i < NUM_MACHINES; i++) {
        printf("| %d       | %d         |\n", i + 1, total_count[i]);
    }

    
    printf("\nProducao Diaria por Maquina\n\n");
    printf("| Data       | Maquina 1 | Maquina 2 | Maquina 3 | Maquina 4 |\n");
    printf("|------------|-----------|-----------|-----------|-----------|\n");
    for (i = 0; i < daily_count; i++) {
        printf("| %s |", daily_production[i].date);
        for (j = 0; j < NUM_MACHINES; j++) {
            printf(" %d         |", daily_production[i].machine_count[j]);
        }
        printf("\n");
    }
}

void writeMarkdownReport(char *filename, int *total_count, DailyProduction *daily_production, int daily_count) {
    FILE *mdfile = fopen(filename, "w");
    if (mdfile == NULL) {
        printf("Erro ao criar o arquivo de relatório %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(mdfile, "# Relatorio de Producao de Explosivos\n\n");

    
    fprintf(mdfile, "## Contagem Total por Maquina\n\n");
    fprintf(mdfile, "| Máquina | Quantidade |\n");
    fprintf(mdfile, "|---------|------------|\n");
    for (i = 0; i < NUM_MACHINES; i++) {
        fprintf(mdfile, "| %d       | %d         |\n", i + 1, total_count[i]);
    }

   
    fprintf(mdfile, "\n## Producao Diária por Maquina\n\n");
    fprintf(mdfile, "| Data       | Maquina 1 | Maquina 2 | Maquina 3 | Maquina 4 |\n");
    fprintf(mdfile, "|------------|-----------|-----------|-----------|-----------|\n");
    for (i = 0; i < daily_count; i++) {
        fprintf(mdfile, "| %s |", daily_production[i].date);
        for (j = 0; j < NUM_MACHINES; j++) {
            fprintf(mdfile, " %d         |", daily_production[i].machine_count[j]);
        }
        fprintf(mdfile, "\n");
    }

    fclose(mdfile);
}

int main() {
    FILE *file = fopen("producao.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo producao.csv\n");
        return EXIT_FAILURE;
    }

    int total_count[NUM_MACHINES] = {0};
    DailyProduction daily_production[100]; 
    int daily_count = 0;

    processCSV(file, total_count, daily_production, &daily_count);

    fclose(file);

    printReport(total_count, daily_production, daily_count);
    writeMarkdownReport("explosivos.md", total_count, daily_production, daily_count);

    printf("\nRelatório gerado com sucesso!\n");

    return 0;
}

