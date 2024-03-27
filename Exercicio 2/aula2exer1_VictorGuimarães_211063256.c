#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 10 // máximo de carros que uma pessoa pode ter
#define MAX_REGISTERS 10000 // número máximo de registros 

// Definição da estrutura para armazenar os dados de uma pessoa
typedef struct {
    char cpf[12]; // Ajuste para 12 para incluir o caractere nulo
    char nome[50];
    char endereco[100];
    char telefone[20];
    int num_carros; //tirar, numero de carros não é atributo de pessoa
} Pessoa;


typedef struct {
    char modelo_carro[50];
    char cor_carro[30];
    char placa_carro[10];
} Carros;

//verifica se há semelhança entre o CPF pretendido a cadastrar com algum previamente cadastrado
int verificaCPF(char *cpf){
    char compare[12];
    FILE *arquivoPessoas = fopen("pessoas.txt", "r");

    while(fgets(compare, 12, arquivoPessoas) != NULL){
        if(strcmp(compare, cpf) == 0){
            printf("CPF ja registrado\n");
            fclose(arquivoPessoas);
            return 0;
        }
    }
    fclose(arquivoPessoas);
    return 1;
}

// Função para cadastrar uma nova pessoa e seus carros
void cadastrar_pessoa() {
    Pessoa pessoa;
    Carros carros;

    FILE *arquivoPessoa;
    FILE *arquivoCarro;

    arquivoPessoa = fopen("pessoas.txt", "a+"); // Modificado para leitura e escrita de texto
    arquivoCarro = fopen("carros.txt", "a+"); // Modificado para leitura e escrita de texto

    printf("Digite o CPF da pessoa: ");
    fgets(pessoa.cpf, 12, stdin);

    if(verificaCPF(pessoa.cpf) == 0){
        exit(1);
    }

    fprintf(arquivoPessoa, "%s\n", pessoa.cpf);
    getchar(); //  limpa o buffer de entrada

    printf("Digite o nome da pessoa: ");
    fgets(pessoa.nome, 50, stdin);
    fprintf(arquivoPessoa, "%s", pessoa.nome);
    
    printf("Digite o Endereco da pessoa: ");
    fgets(pessoa.endereco, 100, stdin);
    fprintf(arquivoPessoa, "%s", pessoa.endereco);

    printf("Digite o telefone da pessoa: ");
    fgets(pessoa.telefone, 20, stdin);
    fprintf(arquivoPessoa, "%s", pessoa.telefone);

    printf("Quantos carros a pessoa possui (max %d)? ", MAX_CARROS);
    scanf("%d", &pessoa.num_carros);
    fprintf(arquivoPessoa, "%d\n", pessoa.num_carros);
    getchar(); //  limpa o buffer de entrada
    
    fprintf(arquivoCarro, ":%s\n", pessoa.cpf);

    for (int i = 0; i < pessoa.num_carros; i++) {

        printf("Digite a placa do carro %d: ", i + 1);
        fgets(carros.placa_carro, 10, stdin);
        fprintf(arquivoCarro, "%s", carros.placa_carro);

        printf("Digite o modelo do carro %d: ", i + 1);
        fgets(carros.modelo_carro, 50, stdin);
        fprintf(arquivoCarro, "%s", carros.modelo_carro);
       
        printf("Digite a cor do carro %d: ", i + 1);
        fgets(carros.cor_carro, 30, stdin);
        fprintf(arquivoCarro, "%s\n", carros.cor_carro);
    }

    fclose(arquivoPessoa);
    fclose(arquivoCarro);
}

// Função auxiliar do bubble sort
void trocar(Pessoa *a, Pessoa *b) {
    Pessoa temp = *a;
    *a = *b;
    *b = temp;
}

// Função para ordenar o arquivo
void bubble_sort(Pessoa vetor[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(vetor[j].cpf, vetor[j+1].cpf) > 0) {
                trocar(&vetor[j], &vetor[j+1]);
            }
        }
    }
}

