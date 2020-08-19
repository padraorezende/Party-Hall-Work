#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int procurarNoArquivo(char *string, char *nomeDoArquivo, int quantidadeDeRegistrosPorBloco, int posicaoItemPesquisa); // Bryann
char* getCodigoByName(char *nome); // Padrão
void cadastrarFornecedor(); // Zé Vitor
void cadastrarFuncionario(); // Vitor
void cadastrarCliente(); //Zé Vitor
void cadastrarFesta(); // Vitor
char* getContratoPorCodigoCliente(char *codigo); // Bryann
char* getFestaPorData(char *data); // Bryann
int relatorioDia(); // Ana
char* diaSemanaFesta(int codigo); // Ana
char* quantidadePessoasFesta(int codigo); // Bryann
void cadastrarContrato(); // padrão
char* pesquisarPorNome(char* nome, char* arquivo, int quantidadeLinhasRegistro, int posicaoLinhaNome, int tipoConsulta); // Bryann
void setLinha(int linha);
int verificaContrato(int codigo);
void alterarContrato();
void listarFestasCliente();
void pesquisarClientes(); // Vitor
void pesquisarFuncionarios();   // Zé Vitor
void pesquisarFornecedores(); //Ana

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do
    {
        system("cls");

        printf("\t\tSalão de Festas\n\n\n");
        printf("\t1- \tCadastrar Cliente\n");
        printf("\t--------------------------------------\n");
        printf("\t2- \tCadastrar Funcionário\n");
        printf("\t--------------------------------------\n");
        printf("\t3- \tCadastrar Fornecedor\n");
        printf("\t--------------------------------------\n");
        printf("\t4- \tCadastrar Festa\n");
        printf("\t--------------------------------------\n");
        printf("\t5- \tCadastrar Contrato\n");
        printf("\t--------------------------------------\n");
        printf("\t6- \tAlterar Contrato\n");
        printf("\t--------------------------------------\n");
        printf("\t7- \tPesquisar Cliente\n");
        printf("\t--------------------------------------\n");
        printf("\t8- \tPesquisar Funcionário\n");
        printf("\t--------------------------------------\n");
        printf("\t9- \tPesquisar Fornecedore\n");
        printf("\t--------------------------------------\n");
        printf("\t10- \tRelatório Cliente\n");
        printf("\t--------------------------------------\n");
        printf("\t11- \tRelatório Dia\n");
        printf("\t--------------------------------------\n");
        printf("\t0- \tSair\n\n\t");

        printf("Opção:\t");

        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            cadastrarFuncionario();
            break;
        case 3:
            cadastrarFornecedor();
            break;
        case 4:
            cadastrarFesta();
            break;
        case 5:
            cadastrarContrato();
            break;
        case 6:
            alterarContrato();
            break;
        case 7:
            pesquisarClientes();
            break;
        case 8:
            pesquisarFuncionarios();
            break;
        case 9:
            pesquisarFornecedores();
            break;
        case 10:
            listarFestasCliente();
            break;
        case 11:
            relatorioDia();
            break;
        case 0:
            break;
        default:
            printf("\n\nValor Inválido Digitado!\n\n");
            system("pause");
            break;
        }
    }
    while (opcao != 0);
}

