#include "investimento.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int ler_int(char *str)
{
    fflush(stdin);
    gets(str);
    return atoi(str);
}

char ler_chr(char *str)
{
    fflush(stdin);
    gets(str);
    return *str;
}

int ler_nr(int nr)
{
    fflush(stdin);
    scanf("%d", &nr);
    return nr;
}

float ler_float(float nr)
{
    fflush(stdin);
    scanf("%f", &nr);
    return nr;
}

void ler_data(int *d, int *m, int *a)
{
    fflush(stdin);
    scanf("%d/%d/%d", d, m, a);
}

time_t convertersegundos(int dia, int mes, int ano)
{
    struct tm data = {0};

    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;

    return mktime(&data);
}
/*
void salvar_arq(struct investimento *investimentos[], int index)
{
    FILE *invs = fopen("investimentos.bin", "rb+");
    if (invs == NULL)
        invs = fopen("investimentos.bin", "wb+");
    fseek(invs, index * sizeof(struct investimento), SEEK_SET);
    fwrite(investimentos[index], sizeof(struct investimento), 1, invs);
    fclose(invs);
}

int ler_arq(struct investimento* aux, int i)
{
    FILE* invs = fopen("investimentos.bin", "rb+");
    if (invs == NULL || feof(invs))
        return 0;
    fseek(invs, i * sizeof(struct investimento), SEEK_SET);
    while(!feof(invs))
        fread(aux, sizeof(struct investimento), 1, invs);
    fclose(invs);
    return 1;
}
*/
void inicializar_vetores_it(struct investimento *investimentos[], int tam)
{
    for(int i = 0; i < tam; i++)
        investimentos[i] = NULL;
}

void liberar_memoria_it(struct investimento *investimentos[], int tam)
{
    for (int i = 0; i < tam; ++i)
    {
        if(investimentos[i] != NULL)
            free(investimentos[i]);
    }
}

