#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
int i, m;

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

void calcularMedias(Produto *produtos, int n, float *media_resistencia, float *media_durabilidade) {
    int soma_resistencia = 0;
    int soma_durabilidade = 0;

    for (i = 0; i < n; i++) {
        soma_resistencia += produtos[i].resistencia;
        soma_durabilidade += produtos[i].durabilidade;
    }

    *media_resistencia = (float)soma_resistencia / n;
    *media_durabilidade = (float)soma_durabilidade / n;
}

void encontrarExtremos(Produto *produtos, int n, int *maior_resistencia, int *menor_resistencia, int *maior_durabilidade, int *menor_durabilidade) {
    *maior_resistencia = *menor_resistencia = produtos[0].resistencia;
    *maior_durabilidade = *menor_durabilidade = produtos[0].durabilidade;

    for (i = 1; i < n; i++) {
        if (produtos[i].resistencia > *maior_resistencia) {
            *maior_resistencia = produtos[i].resistencia;
        }
        if (produtos[i].resistencia < *menor_resistencia) {
            *menor_resistencia = produtos[i].resistencia;
        }
        if (produtos[i].durabilidade > *maior_durabilidade) {
            *maior_durabilidade = produtos[i].durabilidade;
        }
        if (produtos[i].durabilidade < *menor_durabilidade) {
            *menor_durabilidade = produtos[i].durabilidade;
        }
    }
}

void contarAcimaAbaixoDaMedia(Produto *produtos, int n, float media_resistencia, float media_durabilidade, int *acima_resistencia, int *abaixo_resistencia, int *acima_durabilidade, int *abaixo_durabilidade) {
    *acima_resistencia = *abaixo_resistencia = 0;
    *acima_durabilidade = *abaixo_durabilidade = 0;

    for (i = 0; i < n; i++) {
        if (produtos[i].resistencia > media_resistencia) {
            (*acima_resistencia)++;
        } else {
            (*abaixo_resistencia)++;
        }

        if (produtos[i].durabilidade > media_durabilidade) {
            (*acima_durabilidade)++;
        } else {
            (*abaixo_durabilidade)++;
        }
    }
}

void imprimirAnalise(Produto *produtos, int n, float media_resistencia, float media_durabilidade, int maior_resistencia, int menor_resistencia, int maior_durabilidade, int menor_durabilidade, int acima_resistencia, int abaixo_resistencia, int acima_durabilidade, int abaixo_durabilidade) {
    printf("Media de Resistencia: %.2f\n", media_resistencia);
    printf("Media de Durabilidade: %.2f\n", media_durabilidade);

    printf("Produto(s) com Maior Resistencia: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].resistencia == maior_resistencia) {
            printf("%d ", produtos[i].numero_de_serie);
        }
    }
    printf("\n");

    printf("Produto(s) com Menor Resistencia: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].resistencia == menor_resistencia) {
            printf("%d ", produtos[i].numero_de_serie);
        }
    }
    printf("\n");

    printf("Produto(s) com Maior Durabilidade: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].durabilidade == maior_durabilidade) {
            printf("%d ", produtos[i].numero_de_serie);
        }
    }
    printf("\n");

    printf("Produto(s) com Menor Durabilidade: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].durabilidade == menor_durabilidade) {
            printf("%d ", produtos[i].numero_de_serie);
        }
    }
    printf("\n");

    printf("Produtos acima da media de resistencia: %d\n", acima_resistencia);
    printf("Produtos abaixo da media de resistencia: %d\n", abaixo_resistencia);
    printf("Produtos acima da media de durabilidade: %d\n", acima_durabilidade);
    printf("Produtos abaixo da media de durabilidade: %d\n", abaixo_durabilidade);
}

