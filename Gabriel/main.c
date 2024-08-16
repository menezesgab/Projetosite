#include "administrador.c"
#include "usuario.c"
#include "produto.c"

void texto_menu_sem_login();
void menu_sem_login();

int main()
{
    int r;
    printf("login como administrador?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf("%i", &r);
    if (r == 1)
    {
        realizar_login_adm();
    }
    else
    {
        menu_sem_login();
    }
}

void texto_menu_adm()
{
    printf("\tAQUELE MERCADINHO LA\n\n");
    printf("\t\tMENU ADMINISTRADOR\n\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Ver produtos\n");
    printf("3 - Editar produto");
    printf("4 - Excluir produto");
    printf("5 - Editar um usuario");
    printf("6 - Excluir um usuario");
    printf("7 - Listar usuarios");
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
            excluir_produto();
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

void texto_menu_sem_login()
{
    printf("\tAQUELE MERCADINHO LA\n\n");
    printf("\t\tMENU\n\n");
    printf("1 - Login\n");
    printf("2 - Cadastrar usuario\n");
    printf("3 - Ver produtos\n");
    printf("4 - Pesquisar produto\n");
    printf("0 - Sair\n");
}

void menu_sem_login()
{
    int op;
    do
    {
        texto_menu_sem_login();
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            realizar_login();
            break;
        case 2:
            realizar_cadastro();
            break;
        case 3:
            listar_produtos();
            break;
        case 4:
            realizar_busca_produto();
            break;
        case 0:
            system("cls");
            printf("Obrigado por utilizar nossos servicos!\n");
            break;
        default:
            break;
        }

    } while (op != 0);
}
