#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cabecalho.h"

/* Ler arquivo Binário e obter as informações */
Camelo *LerBinario(const char *ArquivoOriginal)
{
    FILE *binario = fopen(ArquivoOriginal, "rb");
    if (binario == NULL)
    {
        printf("Erro ao abrir arquivo binário\n");
        exit(1);
    }
    Camelo *inicio = NULL;
    Camelo *fim = NULL;  /* Adicione um ponteiro para o final da lista */
    Camelo camelo;
    while (fread(&camelo, sizeof(Camelo), 1, binario) == 1)
    {
        Camelo *newCamelo = (Camelo *)malloc(sizeof(Camelo));
        newCamelo->chave = camelo.chave;
        strcpy(newCamelo->nome, camelo.nome);
        newCamelo->idade = camelo.idade;
        newCamelo->proximo = NULL;

        if (inicio == NULL)
        {
            /* Se a lista está vazia, o novo camelo é tanto o início quanto o fim */
            inicio = newCamelo;
            fim = newCamelo;
        }
        else
        {
            /* Adicione o novo camelo ao final da lista */
            fim->proximo = newCamelo;
            fim = newCamelo;
        }
    }
    fclose(binario);
    return inicio;
}


/* Insere um novo camelo */
void InserirCamelo(Camelo **inicio)
{
    int chave, idade;
    char nome[50];

    printf("Insira os dados do novo camelo:\n");
    printf("Chave: ");
    scanf("%d", &chave);
    printf("Nome: ");
    scanf("%s", nome);
    printf("Idade: ");
    scanf("%d", &idade);

    /* Verificar se a chave já existe na lista e remove o camelo já existente automaticamente */
    Camelo *anterior = NULL;
    Camelo *lista = *inicio;
    bool remocaoRealizada = false;

    while (lista != NULL)
    {
        if (lista->chave == chave)
        {
            /* Chave já existe, remova o camelo com a mesma chave automaticamente */
            if (anterior == NULL)
            {
                *inicio = lista->proximo;
            }
            else
            {
                anterior->proximo = lista->proximo;
            }
            free(lista);
            remocaoRealizada = true;  /* Sai do loop após a remoção */
        }
        anterior = lista;
        lista = lista->proximo;
    }

    /* Cria novo camelo */
    Camelo *newCamelo = (Camelo *)malloc(sizeof(Camelo));
    if (newCamelo == NULL)
    {
        printf("Erro ao alocar memoria para o novo camelo\n");
        exit(1);
    }
    newCamelo->chave = chave;
    strncpy(newCamelo->nome, nome, sizeof(newCamelo->nome) - 1);
    newCamelo->nome[sizeof(newCamelo->nome) - 1] = '\0';
    newCamelo->idade = idade;
    newCamelo->proximo = NULL;

    // Inserir o novo camelo na lista
    Camelo *atual = *inicio;

    if (*inicio == NULL || chave < atual->chave)
    {
        /* Inserir no início da lista ou em uma lista vazia */
        newCamelo->proximo = *inicio;
        *inicio = newCamelo;
    }
    else
    {
        /* Procurar a posição correta na lista para inserir o novo camelo */
        while (atual->proximo != NULL && chave > atual->proximo->chave)
        {
            atual = atual->proximo;
        }

        newCamelo->proximo = atual->proximo;
        atual->proximo = newCamelo;
    }
    printf("Camelo inserido com sucesso!\n");
}


/* Remove o Camelo Escolhido */
void RemoverCamelo(Camelo **inicio)
{
    int chave;
    printf("Insira a chave do camelo a ser removido: ");
    scanf("%d", &chave);

    /* Ponteiro para o camelo anterior e o camelo atual na lista */
    Camelo *anterior = NULL;
    Camelo *atual = *inicio;

    /* Encontra o camelo na lista com a chave especificada */
    while (atual != NULL && atual->chave != chave)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    /* Verifica se o camelo foi encontrado */
    if (atual != NULL)
    {
        /* Se o camelo está no início da lista */
        if (anterior == NULL)
        {
            *inicio = atual->proximo;
        }
        else
        {
            /* Se o camelo está no meio ou no fim da lista */
            anterior->proximo = atual->proximo;
        }

        /* Libera a memória alocada para o camelo removido */ 
        free(atual);
        printf("Camelo removido com sucesso.\n");
    }
    else
    {
        /* Caso a chave do camelo não tenha sido encontrado na lista */ 
        printf("Camelo com chave %d nao encontrado.\n", chave);
    }
}


/* Exibe todos os camelos */
void ExibirTodososCamelos(Camelo *atual) {
    if (atual == NULL) {
        return;
    }

    printf("\nCamelo:\n");
    printf("Chave: %d\n", atual->chave);
    printf("Nome: %s\n", atual->nome);
    printf("Idade: %d\n", atual->idade);

    ExibirTodososCamelos(atual->proximo);
}


/* Exibe todos os camelos ou só o escolhido (recursiva com a função ExibirTodososCamelos) */
void ExibirCamelos(Camelo *lista) {
    int opcao;
    printf("1. Exibir todos os camelos\n");
    printf("2. Exibir camelo por chave\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        /* Se o usuário escolher exibir todos os camelos */
        ExibirTodososCamelos(lista);
    } else if (opcao == 2) {
        int chave;
        printf("Insira a chave do camelo a ser exibido: ");
        scanf("%d", &chave);
        
        /* Busca o camelo com a chave especificada na lista */
        while (lista != NULL) {
            if (lista->chave == chave) {
                printf("Camelo:\n");
                printf("Chave: %d\n", lista->chave);
                printf("Nome: %s\n", lista->nome);
                printf("Idade: %d\n", lista->idade);
                return; /* Sai do loop após encontrar o camelo */
            }
            lista = lista->proximo;
        }
        /* Se a chave do camelo não for encontrada na lista */ 
        printf("Camelo com chave %d nao encontrado.\n", chave);
    } else {
        /* Se a opção fornecida não for válida */
        printf("Opcao Invalida.\n");
    }
}


/* Salvar Edições */
void SalvarEdicoes(Camelo **inicio, const char *ArquivoSaida)
{
    FILE *binario = fopen(ArquivoSaida, "wb");
    if (binario == NULL)
    {
        printf("Erro ao abrir arquivo binário\n");
        exit(1);
    }

    Camelo *atual = *inicio;
    /* Percorre a lista e escreve cada camelo no arquivo binário */
    while (atual != NULL)
    {
        /* Escreve o camelo atual no arquivo */
        fwrite(atual, sizeof(Camelo), 1, binario);
        /* Move para o próximo camelo na lista */
        atual = atual->proximo;
    }

    fclose(binario);
    printf("Edicoes salvas com sucesso no arquivo %s\n", ArquivoSaida);
}
