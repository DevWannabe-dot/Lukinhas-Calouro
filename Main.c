#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define SUCESSO 0
#define TAM_MAX_DESC (1000 * sizeof(char))

typedef struct Dados{
	int Codigo;
	float ValorUnitario;
	int Estoque;
	char Descricao[TAM_MAX_DESC];

} tipoDados;

tipoDados* leArquivoDados(FILE* f);
tipoDados* realocarDados(tipoDados*);

int main(int argv, char** argc) {

	FILE* dados = fopen("dados.txt", "r");
	//FILE* compras = fopen("compras.txt", "r");

	if (dados != NULL)
	{
		leArquivoDados(dados);
		fclose(dados);

	}


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