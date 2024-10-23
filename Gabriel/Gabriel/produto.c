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

void listar_produtos() {
    FILE *arch = fopen("produtos.txt", "r");
    if (arch == NULL) {
        exit(EXIT_FAILURE);
    }

    char nome[MAX_LEN];
    float valor;
    int IDaux;

    // Estruturas de nó para produtos
    struct NodeProduto *head = NULL;
    struct NodeProduto *tail = NULL;

    // Carregar os produtos da entrada
    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &valor, &IDaux) == 3) {
        // Criar a estrutura produto
        struct produto *prod = (struct produto *)malloc(sizeof(struct produto));
        prod->nome = (char *)malloc((strlen(nome) + 1) * sizeof(char));
        strcpy(prod->nome, nome);
        prod->preco = valor;
        prod->ID = IDaux;

        // Criar um nó para armazenar o produto
        struct NodeProduto *novo_no = (struct NodeProduto *)malloc(sizeof(struct NodeProduto));
        novo_no->prod = prod;
        novo_no->next = NULL;

        // Inserir o nó na lista
        if (head == NULL) {
            head = novo_no;
            tail = novo_no;
        } else {
            tail->next = novo_no;
            tail = novo_no;
        }
    }

    fclose(arch);

    // Exibir os itens da lista
    struct NodeProduto *current = head;
    while (current != NULL) {
        // Usando os valores armazenados na estrutura
        printf("nome do produto: %s\n", current->prod->nome);
        printf("valor: %f\n", current->prod->preco);
        printf("ID: %i\n", current->prod->ID);
        current = current->next; // Avançar para o próximo nó
    }

    // Liberar a memória usada pela lista
    current = head;
    while (current != NULL) {
        struct NodeProduto *temp = current;
        current = current->next;
        free(temp->prod->nome);
        free(temp->prod);
        free(temp);
    }
}

void adicionar_produto(char *nome, float preco, int ID) {
    struct NodeProduto *novo_no = (struct NodeProduto *)malloc(sizeof(struct NodeProduto));
    novo_no->prod = (struct produto *)malloc(sizeof(struct produto));
    novo_no->prod->nome = strdup(nome);
    novo_no->prod->preco = preco;
    novo_no->prod->ID = ID;
    novo_no->next = head;
    head = novo_no;
}

void popular_lista_produtos(const char *filename) {
    FILE *arch = fopen(filename, "r");
    if (arch == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename);
        return;
    }

    char nome[MAX_LEN];
    float valor;
    int ID;

    // Lê cada produto do arquivo e adiciona à lista
    while (fscanf(arch, "nome do produto: %99[^\n]\nvalor: %f\nID: %i\n", nome, &valor, &ID) == 3) {
        adicionar_produto(nome, valor, ID);
    }

    fclose(arch);
}


void realizar_busca_produto() {
    int ID;
    struct NodeProduto *resultado;
    
    popular_lista_produtos("produtos.txt");

    printf("Insira o ID do produto a ser buscado: ");
    scanf("%i", &ID);

    // Chama a função de busca na lista
    resultado = buscar_produto_na_lista(ID);

    if (resultado == NULL) {
        printf("Produto não encontrado\n");
    } else {
        printf("Produto encontrado:\n");
        printf("nome do produto: %s\n", resultado->prod->nome);
        printf("valor: %f\n", resultado->prod->preco);
        printf("ID: %i\n", resultado->prod->ID);
    }
}


// Função para buscar um produto na lista encadeada
struct NodeProduto *buscar_produto_na_lista(int ID) {
    struct NodeProduto *atual = head;
    while (atual != NULL) {
        if (atual->prod->ID == ID) {
            return atual; // Retorna o nó se o produto for encontrado
        }
        atual = atual->next; // Avança para o próximo nó
    }
    return NULL; // Retorna NULL se o produto não for encontrado
}


void editar_produto() {
    popular_lista_produtos("produtos.txt"); // Popular a lista no início

    int ID;
    char nome[MAX_LEN];
    float preco;

    printf("Insira o ID do produto a ser editado: ");
    scanf("%d", &ID);

    struct NodeProduto *atual = head; // Usa o head global

    // Procura pelo produto na lista encadeada
    while (atual != NULL) {
        if (atual->prod->ID == ID) {
            printf("Produto encontrado! Insira os novos dados:\n");

            printf("Novo nome do produto: ");
            scanf(" %[^\n]", nome);
            printf("Novo valor do produto: ");
            scanf("%f", &preco);

            // Atualiza os dados do produto
            free(atual->prod->nome); // Libera a memória anterior
            atual->prod->nome = strdup(nome); // Aloca novo espaço para o nome
            atual->prod->preco = preco;

            printf("Produto atualizado com sucesso!\n");
            gravar_produtos(); // Grava os produtos atualizados no arquivo
            return; // Sai da função após a atualização
        }
        atual = atual->next; // Avança para o próximo nó
    }

    printf("Produto com ID %d não encontrado.\n", ID);
}




void remover_produto() {
    int ID;

    // A função de popular a lista deve ser chamada antes de remover
    popular_lista_produtos("produtos.txt");

    struct NodeProduto *atual = head; // Usa a cabeça da lista global
    struct NodeProduto *anterior = NULL; // Ponteiro para o nó anterior
    printf("Insira o ID do produto a ser removido: ");
    scanf("%d", &ID);

    // Procura pelo produto na lista encadeada
    while (atual != NULL) {
        if (atual->prod->ID == ID) {
            // Produto encontrado
            printf("Produto com ID %d encontrado e removido.\n", ID);

            if (anterior == NULL) {
                // O produto a ser removido é o primeiro da lista
                head = atual->next; // Atualiza a cabeça da lista
            } else {
                // Remove o produto da lista
                anterior->next = atual->next;
            }

            // Libera a memória do produto e do nó
            free(atual->prod->nome); // Libera o nome do produto
            free(atual->prod); // Libera o objeto produto
            free(atual); // Libera o nó da lista

            // Grava a lista atualizada no arquivo
            gravar_produtos(); // Esta função deve gravar a lista atualizada no arquivo
            return; // Sai da função após a remoção
        }

        anterior = atual; // Avança o ponteiro anterior
        atual = atual->next; // Avança para o próximo nó
    }

    printf("Produto com ID %d não encontrado.\n", ID);
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

void gravar_produtos() {
    FILE *arch = fopen("produtos.txt", "w");
    if (arch == NULL) {
        perror("Erro ao abrir o arquivo para gravação");
        exit(EXIT_FAILURE);
    }

    struct NodeProduto *atual = head; // Usa a cabeça da lista global

    // Percorre a lista encadeada e grava os dados de cada produto
    while (atual != NULL) {
        fprintf(arch, "nome do produto: %s\nvalor: %.2f\nID: %d\n", atual->prod->nome, atual->prod->preco, atual->prod->ID);
        atual = atual->next; // Avança para o próximo nó
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