// Função para listar todas as pessoas cadastradas
void listar_pessoas() {
    Pessoa pessoa;
    Carros carros;
    char cpfDono[12];
    int i;

    FILE *arquivoPessoa = fopen("pessoas.txt", "r"); // Modificado para leitura de texto
    FILE *arquivoCarros = fopen("carros.txt", "r"); // Modificado para leitura de texto

    if (arquivoPessoa == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    if (arquivoCarros == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }


    while (fscanf(arquivoPessoa, "%[^\n]%*c", pessoa.cpf) == 1) {
        fscanf(arquivoPessoa, "%[^\n]%*c", pessoa.nome);
        fscanf(arquivoPessoa, "%[^\n]%*c", pessoa.endereco);
        fscanf(arquivoPessoa, "%[^\n]%*c", pessoa.telefone);
        fscanf(arquivoPessoa, "%d%*c", &pessoa.num_carros);
        printf("Nome: %s\n", pessoa.nome);
        printf("CPF: %s\n", pessoa.cpf);
        printf("Endereco: %s\n", pessoa.endereco);
        printf("Telefone: %s\n", pessoa.telefone);
        printf("Quantidade de carros: %d\n\n", pessoa.num_carros);
        printf("\n");
    }

    fclose(arquivoPessoa);
}


// Lê o arquivo e transforma em vetor -> organiza o vetor -> printa no arquivo
void ordena(FILE *arquivo){
    int i = 0;
    Pessoa person[MAX_REGISTERS]; 
    
    FILE *arquivoPessoa = fopen("pessoas.txt", "r"); // Modificado para leitura de texto

    if (arquivoPessoa == NULL) {
        printf("Erro ao abrir o arquivo(9).\n");
        exit(1);
    }

    while (fscanf(arquivoPessoa, "%[^\n]%*c", person[i].cpf) == 1) {
        fscanf(arquivoPessoa, "%[^\n]%*c", person[i].nome);
        fscanf(arquivoPessoa, "%[^\n]%*c", person[i].endereco);
        fscanf(arquivoPessoa, "%[^\n]%*c", person[i].telefone);
        fscanf(arquivoPessoa, "%d%*c", &person[i].num_carros);
        i++;
    }
    fclose(arquivoPessoa);

    bubble_sort(person, i);
    arquivoPessoa = fopen("pessoas.txt", "w"); // Modificado para leitura de texto

    for(int j = 0; j < i; j++){
        fprintf(arquivoPessoa, "%s\n", person[j].cpf);
        fprintf(arquivoPessoa, "%s\n", person[j].nome);
        fprintf(arquivoPessoa, "%s\n", person[j].endereco);
        fprintf(arquivoPessoa, "%s\n", person[j].telefone);
        fprintf(arquivoPessoa, "%d\n", person[j].num_carros);
    }
    fclose(arquivoPessoa);
}


int main() {
    int opcao;
    char cpf[12];
    Pessoa pessoa[MAX_REGISTERS];

    FILE *arquivoPessoa;
    FILE *arquivoCarro;
    
    arquivoPessoa = fopen("pessoas.txt", "a+"); // Modificado para leitura e escrita de texto
    arquivoCarro = fopen("carros.txt", "a+"); // Modificado para leitura e escrita de texto

    if (arquivoPessoa == NULL) {
        printf("Erro ao abrir o arquivo2.\n");
        return 1;
    }

    if (arquivoCarro == NULL) {
        printf("Erro ao abrir o arquivo3.\n");
        return 1;
    }
    

    do {
        ordena(arquivoPessoa);
        printf("\n1 - Cadastrar nova pessoa\n");
        printf("2 - Listar todas as pessoas cadastradas\n");
        printf("3 - Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n deixado pelo scanf

        switch (opcao) {
            case 1:
                system("cls");
                printf("(  Cadastrar Pessoa  )\n\n");
                cadastrar_pessoa();
                printf("Pessoa cadastrada com sucesso!\n");
                break;
            case 2:
                system("cls");
                printf("(  Listagem de Pessoas  )\n\n");
                listar_pessoas();
                break;
            case 3:
                printf("Encerrando o programa...\n");
                return 0;
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 3);

    fclose(arquivoPessoa);
    fclose(arquivoCarro);

    return 0;
}
