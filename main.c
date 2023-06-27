#include <stdio.h>
#include "investidor.h"
#include "investimento.h"


int main()
{

    const int tam = 50;
    struct investidor *investidores[tam];
    struct  investimento *investimentos[tam];


    inicializar_vetores_id(investidores, tam);
    inicializar_vetores_it(investimentos, tam);



    int opcao = -1;
    do
    {
        int ctrl = 878;
        printf("Escolha o arquivo que deseja acessar: \n\n\n");
        printf("1- Investidor(es)\n");
        printf("2- Investimento(s)\n");
        printf("3- Sair\n\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
            int opcao1;
            case 1:
                printf("\nO que deseja fazer com 'investidor'?\n\n\n");
                printf("1- Inserir um novo investidor\n");
                printf("2- Alterar um investidor existente\n");
                printf("3- Excluir um investidor\n");
                printf("4- Listar dados de um investidor com base no seu código\n");
                printf("5- Listar investidores que tenham um tipo de investimento em comum\n");
                printf("6- Listar todos os investidores em ordem crescente de patrimônio\n");
                printf("7- Voltar\n\n");
                scanf("%d", &opcao1);
                switch (opcao1)
                {
                    case 1:
                        ctrl = inserir_novo_id(investidores, investimentos, tam);
                        if(ctrl == -11)
                            printf("\nErro! (Falta de memoria)\n\n");
                        if(ctrl == -22)
                            printf("\nErro! (O codigo de investidor ja existe!)\n\n");
                        if(ctrl == -33)
                            printf("\nErro! (O CPF inserido já está cadastrado!)\n\n");
                        if(ctrl == -44)
                            printf("\nErro! (O campo foi inserido incorretamente!)\n\n");
                        if(ctrl == -55)
                            printf("\nErro! (Data inválida!)\n\n");
                        if(ctrl == 11)
                            printf("\nInvestidor inserido com sucesso!\n\n");
                        break;
                    case 2:
                        ctrl = alterar_id(investidores, tam);
                        if(ctrl == -22)
                            printf("\nErro! (O codigo de investidor ja existe!)\n\n");
                        if(ctrl == -33)
                            printf("\nErro! (O CPF inserido já está cadastrado!)\n\n");
                        if(ctrl == -44)
                            printf("\nErro! (O campo foi inserido incorretamente!)\n\n");
                        if(ctrl == -55)
                            printf("\nErro! (Data inválida!)\n\n");
                        if(ctrl == -66)
                            printf("\nErro! (Código não encontrado!)\n\n");
                        if(ctrl == 22)
                            printf("\nInvestidor alterado com sucesso!\n\n");
                        break;
                    case 3:
                        ctrl = excluir_id(investidores, tam);
                        if(ctrl == -66)
                            printf("\nErro! (Código não encontrado!)\n\n");
                        if(ctrl == 33)
                            printf("\nInvestidor excluído com sucesso!\n\n");
                        break;
                    case 4:
                        ctrl = listar_id_codigo(investidores, tam);
                        if(ctrl == -66)
                            printf("\nErro! (Código não encontrado!)\n\n");
                        if(ctrl == 44)
                            printf("\nInvestidor listado com sucesso!\n\n");
                        break;
                    case 5:
                        listar_id_tipo(investidores, investimentos, tam);
                        if(ctrl == -77)
                            printf("\nNão foram encontrados investidores com esse tipo de investimento!\n\n");
                        if(ctrl == 44)
                            printf("\nInvestidor listado com sucesso!\n\n");
                        break;
                    case 6:
                        ctrl = listar_id(investidores, tam);
                        if(ctrl == -77)
                            printf("\nErro! (Não há investidores!)\n\n");
                        if(ctrl == -44)
                            printf("\nErro! (Tipo de investimento não encontrado!\n\n");
                        if(ctrl == 44)
                            printf("\nInvestidores listados com sucesso!\n\n");
                        break;
                    case 7:
                        //listar_id_patrimonio();
                        break;
                    case 8:
                        break;
                    default: printf("Opção invalida!\n\n\n\n");
                }
                if(opcao != 2)
                    break;
            case 2:
                if(ctrl != 878)
                    break;
                printf("\nO que deseja fazer com 'investimentos'?\n\n\n");
                printf("1- Inserir um novo investimento\n");
                printf("2- Alterar um investimento existente\n");
                printf("3- Excluir um investimento\n");
                printf("4- Listar dados de um investimento com base no codigo do investimento\n");
                printf("5- Listar todos os investimentos de um investidor com base no codigo do investidor\n");
                printf("6- Listar todos os investimentos em ordem alfabetica pelo tipo de investimento\n");
                printf("7- Voltar\n\n");
                scanf("%d", &opcao1);
                switch (opcao1)
                {
                    case 1:
                        ctrl = inserir_novo_it(investimentos, tam);
                        if (ctrl == -1)
                            printf("\nErro! (Falta de memoria)\n\n");
                        if (ctrl == -2)
                            printf("\nErro! (O codigo de investimento ja existe)\n\n");
                        if (ctrl == -3)
                            printf("\nErro! (Descricao invalida)\n\n");
                        if (ctrl == 0)
                            printf("\nInvestimento inserido com sucesso!\n\n");
                        ctrl = 878;
                        break;
                    case 2:
                        ctrl = alterar_it(investimentos, tam);
                        if (ctrl == -1)
                            printf("\nErro! (O novo codigo de investimento ja existe)\n\n");
                        if (ctrl == -2)
                            printf("\nErro! (Nova descricao invalida)\n\n");
                        if (ctrl == -3)
                            printf("\nErro! (Codigo de investimento informado nao encontrado)\n\n");
                        if (ctrl == 0)
                            printf("\nInvestimento alterado com sucesso!\n\n");
                        ctrl = 878;
                        break;
                    case 3:
                        ctrl = excluir_it(investimentos, tam);
                        if (ctrl == 0)
                            printf("\nInvestimento excluido com sucesso!\n\n");
                        if (ctrl == -1)
                            printf("\nErro! (Codigo do investimento nao encontrado)\n\n");
                        ctrl = 878;
                        break;
                    case 4:
                        ctrl = listar_it_codigo_it(investimentos, tam);
                        if (ctrl == -1)
                            printf("\nErro! (Codigo do investimento nao encontrado)\n\n");
                        ctrl = 878;
                        break;
                    case 5:
                        ctrl = listar_it_codigo_id(investimentos, tam);
                        if (ctrl == -1)
                            printf("\nErro! (Codigo do investidor nao encontrado)\n\n");
                        break;
                    case 6:
                        ctrl = listar_it_ordem(investimentos, tam);
                        if (ctrl == -1)
                            printf("\nErro! (Nenhum investimento inserido)\n\n");
                        break;
                    case 7:
                        break;
                    default:
                        printf("Opcao invalida!\n\n\n\n");
                }
            case 3:
                if(opcao == 3)
                {
                    printf("\nEncerrando o programa\n\n\n");
                    liberar_memoria_it(investidores, tam);
                }
                break;

            default: printf("Opcao invalida!\n\n\n\n");
        }
    } while (opcao != 3);


    return 0;
}