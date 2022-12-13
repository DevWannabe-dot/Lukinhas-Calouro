#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define SUCESSO 0
#define TAM_MAX_DESC (1000 * sizeof(char))
#define TAM_MAX_COD (5 * sizeof(char))

typedef struct Dados{
	int Codigo;
	float ValorUnitario;
	int Estoque;
	char Descricao[TAM_MAX_DESC];

} tipoDados;

typedef struct Compras {
	char Codigo[TAM_MAX_COD];
	int NumItens;
	int* CodigoItens;
	float* ValorUnitario;
	int* QntItem;

} tipoCompras;

tipoDados* leArquivoDados(FILE* f);
tipoDados* realocarDados(tipoDados*);

tipoCompras* leArquivoCompras(FILE* f);
tipoCompras* realocarCompras(tipoCompras*);

int main(int argv, char** argc) {

	FILE* dados = fopen("dados.txt", "r");
	FILE* compras = fopen("compras.txt", "r");

	if (dados != NULL)
	{
		leArquivoDados(dados);
		

	}
	
	if (compras != NULL)
	{
		leArquivoCompras(compras);
		
	}




	fclose(dados);
	fclose(compras);
	return SUCESSO;
}

tipoDados* leArquivoDados(FILE* f) {
	tipoDados* dados;

	dados = (tipoDados*)malloc(sizeof(tipoDados));

	for (int i = 0; !feof(f); i++)
	{

		fscanf(f, "%i %f %i", &dados[i].Codigo, &dados[i].ValorUnitario, &dados[i].Estoque);

		
		fgets(dados[i].Descricao, TAM_MAX_DESC, f);

		if (!feof(f))
		{
			dados = realocarDados(dados, i + 1);
		}
		

	}

	
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

	free(dados);
	return dadosNovo;

}


tipoCompras* leArquivoCompras(FILE* f) {
	tipoCompras* compras;

	compras = (tipoCompras*)malloc(sizeof(tipoCompras));

	for (int i = 0; !feof(f); i++)
	{
		fgets(compras[i].Codigo, TAM_MAX_COD, f);

		fscanf(f, "%i", &compras[i].NumItens);

		compras[i].CodigoItens = (int*)malloc(sizeof(int) * compras[i].NumItens);
		compras[i].ValorUnitario = (float*)malloc(sizeof(float) * compras[i].NumItens);
		compras[i].QntItem = (int*)calloc(compras[i].NumItens, sizeof(int));

		for (int j = 0; j < compras[i].NumItens; j++)
		{
			fscanf(f, "%i ", &compras[i].CodigoItens[j]);
			fscanf(f, "%f ", &compras[i].ValorUnitario[j]);
			fscanf(f, "%i ", &compras[i].QntItem[j]);
		
		}
		

		if (!feof(f))
		{
			compras = realocarCompras(compras, i + 1);
		}


	}


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

	free(compras);
	return comprasNovo;
}
