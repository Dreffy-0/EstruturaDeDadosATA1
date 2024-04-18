#include <stdio.h>
#include <stdlib.h>

struct Aluno {
    char nome[64];
    char tel[64];
    char curso[64];
    float nota1;
    float nota2;
};

int getAlunos(struct Aluno *aluno, FILE *entrada);
float calculaMedia(struct Aluno *aluno);
const char* defineSituacao(float media);

int main() {
    FILE* entrada;
    FILE* saida;
    struct Aluno alunos;
    entrada = fopen("../DadosEntrada.csv", "r");
    saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Arquivos não encontrados!");
        exit(1);
    }

    //Descarta a primeira linha do arquivo de entrada antes de executar o loop;
    getAlunos(&alunos, entrada);
    // Escreve o cabeçalho no arquivo de saída
    fprintf(saida, "NOME, NOTA, SITUACAO\n");

    while (getAlunos(&alunos, entrada) != EOF) {
        fprintf(saida, "%s, %.2f, %s\n", alunos.nome, calculaMedia(&alunos), defineSituacao(calculaMedia(&alunos)));
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}

float calculaMedia(struct Aluno *aluno) {
    float soma = aluno->nota1 + aluno->nota2;
    return soma / 2.0;
}

const char* defineSituacao(float media) {
    if (media >= 7) {
        return "APROVADO";
    } else {
        return "REPROVADO";
    }
}

int getAlunos(struct Aluno *aluno, FILE *entrada) {
    char linha[256];
    if (fgets(linha, sizeof(linha), entrada) == NULL)
        return EOF;

    sscanf(linha, "%[^,],%[^,],%[^,],%f,%f", aluno->nome, aluno->tel, aluno->curso, &aluno->nota1, &aluno->nota2);
    
    return 1;
}

