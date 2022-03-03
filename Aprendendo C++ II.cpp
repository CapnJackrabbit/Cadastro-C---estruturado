#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string>


using namespace std;

void cadastra();
void apresenta();
int valida_cpf(int *temp_cpf);
int posicao(char* nome);
void pesquisa(char* cpf);
void altera(void);
void apaga();


struct dados                               //struct para guardar dados do associado                                            
{                                          
    char nome[30];
    char endereco[50];
    int temp_cpf[12]{NULL};                     // CPF em inteiro, para fazer o cálculo dos dígitos verificadores
    char cpf[12]{NULL};                         // CPF em string, para guardar no arquivo
};

char cpf[11];                             // variável CPF apenas para leitura/consulta no arquivo



int main()
{
    // Declaracoes
    char opcao;
    // Instrucoes

    do
    {
        system("cls");
        system("color 0f");
        printf(" C - CADASTRA UM ASSOCIADO \n");
        printf(" L - APRESENTA TODOS OS ASSOCIADOS CADASTRADOS\n");
        printf(" P - PESQUISA ASSOCIADO POR CPF \n");
        printf(" A - ALTERA OS DADOS DO ASSOCIADO\n");
        printf(" X - EXCLUI OS DADOS DO ASSOCIADO\n");
        printf(" S - SAIR\n");
        opcao = toupper(_getch());
        switch (opcao)
        {
        case 'C':
            cadastra();
            break;
        case 'L':
            apresenta();
            break;
        case 'P':
            printf("INFORME O CPF: ");
            scanf("%s", &cpf);
            pesquisa(cpf);
            break;
        case 'A':
            altera();
            break;
        case 'X':
            apaga();
            break;

        }
    } while (opcao != 'S');
    setbuf(stdin, NULL);
    _getch();
    return 0;
}

void cadastra()
{
    int temp_cpf[11];
    int i;
    struct dados associado;
    FILE *arquivo;                                          //cria uma variável ponteiro do tipo FILE, que recebe um retorno de 'fopen'
 
    arquivo = fopen("outputfile.txt", "ab");
    if (arquivo == NULL)
    {
        system("color 0f");
        fprintf(stdout, "ERRO AO ABRIR ARQUIVO PARA ESCRITA\a");         //stdout é a saída padrão - monitor.
    }
    else
    {
        fprintf(stdout, "DADOS DO ASSOCIADO\n\n");                     //stdin é a entrada padrão - teclado.
        fprintf(stdout, "NOME DO ASSOCIADO\n\n");
        setbuf(stdin, NULL);
        fscanf(stdin, "%s", &associado.nome);
        fprintf(stdout, "ENDERECO DO ASSOCIADO\n\n");
        setbuf(stdin, NULL);
        fscanf(stdin, "%s", &associado.endereco);

        
        do
        {
            system("color 0f");
            fprintf(stdout, "\nCPF DO ASSOCIADO:\n\n");
            for (i = 0; i < 11; i++)
            {
                temp_cpf[i] = _getche();
                if (isdigit(temp_cpf[i]))
                {
                    associado.cpf[i] = temp_cpf[i];
                    temp_cpf[i] -=  '0';     //por alguma razão, isso converte o valor de ASCII para inteiro. vai saber o porquê.
                }
                    
                else
                {
                    system("color 4");
                    system("cls");
                    printf("\a\nAPENAS NUMEROS PERMITIDOS (9)");
                    _getch();
                    break;
                }
            }
        } while (valida_cpf(temp_cpf) != 1);

        if (posicao(associado.cpf) != -1)
        {
            system("color 4f");
            printf("\n\nJA EXISTE UM ASSOCIADO COM ESTE CPF\n");
            _getch();
        }

        else
        {
            if (fwrite(&associado, sizeof(associado), 1, arquivo) == 1)      //sintaxe: fwrite(variável, tamanho, quantidade, fluxo)
            {
                system("color 2");
                system("cls");
                fprintf(stdout, "\n\nARQUIVO GRAVADO COM SUCESSO\n\n");
                _getch();
            }         
            else
            {
                system("color 4f");
                system("cls");
                fprintf(stdout, "\n\nFALHA AO GRAVAR ARQUIVO");
            }
                
        }                 
    }
    if (fclose(arquivo) != 0)
    {
        system("color 4f");
        system("cls");
        fprintf(stdout, "FALHA AO FECHAR O ARQUIVO");
    }
        
    
}


void apresenta()
{
    FILE* arquivo;
    struct dados associado;

    arquivo = fopen("outputfile.txt", "rb");
    if (arquivo == NULL)
    {
        system("color 4f");
        printf("\nERRO AO ABRIR ARQUIVO PARA LEITURA\n\n\a");
    }

    else
    {
        setbuf(arquivo, NULL);
        while (!feof(arquivo))
        {
            if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
            {
                fprintf(stdout, "\n Nome: %s\n", associado.nome);
                fprintf(stdout, " Endereco: %s\n", associado.endereco);
                fprintf(stdout, " CPF: %s\n", associado.cpf);
            }            
        }
        if (fclose(arquivo) != 0)
        {
            system("color 4f");
            printf("ERRO AO FECHAR O ARQUIVO QUE FOI ABERTO");
        }
            
    }
    
    _getch();

}

