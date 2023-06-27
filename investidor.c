#include "investidor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*problemas: ao que parece, meu verificador de codigo esta com algum problema que não identifiquei, mas sei que ele acontece apos
 o primeiro erro de cod ou cpf ja inserido*/

const int INSERIR_SUCESSO_ID = 11;
const int ALTERAR_SUCESSO_ID = 22;
const int EXCLUIR_SUCESSO_ID = 33;
const int LISTAR_SUCESSO_ID = 44;
const int ERRO_FALTA_MEMORIA = -11;
const int ERRO_COD_JA_INSERIDO = -22;
const int ERRO_CPF_JA_INSERIDO = -33;
const int ERRO_INSERIDO_INCORRETAMENTE = -44;
const int ERRO_DATA_INVALIDA = -55;
const int ERRO_COD_NAO_ENCONTRADO = -66;
const int ERRO_SEM_INVESTIDORES = -77;

//proximo passo pra domingo: terminar a alterar, continuar na ideia de salvar as strings antigas e colocar nas novas caso dê erro

void ler_str_id(char *str, int tam)
{
    fflush(stdin);
    fgets(str, tam, stdin);
}

int ler_int_id(char *str, int tam)
{
    fflush(stdin);
    fgets(str, tam, stdin);
    return atoi(str);
}

float ler_float_id(char *str, int tam)
{
    fflush(stdin);
    fgets(str,tam, stdin);
    return atof(str);
}

void ler_data_id(char *data, int tam)
{
    fflush(stdin);
    fgets(data, tam, stdin);

}

int verificar_data(char *data)
{

    int dia = 0, mes = 0, ano = 0, flag = 0;
    if (strlen(data) <= 11) {

        ano = (((data[6] - '0') * 10 + (data[7] - '0')) * 10 + (data[8] - '0')) * 10 + (data[9] - '0');
        if (ano > 1900) {
            flag++;
            mes = (data[3] - '0') * 10 + (data[4] - '0');
        }

        if (mes > 0 && mes < 13) {
            flag++;
            dia = (data[0] - '0') * 10 + (data[1] - '0');
        }

        if ((dia > 0 && dia < 32) && (dia == 31 && mes == 1 || 3 || 5 || 7 || 8 || 10 || 12)) {
            if (mes == 2 && dia > 28)
                return ERRO_DATA_INVALIDA;

            flag++;
        }

    }
    return (flag == 3 ? INSERIR_SUCESSO_ID : ERRO_DATA_INVALIDA);
}


void inicializar_vetores_id(struct investidor *investidores[], int tam) //nÃ£o seria melhor se o vetor fosse de struct, jÃ¡ que armazenaremos vetores de structs?
{
    for(int i = 0; i < tam; i++){
        investidores[i] = NULL;
    }
}




int verificar_cpf(struct investidor *inv_cpf, struct investidor *invs_cpf[], int tam, int index)
{
    for(int i = 0; i<tam; i++)
    {
        if(invs_cpf[i] != NULL && (strcmp(inv_cpf->cpf, invs_cpf[i]->cpf) == 0) && (i != index))
        {
            return ERRO_CPF_JA_INSERIDO;
        }
    }

    return INSERIR_SUCESSO_ID;
}



int verificar_codigo_id(struct investidor *inv_cod, struct investidor *invs_cod[], int tam, int index)
{
    for (int i = 0; i < tam; i++)
    {
        if (invs_cod[i] != NULL && (strcmp(inv_cod->codigo_id, invs_cod[i]->codigo_id) == 0) && (i != index)) {
            return ERRO_COD_JA_INSERIDO;
        }
    }

    return INSERIR_SUCESSO_ID; //quero iterar cada campo de todas as structs pra comparar, nao sei como
}




int verificar_se_ta_vazio(char campo_do_investidor[])
{
    int index = -1;
    int count = 0;
    int i = 0;
    do{
        if (campo_do_investidor[0] == '\n')
            break;

        if(isspace(campo_do_investidor[i]) != 0 && (i != '\n'))
        {                                      //verifica se o usuario deu enter na primeira posiÃ§Ã£o ou se digitou espaÃ§o e enter
            count++;                           //o problema Ã© que nÃ£o funciona quando o usuario aperta espaÃ§o ate estourar o espaÃ§o das strings
        }                                      //nesse caso ele deixa como valido

        i++;
        index = i;
    }
    while(campo_do_investidor[i] != '\n');


    if(index == -1) //caso em que o usuario aperta enter no inicio
    {

        return ERRO_INSERIDO_INCORRETAMENTE;
    }

    else if(count!=index){
        return INSERIR_SUCESSO_ID;
    }

    else{ //caso em que count==index principalmente, significa que o usuario apertou espaço x vezes e enter
        return ERRO_INSERIDO_INCORRETAMENTE;

    }
}

