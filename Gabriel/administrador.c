#include "administrador.h"
struct administrador
{
    char *nome;
    char *senha;
};

void texto_menu_adm()
{
    printf("\tAQUELE MERCADINHO LA\n\n");
    printf("\t\tMENU ADMINISTRADOR\n\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Ver produtos\n");
    printf("3 - Editar produto\n");
    printf("4 - Excluir produto\n");
    printf("5 - Editar um usuario\n");
    printf("6 - Excluir um usuario\n");
    printf("7 - Listar usuarios\n");
    printf("0 - Sair\n");
}

void menu_adm()
{
    int op;
    do
    {
        texto_menu_adm();
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            realizar_cadastro_produto();
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            editar_produto();
            break;
        case 4:
            remover_produto();
            break;
        case 5:
            editar_usuario();
            break;
        case 6:
            excluir_usuario();
            break;
        case 7:
            listar_usuarios();
        case 0:
            system("cls");
            printf("Obrigado por utilizar nossos servicos!\n");
            break;
        default:
            break;
        }

    } while (op != 0);
}

void realizar_login_adm()
{
    char *nome = (char *)malloc(30 * sizeof(char));
    char *senha = (char *)malloc(30 * sizeof(char));
    struct administrador *usuario = NULL;
    printf("Insira o usuario: \n");
    scanf("%s", nome);
    printf("Insira a senha: \n");
    scanf("%s", senha);
    usuario = login_como_adm(nome, senha);

    if (usuario != NULL)
    {
        if ((strcmp(usuario->nome, nome) && strcmp(usuario->senha, senha)) == 0)
        {
            printf("Logado com sucesso!\n");
            menu_adm();
        }
        else
        {
            printf("Senha e/ou email incorretos\n");
        }
    }
    else
    {
        printf("Nenhum usuario encontrado\n");
    }
}

struct administrador *verificar_administrador(char *nome, char *senha)
{
    FILE *arch = fopen("administradores.txt", "r");
    if (arch == NULL)
    {
        exit(EXIT_FAILURE);
    }
    char nomeAux[MAX_LEN];
    char senhaAux[MAX_LEN];
    while (fscanf(arch, "usuario: %99[^\n]\nsenha: %99[^\n]\n", nomeAux, senhaAux) == 2)
    {
        if ((strcmp(nomeAux, nome)) == 0)
        {

            struct administrador *aux = criar_administrador(nomeAux, senhaAux);
            fclose(arch);
            return aux;
        }
    }

    fclose(arch);
    return NULL;
}

struct administrador *login_como_adm(char *nome, char *senha)
{

    struct administrador *administrador_de_login;

    administrador_de_login = verificar_administrador(nome, senha);
    if (administrador_de_login != NULL)
    {
        if (strcmp(administrador_de_login->nome, nome) == 0)
        {
            return administrador_de_login;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

struct administrador *criar_administrador(char *nome, char *senha)
{
    struct administrador *novo = (struct administrador *)malloc(sizeof(struct administrador));
    novo->nome = (char *)malloc(30 * sizeof(char));
    novo->senha = (char *)malloc(30 * sizeof(char));
    strcpy(novo->nome, nome);
    strcpy(novo->senha, senha);
    return novo;
}