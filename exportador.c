#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/* Exportar dados de um arquivo binário para um arquivo de texto no mesmo formato */
void txtbinario(const char *arquivoBinario, const char *arquivoTexto)
{
    FILE *binario = fopen(arquivoBinario, "rb");
    FILE *texto = fopen(arquivoTexto, "w");

    if (binario == NULL || texto == NULL)
    {
        printf("Erro ao abrir arquivos\n");
        exit(1);
    }

    Camelo camelo;
    while (fread(&camelo, sizeof(Camelo), 1, binario) == 1)
    {
        fprintf(texto, "%d %s %d\n", camelo.chave, camelo.nome, camelo.idade);
    }
    fclose(binario);
    fclose(texto);
}


/* Iniciação da geração do Arquivo txt com os dados do arquivo bin editado*/
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s arquivo_binario arquivo_texto\n", argv[0]);
        exit(1);
    }
    /* Converter o arquivo binário para texto */
    txtbinario(argv[1], argv[2]);

    printf("A conversao foi concluida com sucesso!\n");

    return 0;
}