float calcular_patrimonio(char *investidor_codigo, struct investimento *investimentos[], int tam)
{
    int index[tam];
    int flag = 0;
    float patrimonio = 0.0f;
    for(int i = 0; i < tam; i++)
    {
        if(investimentos[i] != NULL && strcmp(investidor_codigo, investimentos[i]->codigo_id) == 0)
        {
            index[i] = i;
            flag++;
        }
    }
    if(flag <= 0)
        return patrimonio;

    float soma = 0.0f;
    int i = 0;
    while(i<flag)
    {
        soma = soma + (investimentos[index[i]]->valor_it * investimentos[index[i]]->valorizacao);
        i++;
    }
    patrimonio = soma;

    return patrimonio;
}





int inserir_novo_id(struct investidor *investidores[], struct investimento *investimentos[], int tam) {

    int index = -1; //
    for (int i = 0; i < tam; i++) {
        if (investidores[i] == NULL) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return ERRO_FALTA_MEMORIA;
    }

    //lembrar: posso fazer o malloc receber direto o novo_id, e apenas no final fazer o investidores[index] = novo_id
    struct investidor *novo_id = malloc(sizeof(struct investidor));
    investidores[index] = novo_id;

    printf("\nDigite o nome do novo investidor.\n\n");
    ler_str_id(novo_id->nome_id, 255);
    int r = verificar_se_ta_vazio(novo_id->nome_id);//lendo nome
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_INSERIDO_INCORRETAMENTE;
    }


    printf("\nInsira um código para o novo investidor.\n\n");
    ler_str_id(novo_id->codigo_id, 11);
    r = verificar_se_ta_vazio(novo_id->codigo_id); //lendo codigo
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_INSERIDO_INCORRETAMENTE;
    }

    r = verificar_codigo_id(novo_id, investidores, tam, index);
    if (r == ERRO_COD_JA_INSERIDO) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_COD_JA_INSERIDO;
    }


    printf("\nDigite o CPF do novo investidor.\n\n");
    ler_str_id(novo_id->cpf, 14); //lendo cpf
    r = verificar_se_ta_vazio(novo_id->cpf);
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_INSERIDO_INCORRETAMENTE;
    }
    r = verificar_cpf(novo_id, investidores, tam, index);
    if (r == ERRO_CPF_JA_INSERIDO) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_CPF_JA_INSERIDO;
    }


    printf("\nInforme, se desejar, o endereço do investidor.\n\n");
    ler_str_id(novo_id->endereco, 255); //nao precisa ver se tá vazio ou em branco

    printf("\nInforme a data de nascimento do investidor na forma DD/MM/AAAA.\n\n");
    ler_data_id(novo_id->data_nascimento.data, 11);
    r = verificar_data(novo_id->data_nascimento.data);
    if (r == ERRO_DATA_INVALIDA) {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_DATA_INVALIDA;
    }

    printf("\nInforme o salário do investidor em R$.\n\n");
    fflush(stdin);
    char salario[10];
    novo_id->salario = ler_float_id(salario, 10);
    r = verificar_se_ta_vazio(salario);
    if (r == ERRO_INSERIDO_INCORRETAMENTE)
    {
        free(novo_id);
        investidores[index] = NULL;
        return ERRO_INSERIDO_INCORRETAMENTE;
    }


    /*novo_id->patrimonio = calcular_patrimonio(novo_id->codigo_id, investimentos, tam);
    printf("\nPatrimônio do investidor: %.2f", novo_id->patrimonio);

    printf("\n\nAperte a tecla ENTER para voltar ao menu.\n\n");
    char tecla[2];
    fflush(stdin);
    fgets(tecla, 2, stdin);*/
    return INSERIR_SUCESSO_ID;
}

//FIM DA INSERIR






