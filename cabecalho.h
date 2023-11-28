#ifndef CAMELO_H
#define CAMELO_H
#include <stddef.h>

/* Definição dos camelos */
typedef struct Camelo
{
    int chave;
    char nome[50];
    int idade;
    struct Camelo *proximo;
} Camelo;

/* Funções declaradas em lista.c */
Camelo* LerBinario(const char* nomeArquivo);
void InserirCamelo(Camelo **inicio);
void RemoverCamelo(Camelo **inicio);
void ExibirCamelos(Camelo *lista);
void SalvarEdicoes(Camelo **inicio, const char *ArquivoSaida);

#endif
