#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
struct produto
{
    char *nome;
    float preco;
    int ID;
};
struct produto *verificar_produto(int ID);
void listar_produtos();
int buscar_produto(int ID);
void realizar_busca_produto();
struct produto *criar_produto(char *nome, float preco, int ID);
void realizar_cadastro_produto();
int cadastrar_produto(char *nome, float preco, int ID);
void editar_produto();
void remover_produto();
int partition_produtos(struct produto produtos[], int low, int high);
void swap_produtos(struct produto *a, struct produto *b);
void quicksort_produtos(struct produto produtos[], int low, int high);
int busca_binaria_produtos(struct produto produtos[], int total, int ID);
void gravar_produtos(struct produto produtos[], int total);
void ler_produtos(struct produto produtos[], int *total);