int alterar_id(struct investidor *investidores[], int tam)
{
    char codigo[11];
    printf("\nInsira o código do investidor que deseja alterar.\n\n");
    ler_str_id(codigo, 11);
    int index = -1;
    for(int i = 0; i<tam; i++)
    {
        if(investidores[i] != NULL && strcmp(codigo, investidores[i]->codigo_id) == 0)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
        return ERRO_COD_NAO_ENCONTRADO;

    struct investidor *alterar = investidores[index];
    printf("\nDigite o novo nome do investidor.\n\n");
    char salvar[255];
    strcpy(salvar, alterar->nome_id);
    ler_str_id(alterar->nome_id, 255);
    int r = verificar_se_ta_vazio(alterar->nome_id);//lendo nome
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        strcpy(alterar->nome_id, salvar);
        return ERRO_INSERIDO_INCORRETAMENTE;
    }


    printf("\nInsira o novo código para o investidor.\n\n");
    char salvar2[11];
    strcpy(salvar2, alterar->codigo_id);
    ler_str_id(alterar->codigo_id, 11);
    r = verificar_se_ta_vazio(alterar->codigo_id); //lendo codigo
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        strcpy(alterar->codigo_id, salvar2);
        return ERRO_INSERIDO_INCORRETAMENTE;
    }
    r = verificar_codigo_id(alterar, investidores, tam, index);
    if (r == ERRO_COD_JA_INSERIDO) {
        strcpy(alterar->codigo_id, salvar2);
        return ERRO_COD_JA_INSERIDO;
    }


    printf("\nDigite o CPF do novo investidor.\n\n");
    char salvar3[14];
    strcpy(salvar3, alterar->nome_id);
    ler_str_id(alterar->cpf, 14); //lendo cpf
    r = verificar_se_ta_vazio(alterar->cpf);
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        strcpy(alterar->cpf, salvar3);
        return ERRO_INSERIDO_INCORRETAMENTE;
    }
    r = verificar_cpf(alterar, investidores, tam, index);
    if (r == ERRO_CPF_JA_INSERIDO) {
        strcpy(alterar->cpf, salvar3);
        return ERRO_CPF_JA_INSERIDO;
    }


    printf("\nInforme o novo endereço do investidor.\n\n");
    ler_str_id(alterar->endereco, 255); //nao precisa ver se tá vazio ou em branco


    printf("\nInforme a nova data de nascimento do investidor na forma DD/MM/AAAA.\n\n");
    char salvar4[11];
    strcpy(salvar4, alterar->data_nascimento.data);
    ler_data_id(alterar->data_nascimento.data, 11);
    r = verificar_data(alterar->data_nascimento.data);
    if (r == ERRO_DATA_INVALIDA) {
        strcpy(alterar->data_nascimento.data, salvar4);
        return ERRO_DATA_INVALIDA;
    }

    printf("\nInforme o salário do investidor em R$.\n\n");
    float salvar5 = alterar->salario;
    char salario[10];
    alterar->salario = ler_float_id(salario, 10);
    r = verificar_se_ta_vazio(salario);
    if (r == ERRO_INSERIDO_INCORRETAMENTE) {
        alterar->salario = salvar5;
        return ERRO_INSERIDO_INCORRETAMENTE;
    }
    return ALTERAR_SUCESSO_ID;
}

//FIM DA ALTERAR


int excluir_id(struct investidor *investidores[], int tam)
{
    char codigo[11]; //tudo isso é char, não faz sentido euj ler como inteiro, eu cometi esse erro e não tenho tempo p consertar
    printf("\nInsira o código do investidor que deseja excluir.\n\n");
    ler_str_id(codigo, 11);

    for(int i = 0; i<tam; i++)
    {
        if(investidores[i] != NULL && strcmp(codigo, investidores[i]->codigo_id) == 0)
        {
            free(investidores[i]);
            investidores[i] = NULL;
            return EXCLUIR_SUCESSO_ID;
        }
    }
    return ERRO_COD_NAO_ENCONTRADO;
}

//FIM DA EXCLUIR



