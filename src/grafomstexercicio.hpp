#include <iostream>
#include <vector>
#include <queue>
#include "stdbool.h"

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

    // Grupo do union-find
    class Grupo
    {
    public:
        int pai;
        int tamanho;
    };

    // encontrar raiz
    // pode ser com ou sem path compression
    int encontrarRaiz(Grupo *grupos, int i)
    {
        while (grupos[i].pai != i)
        {
            grupos[i].pai = grupos[grupos[i].pai].pai;
            i = grupos[i].pai;
        }
        return i;
    }

    bool mesmoGrupo(Grupo *grupos, int a, int b)
    {
        int raizA = encontrarRaiz(grupos, a);
        int raizB = encontrarRaiz(grupos, b);
        return raizA == raizB;
    }

    int tamanhoGrupo(Grupo *grupos, int a)
    {
        // IMPLEMENTAR
        int raizA = encontrarRaiz(grupos, a);
        return grupos[raizA].tamanho;
    }

    void unirGrupos(Grupo *grupos, int a, int b)
    {
        // IMPLEMENTAR
        int raizA = encontrarRaiz(grupos, a);
        int raizB = encontrarRaiz(grupos, b);

        if (raizA == raizB)
            return;

        grupos[raizB].pai = grupos[raizA].pai;
        grupos[raizA].tamanho = grupos[raizA].tamanho + grupos[raizB].tamanho;
    }

    // criei essa classe pra facilitar a ordenacao
    // das arestas com menor peso (que faz parte do
    // algoritmo de Kruskal)
    class Aresta
    {
    public:
        int origem;
        int destino;
        int peso;
        Aresta(int origem, int destino, int peso)
            : origem(origem), destino(destino), peso(peso)
        {
        }
    };

    // sobrescrever operator< para que a priority_queue
    // ordene como desejamos
    friend bool operator<(const Aresta &a1, const Aresta &a2)
    {
        // IMPLEMENTAR
        return a1.peso > a2.peso;
    }

    GrafoListaAdj *KruskalMST()
    {
        // IMPLEMENTAR

        // instanciamos um novo grafo, que armazenara
        // apenas as arestas da MST
        GrafoListaAdj *mst = new GrafoListaAdj();

        // adicionar vertices
        for (auto v : vertices)
        {
            mst->inserirVertice(v);
        }
        // inicializar estrutura do union-find (array de grupos)
        Grupo *grupos = new Grupo[vertices.size()];
        for (int i = 0; i < vertices.size(); i++)
        {
            grupos[i].pai = i;
            grupos[i].tamanho = 1;
        }

        // inicializar priority_queue
        priority_queue<Aresta> arestasMenorPeso;
        // adicionar arestas na fila
        for (int i = 0; i < arestas.size(); i++)
        {
            for (auto a : arestas[i])
            {
                Aresta *temp = new Aresta(i, a.first, a.second);
                arestasMenorPeso.push(*temp);
            }
        }

        // iterar na fila de arestas
        // se os vertices da arestas nao pertencem ao mesmo grupo
        // una-os, e adicione a aresta no MST
        while (!arestasMenorPeso.empty())
        {
            Aresta a = arestasMenorPeso.top();

            arestasMenorPeso.pop();
            if (!mesmoGrupo(grupos, a.origem, a.destino))
            {

                unirGrupos(grupos, a.origem, a.destino);
                mst->inserirArestaNaoDirecionada(vertices[a.origem], vertices[a.destino], a.peso);
            }
        }

        return mst;
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