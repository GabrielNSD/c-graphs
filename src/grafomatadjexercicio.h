#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

struct GrafoMatrizAdj
{
    int **arestas;
    char **rotuloVertices;
    int verticesInseridos;
    int maxNumVertices;
    // faz mais sentido ser apenas numVertices (consertar para a prox turma)
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj *inicializar(int numVertices, bool ponderado)
{
    int valorAresta;
    if (ponderado)
    {
        valorAresta = INT_MAX;
    }
    else
    {
        valorAresta = 0;
    }

    GrafoMatrizAdj *novoGrafo = (GrafoMatrizAdj *)malloc(sizeof(GrafoMatrizAdj));
    novoGrafo->arestas = (int **)malloc(sizeof(int *) * numVertices);
    for (int i = 0; i < numVertices; i++)
    {
        novoGrafo->arestas[i] = (int *)(calloc(numVertices, sizeof(int)));
    }
    novoGrafo->rotuloVertices = (char **)malloc(sizeof(char **) * numVertices);
    novoGrafo->verticesInseridos = 0;
    novoGrafo->maxNumVertices = numVertices;

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            novoGrafo->arestas[i][j] = valorAresta;
        }
    }

    return novoGrafo;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{
    int index = -1;
    for (int i = 0; i < grafo->maxNumVertices; i++)
    {
        // printf("i: %c \n", grafo->rotuloVertices[i]);
        if (grafo->rotuloVertices[i] != NULL)
        {
            if (strcmp(grafo->rotuloVertices[i], rotuloVertice) == 0)
            {
                index = i;
            }
        }
    }
    return index;
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da aresta.
 * Se o grafo for não ponderado, passaremos o valor 1 para a variavel peso, de modo que represente existência da aresta.
 * Se um dos rotulos dos vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino, int peso)
{
    int indiceOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
    int indiceDestino = obterIndiceVertice(grafo, rotuloVDestino);

    if (indiceOrigem < 0 || indiceDestino < 0)
    {
        return;
    }

    grafo->arestas[indiceOrigem][indiceDestino] = peso;
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de vertices que ja foi inserido no grafo.
 * Logo, ela pode/deve ser usada para especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj *grafo, char *rotuloVertice)
{

    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
    grafo->verticesInseridos++;
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois vertices em um grafo ponderado,
 * e haver conexão entre dois vertices em um grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj *grafo, char *rotuloVOrigem, char *rotuloVDestino)
{
    int indiceOrigem = obterIndiceVertice(grafo, rotuloVOrigem);
    int indiceDestino = obterIndiceVertice(grafo, rotuloVDestino);

    if (indiceOrigem < 0 || indiceDestino < 0)
    {
        return false;
    }

    if (grafo->arestas[indiceOrigem][indiceDestino] > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}