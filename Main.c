#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "dados.h"

#define SUCESSO 0
#define FILE_NOT_FOUND_ERROR -1
#define TAM_MAX_DESC (1000 * sizeof(char))
#define TAM_MAX_COD (5 * sizeof(char))


typedef struct Compras {
	char Codigo[TAM_MAX_COD];
	int NumItens;
	int* CodigoItens;
	float* ValorUnitario;
	int* QntItem;

	int NumCompras;
} tipoCompras;

tipoDados* leArquivoDados(FILE* f);
tipoDados* realocarDados(tipoDados*);

tipoCompras* leArquivoCompras(FILE* f);
tipoCompras* realocarCompras(tipoCompras*);

void listaDados(tipoDados* dados);
void listaCompras(tipoCompras* compras);

tipoDados* adicionaItem(tipoDados* dados);
tipoCompras* realizaCompra(tipoCompras* compras, tipoDados* dados);

void encerrar(tipoDados* dados, tipoCompras* compras);
void encerrarDados(tipoDados* dados);
void encerrarCompras(tipoDados* compras);


tipoDados* leArquivoDados(FILE* f) {
	tipoDados* dados;
	int i;

	dados = (tipoDados*)malloc(sizeof(tipoDados));

	for (i = 0; !feof(f); i++)
	{

		fscanf(f, "%i %f %i ", &dados[i].Codigo, &dados[i].ValorUnitario, &dados[i].Estoque);

		
		fgets(dados[i].Descricao, TAM_MAX_DESC, f);

		if (!feof(f))
		{
			dados = realocarDados(dados, i + 1);
		}
		

	}
	dados->NumDados = i;
	
	return dados;
}

tipoDados* realocarDados(tipoDados* dados, int numDados) {

	tipoDados* dadosNovo = (tipoDados*)malloc(sizeof(tipoDados) * (numDados + 1));


	for (int i = 0; i < numDados; i++)
	{
		dadosNovo[i].Codigo = dados[i].Codigo;
		memcpy(dadosNovo[i].Descricao, dados[i].Descricao, TAM_MAX_DESC);
		dadosNovo[i].Estoque = dados[i].Estoque;
		dadosNovo[i].ValorUnitario = dados[i].ValorUnitario;
	}
	dadosNovo->NumDados = (numDados + 1);

	free(dados);
	return dadosNovo;

}


tipoCompras* leArquivoCompras(FILE* f) {
	tipoCompras* compras;
	int i;

	compras = (tipoCompras*)malloc(sizeof(tipoCompras));

	for (i = 0; !feof(f); i++)
	{
		fgets(compras[i].Codigo, TAM_MAX_COD, f);

		fscanf(f, "%i", &compras[i].NumItens);

		compras[i].CodigoItens = (int*)malloc(sizeof(int) * compras[i].NumItens);
		compras[i].ValorUnitario = (float*)malloc(sizeof(float) * compras[i].NumItens);
		compras[i].QntItem = (int*)calloc(compras[i].NumItens, sizeof(int));

		for (int j = 0; j < compras[i].NumItens;)
		{
			fscanf(f, "%i ", &compras[i].CodigoItens[j]);
			fscanf(f, "%f ", &compras[i].ValorUnitario[j]);
			fscanf(f, "%i ", &compras[i].QntItem[j]);


			j += compras[i].QntItem[j];
		}
		

		if (!feof(f))
		{
			compras = realocarCompras(compras, i + 1);
		}


	}
	compras->NumCompras = i;

	return compras;
}

tipoCompras* realocarCompras(tipoCompras* compras, int numCompras) {


	
	tipoCompras* comprasNovo = (tipoCompras*)malloc(sizeof(tipoCompras) * (numCompras + 1));


	for (int i = 0; i < numCompras; i++)
	{
		memcpy(comprasNovo[i].Codigo, compras[i].Codigo, TAM_MAX_COD);
		comprasNovo[i].NumItens = compras[i].NumItens;
		
		
		comprasNovo[i].CodigoItens = compras[i].CodigoItens;
		comprasNovo[i].ValorUnitario = compras[i].ValorUnitario;
		comprasNovo[i].QntItem = compras[i].QntItem;

	}
	comprasNovo->NumCompras = (numCompras + 1);

	free(compras);
	return comprasNovo;
}


