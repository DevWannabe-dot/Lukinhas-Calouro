#pragma once
#ifndef __COMPRAS_h__
#define __COMPRAS_h__

// Inclusoes
#include "dados.h"

// Constantes
#define TAM_MAX_COD (5 * sizeof(char))

// Tipos
typedef struct Compras {
	char Codigo[TAM_MAX_COD];
	int NumItens;
	int* CodigoItens;
	float* ValorUnitario;
	int* QntItem;

	int NumCompras;
} tipoCompras;

// Funcoes exportadas
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

void encerrarCompras(tipoDados* compras) {

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

tipoCompras* realizaCompra(tipoCompras* compras, tipoDados* dados) {

	compras = realocarCompras(compras, compras->NumCompras);

	int index = compras->NumCompras - 1;

	char c[5];
	if (index < 10)
	{
		sprintf(c, "c00%i", index);
	}
	else if (index < 100)
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


#endif
