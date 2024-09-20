#include "produto.h"
#define MAX_LEN 100


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
    char nome[MAX_LEN]; 
    float preco;
    int ID;

    printf("Insira o nome do produto: ");
    scanf(" %[^\n]", nome);
    printf("Insira o valor de venda do produto: ");
    scanf("%f", &preco);
    printf("Insira o ID para o produto: ");
    scanf("%d", &ID);

    if (cadastrar_produto(nome, preco, ID) == 0)
    {
        printf("Produto cadastrado com sucesso!\n");
    }
    else
    {
        printf("Falha ao cadastrar o produto.\n");
    }
}


int cadastrar_produto(char *nome, float preco, int ID)
{
    
    struct produto *novo = criar_produto(nome, preco, ID);
    if (novo == NULL)
    {
        printf("Erro ao criar o produto.\n");
        return -1;
    }

    if (verificar_produto(novo->ID) != NULL)
    {
        printf("Produto já cadastrado no sistema.\n");
        free(novo);  
        return -1;
    }

   
    FILE *arch = fopen("produtos.txt", "a");
    if (arch == NULL)
    {
        perror("Erro ao abrir o arquivo");
        free(novo); 
        return -1;
    }

    fprintf(arch, "nome do produto: %s\nvalor: %.2f\nID: %d\n", novo->nome, novo->preco, novo->ID);
    fclose(arch);  

    free(novo);  
    return 0;
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
    int total = 0;
    struct produto produtos[MAX_LEN] = {0};

    ler_produtos(produtos, &total);
    quicksort_produtos(produtos, 0, total - 1);

    printf("Insira o ID do produto a ser editado: ");
    scanf("%d", &ID);

    int indice = busca_binaria_produtos(produtos, total, ID);

    if (indice != -1)
    {
        printf("Produto encontrado! Insira os novos dados:\n");

        printf("Novo nome do produto: ");
        scanf(" %[^\n]", nome);
        printf("Novo valor do produto: ");
        scanf("%f", &preco);

        free(produtos[indice].nome);
        produtos[indice].nome = strdup(nome);
        produtos[indice].preco = preco;

        gravar_produtos(produtos, total);
    }
    else
    {
        printf("Produto com ID %d não encontrado.\n", ID);
    }
}



void remover_produto()
{
    int ID;
    int total = 0;
    struct produto produtos[MAX_LEN] = {0};

    ler_produtos(produtos, &total);
    quicksort_produtos(produtos, 0, total - 1);

    printf("Insira o ID do produto a ser removido: ");
    scanf("%d", &ID);

    int indice = busca_binaria_produtos(produtos, total, ID);

    if (indice != -1)
    {
        printf("Produto com ID %d encontrado e removido.\n", ID);

        for (int i = indice; i < total - 1; i++)
        {
            produtos[i] = produtos[i + 1];
        }

        total--;

        gravar_produtos(produtos, total);
    }
    else
    {
        printf("Produto com ID %d não encontrado.\n", ID);
    }
}



void quicksort_produtos(struct produto produtos[], int low, int high)
{
    if (low < high)
    {
        int pi = partition_produtos(produtos, low, high);
        quicksort_produtos(produtos, low, pi - 1);
        quicksort_produtos(produtos, pi + 1, high);
    }
}

int partition_produtos(struct produto produtos[], int low, int high)
{
    int pivot = produtos[high].ID;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (produtos[j].ID < pivot)
        {
            i++;
            swap_produtos(&produtos[i], &produtos[j]);
        }
    }
    swap_produtos(&produtos[i + 1], &produtos[high]);
    return (i + 1);
}

void swap_produtos(struct produto *a, struct produto *b)
{
    struct produto temp = *a;
    *a = *b;
    *b = temp;
}

int busca_binaria_produtos(struct produto produtos[], int total, int ID)
{
    int low = 0;
    int high = total - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (produtos[mid].ID == ID)
        {
            return mid; 
        }

        if (produtos[mid].ID < ID)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1; 
}

void gravar_produtos(struct produto produtos[], int total)
{
    FILE *arch = fopen("produtos.txt", "w");
    if (arch == NULL)
    {
        perror("Erro ao abrir o arquivo para gravação");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < total; i++)
    {
        fprintf(arch, "nome do produto: %s\nvalor: %.2f\nID: %d\n", produtos[i].nome, produtos[i].preco, produtos[i].ID);
    }

    fclose(arch);
}

void ler_produtos(struct produto produtos[], int *total)
{
    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char nome_temp[MAX_LEN];
    float preco_temp;
    int ID_temp;

    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %d\n", nome_temp, &preco_temp, &ID_temp) == 3)
    {
        produtos[i].nome = strdup(nome_temp);
        produtos[i].preco = preco_temp;
        produtos[i].ID = ID_temp;
        i++;
    }

    *total = i;
    fclose(arch);
}

