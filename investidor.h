#include <stdio.h>
#ifndef INVESTIDOR_H
#define INVESTIDOR_H

#include "investimento.h"

struct data_nascimento{
    char data[11];
};

struct investidor {
    char codigo_id[11];
    char nome_id[255];
    char cpf[14];
    char endereco[255];
    float salario;
    float patrimonio;
    struct data_nascimento data_nascimento;
};

void inicializar_vetores_id();
int inserir_novo_id();
int alterar_id();
int excluir_id();
int listar_id_codigo();
int listar_id_tipo();
int listar_id();
int listar_id_patrimonio();

#endif