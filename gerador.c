#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/* Ordenar a lista lida com base na chave do camelo */
void Ordenar(Camelo **inicio, Camelo *newCamelo)
{
    Camelo *atual = *inicio;
    Camelo *anterior = NULL;
     /* Percorre a lista até encontrar a posição correta para o novo camelo */
    while (atual != NULL &&atual->chave < newCamelo->chave)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    /* Insere o novo camelo na lista, mantendo a ordem crescente*/
    if (anterior == NULL)
    {
        /* Se anterior for NULL, o novo camelo será o primeiro da lista */
        newCamelo->proximo = *inicio;
        *inicio = newCamelo;
    }
    else
    {
        /* Insere o novo camelo entre o camelo anterior e o camelo atual na lista */
        anterior->proximo = newCamelo;
        newCamelo->proximo = atual;
    }
}


/* Obter dados dos camelos do arquivo texto */
void Lertxt(Camelo **inicio, const char *nomeArquivo)
{
    FILE *file_text = fopen(nomeArquivo, "r");

    if (file_text == NULL)
    {
        printf("Erro ao abrir arquivo de texto\n");
        exit(1);
    }

    Camelo camelo;
    int result;

    while ((result = fscanf(file_text, "%d %49s %d", &camelo.chave, camelo.nome, &camelo.idade)) == 3)
    {
        /* Verificar se o número da chave e da idade foram lidos corretamente */
        if (camelo.chave < 0 || camelo.idade < 0)
        {
            printf("Erro: Chave ou idade inválida\n");
            exit(1);
        }

        /* Verificar se o nome não contém espaços */
        size_t nome_len = strlen(camelo.nome);
        for (size_t i = 0; i < nome_len; ++i)
        {
            if (camelo.nome[i] == ' ')
            {
                printf("Erro: Nome não pode conter espaços\n");
                exit(1);
            }
        }

        Camelo *newCamelo = (Camelo *)malloc(sizeof(Camelo));

        if (newCamelo == NULL)
        {
            printf("Erro ao alocar memória para novo camelo\n");
            exit(1);
        }
        /* Criação de novos elementos da lista */
        newCamelo->chave = camelo.chave;
        strcpy(newCamelo->nome, camelo.nome);
        newCamelo->idade = camelo.idade;
        newCamelo->proximo = NULL;

        Ordenar(inicio, newCamelo);
    }
    if (result != EOF)
    {
        printf("Erro ao ler dados do arquivo\n");
        exit(1);
    }
    fclose(file_text);
}


/* Salvar dados em um arquivo binário */
void Binario(Camelo *inicio, const char *nomeArquivo)
{
    FILE *binario = fopen(nomeArquivo, "wb");

    if (binario == NULL)
    {
        printf("Erro ao abrir arquivo binário"); /* Erro caso não exista o arquivo */
        exit(1);
    }
    Camelo *lista = inicio;
    while (lista != NULL)
    {
        fwrite(lista, sizeof(Camelo), 1, binario);
        lista = lista->proximo;
    }
    fclose(binario);
}


/* Iniciação da geração do Arquivo bin com os dados do arquivo txt*/
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s arquivo_texto arquivo_binario\n", argv[0]);
        exit(1);
    }

    Camelo *inicio = NULL; /* Lista encadeada vazia */

    Lertxt(&inicio, argv[1]);
    Binario(inicio, argv[2]);

    /* Libere a memória alocada para os camelos */
    Camelo *lista = inicio;
    while (lista != NULL)
    {
        Camelo *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    printf("Todos os arquivos foram salvos com sucesso!\n");

    return 0;
}