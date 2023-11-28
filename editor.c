#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/* Editor do Usuário */
void Editor(Camelo **inicio, const char *ArquivoSaida)
{
    int opcao;
    do
    {   /* Opções do menu do Usuário */
        printf("\nEditor de Camelos\n");
        printf("1. Inserir camelo\n");
        printf("2. Remover camelo\n");
        printf("3. Exibir camelo\n");
        printf("4. Salvar edicoes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            InserirCamelo(inicio);
            break;
        case 2:
            RemoverCamelo(inicio);
            break;
        case 3:
            ExibirCamelos(*inicio);
            break;
        case 4:
            SalvarEdicoes(inicio, ArquivoSaida);
            break;
        case 5:
            SalvarEdicoes(inicio, ArquivoSaida); /* Salva as edições antes de sair do editor*/
            printf("Saindo do Editor.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}


/* Inicializa lista com dados do binário, executa o editor, e libera a memória. */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <ArquivoOriginal> <ArquivoSaida>\n", argv[0]);
        exit(1);
    }

    const char *ArquivoOriginal = argv[1];
    const char *ArquivoSaida = argv[2];

    Camelo *inicio = LerBinario(ArquivoOriginal); /* Inicializa a lista encadeada de camelos com os dados do arquivo binário */
    Editor(&inicio, ArquivoSaida); /* Inicia o Seletor de Opções do Usuário */
    
    /* Limpa a memória */
    while (inicio != NULL)
    {
        Camelo *proximo = inicio->proximo;
        free(inicio); /* Libere a memória do camelo lista */
        inicio = proximo;
    }
    return 0;
}