void setLinha(int linha) {
    int numeroDaLinhaAtual = 1, resto;
    char temp[512];
    FILE *arquivo;
    arquivo = fopen("Festa.txt","r");
    while(!feof(arquivo)) {
        fgets(temp,512,arquivo);
        if(numeroDaLinhaAtual >= linha - 7 && numeroDaLinhaAtual < linha) {
            resto = numeroDaLinhaAtual%8;
            switch (resto) {
            case 1:
                printf("------------Dados da festa------------\n");
                printf("Código Festa: %s\n",temp);
                break;
            case 2:
                printf("Convidados: %s\n",temp);
                break;
            case 3:
                printf("Data Festa: %s\n",temp);
                break;
            case 4:
                printf("Dia Semana: %s\n", temp);
                break;
            case 5:
                printf("Horário Inicio: %s\n",temp);
                break;
            case 6:
                printf("Horário Fim: %s\n",temp);
                break;
            case 7:
                printf("Tema Festa: %s\n",temp);
                break;
            }
        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
}

int verificaContrato(int codigo)
{
    FILE *arquivo;
    arquivo = fopen("Contrato.txt","r");
    int numeroDaLinhaAtual = 1;
    char temp[512];
    while(!feof(arquivo))
    {
        fgets(temp,512,arquivo);
        if(numeroDaLinhaAtual%7 == 1)
        {
            if(atoi(temp) == codigo)
            {
                return numeroDaLinhaAtual;
            }
        }
        numeroDaLinhaAtual++;
    }
    return 0;
}

void cadastrarCliente()
{
    int auxiliar = 1;
    FILE *ponteiroArquivo;

    if( access("Cliente.txt", F_OK ) != -1 )
    {
        ponteiroArquivo = fopen ("Cliente.txt","a");
    }
    else
    {
        ponteiroArquivo = fopen ("Cliente.txt","w");
    }

    char nome[30], endereco[70];
    char codigo[10], telefone[15], nascimento[11];

    while(auxiliar != 0)
    {
        system("cls");
        setbuf(stdin, NULL);
        printf("Digite o código do cliente: ");
        gets(codigo);

        int verificaExistencia = procurarNoArquivo(codigo, "Cliente.txt", 5, 1);

        if (verificaExistencia == 3)
        {
            printf("Digite o nome do cliente: ");
            gets(nome);

            printf("Digite o endereço do cliente: ");
            gets(endereco);

            printf("Digite o telefone do cliente: ");
            gets(telefone);

            printf("Digite a data de nascimento do cliente: ");
            gets(nascimento);

            fprintf(ponteiroArquivo, "%s\n", codigo);
            fprintf(ponteiroArquivo, "%s\n", nome);
            fprintf(ponteiroArquivo, "%s\n", endereco);
            fprintf(ponteiroArquivo, "%s\n", telefone);
            fprintf(ponteiroArquivo, "%s\n", nascimento);
            auxiliar = 0;
        }
        else
        {
            printf("\nCódigo de usuário inválido!\n\n\n");
            system("pause");
            auxiliar = 1;
        }
    }
    fclose (ponteiroArquivo);
}

void alterarContrato()
{
    system("cls");
    int codigoContrato, status, linhaContrato, numeroDaLinhaAtual = 1;
    char escolhaString[20], temp[512];
    FILE *arquivo, *arquivoTemp;

    printf("Digite o código do contrato: ");
    scanf("%d",&codigoContrato);
    linhaContrato = verificaContrato(codigoContrato);
    if (linhaContrato == 0)
    {
        system("cls");
        printf("\n\nCódigo não encontrado!\n");
        system("pause");
        alterarContrato();
        return;
    }
    else
    {
        printf("Escolha o status\n\n [1] - Pago\n [2] - Cancelado\n\n");
        scanf("%d",&status);

        switch (status)
        {
        case 1:
            strcpy(escolhaString,"Pago");
            break;
        case 2:
            strcpy(escolhaString,"Cancelado");
        }
        arquivo = fopen("Contrato.txt","r");
        arquivoTemp = fopen("Temporario.txt","w");

        fgets(temp,100,arquivo);

        while (!feof(arquivo))
        {
            if(numeroDaLinhaAtual == linhaContrato + 5)
            {
                fprintf(arquivoTemp,"%s\n",escolhaString);
            }
            else
            {
                fprintf(arquivoTemp,"%s",temp);
            }
            fgets(temp,100,arquivo);
            numeroDaLinhaAtual++;
        }
        fclose(arquivoTemp);
        fclose(arquivo);

        arquivo = fopen("Contrato.txt","w");
        arquivoTemp = fopen("Temporario.txt","r");
        fgets(temp,512,arquivoTemp);
        while(!feof(arquivoTemp))
        {
            fprintf(arquivo,"%s",temp);
            fgets(temp,512,arquivoTemp);
        }
        fclose(arquivo);
        fclose(arquivoTemp);
    }
}

char* getCodigoByName(char *nome)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    int resultado = 0;
    char temp[512];
    int linhaCodigo = 0;

    if((arquivo = fopen("Cliente.txt", "r")) == NULL)
    {
        return "Erro";
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {
        if (numeroDaLinhaAtual%5 == 2)
        {

            if((strstr(temp, nome)) != NULL)
            {

                if (strlen(nome) == (strlen(temp)-1))
                {

                    linhaCodigo = numeroDaLinhaAtual - 1;
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }

    if((arquivo = fopen("Cliente.txt", "r")) == NULL)
    {
        return "Erro";
    }

    numeroDaLinhaAtual = 1;

    if (linhaCodigo!= 0)
    {
        while(fgets(temp, 512, arquivo) != NULL)
        {

            if (numeroDaLinhaAtual == linhaCodigo)
            {

                char *resultadoFinal = temp;
                if(arquivo)
                {
                    fclose(arquivo);
                }
                return resultadoFinal;
            }
            numeroDaLinhaAtual++;
        }
    }

    if(arquivo)
    {
        fclose(arquivo);
    }
    return "Erro";
}

void listarFestasCliente() {
    char nomeCliente[50], temp[512];
    int  codigoCliente, numeroDaLinhaAtual = 1;
    FILE *arquivo;
    do
    {
        system("cls");
        fflush(stdin);
        printf("Digite o nome do cliente: ");
        gets(nomeCliente);
       if(getCodigoByName(nomeCliente) == "Erro")
       {
           printf("Usuário Inexistente!");
           system("pause");
       }
    }while(getCodigoByName(nomeCliente) == "Erro");

    codigoCliente = atoi(getCodigoByName(nomeCliente));
    system("cls");
    arquivo = fopen("Festa.txt","r");
    while(!feof(arquivo)) {
        fgets(temp,512,arquivo);
        if(numeroDaLinhaAtual%8 == 0) {
            if(atoi(temp) == codigoCliente) {
                setLinha(numeroDaLinhaAtual);
            }
        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
    system("pause");
}

void cadastrarFornecedor()
{
    int auxiliar = 1;
    char caminhoArquivo[] = "Fornecedor.txt";
    FILE* ponteiroArquivo;
    if( access(caminhoArquivo, F_OK ) != -1 )
    {
        ponteiroArquivo = fopen (caminhoArquivo,"a");
    }
    else
    {
        ponteiroArquivo = fopen (caminhoArquivo,"w");
    }
    char nome[40], produto[70], telefone[15], codigo[10];

    while (auxiliar != 0)
    {
        system("cls");
        setbuf(stdin, NULL);
        cout << "Digite o código do fornecedor: " << endl;
        gets(codigo);
        int verificaExistencia = procurarNoArquivo(codigo, caminhoArquivo, 4, 1);

        if (verificaExistencia == 3)
        {
            setbuf(stdin, NULL);
            cout << "Digite o nome do fornecedor: " << endl;
            gets(nome);
            setbuf(stdin, NULL);
            cout << "Digite o telefone do fornecedor: " << endl;
            gets(telefone);
            setbuf(stdin, NULL);
            cout << "Digite o produto do fornecedor: " << endl;
            gets(produto);
            setbuf(stdin, NULL);
            fprintf(ponteiroArquivo, "%s\n", codigo);
            fprintf(ponteiroArquivo, "%s\n", nome);
            fprintf(ponteiroArquivo, "%s\n", telefone);
            fprintf(ponteiroArquivo, "%s\n", produto);
            auxiliar = 0;
        }
        else
        {
            printf("\nCódigo Inválido!\n\n\n");
            system("pause");
            auxiliar = 1;
        }
    }
    fclose(ponteiroArquivo);
}

int procurarNoArquivo(char *string, char *nomeDoArquivo, int quantidadeDeRegistrosPorBloco, int posicaoItemPesquisa)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    int resultado = 0;
    char temp[512];

    if((arquivo = fopen(nomeDoArquivo, "r")) == NULL)
    {
        return-1;
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {
        if (numeroDaLinhaAtual%quantidadeDeRegistrosPorBloco == posicaoItemPesquisa)
        {
            if((strstr(temp, string)) != NULL)
            {
                if (strlen(string) == (strlen(temp)-1))
                {
                    resultado++;
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(resultado == 0)
    {
        if(arquivo)
        {
            fclose(arquivo);
        }
        return 3;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }
    return 0;
}

void cadastrarFuncionario()
{
    int auxiliar = 1;
    char caminhoArquivo[] = "Funcionario.txt";
    FILE* fl_fun;

    if( access(caminhoArquivo, F_OK ) != -1 )
    {
        fl_fun = fopen (caminhoArquivo,"a");
    }
    else
    {
        fl_fun = fopen (caminhoArquivo,"w");
    }
    char nome[40], endereco[70], telefone[15], codigo[10], salario[10];
    int tipo = 0;

    while (auxiliar != 0)
    {
        system("cls");
        setbuf(stdin, NULL);
        cout << "Digite o Codigo do Funcionário: ";
        gets(codigo);
        cout << endl;
        int verificaExistencia = procurarNoArquivo(codigo, caminhoArquivo, 6, 1);

        if (verificaExistencia == 3)
        {
            setbuf(stdin, NULL);
            cout << "Digite o nome do Funcionário: " << endl;
            gets(nome);
            setbuf(stdin, NULL);
            cout << "Digite o endereço do Funcionário: " << endl;
            gets(endereco);
            setbuf(stdin, NULL);
            cout << "Digite o telefone do Funcionário: " << endl;
            gets(telefone);
            do
            {
                setbuf(stdin, NULL);
                cout << "Digite o tipo do Funcionário\n\n\t[1] - FIXO\n\t[2] - TEMPORARIO: " << endl;
                cin >> tipo;
                if (tipo != 1 && tipo != 2)
                {
                    tipo = 0;
                    cout << "Tipo de Funcionário inválido!" << endl;
                }
            }
            while (tipo == 0);
            setbuf(stdin, NULL);
            cout << "Digite o salário do Funcionário: " << endl;
            gets(salario);

            setbuf(stdin, NULL);

            fprintf(fl_fun, "%s\n", codigo);
            fprintf(fl_fun, "%s\n", nome);
            fprintf(fl_fun, "%s\n", endereco);
            fprintf(fl_fun, "%s\n", telefone);
            if (tipo == 1)
            {
                fprintf(fl_fun, "%s\n", "Fixo");
            }
            else if (tipo == 2)
            {
                fprintf(fl_fun, "%s\n", "Temporario");
            }
            else
            {
                fprintf(fl_fun, "%s\n", "Erro");
            }
            fprintf(fl_fun, "%s\n", salario);
            auxiliar = 0;
        }
        else
        {
            printf("\nCodigo de Funcionário inválido!\n\n\n");
            system("pause");
            auxiliar = 1;
        }
    }
    fclose(fl_fun);
}

int procurarNoArquivoHoraSabado(char *string,char* horaInicio , char *nomeDoArquivo, int quantidadeDeRegistrosPorBloco, int posicaoItemPesquisa)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    int linhaRegistro = 0;
    int resultado = 0;
    char temp[512];

    if((arquivo = fopen(nomeDoArquivo, "r")) == NULL)
    {
        return-1;
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {
        if (numeroDaLinhaAtual%quantidadeDeRegistrosPorBloco == posicaoItemPesquisa)
        {
            if((strstr(temp, string)) != NULL)
            {
                if (strlen(string) == (strlen(temp)-1))
                {
                    resultado++;
                    linhaRegistro = numeroDaLinhaAtual;
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }

    numeroDaLinhaAtual = 1;

    if(resultado == 0)
    {
        return 3;
    } else {

        if((arquivo = fopen(nomeDoArquivo, "r")) == NULL)
        {
            return-1;
        }

        while(fgets(temp, 512, arquivo) != NULL)
        {
            if (numeroDaLinhaAtual==(linhaRegistro + 2))
            {

                if((strstr(temp, horaInicio)) != NULL)
                {
                    return 4;
                }
            }
            numeroDaLinhaAtual++;
        }
    }

    if(arquivo)
    {
        fclose(arquivo);
    }
    return 0;
}

int procurarNoArquivoSabado(char *string, char *nomeDoArquivo, int quantidadeDeRegistrosPorBloco, int posicaoItemPesquisa)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    int linhaRegistro = 0;
    int resultado = 0;
    char temp[512];

    if((arquivo = fopen(nomeDoArquivo, "r")) == NULL)
    {
        return-1;
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {
        if (numeroDaLinhaAtual%quantidadeDeRegistrosPorBloco == posicaoItemPesquisa)
        {
            if((strstr(temp, string)) != NULL)
            {
                if (strlen(string) == (strlen(temp)-1))
                {
                    resultado++;
                    linhaRegistro = numeroDaLinhaAtual;
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }

    numeroDaLinhaAtual = 1;

    if(resultado == 0)
    {
        return 3;
    } else if (resultado == 1){

        if((arquivo = fopen(nomeDoArquivo, "r")) == NULL)
        {
            return-1;
        }

        while(fgets(temp, 512, arquivo) != NULL)
        {
            if (numeroDaLinhaAtual==(linhaRegistro + 1))
            {

                if((strstr(temp, "Sabado")) != NULL)
                {
                    return 4;
                }
            }
            numeroDaLinhaAtual++;
        }
    }

    if(arquivo)
    {
        fclose(arquivo);
    }
    return 0;
}

void cadastrarFesta()
{
    int auxiliar = 1;
    char caminhoArquivo[] = "Festa.txt";
    FILE* pontiroArquivo;

    if( access(caminhoArquivo, F_OK ) != -1 )
    {
        pontiroArquivo = fopen (caminhoArquivo,"a");
    }
    else
    {
        pontiroArquivo = fopen (caminhoArquivo,"w");
    }

    char codigo[10],quantConvidados[5], data[15], *diaSemana, tema[30], *codigoCliente = (char*) malloc(1*sizeof(char));
    char nomeCliente[40];
    char* horaInicio = new char[6];
    char* horaFim = new char[6];
    int opcao = 0, opcaoHorario = 0, auxiliarConvidadosMaximo = 0;

    while (auxiliar != 0)
    {
        system("cls");
        setbuf(stdin, NULL);
        cout << "Digite o Codigo da Festa: " << endl;
        gets(codigo);
        int verificaExistencia = procurarNoArquivo(codigo, caminhoArquivo, 8,1);

        if (verificaExistencia == 3)
        {
            do
            {
                setbuf(stdin, NULL);
                cout << "Digite quantidade de convidados: " << endl;
                gets(quantConvidados);
                if(atoi(quantConvidados)>100)
                {
                    cout << "Número de convidados máximo é de 100!" << endl;
                    auxiliarConvidadosMaximo = 0;
                }
                else
                {
                    auxiliarConvidadosMaximo = 1;
                }
            }
            while(auxiliarConvidadosMaximo == 0);

            int aux = 1;

            do
            {
                if (aux > 1) {
                    cout << "Data ocupada, favor escolher outra!";
                }
                setbuf(stdin, NULL);
                cout << "\n\nDigite a data da festa: " << endl;
                gets(data);
                aux++;
            }
            while (procurarNoArquivoSabado(data, caminhoArquivo, 8,3) != 3 && procurarNoArquivoSabado(data, caminhoArquivo, 8,3) != 4);

            if (procurarNoArquivoSabado(data, caminhoArquivo, 8,3) == 4) {

                cout << "Dia da festa: Sabado" << endl;
                diaSemana = "Sabado";
                do
                {
                    setbuf(stdin, NULL);
                    cout << "Selecione um horário:\n\n\t[1] - 12:00 às 16:00\n\t[2] - 18:00 às 22:00" << endl;
                    cin >> opcaoHorario;
                    if(opcaoHorario == 1)
                    {
                        horaInicio = "12:00";
                        horaFim = "16:00";
                        if (procurarNoArquivoHoraSabado(data,"12:00" ,caminhoArquivo, 8,3) == 4) {
                            cout << "Horário já ocupado! Escolha Outro!\n";
                            opcaoHorario = 0;
                        }
                    }
                    else if(opcaoHorario == 2)
                    {
                        horaInicio = "18:00";
                        horaFim = "22:00";
                        if (procurarNoArquivoHoraSabado(data,"18:00" ,caminhoArquivo, 8,3) == 4) {
                            cout << "Horário já ocupado! Escolha Outro!\n";
                            opcaoHorario = 0;
                        }
                    }
                    else
                    {
                        opcaoHorario=0;
                        cout << "Horário Inválido" << endl;
                    }
                }
                while (opcaoHorario == 0);


            } else {

                do
                {
                    setbuf(stdin, NULL);
                    cout << "Digite o dia da festa\n\n\t[1] - Domingo\n\t[2] - Segunda-Feira\n\t[3] - Terça-Feira\n\t[4] - Quarta-Feira\n\t[5] - Quinta-Feira\n\t[6] - Sexta-Feira\n\t[7] - Sabado" << endl;
                    cin >> opcao;
                    switch(opcao)
                    {
                    case 1:
                        diaSemana = "Domingo";
                        break;
                    case 2:
                        diaSemana = "Segunda-Feira";
                        break;
                    case 3:
                        diaSemana = "Terça-Feira";
                        break;
                    case 4:
                        diaSemana = "Quarta-Feira";
                        break;
                    case 5:
                        diaSemana = "Quinta-Feira";
                        break;
                    case 6:
                        diaSemana = "Sexta-Feira";
                        break;
                    case 7:
                        diaSemana = "Sabado";
                        break;
                    default:
                        opcao = 0;
                        cout << "Dia Inválido" << endl;
                        break;
                    }
                }
                while (opcao == 0);
                if(opcao == 7)
                {
                    do
                    {
                        setbuf(stdin, NULL);
                        cout << "Selecione um horário:\n\n\t[1] - 12:00 às 16:00\n\t[2] - 18:00 às 22:00" << endl;
                        cin >> opcaoHorario;
                        if(opcaoHorario == 1)
                        {
                            horaInicio = "12:00";
                            horaFim = "16:00";
                        }
                        else if(opcaoHorario == 2)
                        {
                            horaInicio = "18:00";
                            horaFim = "22:00";
                        }
                        else
                        {
                            opcaoHorario=0;
                            cout << "Horário Inválido" << endl;
                        }
                    }
                    while (opcaoHorario == 0);
                }
                else
                {
                    setbuf(stdin, NULL);
                    cout << "Horário de inicio: " << endl;
                    gets(horaInicio);
                    setbuf(stdin, NULL);
                    cout << "Horario de término: " << endl;
                    gets(horaFim);
                }

            }


            setbuf(stdin, NULL);
            cout << "Tema da festa: " << endl;
            gets(tema);
            setbuf(stdin, NULL);
            do
            {
                cout << "Nome do cliente: " << endl;
                gets(nomeCliente);

                if (getCodigoByName(nomeCliente)== "Erro")
                {
                    cout << endl;
                    cout << "Cliente não encontrado!" << endl;
                    system("pause");
                }
            }
            while(getCodigoByName(nomeCliente) == "Erro");
            codigoCliente = getCodigoByName(nomeCliente);

            setbuf(stdin, NULL);
            fprintf(pontiroArquivo, "%s\n", codigo);
            fprintf(pontiroArquivo, "%s\n", quantConvidados);
            fprintf(pontiroArquivo, "%s\n", data);
            fprintf(pontiroArquivo, "%s\n", diaSemana);
            fprintf(pontiroArquivo, "%s\n", horaInicio);
            fprintf(pontiroArquivo, "%s\n", horaFim);
            fprintf(pontiroArquivo, "%s\n", tema);
            fprintf(pontiroArquivo, "%s", codigoCliente);
            auxiliar = 0;
        }
        else
        {
            printf("\nCódigo Inválido!\n\n\n");
            system("pause");
            auxiliar = 1;
        }
    }
    fclose(pontiroArquivo);
}

char* getContratoPorCodigoCliente(char *codigo)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    char temp[512];
    int linhaCodigo = 0;
    char *resultadoFinal = (char*) malloc(1*sizeof(char));

    int auxiliar= 0;

    int *linhas = (int*) malloc(500);
    if((arquivo = fopen("Contrato.txt", "r")) == NULL)
    {
        return "Contrato não Encontrado";
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {

        if (numeroDaLinhaAtual%7 == 0)
        {
            if((strstr(temp, codigo)) != NULL)
            {

                if (strlen(codigo) == (strlen(temp)-1))
                {

                    linhaCodigo = 1;
                    if(auxiliar == 0)
                    {
                        cout << "Codigo da Festa: " << codigo << endl;
                        linhas[0]= numeroDaLinhaAtual-6;
                        linhas[1]= numeroDaLinhaAtual-5;
                        linhas[2]= numeroDaLinhaAtual-4;
                        linhas[3]= numeroDaLinhaAtual-3;
                        linhas[4]= numeroDaLinhaAtual-2;
                        linhas[5]= numeroDaLinhaAtual-1;
                        linhas[6]= numeroDaLinhaAtual;
                        auxiliar++;

                        //for (int i = 0 ; i < 7 ; i++) {
                            //cout << endl << linhas[i] << endl;
                        //}
                    }
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }

    if((arquivo = fopen("Contrato.txt", "r")) == NULL)
    {
        return "Contrato não Encontrado";
    }
    numeroDaLinhaAtual = 1;

    if (linhaCodigo!= 0)
    {
        while(fgets(temp, 512, arquivo) != NULL)
        {
            if (auxiliar == 1)
            {

                if (numeroDaLinhaAtual == linhas[0] ||
                numeroDaLinhaAtual == linhas[1] ||
                numeroDaLinhaAtual == linhas[2] ||
                numeroDaLinhaAtual == linhas[3] ||
                numeroDaLinhaAtual == linhas[4] ||
                numeroDaLinhaAtual == linhas[5])
                {
                    if (numeroDaLinhaAtual == linhas[0])
                    {
                        fflush(stdin);
                        strcat(resultadoFinal, "Número do contrato: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[1])
                    {
                        fflush(stdin);
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Valor Total: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[2])
                    {
                        fflush(stdin);
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Desconto: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[3])
                    {
                        fflush(stdin);
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Valor Final: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[4])
                    {
                        fflush(stdin);
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Forma de Pagamento: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[5])
                    {
                        fflush(stdin);
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Status: ");
                        strcat(resultadoFinal, temp);
                    }
                }
            }
            numeroDaLinhaAtual++;
        }
        free(linhas);
        return resultadoFinal;
    }
    if(arquivo)
    {
        fclose(arquivo);
    }
    return "Contrato não Encontrado";
}

char* getFestaPorData(char *data)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1;
    char temp[512];
    char codigoDaFesta[512];
    int linhaCodigo = 0;
    char *resultadoFinal = (char*) malloc(1*sizeof(char));

    int auxiliar= 0;

    char linhas[17];
    if((arquivo = fopen("Festa.txt", "r")) == NULL)
    {
        return "Erro";
    }

    while(fgets(temp, 512, arquivo) != NULL)
    {
        if (numeroDaLinhaAtual%8 == 3)
        {
            if((strstr(temp, data)) != NULL)
            {
                if (strlen(data) == (strlen(temp)-1))
                {
                    linhaCodigo = 1;
                    if(auxiliar == 0)
                    {
                        linhas[0]= numeroDaLinhaAtual - 2;
                        linhas[1]= numeroDaLinhaAtual - 1;
                        linhas[2]= numeroDaLinhaAtual;
                        linhas[3]= numeroDaLinhaAtual + 1;
                        linhas[4]= numeroDaLinhaAtual + 2;
                        linhas[5]= numeroDaLinhaAtual + 3;
                        linhas[6]= numeroDaLinhaAtual + 4;
                        linhas[7]= numeroDaLinhaAtual + 5;
                        auxiliar++;
                    }
                    else if (auxiliar == 1)
                    {
                        linhas[8] = numeroDaLinhaAtual - 2;
                        linhas[9] = numeroDaLinhaAtual - 1;
                        linhas[10]= numeroDaLinhaAtual;
                        linhas[11]= numeroDaLinhaAtual + 1;
                        linhas[12]= numeroDaLinhaAtual + 2;
                        linhas[13]= numeroDaLinhaAtual + 3;
                        linhas[14]= numeroDaLinhaAtual + 4;
                        linhas[15]= numeroDaLinhaAtual + 5;
                        auxiliar++;
                    }
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }

    if((arquivo = fopen("Festa.txt", "r")) == NULL)
    {
        return "Erro";
    }
    numeroDaLinhaAtual = 1;

    if (linhaCodigo!= 0)
    {
        while(fgets(temp, 512, arquivo) != NULL)
        {
            if (auxiliar == 2)
            {
                if (numeroDaLinhaAtual == linhas[0] ||
                numeroDaLinhaAtual == linhas[1] ||
                numeroDaLinhaAtual == linhas[2] ||
                numeroDaLinhaAtual == linhas[3] ||
                numeroDaLinhaAtual == linhas[4] ||
                numeroDaLinhaAtual == linhas[5] ||
                numeroDaLinhaAtual == linhas[6] ||
                numeroDaLinhaAtual == linhas[7] ||
                numeroDaLinhaAtual == linhas[8] ||
                numeroDaLinhaAtual == linhas[9] ||
                numeroDaLinhaAtual == linhas[10] ||
                numeroDaLinhaAtual == linhas[11] ||
                numeroDaLinhaAtual == linhas[12] ||
                numeroDaLinhaAtual == linhas[13] ||
                numeroDaLinhaAtual == linhas[14] ||
                numeroDaLinhaAtual == linhas[15])
                {
                    if (numeroDaLinhaAtual == linhas[0])
                    {
                        strcat(resultadoFinal, "\n\nCódigo da Festa: ");
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, temp);
                        for (int i = 0 ; i<strlen(temp) ; i++) {
                            codigoDaFesta[i] = temp[i];
                        }
                    }
                    else if (numeroDaLinhaAtual == linhas[1])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Quantidade de convidados: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[2])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Data: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[3])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Dia: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[4])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Inicio: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[5])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Fim: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[6])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Tema: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[7])
                    {

                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Código do Cliente: ");
                        strcat(resultadoFinal, temp);

                        char *codFestaLimpo = (char*) malloc(1*sizeof(char));

                        for (int i = 0 ; i < strlen(codigoDaFesta)-1 ; i ++)
                        {
                            codFestaLimpo[i] = codigoDaFesta[i];
                        }
                        strcat(resultadoFinal, getContratoPorCodigoCliente(codFestaLimpo));
                    }
                    else if (numeroDaLinhaAtual == linhas[8])
                    {
                        strcat(resultadoFinal, "\n\nCódigo da Festa: ");
                        setbuf(stdin, NULL);
                        for (int i = 0 ; i<strlen(temp) ; i++) {
                            codigoDaFesta[i] = temp[i];
                        }
                        strcat(resultadoFinal, codigoDaFesta);
                    }
                    else if (numeroDaLinhaAtual == linhas[9])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Quantidade de convidados: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[10])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Data: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[11])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Dia: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[12])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Inicio: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[13])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Fim: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[14])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Tema: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[15])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Código do Cliente: ");
                        strcat(resultadoFinal, temp);

                        char *codFestaLimpo = (char*) malloc(1*sizeof(char));

                        for (int i = 0 ; i < strlen(codigoDaFesta)-1 ; i ++)
                        {
                            codFestaLimpo[i] = codigoDaFesta[i];
                        }
                        strcat(resultadoFinal, getContratoPorCodigoCliente(codFestaLimpo));
                    }
                }
            }
            else if (auxiliar == 1)
            {
                if (numeroDaLinhaAtual == linhas[0] ||
                numeroDaLinhaAtual == linhas[1] ||
                numeroDaLinhaAtual == linhas[2] ||
                numeroDaLinhaAtual == linhas[3] ||
                numeroDaLinhaAtual == linhas[4] ||
                numeroDaLinhaAtual == linhas[5] ||
                numeroDaLinhaAtual == linhas[6] ||
                numeroDaLinhaAtual == linhas[7])
                {
                    if (numeroDaLinhaAtual == linhas[0])
                    {
                        strcat(resultadoFinal, "\n\nCódigo da Festa: ");
                        strcat(resultadoFinal, temp);
                        for (int i = 0 ; i<strlen(temp) ; i++) {
                            codigoDaFesta[i] = temp[i];
                        }
                    }
                    else if (numeroDaLinhaAtual == linhas[1])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Quantidade de convidados: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[2])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Data: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[3])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Dia: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[4])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Inicio: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[5])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Fim: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[6])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Tema: ");
                        strcat(resultadoFinal, temp);
                    }
                    else if (numeroDaLinhaAtual == linhas[7])
                    {
                        setbuf(stdin, NULL);
                        strcat(resultadoFinal, "Código do Cliente: ");
                        strcat(resultadoFinal, temp);

                        char *codFestaLimpo = (char*) malloc(1*sizeof(char));

                        for (int i = 0 ; i < strlen(codigoDaFesta)-1 ; i ++)
                        {
                            codFestaLimpo[i] = codigoDaFesta[i];
                        }
                        strcat(resultadoFinal, getContratoPorCodigoCliente(codFestaLimpo));
                    }
                }
            }
            numeroDaLinhaAtual++;
        }
        return resultadoFinal;
    }

    if(arquivo)
    {
        fclose(arquivo);
    }
    return "Erro";
}

void cadastrarContrato()
{
    int auxiliar = 1;
    int auxX = 1;
    char caminhoArquivo[] = "Contrato.txt";
    FILE* ponteiroArquivo;

    if( access(caminhoArquivo, F_OK ) != -1 )
    {
        ponteiroArquivo = fopen (caminhoArquivo,"a");
    }
    else
    {
        ponteiroArquivo = fopen (caminhoArquivo,"w");
    }
    char caminhoArquivoFesta[] = "Festa.txt";

    FILE* pontiroArquivo;

    if( access(caminhoArquivoFesta, F_OK ) != -1 )
    {
        pontiroArquivo = fopen (caminhoArquivoFesta,"a");
    }
    else
    {
        pontiroArquivo = fopen (caminhoArquivoFesta,"w");
    }

    char numeroContrato[10], *valorTotal, *desconto, *valorFinal, *formaDePagamento = (char*) malloc(1*sizeof(char)), *status  = (char*) malloc(1*sizeof(char)), *codigoFesta = (char*) malloc(1*sizeof(char));
    int opcao = 0;

    while (auxX != 0)
    {
        system("cls");
        setbuf(stdin, NULL);
        cout << "Código da Festa: " << endl;
        fflush(stdin);
        cin >> codigoFesta;

        int verificaExistencia = procurarNoArquivo(codigoFesta, caminhoArquivoFesta, 8,1);
        int verificaExistencia2 = procurarNoArquivo(codigoFesta, caminhoArquivo, 7,0);

        if ((verificaExistencia != 3) && (verificaExistencia2 == 3))
        {
            auxX = 0;
        }
        else
        {
            printf("\nCodigo Inválido\n\n\n");
            system("pause");
            auxX = 1;
        }

    }
    char* quantidadeConvidados = quantidadePessoasFesta(atoi(codigoFesta));
    char* diaSemana = diaSemanaFesta(atoi(codigoFesta));

    if(atoi(quantidadeConvidados) > 0 && atoi(quantidadeConvidados) <= 30)
    {
        if (strcmp(diaSemana,"Segunda-Feira\n")==0||strcmp(diaSemana,"Terça-Feira\n")==0||strcmp(diaSemana,"Quarta-Feira\n")==0||strcmp(diaSemana,"Quinta-Feira\n")==0)
        {
            valorTotal = "1899.00";
        }
        else if(strcmp(diaSemana,"Sexta-Feira\n")==0||strcmp(diaSemana,"Sabado\n")==0||strcmp(diaSemana,"Domingo\n")==0)
        {
            valorTotal = "2099.00";
        }
    }
    else if(atoi(quantidadeConvidados) > 30 && atoi(quantidadeConvidados) <= 50)
    {
        if (strcmp(diaSemana,"Segunda-Feira\n")==0||strcmp(diaSemana,"Terça-Feira\n")==0||strcmp(diaSemana,"Quarta-Feira\n")==0||strcmp(diaSemana,"Quinta-Feira\n")==0)
        {
            valorTotal = "2199.00";
        }
        else if(strcmp(diaSemana,"Sexta-Feira\n")==0||strcmp(diaSemana,"Sabado\n")==0||strcmp(diaSemana,"Domingo\n")==0)
        {
            valorTotal = "2299.00";
        }
    }
    else if(atoi(quantidadeConvidados) > 50 && atoi(quantidadeConvidados) <= 80)
    {
        if (strcmp(diaSemana,"Segunda-Feira\n")==0||strcmp(diaSemana,"Terça-Feira\n")==0||strcmp(diaSemana,"Quarta-Feira\n")==0||strcmp(diaSemana,"Quinta-Feira\n")==0)
        {
            valorTotal = "3199.00";
        }
        else if(strcmp(diaSemana,"Sexta-Feira\n")==0||strcmp(diaSemana,"Sabado\n")==0||strcmp(diaSemana,"Domingo\n")==0)
        {
            valorTotal = "3499.00";
        }
    }
    else if(atoi(quantidadeConvidados) > 80 && atoi(quantidadeConvidados) <= 100)
    {
        if (strcmp(diaSemana,"Segunda-Feira\n")==0||strcmp(diaSemana,"Terça-Feira\n")==0||strcmp(diaSemana,"Quarta-Feira\n")==0||strcmp(diaSemana,"Quinta-Feira\n")==0)
        {
            valorTotal = "3799.00";
        }
        else if(strcmp(diaSemana,"Sexta-Feira\n")==0||strcmp(diaSemana,"Sabado\n")==0||strcmp(diaSemana,"Domingo\n")==0)
        {
            valorTotal = "3999.00";
        }
    }
    else
    {
        cout << "Houve um erro na leitura da quantidade de usuarios" << endl;
    }

    while (auxiliar != 0)
    {
        setbuf(stdin, NULL);
        cout << "Digite o numero do contrato: " << endl;
        gets(numeroContrato);

        int verificaExistencia = procurarNoArquivo(numeroContrato, caminhoArquivo, 7,1);

        if (verificaExistencia == 3)
        {
            do
            {
                setbuf(stdin, NULL);
                cout << "\nDigite a forma de pagamento\n\n\t[1] - A vista\n\t[2] - Duas Vezes\n\t[3] - Três vezes\n\t[4] - Quarto ou mais vezes" << endl;
                cin >> opcao;
                switch(opcao)
                {
                case 1:
                    formaDePagamento = "A vista";
                    desconto = "10";
                    break;
                case 2:
                    formaDePagamento = "Duas Vezes";
                    desconto = "5";
                    break;
                case 3:
                    formaDePagamento = "Três vezes";
                    desconto = "2";
                    break;
                case 4:
                    formaDePagamento = "Quarto ou mais vezes";
                    desconto = "0";
                    break;
                default:
                    opcao = 0;
                    cout << "Forma de pagamento digitado invalido.....Informe a forma de pagamento novamente" << endl;
                    break;
                }
            }
            while (opcao == 0);

            opcao = 1;

            do
            {
                setbuf(stdin, NULL);
                cout << "\nStatus do pagamento:\n\n\t[1] - Pendente\n\t[2] - Pago\n\t[3] - Cancelado" << endl;
                cin >> opcao;



                switch(opcao)
                {
                case 1:
                    status = "Pendente";
                    break;
                case 2:
                    status = "Pago";
                    break;
                case 3:
                    status = "Cancelado";
                    break;
                default:
                    opcao = 0;
                    cout << "Status Inválido" << endl;
                    break;
                }
            }
            while (opcao == 0);

            int valorDesconto = atoi(desconto);
            float valorTotalFloat = atof(valorTotal);
            system("pause");
            float descontoNumero;

            if(valorDesconto == 10)
            {
                descontoNumero = 0.9;
            }
            else if(valorDesconto == 5)
            {
                descontoNumero = 1 - 0.05;
            }
            else if(valorDesconto == 2)
            {
                descontoNumero = 1 - 0.02;
            }
            else
            {
                descontoNumero = 1;
            }
            float valorFinal = valorTotalFloat * descontoNumero;

            fprintf(ponteiroArquivo, "%s\n", numeroContrato);
            fprintf(ponteiroArquivo, "%.2f\n", valorTotalFloat);
            fprintf(ponteiroArquivo, "%s\n", desconto);
            fprintf(ponteiroArquivo, "%.2f\n", valorFinal);
            fprintf(ponteiroArquivo, "%s\n", formaDePagamento);
            fprintf(ponteiroArquivo, "%s\n", status);
            fprintf(ponteiroArquivo, "%s\n", codigoFesta);
            auxiliar = 0;
        }
        else
        {
            printf("\nNúmero Inválido\n\n\n");
            system("pause");
            auxiliar = 1;
        }
    }
    fclose(ponteiroArquivo);
    fclose(pontiroArquivo);
}

int relatorioDia()
{
    char *data;
    system("cls");
    printf("Data do relatório: ");
    setbuf(stdin, NULL);
    cin >> data;
    cout << getFestaPorData(data);
    getchar();
    return 0;
}

char* diaSemanaFesta(int codigo)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1,linhaCodigo;
    char temp[512], *semana = (char*) malloc(1*sizeof(char));
    arquivo = fopen("Festa.txt","r");

    while(fgets(temp,512,arquivo))
    {
        if(numeroDaLinhaAtual%8==1) {
            if(codigo == atoi(temp))
            {
                linhaCodigo = numeroDaLinhaAtual + 3;
            }
        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
    numeroDaLinhaAtual = 1;
    arquivo = fopen("Festa.txt","r");

    while(fgets(temp,512,arquivo))
    {
        if(linhaCodigo == numeroDaLinhaAtual)
        {
            strcpy(semana,temp);
        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
    return semana;
}

char* quantidadePessoasFesta(int codigo)
{
    FILE *arquivo;
    int numeroDaLinhaAtual = 1,linhaCodigo = 0;
    char temp[512], *quantidadePessoas = (char*) malloc(1*sizeof(char));
    char *valorSemQuebraDeLinha = (char*) malloc(1*sizeof(char));
    arquivo = fopen("Festa.txt","r");
    char *auxiliarVetor;
    while(fgets(temp,512,arquivo) != NULL)
    {
        if(strchr(temp, '\n')){
            valorSemQuebraDeLinha = (char*) malloc(1*sizeof(char));
            for (int i = 0 ; i < strlen(temp) -1 ; i ++) {
                    valorSemQuebraDeLinha[i] = temp[i];
            }

            if(numeroDaLinhaAtual%8==1) {

                if(codigo == atoi(valorSemQuebraDeLinha))
                {
                    linhaCodigo = numeroDaLinhaAtual + 1;
                }
            }
        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
    numeroDaLinhaAtual = 1;
    arquivo = fopen("Festa.txt","r");

    while(fgets(temp,512,arquivo) != NULL)
    {
        if(linhaCodigo == numeroDaLinhaAtual)
        {
            strcat(quantidadePessoas, temp);

        }
        numeroDaLinhaAtual++;
    }
    fclose(arquivo);
    return quantidadePessoas;
}

void pesquisarFornecedores()
{
    char nome[50];
    system("cls");
    printf("Nome do Fornecedor: ");
    setbuf(stdin, NULL);
    gets(nome);
    cout << pesquisarPorNome(nome, "Fornecedor.txt", 4, 2, 2);
    cout << endl;
    system("pause");
    getchar();
}

char* pesquisarPorNome(char* nome, char* arquivo, int quantidadeLinhasRegistro, int posicaoLinhaNome, int tipoConsulta)
{
    FILE *arquivoPonteiro;
    int numeroDaLinhaAtual = 1;
    int resultado = 0;
    char temp[512];
    int primeiraLinha = 0;

    if((arquivoPonteiro = fopen(arquivo, "r")) == NULL)
    {
        return "Erro";
    }

    while(fgets(temp, 512, arquivoPonteiro) != NULL)
    {
        if (numeroDaLinhaAtual%quantidadeLinhasRegistro == posicaoLinhaNome)
        {
            if((strstr(temp, nome)) != NULL)
            {
                if (strlen(nome) == (strlen(temp)-1))
                {
                    primeiraLinha = numeroDaLinhaAtual - 1;
                }
            }
        }
        numeroDaLinhaAtual++;
    }

    if(arquivoPonteiro)
    {
        fclose(arquivoPonteiro);
    }

    if((arquivoPonteiro = fopen(arquivo, "r")) == NULL)
    {
        return "Erro";
    }

    numeroDaLinhaAtual = 1;
    char *matrizMes[3][7] = { "\n\nCódigo do Cliente: ", "Nome: ", "Endereço: ", "Telefone: ", "Data de Nascimento: ", "", "", "\n\nCódigo do Funcionário: ", "Nome: ", "Endereço: ", "Telefone: ", "Tipo: ",
    "Salário: ", " ", "\n\nCódigo do Fornecedor: " , "Nome: " , "Telefone: " , "Produto: " , " " , " ", " " };
    char *resultadoFinal = (char*) malloc(1*sizeof(char));
    int auxiliar = 0;

    if (primeiraLinha!= 0)
    {
        while(fgets(temp, 512, arquivoPonteiro) != NULL)
        {
            if (numeroDaLinhaAtual >= primeiraLinha && numeroDaLinhaAtual < (quantidadeLinhasRegistro + primeiraLinha))
            {
                strcat(resultadoFinal, matrizMes[tipoConsulta][auxiliar]);
                strcat(resultadoFinal, temp);
                auxiliar++;
            }
            numeroDaLinhaAtual++;
        }
        if(arquivoPonteiro)
        {
            fclose(arquivoPonteiro);
        }
        return resultadoFinal;
    }

    if(arquivoPonteiro)
    {
        fclose(arquivoPonteiro);
    }

    return "Erro";
}

void pesquisarClientes()
{
    char nome[50];
    system("cls");
    printf("Nome do Cliente: ");
    setbuf(stdin, NULL);
    gets(nome);
    cout << pesquisarPorNome(nome, "Cliente.txt", 5, 2, 0);
    cout << endl;
    system("pause");
    getchar();
}

void pesquisarFuncionarios()
{
    char nome[50];
    system("cls");
    printf("Nome do Funcionário: ");
    setbuf(stdin, NULL);
    gets(nome);
    cout << pesquisarPorNome(nome, "Funcionario.txt", 6, 2, 1);
    cout << endl;
    system("pause");
    getchar();
}



