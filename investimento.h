#include <stdio.h>
#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H


enum tipo_it
{
    CDB, CRI, CRA, LCA, LCI, Acao
};

struct data
{
    int dia;
    int mes;
    int ano;
};

struct investimento
{
    char codigo_it[11];
    char codigo_id[11];
    int tipo_it;
    float valor_it;
    char descricao_it[255];
    int prazo; // periodo q vai render
    float rentabilidade; // data atual
    struct data dataaplicacao;
    float valorizacao;
};

void inicializar_vetores_it();
int inserir_novo_it();
int alterar_it();
int excluir_it();
int listar_it_codigo_it();
int listar_it_codigo_id();
int listar_it_ordem();

#endif