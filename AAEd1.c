/*
THALIA FERREIRA PINTO
UNIVERSIDADE FEDERAL RURAL DO RIO DE JANEIRO
ATIVIDADE ACADÊMICA DE ESTRUTURA DE DADOS 1 - 2017.2
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct arv Arvore;
typedef struct l Lista;

struct arv
{
	int valor;
	void *esquerda;
	void *direita;
	char site[256];
};

struct l
{
	int indice;
	Lista* prox;
	Arvore* arvore;
	
};

Lista* cria_lista()
{
	return NULL;
}

Arvore* cria_arvore()
{
	return NULL;
}

int lista_vazia(Lista **lista)
{
	return lista == NULL;
}

int arvore_vazia(Arvore* arvore)
{
	return arvore == NULL;
}

Arvore* insere_elemento(Arvore *arvore, int valor, char site[])
{
	if(arvore == NULL)
	{
		arvore = (Arvore*)malloc(sizeof(Arvore));
		arvore->esquerda = NULL;
		arvore->direita = NULL;
		arvore->valor = valor;
		strcpy(arvore->site, site);
		return arvore;
	}
	
	if(valor <= arvore->valor)
		arvore->esquerda = insere_elemento(arvore->esquerda, valor, site);
	else
		arvore->direita = insere_elemento(arvore->direita, valor, site);

	return arvore;
}

void insere_lista(Lista **lista, Arvore **arvore, int indice)
{
	if(*lista == NULL)
	{
		*lista = (Lista*) malloc(sizeof(Lista));
		(*lista)->prox = NULL;
		(*lista)->indice = indice;
		(*lista)->arvore = *arvore;
	}

	else
	{
		insere_lista(&(*lista)->prox, arvore, indice+1);
	}
}

Lista* busca_lista(Lista **lista, int indice)
{
	if(lista_vazia(lista))
		return NULL;

	Lista* ptr;

	for(ptr = (*lista); ptr != NULL; ptr = ptr->prox)
	{
		if(ptr->indice == indice)
		{
			return ptr;
		}
	}

	return NULL;

}

void destroi_conjunto(Lista **lista, int indice)
{
	Lista* anterior = NULL;
	Lista* ptr = (*lista);

	while(ptr != NULL && ptr->indice != indice)
	{
		anterior = ptr;
		ptr = ptr->prox;
	}

	if(anterior == NULL)
		(*lista) = ptr->prox;

	else
		anterior->prox = ptr->prox;

	free(ptr->arvore);
	free(ptr);
}

Arvore* busca_arvore(Lista** lista, int indice)
{
	Lista* ptr;

	for(ptr = (*lista); ptr != NULL; ptr = ptr->prox)
	{
		if(ptr->indice == indice)
		{
			return ptr->arvore;
		}
	}

	return NULL;

}


void busca_elemento(Arvore* arvore, int elemento)
{

	if(arvore == NULL)
	{
		printf("Árvore vazia.\n");
		return;
	}

	if(arvore->valor == elemento)
	{
		printf("\nÍndice: %d\n", arvore->valor);
		printf("Site: %s\n\n", arvore->site);
	}

	else if (elemento < arvore->valor)
		busca_elemento(arvore->esquerda, elemento);
	else
		busca_elemento(arvore->direita, elemento);

}

int busca(Arvore* arvore, int elemento)
{
	if(arvore == NULL)
		return 0;
	if(arvore->valor == elemento || busca(arvore->esquerda, elemento) || busca(arvore->direita, elemento))
		return 1;
}

Arvore* uniao_arvores(Arvore* ab, Arvore* c)
{
	if(ab != NULL)
	{
		if(c == NULL)
			c = insere_elemento(c, ab->valor, ab->site);

		else if(!busca(c, ab->valor))
			c = insere_elemento(c, ab->valor, ab->site);

		if(ab->esquerda != NULL)
			uniao_arvores(ab->esquerda, c);
		if(ab->direita != NULL)
			uniao_arvores(ab->direita, c);
		return c;
	}

	else
		return c;
}

Arvore* interseccao_arvores(Arvore* a, Arvore* b, Arvore* c)
{

	if(a != NULL)
	{
		if(busca(b, a->valor))
			c = insere_elemento(c, a->valor, a->site);

		if(a->esquerda != NULL)
			c = interseccao_arvores(a->esquerda, b, c);

		if(a->direita != NULL)
			c = interseccao_arvores(a->direita, b, c);
		return c;
	}

	else
		return c;
}

void imprime_arvores(Arvore* arvore)
{
	if(!arvore_vazia(arvore))
	{
		printf("%d\n", arvore->valor);
		imprime_arvores(arvore->esquerda);
		imprime_arvores(arvore->direita);
	}
}

void imprime_lista(Lista* lista)
{
	Lista* ptr;

	for(ptr = lista; ptr != NULL; ptr = ptr->prox)
	{
		printf("\nÁrvore de índice %d:\n", ptr->indice);
		imprime_arvores(ptr->arvore);
	}

	return;
}

void imprime_indices(Lista* lista)
{
	Lista* ptr;

	for(ptr = lista; ptr != NULL; ptr = ptr->prox)
	{
		printf("\nÁrvore de índice %d\n", ptr->indice);
	}

	return;
}

int altura_arvore(Arvore* arvore)
{
	int altura_dir = 0;
	int altura_esq = 0;

	if(arvore->esquerda)
		altura_esq = altura_arvore(arvore->esquerda);

	else if(arvore->direita)
		altura_dir = altura_arvore(arvore->direita);

	if(altura_dir > altura_esq)
		return ++altura_dir;

	return ++altura_esq;
}

int fator_balanceamento(Arvore* arvore)
{
	int fator_esq = 0;
	int fator_dir = 0;

	if(arvore->esquerda)
		fator_esq += altura_arvore(arvore->esquerda);

	if(arvore->direita)
		fator_dir += altura_arvore(arvore->direita);

	return fator_esq-fator_dir;
}



int main(void)
{
	Lista* lista = cria_lista();

	int ligado = 1;
	int indice = 1;
	char site[256];
	char escolha;

	while(ligado)
	{
		printf("\nMENU\n\n");
		printf("1- Criar conjunto.\n");
		printf("2- Destruir conjunto.\n");
		printf("3- Pesquisar elemento no conjunto.\n");
		printf("4- União de dois conjuntos.\n");
		printf("5- Intersecção de dois conjuntos.\n");
		printf("6- Exibir árvores.\n");
		printf("7- Exibir todos os elementos de um conjunto em ordem.\n");
		printf("8- Exibir altura da árvore.\n");
		printf("F- Fim do programa.\n\n");

		scanf(" %c", &escolha);

		while(escolha == '1')
		{
			char resposta;
			Arvore* arvore = cria_arvore();

			printf("Deseja inserir elemento? (s/n)\n");
			scanf(" %c", &resposta);

			while(resposta == 's')
			{
				int i;

				printf("Digite o indice a inserir\n");
				scanf(" %d", &i);
				printf("Digite o site a inserir\n");
				scanf(" %s", site);

				arvore = insere_elemento(arvore, i, site);

				printf("Deseja continuar inserindo elementos? (s/n)\n");
				scanf(" %c", &resposta);
			}

			insere_lista(&lista, &arvore, indice);

			printf("Deseja criar outro conjunto? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '1';
			else
				escolha = '0';

		}

		while(escolha == '2')
		{
			int ind = 0;
			char resposta;

			printf("Digite o indice do conjunto a ser destruído\n");
			scanf(" %d", &ind);

			if(busca_lista(&lista, ind) == NULL)
			{
				printf("\nCONJUNTO NAO EXISTE\n\n");

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();

				escolha = '2';
			}
			else
			{
				destroi_conjunto(&lista, ind);
				printf("\nConjunto destruído\n\n");
			}

			printf("Deseja destruir outro conjunto? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '2';
			else
				escolha = '0';
			
		}

		while(escolha == '3')
		{
			int ind = 0, elemento = 0;
			char resposta;
			Arvore* arv;

			printf("Digite o indice do conjunto\n");
			scanf(" %d", &ind);

			if(busca_lista(&lista, ind) == NULL)
			{
				printf("\nERRO. Indice inválido.\n\n");

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();

				escolha = '3';
			}

			else
			{
				printf("Digite o indice do elemento a ser procurado no conjunto\n");
				scanf(" %d", &elemento);

				arv = busca_arvore(&lista, ind);
				busca_elemento(arv, elemento);

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();

			}
			
			printf("Deseja procurar outro elemento? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '3';
			else
				escolha = '0';
		}

		while(escolha == '4')
		{
			int ind1 = 0, ind2 = 0, elemento = 0;
			char resposta;
			Arvore* arv1 = cria_arvore();
			Arvore* arv2 = cria_arvore();
			Arvore* arv3 = cria_arvore();


			printf("Digite o indice do conjunto A\n");
			scanf(" %d", &ind1);

			if(busca_lista(&lista, ind1) == NULL)
			{
				printf("\nERRO. Indice do conjunto A é inválido.\n\n");

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();
			}

			else
			{
				printf("Digite o indice do conjunto B\n");
				scanf(" %d", &ind2);

				if(busca_lista(&lista, ind2) == NULL)
				{
					printf("\nERRO. Indice do conjunto B é inválido.\n\n");
					
					printf("Pressione ENTER para continuar\n");
					getchar();
					getchar();
				}

				else
				{
					arv1 = busca_arvore(&lista, ind1);
					arv2 = busca_arvore(&lista, ind2);

					arv3 = uniao_arvores(arv1, arv3);
					arv3 = uniao_arvores(arv2, arv3);

					insere_lista(&lista, &arv3, indice);

				}
			}

			printf("Deseja unir outros conjuntos? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '4';
			else
				escolha = '0';
			
		}

		while(escolha == '5')
		{
			int ind1 = 0, ind2 = 0, elemento = 0;
			char resposta;
			Arvore* arv1 = cria_arvore();
			Arvore* arv2 = cria_arvore();
			Arvore* arv3 = cria_arvore();


			printf("Digite o indice do conjunto A\n");
			scanf(" %d", &ind1);

			if(busca_lista(&lista, ind1) == NULL)
			{
				printf("\nERRO. Indice do conjunto A é inválido.\n\n");

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();
			}

			else
			{
				printf("Digite o indice do conjunto B\n");
				scanf(" %d", &ind2);

				if(busca_lista(&lista, ind2) == NULL)
				{
					printf("\nERRO. Indice do conjunto B é inválido.\n\n");
					
					printf("Pressione ENTER para continuar\n");
					getchar();
					getchar();
				}

				else
				{
					arv1 = busca_arvore(&lista, ind1);
					arv2 = busca_arvore(&lista, ind2);

					arv3 = interseccao_arvores(arv1, arv2, arv3);

					insere_lista(&lista, &arv3, indice);

				}
			}

			printf("Deseja realizar intersecção de outros conjuntos? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '5';
			else
				escolha = '0';
			
		}



		while(escolha == '6')
		{
			char resposta;

			imprime_indices(lista);

			printf("\nPressione ENTER para retornar ao menu\n");
			getchar();
			getchar();

			escolha = '0';
		}

		while(escolha == '7')
		{
			char resposta;

			imprime_lista(lista);

			printf("Pressione ENTER para retornar ao menu\n");
			getchar();
			getchar();

			escolha = '0';
		}

		while(escolha == '8')
		{
			Arvore* arvore = cria_arvore();
			int ind = 0, altura = 0, fb = 0;
			char resposta;

			printf("Digite o índice do conjunto\n");
			scanf(" %d", &ind);

			if(busca_lista(&lista, ind) == NULL)
			{
				printf("\nCONJUNTO NAO EXISTE\n\n");

				printf("Pressione ENTER para continuar\n");
				getchar();
				getchar();
			}

			else
			{
				arvore = busca_arvore(&lista, ind);

				altura = altura_arvore(arvore);

				printf("Altura da árvore: %d\n", altura);

				fb = fator_balanceamento(arvore);

				if(fb < -1 || fb > 1)
					printf("A árvore está desbalanceada.\n");
				else
					printf("A árvore está balanceada.\n");
			}

			printf("Deseja pesquisar altura de outro conjunto? (s/n)\n");
			scanf(" %c", &resposta);

			if(resposta == 's')
				escolha = '8';
			else
				escolha = '0';


			
		}

		if(escolha == 'f' || escolha == 'F')
		{
			printf("Programa finalizado.\n");
			ligado = 0;
		}


	}

	free(lista);
	return 0;
}