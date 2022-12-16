#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "compras.h"

#define SUCESSO 0
#define FILE_NOT_FOUND_ERROR -1

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