int inserir_novo_it(struct investimento *investimentos[], int tam)
{
    int index = -1;
    /*struct investimento* p = NULL;
    int leitura = ler_arq(p, 0);
    ler_arq(p, 0);
    if(leitura == 0)
    {*/
        for (int i = 0; i < tam; i++)
        {
            if (investimentos[i] == NULL)
            {
                index = i;
                break;
            }
        }
    /*} else
    {
        p = malloc(sizeof(struct investimento));
        if (p == NULL)
            return -1; // ERRO FALTA DE MEMORIA
        for (int i = 0; i < tam; ++i)
        {
            leitura = ler_arq(p, i);
            if(investimentos[i] == NULL && leitura == 1)
            {
                investimentos[i] = malloc(sizeof(struct investimento));
                investimentos[i] = p;
                index = i;
            }
        }
    }*/

    if (index == -1)
        return -1; // ERRO FALTA DE MEMORIA

    struct investimento *novo_it = malloc(sizeof(struct investimento));

    puts("\nDigite o codigo do investimento:");
    ler_int(novo_it->codigo_it);

    for (int i = 0; i < tam; i++)
    {
        if (investimentos[i] != NULL && (strcmp(investimentos[i]->codigo_it, novo_it->codigo_it) == 0))
        {
            free(investimentos[index]);
            return -2; // ERRO CODIGO DE INVESTIMENTO JA INSERIDO
        }
    }

    puts("\nDigite o codigo do investidor:");
    ler_int(novo_it->codigo_id);

    puts("\nDigite o tipo do investimento:\n\n0-CBD\t1-CRI\t2-CRA\t3-LCA\t4-LCI\t5-Acao\n");
    int var;
    do
    {
        var = ler_nr(var);
        novo_it->tipo_it = var ;
    } while (novo_it->tipo_it < 0 || novo_it->tipo_it > 5);

    puts("\nDigite o valor do investimento (em RS):");
    float num;
    novo_it->valor_it = ler_float(num); // como trocar , por .?


    for(int i = 0; i < 255; i++)
    {
        novo_it->descricao_it[i] = '\0';
    }

    puts("\nAdicione uma descricao ao investimento:");
    ler_chr(novo_it->descricao_it);
    int countc = 0;
    for (int i = 0; i < 255; i++)
    {
        if (novo_it->descricao_it[i] != '\0' && novo_it->descricao_it[i] != ' ')
        {
            countc++;
            break;
        }
    }
    if (countc == 0)
        return -3; // ERRO DESCRICAO INVALIDA

    puts("\nInforme o prazo do investimento em dias corridos:");
    int prazo;
    prazo = ler_nr(prazo);
    novo_it->prazo = prazo;

    puts("\nInforme, se desejar, a data de aplicacao do investimento na forma DD/MM/AAAA");
    int dia, mes, ano;
    ler_data(&dia, &mes, &ano);
    int data_valida = 1; //ve se a data eh valida
    if (mes < 1 || mes > 12)
    {
        data_valida = 0;
    } else
    {
        int dias_no_mes;
        switch (mes)
        {
            case 2:
                if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                {
                    dias_no_mes = 29;
                } else
                {
                    dias_no_mes = 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dias_no_mes = 30;
                break;
            default:
                dias_no_mes = 31;
                break;
        }
        if (dia < 1 || dia > dias_no_mes)
            data_valida = 0;

    }
    if (data_valida)
    {
        novo_it->dataaplicacao.dia = dia;
        novo_it->dataaplicacao.mes = mes;
        novo_it->dataaplicacao.ano = ano;
    } else
    {
        time_t tempo_hj;
        struct tm *tempo;
        time(&tempo_hj);
        tempo = localtime(&tempo_hj);
        novo_it->dataaplicacao.dia = tempo->tm_mday;
        novo_it->dataaplicacao.mes = tempo->tm_mon + 1; // tm_mon inicia em 0, adicionamos 1 para obter o mes correto
        novo_it->dataaplicacao.ano = tempo->tm_year + 1900; // tm_year contem o numero de anos desde 1900
    }

    double rentabd = ((pow(1+ 0.1375, 1.0/365.0)) - 1)*100; // calcula a rentabilidade diaria
    double prazoinv = (novo_it->prazo)*24*60*60;
    time_t hoje = time(NULL);
    time_t dataapl = convertersegundos(novo_it->dataaplicacao.dia, novo_it->dataaplicacao.mes, novo_it->dataaplicacao.ano);
    if ((dataapl + prazoinv) < hoje)
    {
        novo_it->rentabilidade = pow(1 + rentabd / 100, novo_it->prazo);
        novo_it->valorizacao = novo_it->valor_it * novo_it->rentabilidade;
    }

    if (dataapl + prazoinv > hoje)
    {
        prazoinv = hoje - dataapl;
        double aux = (prazoinv) / (60 * 60 * 24);
        novo_it->rentabilidade = pow(1 + rentabd / 100, aux);
        novo_it->valorizacao = novo_it->valor_it * novo_it->rentabilidade;
    }

    investimentos[index] = novo_it;

    //salvar_arq(&investimentos[index], index);

    return 0; // INSERIR SUCESSO
}

int alterar_it(struct investimento *investimentos[], int tam)
{
    puts("\nDigite o codigo do investimento a ser alterado:");
    char cod[11];
    ler_int(cod);

    for(int i = 0; i < tam; i++)
    {
        if (investimentos[i] != NULL && (strcmp(cod, investimentos[i]->codigo_it) == 0))
        {
            puts("\nDigite o novo codigo do investimento:");
            ler_int(investimentos[i]->codigo_it);

            for (int j = 0; j < tam; j++)
            {
                if (investimentos[j] != NULL && (strcmp(investimentos[j]->codigo_it, investimentos[i]->codigo_it) == 0) && i != j)
                {
                    return -1; // ERRO CODIGO DE INVESTIMENTO JA INSERIDO
                }
            }

            puts("\nDigite o novo codigo do investidor:");
            ler_int(investimentos[i]->codigo_id);

            puts("\nDigite o novo tipo do investimento:\n\n0-CBD\t1-CRI\t2-CRA\t3-LCA\t4-LCI\t5-Acao\n");
            int var;
            do
            {
                var = ler_nr(var);
                investimentos[i]->tipo_it = var;
            } while (investimentos[i]->tipo_it < 0 || investimentos[i]->tipo_it > 5);

            puts("\nDigite o novo valor do investimento (em RS):");
            float num;
            investimentos[i]->valor_it = ler_float(num); // como trocar , por .?


            for (int j = 0; j < 255; j++)
            {
                investimentos[i]->descricao_it[i] = '\0';
            }

            puts("\nAdicione uma nova descricao ao investimento:");
            ler_chr(investimentos[i]->descricao_it);
            int countc = 0;
            for (int j = 0; j < 255; j++)
            {
                if (investimentos[i]->descricao_it[j] != '\0' && investimentos[i]->descricao_it[j] != ' ')
                {
                    countc++;
                    break;
                }
            }
            if (countc == 0)
                return -2; // ERRO DESCRICAO INVALIDA

            puts("\nInforme o prazo do investimento em dias corridos:");
            int prazo;
            prazo = ler_nr(prazo);
            investimentos[i]->prazo = prazo;

            puts("\nInforme, se desejar, a nova data de aplicacao do investimento na forma DD/MM/AAAA");
            int dia, mes, ano;
            ler_data(&dia, &mes, &ano);
            int data_valida = 1;
            if (mes < 1 || mes > 12)
            {
                data_valida = 0;
            } else
            {
                int dias_no_mes;
                switch (mes)
                {
                    case 2:
                        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                        {
                            dias_no_mes = 29;
                        } else
                        {
                            dias_no_mes = 28;
                        }
                        break;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        dias_no_mes = 30;
                        break;
                    default:
                        dias_no_mes = 31;
                        break;
                }
                if (dia < 1 || dia > dias_no_mes)
                    data_valida = 0;

            }
            if (data_valida)
            {
                investimentos[i]->dataaplicacao.dia = dia;
                investimentos[i]->dataaplicacao.mes = mes;
                investimentos[i]->dataaplicacao.ano = ano;
            } else
            {
                time_t tempo_hj;
                struct tm *tempo;
                time(&tempo_hj);
                tempo = localtime(&tempo_hj);
                investimentos[i]->dataaplicacao.dia = tempo->tm_mday;
                investimentos[i]->dataaplicacao.mes = tempo->tm_mon + 1;
                investimentos[i]->dataaplicacao.ano = tempo->tm_year + 1900;
            }

            double rentabd = ((pow(1+ 0.1375, 1.0/365.0)) - 1)*100; // calcula a rentabilidade diaria
            double prazoinv = (investimentos[i]->prazo)*24*60*60;
            time_t hoje = time(NULL);
            time_t dataapl = convertersegundos(investimentos[i]->dataaplicacao.dia, investimentos[i]->dataaplicacao.mes, investimentos[i]->dataaplicacao.ano);
            if ((dataapl + prazoinv) < hoje)
            {
                investimentos[i]->rentabilidade = pow(1 + rentabd / 100, investimentos[i]->prazo);
                investimentos[i]->valorizacao = investimentos[i]->valor_it * investimentos[i]->rentabilidade;
            }

            if (dataapl + prazoinv > hoje)
            {
                prazoinv = hoje - dataapl;
                double aux = (prazoinv) / (60 * 60 * 24);
                investimentos[i]->rentabilidade = pow(1 + rentabd / 100, aux);
                investimentos[i]->valorizacao = investimentos[i]->valor_it * investimentos[i]->rentabilidade;
            }

            return 0;
        }
    }

    return - 3; // ERRO CODIGO INSERIDO PRA ALTERACAO NAO ENCONTRADO
}


int excluir_it(struct investimento *investimentos[], int tam) // PRECISA DAR FREE?
{
    puts("\nDigite o codigo do investimento a ser excluido:");
    char cod[11];
    ler_int(cod);
    for(int i = 0; i < tam; i++)
    {
        if (investimentos[i] != NULL && (strcmp(cod, investimentos[i]->codigo_it) == 0))
        {
            investimentos[i] = NULL;
            return 0; // EXCLUIR SUCESSO
        }
    }
    return -1; // EXCLUIR ERRO CODIGO NAO ENCONTRADO
}

int listar_it_codigo_it(struct investimento *investimentos[], int tam)
{
    puts("\nDigite o codigo do investimento a ser listado:");
    char cod[11];
    ler_int(cod);

    for(int i = 0; i < tam; ++i)
    {
        if(investimentos[i] != NULL && (strcmp(cod, investimentos[i]->codigo_it) == 0))
        {
            printf("\nCodigo do investimento: %s", investimentos[i]->codigo_it);
            printf("\nCodigo do investidor: %s", investimentos[i]->codigo_id);
            int op = investimentos[i]->tipo_it;
            switch (op)
            {
                case 0:
                    printf("\nTipo de investimento: CBD");
                    break;
                case 1:
                    printf("\nTipo de investimento: CRI");
                    break;
                case 2:
                    printf("\nTipo de investimento: CRA");
                    break;
                case 3:
                    printf("\nTipo de investimento: LCA");
                    break;
                case 4:
                    printf("\nTipo de investimento: LCI");
                    break;
                case 5:
                    printf("\nTipo de investimento: Acao");
                    break;
            }
            printf("\nValor do investimento: R$%.3f", investimentos[i]->valor_it);
            printf("\nDescricao do investimento: %s", investimentos[i]->descricao_it);
            printf("\nPrazo do investimento (em dias corridos): %d", investimentos[i]->prazo);
            printf("\nData de aplicacao do investimento : %d/%d/%d\n", investimentos[i]->dataaplicacao.dia, investimentos[i]->dataaplicacao.mes, investimentos[i]->dataaplicacao.ano);
            printf("\nRentabilidade do investimento: %.3f\n", investimentos[i]->rentabilidade);
            printf("\nValorizacao: %f\n\n\n", investimentos[i]->valorizacao);
            return 0; //LISTAR SUCESSO
        }
    }
    return -1; //LISTAR CODIGO DO INVESTIMENTO NAO ENCONTRADO
}

int listar_it_codigo_id(struct investimento *investimentos[], int tam)
{
    puts("\nDigite o codigo do investidor a ser listado:");
    char cod[11];
    ler_int(cod);
    int count = 0;

    for(int i = 0; i < tam; ++i)
    {
        if(investimentos[i] != NULL && (strcmp(cod, investimentos[i]->codigo_id) == 0))
        {
            printf("\nCodigo do investimento: %s", investimentos[i]->codigo_it);
            printf("\nCodigo do investidor: %s", investimentos[i]->codigo_id);
            int op = investimentos[i]->tipo_it;
            switch (op)
            {
                case 0:
                    printf("\nTipo de investimento: CBD");
                    break;
                case 1:
                    printf("\nTipo de investimento: CRI");
                    break;
                case 2:
                    printf("\nTipo de investimento: CRA");
                    break;
                case 3:
                    printf("\nTipo de investimento: LCA");
                    break;
                case 4:
                    printf("\nTipo de investimento: LCI");
                    break;
                case 5:
                    printf("\nTipo de investimento: Acao");
                    break;
            }
            printf("\nValor do investimento: R$%.3f", investimentos[i]->valor_it);
            printf("\nDescricao do investimento: %s", investimentos[i]->descricao_it);
            printf("\nPrazo do investimento (em dias corridos): %d", investimentos[i]->prazo);
            printf("\nData de aplicacao do investimento : %d/%d/%d", investimentos[i]->dataaplicacao.dia, investimentos[i]->dataaplicacao.mes, investimentos[i]->dataaplicacao.ano);
            printf("\nRentabilidade do investimento: %.3f", investimentos[i]->rentabilidade);
            printf("\nValorizacao: %f\n\n\n", investimentos[i]->valorizacao);
            count++;
        }
    }
    if(count > 0)
    return 0; //LISTAR SUCESSO
    if(count == 0)
    return -1; //CODIGO DO INVESTIDOR NAO ENCONTRADO
}

int listar_it_ordem(struct investimento *investimentos[], int tam)
{
    int tipo = 0;
    int count = 0;
    while(tipo < 6)
    {
        for(int i = 0; i < tam; ++i)
        {
            if(investimentos[i] != NULL)
            {
                if(investimentos[i]->tipo_it == tipo)
                {
                    if(tipo == 0)
                        printf("\nINVESTIMENTO: CBD");
                    if(tipo == 1)
                        printf("\nINVESTIMENTO: CRI");
                    if(tipo == 2)
                        printf("\nINVESTIMENTO: CRA");
                    if(tipo == 3)
                        printf("\nINVESTIMENTO: LCA");
                    if(tipo == 4)
                        printf("\nINVESTIMENTO: LCI");
                    if(tipo == 5)
                        printf("\nINVESTIMENTO: Acao");

                    printf("\nCodigo do investimento: %s", investimentos[i]->codigo_it);
                    printf("\nCodigo do investidor: %s", investimentos[i]->codigo_id);
                    printf("\nValor do investimento: R$%.3f", investimentos[i]->valor_it);
                    printf("\nDescricao do investimento: %s", investimentos[i]->descricao_it);
                    printf("\nPrazo do investimento (em dias corridos): %d", investimentos[i]->prazo);
                    printf("\nData de aplicacao do investimento : %d/%d/%d", investimentos[i]->dataaplicacao.dia, investimentos[i]->dataaplicacao.mes, investimentos[i]->dataaplicacao.ano);
                    printf("\nRentabilidade do investimento: %.3f", investimentos[i]->rentabilidade);
                    printf("\nValorizacao: %f\n\n\n", investimentos[i]->valorizacao);
                    count++;
                }
            }
        }
        tipo++;
    }
    if(count != 0)
    return 0; // LISTAR SUCESSO
    if(count == 0)
    return -1; // LISTAR NAO TEM INVESTIMENTO
}