int valida_cpf (int *temp_cpf)
{
    int i, v1, v2;
    int soma = 0;
    int soma2 = 0;

    soma += (temp_cpf[0] * 10);
    soma += (temp_cpf[1] * 9);
    soma += (temp_cpf[2] * 8);
    soma += (temp_cpf[3] * 7);
    soma += (temp_cpf[4] * 6);
    soma += (temp_cpf[5] * 5);
    soma += (temp_cpf[6] * 4);
    soma += (temp_cpf[7] * 3);
    soma += (temp_cpf[8] * 2);
    v1 = (soma * 10) % 11;

    if (v1 == 10)
        v1 = 0;

    soma2 += temp_cpf[0] * 11;
    soma2 += temp_cpf[1] * 10;
    soma2 += temp_cpf[2] * 9;
    soma2 += temp_cpf[3] * 8;
    soma2 += temp_cpf[4] * 7;
    soma2 += temp_cpf[5] * 6;
    soma2 += temp_cpf[6] * 5;
    soma2 += temp_cpf[7] * 4;
    soma2 += temp_cpf[8] * 3;
    soma2 += v1 * 2;
    v2 = (soma2 * 10) % 11;

    if (v2 == 10)
        v2 = 0;

    if (temp_cpf[9] == v1 && temp_cpf[10] == v2)
    {
        return 1;
    }
    else
    {
        printf("CPF INVALIDO\n");
        return 0;
    }
}

int posicao(char *cpf)
{
    FILE* arquivo;
    struct dados associado;
    int posicao = 0, seq = -1;
    arquivo = fopen("outputfile.txt", "rb");
    if (arquivo == NULL)
    {
        system("color 4f");
        fprintf(stdout, " ERRO AO ABRIR ARQUIVO\n");
    }
    else
    {
        while (!feof(arquivo))
        {
            if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
            {
                if (strcmp(associado.cpf, cpf) == 0)
                {
                    seq = posicao;
                    break;
                }
                posicao++;
            }
        }
        if (fclose(arquivo) != 0)
        {
            
            fprintf(stdout, " ERRO AO FECHAR ARQUIVO\n");
        }
            
    }
    return seq;
}

void pesquisa(char* cpf)
{
    int seq;
    FILE* arquivo;
    struct dados associado;
    system("cls");
    seq = posicao(cpf);
    if (seq == -1)
    {
        system("color 4f");
        fprintf(stdout, "CPF NAO CADASTRADO \n");
    }
    else
    {
        fprintf(stdout, "ASSOCIADO NA POSICAO %d\n", seq + 1);
        arquivo = fopen("outputfile.txt", "rb");
        if (arquivo == NULL)
        {
            system("color 4f");
            fprintf(stdout, "ERRO AO ABRIR ARQUIVO\n\a");
        }
        else
        {
            // posiciona no arquivo
            if (fseek(arquivo, seq * sizeof(associado), SEEK_SET) == 0)
            {
                // ler os dados
                if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
                {
                    fprintf(stdout, " CPF: %s\n", associado.cpf);
                    fprintf(stdout, " Endereco: %s\n", associado.endereco);
                    fprintf(stdout, " Nome: %s\n", associado.nome);
                }
            }
            fclose(arquivo);
        }
    }
    _getch();
}

void altera(void)
{
    int seq;
    char cpf[11];
    FILE* arquivo;
    struct dados associado;
    char opcao;
    system("cls");
    printf(" CPF DO ASSOCIADO A ALTERAR: ");
    scanf("%s", &cpf);
    seq = posicao(cpf);
    if (seq == -1)
    {
        system("color 4f");
        fprintf(stdout, "CPF NAO CADASTRADO! \n\a");
    }
    else
    {
        fprintf(stdout, " ASSOCIADO NA POSICAO %d\n", seq + 1);
        arquivo = fopen("outputfile.txt", "r+b");
        if (arquivo == NULL)
        {
            system("color 4f");
            fprintf(stdout, "ERRO AO ABRIR ARQUIVO\n\a");
        }
        else
        {
            // posiciona-se no arquivo
            if (fseek(arquivo, seq * sizeof(associado), SEEK_SET) == 0)
            {
                // lê os dados
                if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
                {
                    fprintf(stdout, " CPF: %s\n", associado.cpf);
                    fprintf(stdout, " ENDERECO: %s\n", associado.endereco);
                    fprintf(stdout, " NOME: %s\n", associado.nome);
                }
                system("color 0e");
                printf("TEM CERTEZA QUE DESESA ALTERAR OS DADOS DE %s ? S/N",associado.nome);
                opcao = toupper(_getch());
                system("color 0b");
                if (opcao == 'S')
                {
                    printf("\nALTERAR O NOME DO ASSOCIADO  S/N?");
                    fflush(stdin);
                    opcao = toupper(_getch());
                    if (opcao == 'S')
                    {
                        printf("\nINFORME O NOME: ");
                        fgets(associado.nome, sizeof(associado.nome), stdin);
                    }
                    printf("\nALTERA O ENDERECO DO ASSOCIADO   S/N?");
                    opcao = toupper(_getch());
                    if (opcao == 'S')
                    {
                        printf("\nINFORME O NOVO ENDERECO: ");
                        scanf("%s", &associado.endereco);
                    }
                    // posiciona no arquivo
                    if (fseek(arquivo, seq * sizeof(associado), SEEK_SET) == 0)
                    {
                        if (fwrite(&associado, sizeof(associado), 1, arquivo) == 1)
                        {
                            system("color 2");
                            printf("\nALTERACAO REALIZADA COM SUCESSO\n\a");
                        }
                        else
                        {
                            system("color 4f");
                            printf("\nERRO AO REGRAVAR OS DADOS DO ASSOCIADO\n");
                        }
                    }
                }
            }
            fclose(arquivo);
        }
    }
    _getch();
}

