#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
struct produto;
struct produto *verificar_produto(int ID);
void listar_produtos();
int buscar_produto(int ID);
void realizar_busca_produto();
struct produto *criar_produto(char *nome, float preco, int ID);
void realizar_cadastro_produto();
int cadastrar_produto(char *nome, float preco, int ID);
void editar_produto();
void excluir_produto();