int listar_id_codigo(struct investidor *investidores[], int tam)
{
    char codigo[11]; //tudo isso é char, não faz sentido euj ler como inteiro, eu cometi esse erro e não tenho tempo p consertar
    printf("\nInsira o código do investidor cujos dados deseja listar.\n\n");
    ler_str_id(codigo, 11);
    int index = -1;
    for(int i = 0; i<tam; i++)
    {
        if (investidores[i] != NULL && strcmp(codigo, investidores[i]->codigo_id) == 0) {
            index = i;
            break;
        }
    }
    if(index == -1)
        return ERRO_COD_NAO_ENCONTRADO;

    puts("###################DADOS DO INVESTIDOR###################");
    printf("Nome do investidor: %s", investidores[index]->nome_id);
    printf("Código do investidor: %s", investidores[index]->codigo_id);
    printf("CPF do investidor: %s", investidores[index]->cpf);
    printf("Endereço do investidor: %s", investidores[index]->endereco);
    printf("Data de nascimento do investidor: %s\n", investidores[index]->data_nascimento.data);
    printf("Salario do investidor: R$ %.2f\n", investidores[index]->salario);
    //printf("\nPatrimônio do investidor: %s", investidores[index]->patrimonio);
    puts("##########################################################");



    printf("Aperte a tecla ENTER para voltar ao menu.\n\n");
    char tecla[2];
    fflush(stdin);
    fgets(tecla, 2, stdin);

    return LISTAR_SUCESSO_ID;


}


//FIM DA LISTAR_CODIGO_ID


int listar_id_tipo(struct investidor *investidores[], struct investimento *investimentos[], int tam)
{
    int count = 0;
    int num;
    char str[2];

    printf("\nInsira o tipo de investimento\n\n");
    printf("0-CDB   1-CRI   2-CRA   3-CRA   4-LCA   5-LCI   6-Acao\n\n");
    num = ler_int_id(str, 2);

    switch(num)
    {
        case 0:
            for(int i = 0; i < tam; i++)
            {
                if(investimentos[i] != NULL && investimentos[i]->tipo_it == num)
                {

                    for(int j = 0; j<tam; j++)
                    {
                        if(investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0)
                        {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 1:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 4:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 5:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        case 6:
            for(int i = 0; i < tam; i++) {
                if (investimentos[i] != NULL && investimentos[i]->tipo_it == num) {

                    for (int j = 0; j < tam; j++) {
                        if (investidores[j] != NULL && strcmp(investimentos[i]->codigo_id, investidores[j]->codigo_id) == 0) {
                            puts("###################DADOS DO INVESTIDOR###################");
                            printf("Nome do investidor: %s", investidores[j]->nome_id);
                            printf("Código do investidor: %s", investidores[j]->codigo_id);
                            printf("CPF do investidor: %s", investidores[j]->cpf);
                            printf("Endereço do investidor: %s", investidores[j]->endereco);
                            printf("Data de nascimento do investidor: %s\n", investidores[j]->data_nascimento.data);
                            printf("Salario do investidor: R$ %.2f\n", investidores[j]->salario);
                            //printf("\nPatrimônio do investidor: %s", investidores[j]->patrimonio);
                            puts("##########################################################");
                            printf("\n");
                            count++;
                        }
                    }
                }
            }
            break;
        default:
            return ERRO_INSERIDO_INCORRETAMENTE;
            break;

            if(count == 0)
                return ERRO_SEM_INVESTIDORES;

            printf("Aperte a tecla ENTER para voltar ao menu.\n\n");
            char tecla[2];
            fflush(stdin);
            fgets(tecla, 2, stdin);
            return LISTAR_SUCESSO_ID;
    }

}




int listar_id(struct investidor *investidores[], int tam)
{
    int flag = 0;
    for(int i = 0; i<tam; i++)
    {
        if(investidores[i] != NULL)
        {
            puts("###################DADOS DO INVESTIDOR###################");
            printf("Nome do investidor: %s", investidores[i]->nome_id);
            printf("Código do investidor: %s", investidores[i]->codigo_id);
            printf("CPF do investidor: %s", investidores[i]->cpf);
            printf("Endereço do investidor: %s", investidores[i]->endereco);
            printf("Data de nascimento do investidor: %s\n", investidores[i]->data_nascimento.data);
            printf("Salario do investidor: R$ %.2f\n", investidores[i]->salario);
            //printf("\nPatrimônio do investidor: %s", investidores[i]->patrimonio);
            puts("##########################################################");
            printf("\n");
            flag++;
        }
    }
    if(flag == 0)
        return ERRO_SEM_INVESTIDORES;
    else
    {
        printf("Aperte a tecla ENTER para voltar ao menu.\n\n");
        char tecla[2];
        fflush(stdin);
        fgets(tecla, 2, stdin);
        return LISTAR_SUCESSO_ID;
    }
}