void apaga()
{
    int seq, existeErro;
    FILE* arquivo, * temp;
    struct dados associado;
    char opcao;
    char cpf[11];

    system("cls");
    printf(" CPF DO ASSOCIADO A SER EXCLUIDO: ");
    scanf("%s", &cpf);
    seq = posicao(cpf);
    if (seq == -1)
    {
        system("color 4f");
        printf("\nERRO AO REGRAVAR OS DADOS DO ASSOCIADO\n");
        fprintf(stdout, " CPF NAO CADASTRADO \n");
    }
    else
    {
        fprintf(stdout, " ASSOCIADO NA POSICAO %d\n", seq + 1);
        arquivo = fopen("outputfile.txt", "rb");
        if (arquivo == NULL)
        {
            system("color 4f");
            fprintf(stdout, "ERRO AO ABRIR ARQUIVO\n");
        }
        else
        {
            // posiciona no arquivo
            if (fseek(arquivo, seq * sizeof(associado), SEEK_SET) == 0)
            {
                // ler os dados
                if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
                {
                    fprintf(stdout, " CPF: %s\n", associado.cpf);
                    fprintf(stdout, " ENDERECO: %s\n", associado.endereco);
                    fprintf(stdout, " NOME: %s\n", associado.nome);
                }
                system("color 0e");
                printf("TEM CERTEZA QUE DESEJA EXLUIR %s?",associado.nome);
                opcao = toupper(_getch());
                if (opcao == 'S')
                {
                    // cria um novo arquivo temporário
                    temp = fopen("temp.txt", "wb");
                    if (temp == NULL)
                    {
                        system("color 4f");
                        fprintf(stdout, " ERRO AO CRIAR ARQUIVO TEMPORARIO \n");
                        fprintf(stdout, " EXCLUSAO NAO FOI POSSIVEL\n");
                    }
                    else
                    {
                        existeErro = 0;
                        // reposiciona o arquivo no comeco
                        rewind(arquivo);
                        while (!feof(arquivo))
                        {
                            if (fread(&associado, sizeof(associado), 1, arquivo) == 1)
                            {
                                if (strcmp(associado.cpf,cpf) != 0)
                                {
                                    if (fwrite(&associado, sizeof(associado), 1, temp) == 0)
                                    {
                                        existeErro = 1;
                                        system("color 4f");
                                        printf(" ERRO AO COPIAR DADOS PARA ARQUIVO TEMPORARIO\n");
                                    }
                                }
                            }
                        }
                        // fecha os arquivos
                        if (fclose(arquivo) == 0)
                        {
                            if (fclose(temp) == 0)
                            {
                                if (existeErro == 0)
                                {
                                    // remove o arquivo original     
                                    if (remove("outputfile.txt") == 0)
                                    {
                                        if (rename("temp.txt", "outputfile.txt") == 0)
                                        {
                                            system("color 2");
                                            fprintf(stdout, " EXCLUSAO REALIZADA COM SUCESSO\n");
                                        }
                                        else
                                        {
                                            existeErro = 1;
                                            system("color 4f");
                                            printf(" ERRO AO RENOMEAR ARQUIVO\n");
                                            perror(" Erro no rename");
                                        }
                                    }
                                    else
                                    {
                                        existeErro = 1;
                                        system("color 4f");
                                        perror(" ERRO AO REMOVER ARQUIVO");
                                    }

                                }
                            }
                            else
                            {
                                system("color 4f");
                                printf(" ERRO AO FECHAR ARQUIVO (temp)\n");
                                existeErro = 1;
                            }
                        }
                        else
                        {
                            existeErro = 1;
                            system("color 4f");
                            printf(" ERRO AO FECHAR ARQUIVO (arquivo)\n");
                        }

                        if (existeErro == 1)
                        {
                            system("color 4f");
                            fprintf(stdout, " ERRO AO EXCLUIR ASSOCIADO\n");
                        }
                    }
                }
            }
        }
    }
    _getch();
}
