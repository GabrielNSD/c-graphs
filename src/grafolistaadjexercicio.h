#include <iostream>
#include <vector>
#include <limits.h>

#include <bits/stdc++.h>
using namespace std;

class GrafoListaAdj
{
private:
    vector<string> vertices;

    // first é o indice do vertice, second é o peso (caso o grafo seja ponderado)
    vector<vector<pair<int, int>>> arestas;

    /**
     * A principio nao temos nenhuma ordenacao usando os rotulos.
     * Portanto, usaremos busca linear.
     **/
    int obterIndiceVertice(string rotuloVertice)
    {
        int index = -1;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (rotuloVertice == vertices[i])
            {
                index = i;
            }
        }
        return index;
    }

public:
    /**
     * Lembrem-se:
     *       1) nao podemos inserir vertices com mesmo rotulo
     *       2) toda vez que inserirmos um novo vértice, precisaremos
     *          inserir um vetor para representar as conexões daquele
     *          vértice na lista de adjacências
     **/
    void inserirVertice(string rotuloVertice)
    {
        int index = obterIndiceVertice(rotuloVertice);
        if (index < 0)
        {
            vertices.push_back(rotuloVertice);
            vector<pair<int, int>> tempVector;
            arestas.push_back(tempVector);
        }
    }

    /**
     * Sempre que o grafo for não ponderado, adicionaremos o peso 1,
     * por conveniência.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
    }

    void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
        inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
    }

    /**
     * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
     * especificado.
     **/
    void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso)
    {
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        int indiceDestino = obterIndiceVertice(rotuloVDestino);

        if (indiceOrigem < 0 || indiceDestino < 0)
        {
            return;
        }
        pair<int, int> tempPair; //(indiceDestino, peso);
        tempPair.first = indiceDestino;
        tempPair.second = peso;
        arestas[indiceOrigem].push_back(tempPair);
    }

    /**
     * Verifica se vértice rotuloVOrigem e vértice rotuloVDestino são
     * conectados (vizinhos).
     **/
    bool saoConectados(string rotuloVOrigem, string rotuloVDestino)
    {
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        int indiceDestino = obterIndiceVertice(rotuloVDestino);

        bool resultado = false;

        if (indiceOrigem < 0 || indiceDestino < 0)
        {
            return false;
        }

        for (int j = 0; j < arestas[indiceOrigem].size(); j++)
        {
            if (arestas[indiceOrigem][j].first == indiceDestino)
            {
                resultado = true;
            }
        }

        return resultado;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    vector<vector<pair<int, int>>> getArestas()
    {
        return arestas;
    }
};