void salvarAnaliseMarkdown(char *filename, Produto *produtos, int n, float media_resistencia, float media_durabilidade, int maior_resistencia, int menor_resistencia, int maior_durabilidade, int menor_durabilidade, int acima_resistencia, int abaixo_resistencia, int acima_durabilidade, int abaixo_durabilidade) {
    FILE *mdfile = fopen(filename, "w");
    if (mdfile == NULL) {
        printf("Erro ao criar o arquivo de relatorio %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(mdfile, "# Analise de Qualidade dos Produtos\n\n");

    fprintf(mdfile, "## Medias\n\n");
    fprintf(mdfile, "- Media de Resistencia: %.2f\n", media_resistencia);
    fprintf(mdfile, "- Media de Durabilidade: %.2f\n\n", media_durabilidade);

    fprintf(mdfile, "## Extremos\n\n");

    fprintf(mdfile, "- Produto(s) com Maior Resistencia: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].resistencia == maior_resistencia) {
            fprintf(mdfile, "%d ", produtos[i].numero_de_serie);
        }
    }
    fprintf(mdfile, "\n");

    fprintf(mdfile, "- Produto(s) com Menor Resistencia: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].resistencia == menor_resistencia) {
            fprintf(mdfile, "%d ", produtos[i].numero_de_serie);
        }
    }
    fprintf(mdfile, "\n");

    fprintf(mdfile, "- Produto(s) com Maior Durabilidade: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].durabilidade == maior_durabilidade) {
            fprintf(mdfile, "%d ", produtos[i].numero_de_serie);
        }
    }
    fprintf(mdfile, "\n");

    fprintf(mdfile, "- Produto(s) com Menor Durabilidade: ");
    for (i = 0; i < n; i++) {
        if (produtos[i].durabilidade == menor_durabilidade) {
            fprintf(mdfile, "%d ", produtos[i].numero_de_serie);
        }
    }
    fprintf(mdfile, "\n");

    fprintf(mdfile, "## Comparacao com as Medias\n\n");
    fprintf(mdfile, "- Produtos acima da media de resistencia: %d\n", acima_resistencia);
    fprintf(mdfile, "- Produtos abaixo da media de resistencia: %d\n", abaixo_resistencia);
    fprintf(mdfile, "- Produtos acima da media de durabilidade: %d\n", acima_durabilidade);
    fprintf(mdfile, "- Produtos abaixo da media de durabilidade: %d\n", abaixo_durabilidade);

    fclose(mdfile);
}

int main() {
    FILE *file = fopen("parametros.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo parametros.csv\n");
        return EXIT_FAILURE;
    }

    Produto produtos[100];
    int n = 0;
    char line[MAX_LINE_LENGTH];
    char *token;

    
    fgets(line, MAX_LINE_LENGTH, file);

    
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        token = strtok(line, ";");
        produtos[n].numero_de_serie = atoi(token);

        token = strtok(NULL, ";");
        produtos[n].resistencia = atoi(token);

        token = strtok(NULL, ";");
        produtos[n].durabilidade = atoi(token);

        n++;
    }

    fclose(file);

    float media_resistencia, media_durabilidade;
    int maior_resistencia, menor_resistencia, maior_durabilidade, menor_durabilidade;
    int acima_resistencia, abaixo_resistencia, acima_durabilidade, abaixo_durabilidade;

    calcularMedias(produtos, n, &media_resistencia, &media_durabilidade);
    encontrarExtremos(produtos, n, &maior_resistencia, &menor_resistencia, &maior_durabilidade, &menor_durabilidade);
    contarAcimaAbaixoDaMedia(produtos, n, media_resistencia, media_durabilidade, &acima_resistencia, &abaixo_resistencia, &acima_durabilidade, &abaixo_durabilidade);

    imprimirAnalise(produtos, n, media_resistencia, media_durabilidade, maior_resistencia, menor_resistencia, maior_durabilidade, menor_durabilidade, acima_resistencia, abaixo_resistencia, acima_durabilidade, abaixo_durabilidade);
    salvarAnaliseMarkdown("qualidade.md", produtos, n, media_resistencia, media_durabilidade, maior_resistencia, menor_resistencia, maior_durabilidade, menor_durabilidade, acima_resistencia, abaixo_resistencia, acima_durabilidade, abaixo_durabilidade);

    printf("\nRelatorio gerado com sucesso!\n");

    return 0;
}

