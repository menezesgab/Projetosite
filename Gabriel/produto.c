#include "produto.h"

struct produto
{
    char *nome;
    float preco;
    int ID;
};

struct produto *criar_produto(char *nome, float preco, int ID)
{
    struct produto *novo = (struct produto *)malloc(sizeof(struct produto));
    novo->nome = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    novo->preco = preco;
    novo->ID = ID;
    strcpy(novo->nome, nome);
    return novo;
}

void realizar_cadastro_produto()
{
    char *nome = (char *)malloc(30 * sizeof(char));
    float preco;
    int ID;
    printf("Insira o nome do produto: ");
    scanf("%s", nome);
    printf("Insira o nome do valor de venda do produto: ");
    scanf("%f", preco);
    printf("Insira o ID para o produto: ");
    scanf("%i", ID);
    cadastrar_produto(nome, preco, ID);
}

int cadastrar_produto(char *nome, float preco, int ID)
{
    struct produto *novo;
    novo = criar_produto(nome, preco, ID);
    FILE *arch = fopen("produtos.txt", "a");
    if (arch == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (verificar_produto(novo->ID) != NULL)
    {
        system("cls");
        printf("Produto ja cadastrado no sistema\n");
        return -1;
    }
    else
    {
        fprintf(arch, "nome do produto: %s\nvalor: %f\nID: %i\n", novo->nome, novo->preco, novo->ID);
        return 0;
    }
}

struct produto *verificar_produto(int ID)
{
    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char nome[MAX_LEN];
    float valor;
    int IDaux;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &valor, &IDaux) == 3)
    {
        if (IDaux == ID)
        {
            struct produto *aux = criar_produto(nome, valor, IDaux);
            fclose(arch);
            return aux;
        }
    }

    fclose(arch);
    return NULL;
}

void listar_produtos()
{
    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char nome[MAX_LEN];
    float valor;
    int IDaux;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &valor, &IDaux) == 3)
    {
        printf("nome do produto: %s\nvalor: %f\nID: %i\n", nome, valor, IDaux);
    }

    fclose(arch);
}

void realizar_busca_produto()
{
    int ID;
    int verificador;
    printf("Insira o ID do produto a ser buscado\n");
    scanf("%i", &ID);
    verificador = buscar_produto(ID);
    if (verificador == 1)
    {
        printf("Produto não encontrado\n");
    }
}

int buscar_produto(int ID)
{
    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char nome[MAX_LEN];
    float valor;
    int IDaux;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &valor, &IDaux) == 3)
    {
        if (IDaux == ID)
        {
            printf("nome do produto: %s\nvalor: %f\nID: %i\n", nome, valor, IDaux);
            return 0;
        }
    }

    fclose(arch);
    return 1;
}

void editar_produto()
{
    int ID;
    char nome[MAX_LEN];
    float preco;
    int encontrado = 0;

    printf("Insira o ID do produto a ser editado: ");
    scanf("%d", &ID);

    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    FILE *temp = fopen("produtos_temp.txt", "w");
    if (temp == NULL)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(arch);
        exit(EXIT_FAILURE);
    }

    char nome_temp[MAX_LEN];
    float preco_temp;
    int ID_temp;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome_temp, &preco_temp, &ID_temp) == 3)
    {
        if (ID_temp == ID)
        {
            encontrado = 1;
            printf("Produto encontrado! Insira os novos dados:\n");

            printf("Novo nome do produto: ");
            scanf(" %[^\n]", nome);
            printf("Novo valor do produto: ");
            scanf("%f", &preco);

            fprintf(temp, "nome do produto: %s\nvalor: %f\nID: %i\n", nome, preco, ID);
        }
        else
        {
            fprintf(temp, "nome do produto: %s\nvalor: %f\nID: %i\n", nome_temp, preco_temp, ID_temp);
        }
    }

    if (!encontrado)
    {
        printf("Produto com ID %d não encontrado.\n", ID);
    }

    fclose(arch);
    fclose(temp);

    if (remove("produtos.txt") != 0)
    {
        perror("Erro ao remover o arquivo original");
        exit(EXIT_FAILURE);
    }

    if (rename("produtos_temp.txt", "produtos.txt") != 0)
    {
        perror("Erro ao renomear o arquivo temporário");
        exit(EXIT_FAILURE);
    }
}

void excluir_produto()
{
    int ID;
    int encontrado = 0;

    printf("Insira o ID do produto a ser excluído: ");
    scanf("%d", &ID);

    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    FILE *temp = fopen("produtos_temp.txt", "w");
    if (temp == NULL)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(arch);
        exit(EXIT_FAILURE);
    }

    char nome[MAX_LEN];
    float preco;
    int ID_temp;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &preco, &ID_temp) == 3)
    {
        if (ID_temp == ID)
        {
            encontrado = 1;
            printf("Produto com ID %d foi excluído.\n", ID);
            continue;
        }

        fprintf(temp, "nome do produto: %s\nvalor: %f\nID: %i\n", nome, preco, ID_temp);
    }

    if (!encontrado)
    {
        printf("Produto com ID %d não encontrado.\n", ID);
    }

    fclose(arch);
    fclose(temp);

    if (remove("produtos.txt") != 0)
    {
        perror("Erro ao remover o arquivo original");
        exit(EXIT_FAILURE);
    }

    if (rename("produtos_temp.txt", "produtos.txt") != 0)
    {
        perror("Erro ao renomear o arquivo temporário");
        exit(EXIT_FAILURE);
    }
}