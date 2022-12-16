// ESTOQUE
// Listar os itens em estoque
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "dados.h"
#include "compras.h"

#define SUCESSO 0
#define FILE_NOT_FOUND_ERROR -1

void encerrar(tipoDados* dados, tipoCompras* compras) {
    encerrarCompras(compras);
    encerrarDados(dados);
}

void mostraEstoque(FILE* fp) {

    char nomeProduto[40];

    float valorProduto;
    int codigoProduto, qntdProduto;
    // se o começo da linha não for o inicio do codigo, leia o nome do produto

    while (feof(fp) == 0) {
        char aux;
        aux = fgetc(fp);
        strcpy(nomeProduto, "");
        if (aux >= 49 && aux <= 57) {
            fseek(fp, -1, SEEK_CUR);
            fscanf(fp, "%i", &codigoProduto);
            fscanf(fp, "%f", &valorProduto);
            fscanf(fp, "%i", &qntdProduto);
            fgets(nomeProduto, 40, fp);
            nomeProduto[strlen(nomeProduto) - 1] = '\0';
            printf("Restam %i unidades de '%s'\n", qntdProduto, nomeProduto);
        }
    }
    fclose(fp);
}

int main(int argv, char** argc) {

	FILE* fpDados = fopen("dados.txt", "r");
	FILE* fpCompras = fopen("compras.txt", "r");
    int opcaoMenuSwitch = 0;


    int codigoInserir, qntdInserir;
    float valorInserir;
    char descInserir[40];
    
    setlocale(LC_CTYPE, "Portuguese");

    if (fpDados == NULL || fpCompras == NULL) return FILE_NOT_FOUND_ERROR;

    tipoDados* dados = leArquivoDados(fpDados);
    tipoCompras* compras = leArquivoCompras(fpCompras);

    fclose(fpDados);
    fclose(fpCompras);

    //Onde vc vai colocar o switch, as funções abaixo são as que você chama no switch;
    
    // listaDados(dados);
    // dados = adicionaItem(dados);
    // compras = realizaCompra(compras, dados);
    // listaCompras(compras);
    // encerrar(dados, compras);

    while (opcaoMenuSwitch < 5) {
        printf("--------------------");
        printf("\nOpcoes: \n");
        printf("1 - Listar estoque\n");
        printf("2 - Adicionar itens ao estoque\n");
        printf("3 - Realizar compras\n");
        printf("4 - Listar compras já realizadas\n");
        printf("5 - Sair do programa\n");
        printf("O que deseja fazer? (digite o numero): ");
        scanf("%i", &opcaoMenuSwitch);
        if (opcaoMenuSwitch == 5) printf("Finalizando o programa.\n");
        if (opcaoMenuSwitch > 5) printf("\nOpcao inexistente. Programa finalizado.\n");
        switch (opcaoMenuSwitch) {
            case 1:
                mostraEstoque(fpDados);
                break;
            case 2:
                printf("Adicione um item novo item (proibido aumentar o estoque!)\n"); 
                printf("Digite, respectivamente, o codigo do item, o valor do item unitariamente (usando ponto), a quantidade a adicionar e a descrição do item.\n");
                printf("Siga o modelo: 231(codigo) 1.99(valor) 1(qntd) arroz e feijao(descricao)\n");
                scanf(" %i %f %i", &codigoInserir, &valorInserir, &qntdInserir);
                fgets(descInserir, 40, stdin);
                descInserir[strlen(descInserir) - 1] = '\0';
                fseek(fpDados, -1, SEEK_END);
                fprintf(fpDados, "%i %.2f %i %s\n", codigoInserir, valorInserir, qntdInserir, descInserir);
                fclose(fpDados);
                break;
        }
    }

    system("pause");

	return SUCESSO;
}