void listaDados(tipoDados* dados) {

	for (int i = 0; i < dados->NumDados; i++)
	{
		fputs(dados[i].Descricao, stdout);
		printf("\nCodigo: %i\n", dados[i].Codigo);
		printf("Valor unitario: %f\n", dados[i].ValorUnitario);
		printf("Estoque: %i\n\n", dados[i].Estoque);
	}
	


}
void listaCompras(tipoCompras* compras) {

	for (int i = 0; i < compras->NumCompras; i++)
	{
		printf("\nCodigo da compra: ");
		fputs(compras[i].Codigo, stdout);

		printf("\nNum. de itens na compra: %i\n", compras[i].NumItens);

		for (int j = 0, k = 1; j < compras[i].NumItens; k++)
		{
			printf("\nItem %i:", k);
			printf("\nCodigo: %i\n", compras[i].CodigoItens[j]);
			printf("Valor unitario: %f\n", compras[i].ValorUnitario[j]);
			printf("Estoque: %i\n\n", compras[i].QntItem[j]);



			j += compras[i].QntItem[j];
		}
		
	}
}

tipoDados* adicionaItem(tipoDados* dados) {
	int codigo, qnt = 0;
	float valor = 0;
	char desc[TAM_MAX_DESC];

	printf("Codigo do item: ");
	scanf("%i", &codigo);

	for (int i = 0; i < dados->NumDados; i++)
	{
		if (codigo == dados[i].Codigo)
		{
			printf("Digite a quantidade que voce deseja adicionar ao estoque: ");
			scanf("%i", &qnt);
			dados[i].Estoque += qnt;

			return dados;
		}
	}
	dados = realocarDados(dados, dados->NumDados);
	int index = dados->NumDados - 1;

	printf("Digite a descricao do item: ");
	getchar();
	fgets(desc, TAM_MAX_DESC, stdin);

	printf("Digite o valor unitario do item: ");
	scanf("%f", &valor);
	printf("Digite a quantidade que voce deseja adicionar ao estoque: ");
	scanf("%i", &qnt);

	dados[index].Codigo = codigo;
	memcpy(dados[index].Descricao, desc, TAM_MAX_DESC);
	dados[index].ValorUnitario = valor;
	dados[index].Estoque = qnt ;

	return dados;
}
tipoCompras* realizaCompra(tipoCompras* compras, tipoDados* dados) {
	
	compras = realocarCompras(compras, compras->NumCompras);

	int index = compras->NumCompras - 1;

	char c[5];
	if (index < 10)
	{
		sprintf(c, "c00%i", index);
	}
	else if(index < 100)
	{
		sprintf(c, "c0%i", index);
	}
	else
	{
		sprintf(c, "c%i", index);
	}
	memcpy(compras[index].Codigo, c, 5);


	printf("\nDigite o num. de itens na compra:");
	scanf("%i", &compras[index].NumItens);

	compras[index].CodigoItens = (int*)malloc(sizeof(int) * compras[index].NumItens);
	compras[index].ValorUnitario = (float*)malloc(sizeof(float) * compras[index].NumItens);
	compras[index].QntItem = (int*)calloc(compras[index].NumItens, sizeof(int));


	for (int j = 0, k = 0; j < compras[index].NumItens; k++)
	{
		int codigoValido = 1;
		do
		{
			printf("\nDigite o codigo do item %i: ", k);
			scanf("%i", &compras[index].CodigoItens[j]);

			for (int i = 0; i < dados->NumDados; i++)
			{
				if (compras[index].CodigoItens[j] == dados[i].Codigo)
				{
					codigoValido = 0;
					compras[index].ValorUnitario[j] = dados[i].ValorUnitario;

					int funcionou = 0;
					do
					{
						printf("Digite a quantidade que voce desja comprar: ");
						scanf("%i", &compras[index].QntItem[j]);
						if (compras[index].QntItem[j] > dados[i].Estoque) {
							printf("O estoque do item pedido eh de apenas %i un.", dados[i].Estoque);
						}
						else
						{
							dados[i].Estoque -= compras[index].QntItem[j];
							break;
						}

					} while (funcionou == 0);


				}
			}





			printf("\n");

			j++;

		} while (codigoValido != 0);
		
	}

	

	return compras;
}

void encerrar(tipoDados* dados, tipoCompras* compras) {
	encerrarCompras(compras);
	encerrarDados(dados);
}

void encerrarDados(tipoDados* dados) {

}
void encerrarCompras(tipoDados* compras) {

}

int main(int argv, char** argc) {

	FILE* dadosArq = fopen("dados.txt", "r");
	FILE* comprasArq = fopen("compras.txt", "r");

	if (dadosArq == NULL || comprasArq == NULL)
	{
		return FILE_NOT_FOUND_ERROR;
	}

	tipoDados* dados = leArquivoDados(dadosArq);
	tipoCompras* compras = leArquivoCompras(comprasArq);

	fclose(dadosArq);
	fclose(comprasArq);


	//Onde vc vai colocar o switch, as funções abaixo são as que você chama no switch;
	//listaDados(dados);

	//dados = adicionaItem(dados);
	compras = realizaCompra(compras, dados);

	listaCompras(compras);

	encerrar(dados, compras);



	return SUCESSO;
}