#pragma once
#ifndef __DADOS_h__
#define __DADOS_h__

// Inclusoes

// Constantes
#define TAM_MAX_DESC (1000 * sizeof(char))

// Tipos
typedef struct Dados {
	int Codigo;
	float ValorUnitario;
	int Estoque;
	char Descricao[TAM_MAX_DESC];

	int NumDados;
} tipoDados;

// Funcoes exportadas
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
	dados[index].Estoque = qnt;

	return dados;
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

void encerrarDados(tipoDados* dados) {

}

#endif