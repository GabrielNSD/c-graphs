#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
using namespace std;

class GrafoListaAdj
{
private:
    vector<string> vertices;

    // first � o indice do vertice, second � o peso (caso o grafo seja ponderado)
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

    /**
     * O argumento indicesVerticesVisitados serve para controlar quais
     * vertices já foram visitados.
     * Lembrando que DFS é uma função recursiva.
     **/
    void dfs(string rotuloVOrigem, bool *indicesVerticesVisitados)
    {
        int index = obterIndiceVertice(rotuloVOrigem);
        if (indicesVerticesVisitados[index])
        {
            return;
        }
        else
        {
            indicesVerticesVisitados[index] = true;
            for (int i = 0; i < arestas[index].size(); i++)
            {
                string newOrigin = vertices[arestas[index][i].first];
                // cout << newOrigin << endl;
                dfs(newOrigin, indicesVerticesVisitados);
            }
        }
    }

public:
    /**
     * Lembrem-se:
     *       1) nao podemos inserir vertices com mesmo rotulo
     *       2) toda vez que inserirmos um novo v�rtice, precisaremos
     *          inserir um vetor para representar as conex�es daquele
     *          v�rtice na lista de adjac�ncias
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
     * Sempre que o grafo for n�o ponderado, adicionaremos o peso 1,
     * por conveni�ncia.
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
     * Verifica se v�rtice rotuloVOrigem e v�rtice rotuloVDestino s�o
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

    /**
     * Verifica se há algum caminho entre vértice rotuloVOrigem e
     * vértice rotuloVDestino.
     * A melhor forma de fazer isto é reusando a função dfs.
     **/
    bool haCaminho(string rotuloVOrigem, string rotuloVDestino)
    {

        int indexOrigem = obterIndiceVertice(rotuloVOrigem);
        int indexDestino = obterIndiceVertice(rotuloVDestino);
        bool *indicesVerticesVisitados = new bool[vertices.size()]{false};
        if (indexOrigem == 0 && indexDestino == 0)
        {
            return false;
        }
        dfs(rotuloVOrigem, indicesVerticesVisitados);
        if (indicesVerticesVisitados[indexOrigem] && indicesVerticesVisitados[indexDestino])
        {
            delete[] indicesVerticesVisitados;
            return true;
        }
        else
        {
            delete[] indicesVerticesVisitados;
            return false;
        }
    }

    /**
     * Muda os r�tulos do v�rtices dos diferentes componentes para
     * nomes que representam cores.
     * Dica: procura componentes partindo do v�rtice v0 ou v1, em ordem
     * crescente (mas voc� pode usar outra ordem se desejar).
     * Retorna a quantidade de componentes.
     * A melhor forma de fazer isto � reusando a fun��o dfs.
     **/
    int colorir()
    {
        int size = vertices.size();
        if (size == 0)
        {
            return 0;
        }
        else
        {
            bool *visitados = new bool[size]{0};
            int count = 0;

            for (int i = 0; i < size; i++)
            {
                string origem = vertices[i];
                bool change = false;
                bool *tempVisitados = new bool[size]{0};
                copy(visitados, visitados + size, tempVisitados);

                if (visitados[i] == false)
                {
                    count++;
                    change = true;
                    dfs(origem, visitados);
                }

                if (change)
                {
                    for (int j = i; j < size; j++)
                    {
                        if (visitados[j] != tempVisitados[j])
                        {
                            vertices[j] = origem;
                        }
                    }
                }
            }

            delete[] visitados;
            return count;
        }
    }

    /**
     * Usa a abordagem de navega��o BFS para listar as dist�ncias
     * entre o v�rtice rotuloVOrigem e cada um dos demais v�rtices.
     * A fun��o BFS consegue listar a menor dist�ncia entre um v�rtice
     * e os demais se o grafo for N�O-PONDERADO.
     * Retorna um vetor de inteiros com a quantidade de arestas
     * (dist�ncia) e o v�rtice rotuloVOrigem e cada um dos demais v�rtices.
     * N�o � uma fun��o recursiva.
     * � necess�rio utilizar a ED fila.
     **/
    int *bfs(string rotuloVOrigem)
    {
        queue<int> filaDeVertices;
        int *distancias = new int[vertices.size()]{0};
        bool *visitados = new bool[vertices.size()]{0};
        int indiceOrigem = obterIndiceVertice(rotuloVOrigem);
        filaDeVertices.push(indiceOrigem);
        visitados[indiceOrigem] = true;
        distancias[indiceOrigem];

        while (!filaDeVertices.empty())
        {
            int s = filaDeVertices.front();
            filaDeVertices.pop();

            for (auto u : arestas[s])
            {
                if (!visitados[u.first])
                {
                    visitados[u.first] = true;
                    int distancia = distancias[s] + u.second;
                    distancias[u.first] = distancias[s] + u.second;
                    filaDeVertices.push(u.first);
                }
            }
        }

        delete[] visitados;
        return distancias;
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